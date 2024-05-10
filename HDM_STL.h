#ifndef HDM_STL_H
#define HDM_STL_H
#include <map>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "dm_array.h"
#include "HDM.h"
high_precision sta_n;
bool input_file=0,output_file=0,do_output=1;
std::fstream input_value,output_value;
std::map<std::string,std::string> _file_help;
std::map<FF_pair<std::string,std::string>,std::string> _function_help;
void add_change(char inp_char,high_precision& inp_n){
    if(inp_char==function_left_bracket||inp_char==multi_parameter_left_breacket) inp_n++;
    else if(inp_char==function_right_bracket||inp_char==multi_parameter_left_breacket) inp_n--;
}
high_precision_fraction sum_h(MFE* val,std::string input,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    std::string value_name,start_from,go_to,expression;
    size_t last,pos=0,end;
    high_precision_fraction start_v,end_v,answer=(high_precision_fraction)0;
    input=no_white(input);
    end=input.size();
    sta_n=0;
    while((sta_n||input[pos]!=function_input_separator)&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Sum with no ','.\n";
        return (high_precision_fraction)0;
    }
    start_from=input.substr(0,pos);
    last=++pos;
    sta_n=0;
    while((sta_n||input[pos]!=function_input_separator)&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Sum with no ','.\n";
        return (high_precision_fraction)0;
    }
    go_to=input.substr(last,pos-last);
    expression=input.substr(pos+1);
    pos=0;
    end=start_from.size();
    sta_n=0;
    while((sta_n||start_from[pos]!='=')&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Sum with no '='. \n";
        return (high_precision_fraction)0;
    }
    value_name=start_from.substr(0,pos);
    start_v=val->calculate(start_from.substr(pos+1),given_input).second;
    end_v=val->calculate(go_to,given_input).second;
    end=given_input.size();
    given_input[end]=FF_pair<std::string,high_precision_fraction>(value_name,start_v);
    for(high_precision_fraction count_value=start_v;count_value<=end_v;count_value+=(high_precision_fraction)1){
        given_input[end].second=count_value;
        answer+=val->calculate(expression,given_input).second;
    }
    return answer;
}
high_precision_fraction prod_h(MFE* val,std::string input,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    std::string value_name,start_from,go_to,expression;
    size_t last,pos=0,end;
    high_precision_fraction start_v,end_v,answer=(high_precision_fraction)1;
    input=no_white(input);
    end=input.size();
    sta_n=0;
    while((sta_n||input[pos]!=function_input_separator)&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Prod with no ','.\n";
        return (high_precision_fraction)0;
    }
    start_from=input.substr(0,pos);
    last=++pos;
    sta_n=0;
    while((sta_n||input[pos]!=function_input_separator)&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Prod with no ','.\n";
        return (high_precision_fraction)0;
    }
    go_to=input.substr(last,pos-last);
    expression=input.substr(pos+1);
    pos=0;
    end=start_from.size();
    while((sta_n||start_from[pos]!='=')&&pos<end){
        add_change(input[pos],sta_n);
        pos++;
    }
    if(pos==end){
        std::cerr<<"Prod with no '='. \n";
        return (high_precision_fraction)0;
    }
    value_name=start_from.substr(0,pos);
    start_v=val->calculate(start_from.substr(pos+1),given_input).second;
    end_v=val->calculate(go_to,given_input).second;
    end=given_input.size();
    given_input[end]=FF_pair<std::string,high_precision_fraction>(value_name,start_v);
    for(high_precision_fraction count_value=start_v;count_value<=end_v;count_value+=(high_precision_fraction)1){
        given_input[end].second=count_value;
        answer*=val->calculate(expression,given_input).second;
    }
    return answer;
}
high_precision_fraction floor_h(MFE* from,dynamic_array<high_precision_fraction> input_value){return input_value[0].show_up()/input_value[0].show_down();}
high_precision_fraction ceil_h(MFE* from,dynamic_array<high_precision_fraction> input_value){return input_value[0].show_up()/input_value[0].show_down()+(high_precision)((input_value[0].show_up()%input_value[0].show_down())>0);}
void add_in_math_h(MFE& to){
    to.insert("sum(start_from,go_to,expression)",sum_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("prod(start_from,go_to,expression)",prod_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("floor(input_value)",floor_h,NUMBER_STYLE,DO_SAVE);
    to.insert("ceil(input_value)",ceil_h,NUMBER_STYLE,DO_SAVE);
}
high_precision_fraction high_precision_fraction_do_reduction(MFE* from,dynamic_array<high_precision_fraction> input){
    do_reduction=(input[0]!=(high_precision_fraction)0);
    return high_precision(0);
}
high_precision_fraction high_precision_fraction_output_style(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    if(inp=="fraction") output_style=FRACTION_STYLE;
    else if(inp=="decimal") output_style=DECIMAL_STYLE;
    else std::cerr<<"Wrong input, input can only be fraction or decimal!\n";
    return (high_precision)0;
}
high_precision_fraction high_precision_fraction_save_decimal_point(MFE* from,dynamic_array<high_precision_fraction> input){
    save_decimal_point=input[0].show_up()/input[0].show_down();
    return (high_precision)0;
}
high_precision_fraction high_precision_fraction_expression_output(MFE* from,dynamic_array<high_precision_fraction> input){
    expression_output=input[0]!=(high_precision_fraction)0;
    return (high_precision)0;
}
high_precision_fraction system_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    system(get_normal(inp).c_str());
    return (high_precision)0;
}
high_precision_fraction do_output_h(MFE* from,dynamic_array<high_precision_fraction> input_value){
    do_output=input_value[0]!=(high_precision_fraction)0;
    return (high_precision)0;
}
void add_in_system_h(MFE& to){
    to.insert("do_reduction(change_value)",high_precision_fraction_do_reduction,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("output_style(change_value)",high_precision_fraction_output_style,STRING_STYLE,DO_NOT_SAVE);
    to.insert("save_decimal_point(change_value)",high_precision_fraction_save_decimal_point,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("expression_output(change_value)",high_precision_fraction_expression_output,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("system(do_string)",system_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("do_output(change_value)",do_output_h,NUMBER_STYLE,DO_NOT_SAVE);
}
high_precision_fraction printn_h(MFE* from,dynamic_array<high_precision_fraction> input){
    if(output_file) output_value<<input[0];
    if(do_output) std::cout<<input[0];
    return input[0];
}
high_precision_fraction prints_h(MFE* from,std::string input_value,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    if(output_file) output_value<<get_normal(no_white(input_value));
    if(do_output)std::cout<<get_normal(no_white(input_value));
    return (high_precision)0;
}
high_precision_fraction printw_h(MFE* from,std::string input_value,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    if(output_file) output_value<<' ';
    if(do_output)std::cout<<' ';
    return (high_precision)0;
}
high_precision_fraction printl_h(MFE* from,std::string input_value,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    if(output_file) output_value<<std::endl;
    if(do_output)std::cout<<std::endl;
    return (high_precision)0;
}
high_precision_fraction printv_h(MFE* from,std::string input_value,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    high_precision_fraction answer,every_answer;
    size_t next=1,end=input_value.size()-1;
    std::string put_string;
    bool is_string=1;
    if(input_value[0]!=multi_parameter_left_breacket&&input_value[0]!=function_left_bracket){if(output_file) output_value<<get_normal(input_value);if(do_output)std::cout<<get_normal(input_value);}
    else{
        while(next<end){
            sta_n=0;
            put_string="";
            while(next<end&&(input_value[next]!=function_input_separator||sta_n)){
                add_change(input_value[next],sta_n);
                if(input_value[next]=='\\'){put_string+=hash_s[input_value[++next]];}
                else put_string+=input_value[next];
                next++;
            }
            if(is_string){if(output_file) output_value<<put_string;if(do_output)std::cout<<put_string;}
            else{if(output_file) output_value<<(every_answer=from->calculate(put_string,given_input).second);if(do_output) std::cout<<(every_answer=from->calculate(put_string,given_input).second);answer+=every_answer;}
            is_string=!is_string;
            next++;
        }
    }
    return answer;
}
high_precision_fraction getchar_h(MFE* from,dynamic_array<high_precision_fraction> input){char val; if(input_file) input_value>>val;else val=getchar();return (high_precision)val;}
high_precision_fraction putchar_h(MFE* from,dynamic_array<high_precision_fraction> input){
    char val=int((input[0].show_up()/input[0].show_down())%255);if(output_file) output_value<<val;if(do_output) std::cout<<val;return input[0];}
high_precision_fraction to_int_h(MFE* from,std::string input_value,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){return (high_precision)(int)(input_value[0]=='\\'?hash_s[input_value[1]][0]:input_value[0]);}
void add_in_print_h(MFE& to){
    to.insert("printn(output_value)",printn_h,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("prints(output_value)",prints_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("printw()",printw_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("printl()",printl_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("printv(answer)",printv_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("getchar()",getchar_h,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("putchar(input_value)",putchar_h,NUMBER_STYLE,DO_NOT_SAVE);
    to.insert("to_int(char_value)",to_int_h,STRING_STYLE,DO_NOT_SAVE);
}
high_precision_fraction equal_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    size_t pos;
    std::string var_name=inp.substr(0,pos=inp.find(function_input_separator));
    FF_pair<std::string,high_precision_fraction>* change=NULL;
    for(FF_pair<std::string,high_precision_fraction> *cnt_value=from->static_given_input.begin(),*end=from->static_given_input.end();cnt_value<end;cnt_value++)
        if(cnt_value->first==var_name)
            change=cnt_value;
    if(!change){
        from->static_given_input.push(FF_pair<std::string,high_precision_fraction>(var_name,(high_precision_fraction)0));
        change=from->static_given_input.end()-1;
    }
    return change->second=from->calculate(inp.substr(pos+1),given_input).second;
}//need to save size and judge, add{} to functions
high_precision_fraction make_array_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    auto floor=[](const high_precision_fraction& value)->high_precision{return value.show_up()/value.show_down();};
    dynamic_array<size_t> value;
    size_t pos=inp.find(function_input_separator),evepos,evelast,end=inp.size();
    std::string name;
    bool with_b;
    evepos=evelast=pos+(with_b=(bool)(inp[pos+1]==function_left_bracket))+1;
    name=inp.substr(0,pos);
    while(evelast<end){
        sta_n=0;
        while(evepos<end&&(inp[evepos]!=function_input_separator||sta_n)){
            add_change(inp[evepos],sta_n);
            evepos++;
        }
        value.push(floor(from->calculate(inp.substr(evelast,evepos>=end?end-evelast-with_b:evepos-evelast),given_input).second));
        if(evepos>end) break;
        evelast=++evepos;
    }
    return (high_precision)(from->name_to_number[name]=from->array_value.insert(value.size(),value));
}
high_precision_fraction equal_two_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    auto floor=[](const high_precision_fraction& value)->high_precision{return value.show_up()/value.show_down();};
    dynamic_array<size_t> value;
    size_t pos=inp.find(function_input_separator),evepos,evelast,end=inp.size();
    std::string name;
    bool with_b;
    evepos=evelast=pos+(with_b=(bool)(inp[pos+1]==function_left_bracket))+1;
    name=inp.substr(0,pos);
    while(evelast<end){
        sta_n=0;
        while(evepos<end&&((inp[evepos]!=function_input_separator&&inp[evepos]!=function_right_bracket)||sta_n)){
            add_change(inp[evepos],sta_n);
            evepos++;
        }
        value.push(floor(from->calculate(inp.substr(evelast,evepos-evelast),given_input).second));
        evelast=++evepos;
        if(inp[evepos-1]==function_right_bracket||((!with_b)&&inp[evepos-1]==function_input_separator)) break;
    }
    if(from->name_to_number.find(name)==from->name_to_number.end()){std::cerr<<"Array "<<name<<" doesn't exist."<<std::endl;return (high_precision_fraction)0;}
    return from->array_value.at(from->name_to_number[name],value)=from->calculate(inp.substr(evelast+with_b),given_input).second;
}
high_precision_fraction array_at_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    auto floor=[](const high_precision_fraction& value)->high_precision{return value.show_up()/value.show_down();};
    dynamic_array<size_t> value;
    size_t pos=inp.find(function_input_separator),evepos,evelast,end=inp.size();
    std::string name;
    bool with_b;
    evepos=evelast=pos+(with_b=(bool)(inp[pos+1]==function_left_bracket))+1;
    name=inp.substr(0,pos);
    while(evelast<end){
        sta_n=0;
        while(evepos<end&&(inp[evepos]!=function_input_separator||sta_n)){
            add_change(inp[evepos],sta_n);
            evepos++;
        }
        value.push(floor(from->calculate(inp.substr(evelast,evepos>=end?end-evelast-with_b:evepos-evelast),given_input).second));
        if(evepos>end) break;
        evelast=++evepos;
    }
    if(from->name_to_number.find(name)==from->name_to_number.end()){std::cerr<<"Array "<<name<<" doesn't exist."<<std::endl;return (high_precision_fraction)0;}
    return from->array_value.at(from->name_to_number[name],value);
}
void add_in_variable_h(MFE& to){
    to.insert("equal(variable,equal_expression)",equal_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("make_array(array_name,array_info)",make_array_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("equal(array_name,array_info,value)",equal_two_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("at(array_name,pos)",array_at_h,STRING_STYLE,DO_NOT_SAVE);
    to.array_value.set_original((high_precision)0);
}
high_precision_fraction random_h(MFE* from,dynamic_array<high_precision_fraction> input){
    high_precision left_val=input[0].show_up()/input[0].show_down(),right_val=input[1].show_up()/input[1].show_down(),answer;
    high_precision_fraction final_answer;
    std::string prev_ans_val;
    size_t size;
    if(left_val>right_val) std::swap(left_val,right_val);
    size=right_val.to_string().size()+1;
    for(size_t i=0;i<size;i++)
        prev_ans_val+=(rand()%10)+'0';
    answer.get(prev_ans_val);
    final_answer.set_up(answer%(right_val-left_val+1)+left_val);
    return final_answer;
}
void add_in_random_h(MFE& to){
    to.insert("random(left_value,right_value)",random_h,NUMBER_STYLE,DO_NOT_SAVE);
    srand((unsigned)time(NULL));
}
high_precision_fraction read_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    input_file=1;
    input_value.open(inp);
    return (high_precision)0;
}
high_precision_fraction read_empty_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    input_file=0;
    if(input_value.is_open()) input_value.close();
    return (high_precision)0;
}
high_precision_fraction write_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    output_file=1;
    output_value.open(inp);
    return (high_precision)0;
}
high_precision_fraction write_empty_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    output_file=0;
    if(output_value.is_open()) output_value.close();
    return (high_precision)0;
}
void add_in_file_h(MFE& to){
    to.insert("read(file_name)",read_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("read()",read_empty_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("write(file_name)",write_h,STRING_STYLE,DO_NOT_SAVE);
    to.insert("write()",write_empty_h,STRING_STYLE,DO_NOT_SAVE);
}
void add_in_pointer_function(){
    add_in["math.h"]=add_in_math_h;
    add_in["system.h"]=add_in_system_h;
    add_in["print.h"]=add_in_print_h;
    add_in["variable.h"]=add_in_variable_h;
    add_in["random.h"]=add_in_random_h;
    add_in["file.h"]=add_in_file_h;
    //这里做文件的map的录入，每一个文件的定义写在另一个函数里，而函数的录入在该文件中
}
high_precision_fraction help_h(MFE* from,dynamic_array<high_precision_fraction> input){
    std::cout<<"Hi, thank you for using the function calculater.(Input help(version) to check out the version of the calculator.) This is basically a calculater,but what's more is that you can calculate functions. Allow me to demonstrate:\n"\
    "You can input simple expressions like 1+1, 2^2, etc. Here are the rools:\n"\
    "note: in here, 0 stands for false, 1 stands for true.\n"\
    "+ stands for plus, means you add two things together. 1+1=2 \n"\
    "- stands for minus, means you let a number minus another. 2-1=1 \n"\
    "* stands for times, means you let a number times another. 2*2=4 \n"\
    "/ stands for division(I'll skip on the detail explanation). 6/2=3 \n"\
    "% means mod. 11%3=2 \n"\
    "^ means power. 3^3=27 \n"\
    "| means or. 1|1=1 0|1=1 0|0=0 \n"\
    "& means and. 1&1=1 0&1=0 0&0=0 \n"\
    "> means bigger than. 2>1=1 1>1=1 0>1=0\n"
    "< means smaller than. 2<1=0 1<1=0 0<1=1\n"\
    "= means equal. (1=1)=1 (2=1)=0\n"\
    "() are brackets.\n"\
    "That's all the operators. Now, I'll show you how to define a function:\n"\
    "There are two modes, calculation mode and function mode.\n"\
    "I was teaching you how to use the function mode just then, you can enter expressions and calculate them.\n"\
    "But, if you want to add in functions, you can:\n"\
    "first, use command \"add\", like add:math.h.\n"\
    "second, if you just want to write one function, you can just define it. You can input \"break\" if you want to exit.\n"\
    "third, you can use command \"file\", like file:(here you can define functions just like in a file). Input end to end the entering and start calculating with the new defined functions, or input break to exit function mode and leave the defined functions.\n"\
    "In the function mode, you can define functions, here's the rools:"\
    "function[do_save or do_not_save or don't write anything]=function_name(function_parameters){\n"\
    "   if(function_condition) function_expression;\n"\
    "}\n"\
    "If you enter do_save,that means the calculater will save the result, and when you call the function with the same values again, it will return the answer.(It is do_save if you don't write anything.)\n"\
    "The answer of the function is the first function_expression that the function_condition paired with it is true.\n"\
    "Example:\n"\
    "function[]=f(x){\n"\
    "   if(x>2) f(x-1)+f(x-2);\n"\
    "   if((x<2)|(x=2)) 1;\n"\
    "}\n"\
    "You can write a expression in function mode, and it will be calculated when you add the function in.\n"\
    "You can also add files in function mode with \"add\", but in another way:\n"\
    "like add[\\user\\blablabla\\main.hdm,test.hdm,math.h], the first one means add in \\user\\blablabla\\main.hdm,the second one means add in test.hdm which is in the same directory,the third one means add in a STL,which will be explained later.\n"\
    "You can write notes with // or /**/ in function mode.\n"\
    "//this makes the hole line after it a note.\n"\
    "/*this makes anything between it a note.*/\n"\
    "Note doesn't count as column in errors.\n"\
    "STL is a lot of functions that are defined by the calculater, you can add them like a normal file,and use help(file_name) (like help(math.h)) to check out what can the file do, and use help(file_name,function_name) (like help(math.h,floor)) to check out what a function can do.\n"\
    "Here are the STL files:\n"\
    "math.h\n"\
    "system.h\n"\
    "print.h\n"\
    "variable.h\n"\
    "random.h\n"\
    "file.h\n"
    ;//
    return (high_precision_fraction)0;//hange_order({{'|'},{'&'},{'!'},{'>','<','='},{'(',')','[',']','{','}'}});
}
high_precision_fraction help_one_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    std::map<std::string,std::string>::iterator cnt_value=_file_help.find(inp);
    if(cnt_value==_file_help.end()) std::cout<<"No help found.\n";
    else std::cout<<cnt_value->second;
    return (high_precision_fraction)0;
}
high_precision_fraction help_two_h(MFE* from,std::string inp,dynamic_array<FF_pair<std::string,high_precision_fraction>> given_input){
    size_t pos=inp.find(function_input_separator);
    std::string file_name=inp.substr(0,pos),function_name=inp.substr(pos+1);
    std::map<FF_pair<std::string,std::string>,std::string>::iterator cnt_value=_function_help.find(FF_pair<std::string,std::string>(file_name,function_name));
    if(cnt_value==_function_help.end()) std::cout<<"No help found.\n";
    else std::cout<<cnt_value->second;
    return (high_precision_fraction)0;
}
void change_string(){
    extern MFE environment;
    environment.insert("help()",help_h,NUMBER_STYLE,DO_NOT_SAVE);
    environment.insert("help(file_name)",help_one_h,STRING_STYLE,DO_NOT_SAVE);
    environment.insert("help(file_name,function_name)",help_two_h,STRING_STYLE,DO_NOT_SAVE);
    std::cout<<"This is the function calculater(Powered by Tony hu). Input help() to learn more."<<std::endl;
    _file_help["math.h"]="This is a file that contains mathematic calculation functions. With sum(start_from,go_to,expression), prod(start_from,go_to,expression), floor(input_value), ceil(input_value) four functions.\n";
    _function_help[FF_pair<std::string,std::string>("math.h","sum")]="This is a mathematic calculation function. It's like sigma, which is a summation operation. sum(i=a,b,f(i)) means f(a)+f(a+1)...+f(b-1)+f(b). For example, sum(k=0,5,k^2) = 0^2+ 1^2+2^2+3^2+4^2+5^2. \n";
    _function_help[FF_pair<std::string,std::string>("math.h","prod")]="This is a mathematic calculation function. It's like Π, which is a quadrature operation. prod(i=a,b,f(i)) means f(a)*f(a+1)*f(a+2)...*f(b-1)*f(b). For example, sum(k=0,3,2*i+1)=1*3*5*7. \n";
    _function_help[FF_pair<std::string,std::string>("math.h","floor")]="This is a mathematic calculation function. floor(a) means the first integer that is smaller than or equal to a. For example, floor(1.2)=1, floor(-12/13)=-1.\n";
    _function_help[FF_pair<std::string,std::string>("math.h","ceil")]="This is a mathematic calculation function. ceil(a) means the first integer that is bigger than or equal to a. For example, floor(1.2)=2, floor(-12/13)=0.\n";
    _file_help["system.h"]="This is a file that contains system setting functions. With do_reduction(change_value), output_style(change_value), save_decimal_point(change_value), expression_output(change_value), system(do_string), do_output(change_value) .\n";
    _function_help[FF_pair<std::string,std::string>("system.h","do_reduction")]="This is a system function. do_reduction(change_value). If change_value equals 0, it means do not do reduction, which means if you input 12/8 it will give you 12/8. If change_value equals 1,it means do reduction, which means if you input 12/3 it will give you 3/2(assuming you are in fraction mode, more on that in output_style). Function returns 0. \n";
    _function_help[FF_pair<std::string,std::string>("system.h","output_style")]="This is a system function. output_style(change_value). If change_value is fraction, the answer of a calculation will be a fraction, which means if you input 12/8 it will give you 3/2. If change_value is decimal, the answer of a calculation will be a decimal,which means if you input 12/8 it will give you 1.50000(you can use save_decimal_point to change how many points will be saved, assuming it's five). Function returns 0. \n";
    _function_help[FF_pair<std::string,std::string>("system.h","save_decimal_point")]="This is a system function. save_decimal_point(change_value). change_value is the decimal points that will be saved with the answer(which will still be calculated by fraction) , and it will be the decimal point that will be saved with the ^ operator. For example, when you're in the decimal mode (more on that in output_style) ,if the change_value is 1, the answer of 12/5 is 2.4, if the change_value is 5, the answer of 12/5 is 2.40000 . If the change_value is 0, the answer of 15^(1/2) is 3. If the change_value is five, the answer of 15^(1/2) is 193649/50000 (assuming you're in fraction mode). Function returns 0.\n";
    _function_help[FF_pair<std::string,std::string>("system.h","expression_output")]="This is a system function. expression_output(change_value). If change_value equals 1,it means the calculater will output the expression when calculating in function mode, If change_value equals 0, it means the calculater won't. Function returns 0.\n";
    _function_help[FF_pair<std::string,std::string>("system.h","system")]="This is a system function that allows you to use terminal in the function calculator. Use it like the print functions. Function returns 0.\n";
    _function_help[FF_pair<std::string,std::string>("system.h","do_output")]="This is a system function that allows you to set if the print function print on the terminal.(0 for false, 1 for true) Function returns 0.\n";
    _file_help["print.h"]="This is a file that allows you to output stuff. It contains printn(output_value), prints(output_value), printw(), printl(), printv(answer), getchar(), putchar(input_value), to_int(char_value). Note: to output line feed \" \" and \",\", you need to write \\n \\w and \\,. \n";
    _function_help[FF_pair<std::string,std::string>("print.h","printn")]="This is a function that allows you to output number. printn(output_value) means output output_value. For example, printn(1+1) outputs 2. Function returns output_value. \n";
    _function_help[FF_pair<std::string,std::string>("print.h","prints")]="This is a function that allows you to output strings. prints(output_value) means output output_value, and return 0. For example, prints(1+1,1+1) outputs 1+1 and returns 2. \n";
    _function_help[FF_pair<std::string,std::string>("print.h","printw")]="This is a function that allows you to output white space. printw() means output a white space, and return 0.\n";
    _function_help[FF_pair<std::string,std::string>("print.h","printl")]="This is a function that allows you to output line feed. printl() means output a line feed, and return 0.\n";
    _function_help[FF_pair<std::string,std::string>("print.h","printv")]="This is a function that allows you to output strings and numbers at the same time. printv({arg1,arg2,...}) (note: the double bracket can let you input multiple parameters). The function will think arg1 is a string, arg2 is a number, arg3 is a string... Function returns the sum of the numbers. For example, printv({expression:,1+1,+,2+2,=,1+1+2+2}) outputs expression:2+4=6, returns 12. \n";
    _function_help[FF_pair<std::string,std::string>("print.h","getchar")]="This is a function that allows you to input one char. The function returns the ASCII code of the char that was inputted.\n";
    _function_help[FF_pair<std::string,std::string>("print.h","putchar")]="This is a function that allows you to output one char. putchar(input_value) will output the char that has the ASCII code input_value. The function returns the ASCII code of the char that was outputted.\n";
    _function_help[FF_pair<std::string,std::string>("print.h","to_int")]="This is a function that allows you to turn one char into a number. to_int(char_value) will return the ACSII code of char_value.\n";
    _file_help["variable.h"]="This is a file that allows you to create variables. It contains equal(variable,equal_expression), make_array(array_name,array_info), equal(array_name,array_info,value), at(array_name,pos).\n";
    _function_help[FF_pair<std::string,std::string>("variable.h","equal")]="There are two functions that are both called equal: equal(variable,equal_expression) and equal(array_name,array_info,value). The first equal can assign variable with equal_expression, if variable don't exist, the function will define it first and assign it with equal_expression (note: if you use the variable in equal_expression but the variable don't exist, the program will assume variable is 0).the function will return equal_expression. The second equal can assign a number in a array. Assign array_name[array_info] with value. (note: if array_info have more than one layer, you need to enclose it in parentheses.) For example, equal(a,10,1+1) means a[10]=1+1, equal(b,(1,2),2+3) means b[1][2]=2+3. (note:subscript starts with 0.) The function will return value.\n";
    _function_help[FF_pair<std::string,std::string>("variable.h","make_array")]="This function allows you to define an array. make_array(array_name,array_info) means define a array called array_name with array_info. If the array have more than one layer, you'll have to enclose it in parentheses. For example: make_array(a,3) means define a[3], but you can only visit a[0~2]; make_array(b,(3,5)) means define b[3][5], but you can only visit b[0~2][0~4].\n";
    _function_help[FF_pair<std::string,std::string>("variable.h","at")]="This function allows you to visit a number in an array. at(array_name,pos) means visit array_name at pos. If the array have more than one layer, you'll have to enclose pos in parentheses. For example, at(a,12) means visit a[12], at(b,(3,2,1)) means visit b[3][2][1].\n";
    _file_help["random.h"]="This is a file that allows you to get random numbers. It contains random(left_value,right_value).\n";
    _function_help[FF_pair<std::string,std::string>("random.h","random")]="This is a function that allows you to get random numbers. random(left_value,right_value) means get a random number between left_value and right_value (could be left_value or right_value).\n";
    _file_help["file.h"]="This is a file that contains the file function that allows you to read from file and write things in a file. It contains read(file_name) and write(file_name).\n";
    _function_help[FF_pair<std::string,std::string>("file.h","read")]="This is a function that allows you to set where the calculator will get inputs. read(file_name) means get the inputs from the file file_name, and read() means get the inputs from the terminal.\n";
    _function_help[FF_pair<std::string,std::string>("file.h","write")]="This is a function that allows you to set where the calculator will output. write(file_name) means output to the file file_name, and write() means output to the terminal.\n";
    _file_help["version"]="The version is 2.0 . The function \"system\" and the file \"file.h\" is added. \n";
}
#endif
