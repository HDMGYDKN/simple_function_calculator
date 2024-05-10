#ifndef MFE_H
#define MFE_H
#include <algorithm>
#include <map>
#include "dm_array.h"
#include "high_precision_fraction.h"
#include "dynamic_array.h"
#include "FF_pair.h"
#include "string_replace.h"
#define NUMBER_STYLE 0
#define STRING_STYLE 1
#define DO_NOT_SAVE 0
#define DO_SAVE 1
#define STRING_FUNCTION 0
#define POINTER_FUNCTION 1
#define UNARY_FUNCTION 0
#define BINARY_FUNCTION 1
char function_left_bracket='(',function_right_bracket=')',function_input_separator=',',equal_sign='=',skip_char=' ',multi_parameter_left_breacket='{',multi_parameter_right_breacket='}';
class MFE{//Multi-Function Environment
private:
    using unary_operator_function_name=high_precision_fraction(*)(high_precision_fraction);
    using operator_function_name=high_precision_fraction(*)(high_precision_fraction,high_precision_fraction);
    using string_style_function_pointer=high_precision_fraction(*)(MFE*,std::string,dynamic_array<FF_pair<std::string,high_precision_fraction>>);
    using number_style_function_pointer=high_precision_fraction(*)(MFE*,dynamic_array<high_precision_fraction>);
    size_t order[255]{0};
    void* operator_function[255][2]{NULL,NULL};//UNARY BINARY
    bool is_left_bracket[255]{0};
    char bracket_pair[255]{0};
    std::map<FF_pair<std::string,size_t>,FF_pair<dynamic_array<std::string>,dynamic_array<FF_pair<std::string,std::string>>>> string_function_value;
    std::map<FF_pair<std::string,size_t>,FF_pair<bool,void*>> pointer_function_value;
    std::map<FF_pair<std::string,size_t>,bool> _save;//save the result's or not
    std::map<FF_pair<FF_pair<std::string,size_t>,std::string>,high_precision_fraction> _prev_input;
    std::map<FF_pair<std::string,size_t>,dynamic_array<std::string>> function_prev_input;
    dynamic_array<dynamic_array<char>> prev_input;
    void get_info(std::string function_information,std::string& function_name,dynamic_array<std::string>& function_parameter){
        size_t string_count=0,last_count,string_size=function_information.size();
        while(function_information[string_count]!=function_left_bracket&&string_count<string_size){string_count++;}
        if(string_count==string_size){std::cerr<<string_replace(read_wrong_warning,{FF_pair<std::string,std::string>(::function_info,function_information)});return;}
        function_name=function_information.substr(0,string_count);
        last_count=++string_count;
        while(function_information[string_count]!=function_right_bracket&&string_count<string_size){
            while(function_information[string_count]!=function_input_separator&&function_information[string_count]!=function_right_bracket&&string_count<string_size) string_count++;
            function_parameter.push(function_information.substr(last_count,string_count-last_count));
            last_count=++string_count;
        }
        if(function_information[string_size-1]!=function_right_bracket||function_information[string_size-2]==function_input_separator){std::cerr<<string_replace(read_wrong_warning,{FF_pair<std::string,std::string>(::function_info,function_information)});return;}
        for(auto function_count:function_parameter){
            if(function_count==""){
                std::cerr<<string_replace(read_wrong_warning,{FF_pair<std::string,std::string>(::function_info,function_information)});
                return;
            }
        }
    }
public:
    dynamic_array<FF_pair<std::string,high_precision_fraction>> static_given_input;
    dm_array<high_precision_fraction> array_value;
    std::map<std::string,size_t> name_to_number;
    MFE(){
        change_order({{'|'},{'&'},{'!'},{'>','<','='},{'+','-'},{'*','/','%'},{'^'},{'(',')'}});
        set_operator_function('%',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input%second_input;});
        set_operator_function('+',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input+second_input;});
        set_operator_function('+',(unary_operator_function_name)([](high_precision_fraction input)mutable->high_precision_fraction{return input;}),UNARY_FUNCTION);
        set_operator_function('-',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input-second_input;});
        set_operator_function('-',(unary_operator_function_name)([](high_precision_fraction input)mutable->high_precision_fraction{return -input;}),UNARY_FUNCTION);
        set_operator_function('*',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input*second_input;});
        set_operator_function('/',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input/second_input;});
        set_operator_function('^',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return first_input.pow(second_input);});
        set_operator_function('&',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return (high_precision)((first_input!=(high_precision_fraction)0)&&(second_input!=(high_precision_fraction)0));});
        set_operator_function('|',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return (high_precision)((first_input!=(high_precision_fraction)0)||(second_input!=(high_precision_fraction)0));});
        set_operator_function('!',(unary_operator_function_name)([](high_precision_fraction input)mutable->high_precision_fraction{return (high_precision)(input==(high_precision_fraction)0);}),UNARY_FUNCTION);
        set_operator_function('>',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return (high_precision)(first_input>second_input);});
        set_operator_function('<',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return (high_precision)(first_input<second_input);});
        set_operator_function('=',(operator_function_name)[](high_precision_fraction first_input,high_precision_fraction second_input)mutable->high_precision_fraction{return (high_precision)(first_input==second_input);});
        add_bracket_pair('(',')');
    }
    void change_order(dynamic_array<dynamic_array<char>> input){
        prev_input=input;
        memset(order,0,255*sizeof(size_t));
        for(size_t count=0,end=input.size();count<end;count++)
            for(size_t count2=0,end2=input[count].size();count2<end2;count2++)
                order[(unsigned char)input[count][count2]]=count+1;
    }
    dynamic_array<dynamic_array<char>> show_order(){return prev_input;}
    void insert(std::string function_information,dynamic_array<FF_pair<std::string,std::string>> function_expression,bool save=DO_SAVE){//first condition, then expression
        std::string function_name;
        dynamic_array<std::string> function_parameter;
        get_info(function_information,function_name,function_parameter);
        delete_prev_input(function_name,function_parameter.size());
        string_function_value[FF_pair<std::string,size_t>(function_name,function_parameter.size())]=FF_pair<dynamic_array<std::string>,dynamic_array<FF_pair<std::string,std::string>>>(function_parameter,function_expression);
        _save[FF_pair<std::string,size_t>(function_name,function_parameter.size())]=save;
    }
    template<typename function>
    void insert(std::string function_information,function* func_o_pointer,bool style=NUMBER_STYLE,bool save=DO_SAVE){
        void* func_pointer=(void*)func_o_pointer;
        std::string function_name;
        dynamic_array<std::string> function_parameter;
        get_info(function_information,function_name,function_parameter);
        delete_prev_input(function_name,function_parameter.size());
        pointer_function_value[FF_pair<std::string,size_t>(function_name,function_parameter.size())]=FF_pair<bool,void*>(style,func_pointer);
        _save[FF_pair<std::string,size_t>(function_name,function_parameter.size())]=save;
    }
    dynamic_array<FF_pair<std::string,size_t>> all_function(){
        dynamic_array<FF_pair<std::string,size_t>> answer_value;
        for(auto count=string_function_value.begin(),end=string_function_value.end();count!=end;count++)
            answer_value.push(count->first);
        for(auto count=pointer_function_value.begin(),end=pointer_function_value.end();count!=end;count++)
            answer_value.push(count->first);
        return answer_value;
    }
    dynamic_array<bool> find(std::string function_name,size_t function_par){
        bool save=0,style=0,exist=0,form=0;
        auto find_value=FF_pair<std::string,size_t>(function_name,function_par);
        auto pointer=string_function_value.find(find_value);
        if(pointer!=string_function_value.end()){exist=1;form=0;}
        else{
            auto second_pointer=pointer_function_value.find(find_value);
            if(second_pointer!=pointer_function_value.end()){
                exist=1;form=1;style=second_pointer->second.first;
            }
        }
        auto third_pointer=_save.find(find_value);
        if(third_pointer!=_save.end()){save=third_pointer->second;}
        return {exist,form,save,style};
    }
    FF_pair<bool,FF_pair<dynamic_array<std::string>,dynamic_array<FF_pair<std::string,std::string>>>> string_detail(std::string function_name,size_t function_par){
        FF_pair<bool,FF_pair<dynamic_array<std::string>,dynamic_array<FF_pair<std::string,std::string>>>> answer;
        answer.first=0;
        auto pointer=string_function_value.find(FF_pair<std::string,size_t>(function_name,function_par));
        if(pointer!=string_function_value.end()){answer.first=1;answer.second=pointer->second;}
        return answer;
    }
    FF_pair<bool,FF_pair<bool,void*>> pointer_detail(std::string function_name,size_t function_par){
        FF_pair<bool,FF_pair<bool,void*>> answer=FF_pair<bool,FF_pair<bool,void*>>(0,FF_pair<bool,void*>(0,NULL));
        auto pointer=pointer_function_value.find(FF_pair<std::string,size_t>(function_name,function_par));
        if(pointer!=pointer_function_value.end()){answer.first=1;answer.second=pointer->second;}
        return answer;
    }
    template<typename pointer_typename>
    void set_operator_function(char operator_c,pointer_typename* pointer_value,bool function_type=BINARY_FUNCTION){operator_function[(unsigned char)operator_c][function_type]=(void*)pointer_value;}
    FF_pair<void*,void*> show_operator_fraction(char operator_c){return FF_pair<void*,void*>(operator_function[(unsigned char)operator_c][UNARY_FUNCTION],operator_function[(unsigned char)operator_c][BINARY_FUNCTION]);}
    void add_bracket_pair(char left_bracket,char right_bracket){bracket_pair[right_bracket]=left_bracket;is_left_bracket[left_bracket]=true;}
    char check_bracket_pair(char right_bracket){return bracket_pair[right_bracket];}
    FF_pair<bool,high_precision_fraction> calculate(std::string input,dynamic_array<FF_pair<std::string,high_precision_fraction>> give_input={}){
        std::map<std::string,high_precision_fraction> name_to_value;
        std::map<std::string,high_precision_fraction>::iterator name_to_value_every_value;
        std::map<FF_pair<std::string,size_t>,FF_pair<bool,void*>>::iterator get_pointer_function;
        std::map<FF_pair<FF_pair<std::string,size_t>,std::string>,high_precision_fraction>::iterator function_answer;
        std::map<FF_pair<std::string,size_t>,bool>::iterator save_check;
        std::map<FF_pair<std::string,size_t>,FF_pair<dynamic_array<std::string>,dynamic_array<FF_pair<std::string,std::string>>>>::iterator string_function_check;
        FF_pair<FF_pair<std::string,size_t>,std::string> prev_input_value;
        FF_pair<std::string,high_precision_fraction> *every_value,*end_val;
        FF_pair<std::string,size_t> function_info;
        FF_pair<bool,high_precision_fraction> get_answer;
        std::string value_name,function_name,check_string;
        size_t par_amount,value_pos,par_at,first_func,function_check,end_check_val;
        high_precision_fraction function_final_answer;
        bool exist=1,is_true,have_unary_function,have_binary_function;
        dynamic_array<high_precision_fraction> number_stack,pointer_function_input;
        dynamic_array<FF_pair<char,bool>> operator_stack;
        dynamic_array<FF_pair<std::string,high_precision_fraction>> call_func_input;
        high_precision bracket_stack;//check if is in a bracket
        char left_bracket;
        high_precision_fraction first_par,second_par;
        if(input==""){return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);}
        for(auto value:static_given_input)
            name_to_value[value.first]=value.second;
        for(auto value:give_input)
            name_to_value[value.first]=value.second;
        auto do_operation=[&](){// binary first, unary second
            if(number_stack.empty()){std::cerr<<string_replace(wrong_expression_warning,{FF_pair<std::string,std::string>(expression_string,input)});exist=0;return;}
            second_par=number_stack.top();
            number_stack.pop();
            if(operator_stack.empty()){std::cerr<<string_replace(wrong_expression_warning,{FF_pair<std::string,std::string>(expression_string,input)});exist=0;return;}
            have_unary_function=operator_function[(unsigned char)operator_stack.top().first][UNARY_FUNCTION]!=NULL;
            have_binary_function=operator_function[(unsigned char)operator_stack.top().first][BINARY_FUNCTION]!=NULL;
            if(!have_unary_function&&(!have_binary_function||operator_stack.top().second)){std::string  char_val;char_val+=operator_stack.top().first;if(char_val[0]!=function_left_bracket) std::cerr<<string_replace(no_char_function_warning,{FF_pair<std::string,std::string>(::char_operator,char_val)});else std::cerr<<string_replace(no_right_bracket_warning,{FF_pair<std::string,std::string>(::expression_string,input)});exist=0;return;}
            if(have_unary_function&&(!have_binary_function||operator_stack.top().second)){//(-1)
                number_stack.push(((unary_operator_function_name)(operator_function[(unsigned char)operator_stack.top().first][UNARY_FUNCTION]))(second_par));
                operator_stack.pop();
                return;
            }
            if(number_stack.empty()){std::cerr<<string_replace(wrong_expression_warning,{FF_pair<std::string,std::string>(expression_string,input)});exist=0;return;}
            first_par=number_stack.top();
            number_stack.pop();
            number_stack.push(((operator_function_name)(operator_function[(unsigned char)operator_stack.top().first][BINARY_FUNCTION]))(first_par,second_par));
            operator_stack.pop();
        };
        for(size_t pos=0,end=input.size(),last_pos;exist&&pos<end;pos++){
            while(input[pos]==skip_char) pos++;
            last_pos=pos;
            while(((input[pos]<='9'&&input[pos]>='0')||input[pos]=='.')&&pos<end) pos++;
            if(pos!=last_pos)
                number_stack.push(to_fraction(input.substr(last_pos,pos-last_pos)));
            last_pos=pos;
            while(!order[input[pos]]&&pos<end) pos++;
            if(pos!=last_pos){
                if(input[pos]==function_left_bracket){
                    function_name=input.substr(last_pos,pos-last_pos);
                    last_pos=pos++;
                    par_amount=1;
                    bracket_stack=0;
                    while((bracket_stack||input[pos]!=function_right_bracket)&&pos<end){
                        if(input[pos]==function_left_bracket||input[pos]==multi_parameter_left_breacket)bracket_stack++;
                        else if(input[pos]==function_right_bracket||input[pos]==multi_parameter_right_breacket) bracket_stack--;
                        if(input[pos++]==function_input_separator&&input[pos-2]!='\\'&&bracket_stack==0)
                            par_amount++;
                    }
                    if(pos==last_pos+1)
                        par_amount=0;
                    save_check=_save.find(FF_pair<std::string,size_t>(function_name,par_amount));
                    if(save_check==_save.end()){
                        std::cerr<<string_replace(do_not_exist_warning,{FF_pair<std::string,std::string>(::function_name,function_name),FF_pair<std::string,std::string>(::function_parameter_amount,std::to_string(par_amount))});
                        exist=0;
                        return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                    }
                    get_pointer_function=pointer_function_value.find(function_info=FF_pair<std::string,size_t>(function_name,par_amount));
                    if(get_pointer_function!=pointer_function_value.end()){
                        if(get_pointer_function->second.first==STRING_STYLE){
                            check_string=input.substr(last_pos,pos-last_pos+1);
                            end_val=give_input.end();
                            for(every_value=give_input.begin();every_value<end_val;every_value++)
                                check_string+=every_value->first+equal_sign+every_value->second.to_string()+function_input_separator;
                            function_answer=_prev_input.find(prev_input_value=FF_pair<FF_pair<std::string,size_t>,std::string>(FF_pair<std::string,size_t>(function_name,par_amount),check_string));
                            if(save_check->second&&function_answer!=_prev_input.end())number_stack.push(function_answer->second);
                            else{
                                function_final_answer=((string_style_function_pointer)(get_pointer_function->second.second))(this,input.substr(last_pos+1,pos-last_pos-1),give_input);
                                number_stack.push(function_final_answer);
                                if(save_check->second){
                                    _prev_input[FF_pair<FF_pair<std::string,size_t>,std::string>(FF_pair<std::string,size_t>(function_name,par_amount),check_string)]=function_final_answer;
                                    function_prev_input[FF_pair<std::string,size_t>(function_name,par_amount)].push(check_string);
                                }
                            }
                        }
                        else{
                            pointer_function_input(0);
                            value_pos=last_pos+1;
                            check_string="";
                            bracket_stack=0;
                            while(value_pos<pos){
                                while((bracket_stack||input[value_pos]!=function_input_separator)&&value_pos<pos){
                                    if(input[value_pos]==function_left_bracket||input[value_pos]==multi_parameter_left_breacket) bracket_stack++;
                                    else if(input[value_pos]==function_right_bracket||input[value_pos]==multi_parameter_right_breacket) bracket_stack--;
                                    value_pos++;
                                }
                                if(value_pos==last_pos+1) break;
                                get_answer=calculate(input.substr(last_pos+1,value_pos-last_pos-1),give_input);
                                exist&=get_answer.first;
                                if(!exist) return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                                pointer_function_input.push(get_answer.second);
                                check_string+=get_answer.second.to_string()+',';
                                last_pos=value_pos++;
                            }
                            function_answer=_prev_input.find(prev_input_value=FF_pair<FF_pair<std::string,size_t>,std::string>(FF_pair<std::string,size_t>(function_name,par_amount),check_string));
                            if(save_check->second&&function_answer!=_prev_input.end())number_stack.push(function_answer->second);
                            else{
                                function_final_answer=((number_style_function_pointer)(get_pointer_function->second.second))(this,pointer_function_input);
                                number_stack.push(function_final_answer);
                                if(save_check->second){
                                    _prev_input[FF_pair<FF_pair<std::string,size_t>,std::string>(FF_pair<std::string,size_t>(function_name,par_amount),check_string)]=function_final_answer;
                                    function_prev_input[FF_pair<std::string,size_t>(function_name,par_amount)].push(check_string);
                                }
                            }
                        }
                    }
                    else{
                        string_function_check=string_function_value.find(function_info);
                        if(string_function_check!=string_function_value.end()){
                            call_func_input(0);
                            value_pos=last_pos+1;
                            check_string="";
                            par_at=0;
                            bracket_stack=0;
                            while(value_pos<pos){
                                while((bracket_stack||input[value_pos]!=function_input_separator)&&value_pos<pos){
                                    if(input[value_pos]==function_left_bracket||input[value_pos]==multi_parameter_left_breacket) bracket_stack++;
                                    else if(input[value_pos]==function_right_bracket||input[value_pos]==multi_parameter_right_breacket) bracket_stack--;
                                    value_pos++;
                                }
                                if(value_pos==last_pos+1) break;
                                get_answer=calculate(input.substr(last_pos+1,value_pos-last_pos-1),give_input);
                                exist&=get_answer.first;
                                if(!exist) return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                                call_func_input.push(FF_pair<std::string,high_precision_fraction>(string_function_check->second.first[par_at],get_answer.second));
                                check_string+=get_answer.second.to_string()+',';
                                last_pos=value_pos++;
                                par_at++;
                            }
                            function_answer=_prev_input.find(FF_pair<FF_pair<std::string,size_t>,std::string>(function_info,check_string));
                            if(save_check->second&&function_answer!=_prev_input.end())number_stack.push(function_answer->second);
                            else{
                                first_func=0;
                                end_check_val=string_function_check->second.second.size();
                                for(function_check=0;function_check<end_check_val&&exist;function_check++){
                                    get_answer=calculate(string_function_check->second.second[function_check].first,call_func_input);
                                    exist&=get_answer.first;
                                    if(!exist) return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                                    is_true=get_answer.second!=(high_precision_fraction)0;
                                    if(is_true){
                                        first_func=function_check+1;
                                        break;
                                    }
                                }
                                if(first_func){
                                    get_answer=calculate(string_function_check->second.second[first_func-1].second,call_func_input);
                                    exist&=get_answer.first;
                                    if(!exist) return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                                    number_stack.push(get_answer.second);
                                    if(save_check->second){
                                        _prev_input[FF_pair<FF_pair<std::string,size_t>,std::string>(function_info,check_string)]=get_answer.second;
                                        function_prev_input[FF_pair<std::string,size_t>(function_name,par_amount)].push(check_string);
                                    }
                                }
                                else{
                                    std::cerr<<string_replace(can_not_calculate_warning,{FF_pair<std::string,std::string>(::function_name,function_info.first),FF_pair<std::string,std::string>(::function_parameter_amount,std::to_string(function_info.second)),FF_pair<std::string,std::string>(::variable_value,check_string)});
                                    exist=0;
                                    return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
                                }
                            }
                        }
                    }
                    pos++;
                }
                else{
                    name_to_value_every_value=name_to_value.find(value_name =input.substr(last_pos,pos-last_pos));
                    if(name_to_value_every_value->first==value_name) number_stack.push(name_to_value_every_value->second);
                    else{std::cerr<<string_replace(value_do_not_exist_warning,{FF_pair<std::string,std::string>(::variable_name,value_name)});exist=0;return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);}
                }
            }
            if(pos>=end) break;
            while(input[pos]==skip_char) pos++;
            if((left_bracket=bracket_pair[input[pos]])){
                while(exist&&!operator_stack.empty()&&operator_stack.top().first!=left_bracket)
                    do_operation();
                if(operator_stack.empty()){std::cerr<<string_replace(no_left_bracket_warning,{FF_pair<std::string,std::string>(expression_string,input)});exist=0;return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);}
                operator_stack.pop();
                continue;
            }
            while(exist&&!operator_stack.empty()&&!is_left_bracket[operator_stack.top().first]&&order[operator_stack.top().first]>=order[input[pos]])
                do_operation();
            if(!exist)return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
            operator_stack.push(FF_pair<char,bool>(input[pos],!pos||(order[input[pos-1]]&&!bracket_pair[input[pos-1]])));
        }
        while(exist&&!operator_stack.empty())
            do_operation();
        if(number_stack.size()>1){
            std::cerr<<string_replace(wrong_expression_warning,{FF_pair<std::string,std::string>(expression_string,input)});
            return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
        }
        if(!exist) return FF_pair<bool,high_precision_fraction>(0,(high_precision_fraction)0);
        return FF_pair<bool,high_precision_fraction>(exist,number_stack.top());
    }
    size_t function_amount(){return _save.size();}
    size_t string_function_amount(){return string_function_value.size();}
    size_t pointer_function_amount(){return pointer_function_value.size();}
    size_t prev_input_amount(){return _prev_input.size();}
    void delete_prev_input(std::string function_name,size_t function_par){
        FF_pair<std::string,size_t> function_info(function_name,function_par);
        dynamic_array<std::string> *input_value_p=&function_prev_input[function_info],input_value=*input_value_p;
        (*input_value_p)(0);
        for(std::string delete_value:input_value)_prev_input.erase(FF_pair<FF_pair<std::string,size_t>,std::string>(function_info,delete_value));
    }
};
#endif
