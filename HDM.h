#ifndef HDM_H
#define HDM_H
#include "MFE.h"
#include <fstream>
#include <algorithm>
#include "string_replace.h"
std::map<std::string,void(*)(MFE&)> add_in;
bool expression_output=1;
std::string no_white(std::string input){
    std::string answer;
    for(size_t i=0,end=input.size();i<end;i++)
        if(input[i]!=' '&&input[i]!='\t'&&input[i]!='\r'&&input[i]!='\n')
            answer+=input[i];
    return answer;
}
size_t get_column(const std::string& input_value,size_t at){
    size_t ori_at=at;
    while(input_value[at]!='\n'&&at>0) at--;
    return input_value[at]=='\n'?ori_at-at:ori_at+1;
}
FF_pair<bool,std::string> read_file_value(std::string file_name){
    std::fstream file_input(file_name,std::ios::in);
    std::string string_value,every_line_value;
    if(!file_input.is_open())
        return FF_pair<bool,std::string>(0,string_value);
    while(getline(file_input,every_line_value))
        string_value+=every_line_value+'\n';
    file_input.close();
    return FF_pair<bool,std::string>(1,string_value);
}
bool read_from_file(MFE& environment,std::string file_name,std::string file_string,bool is_file,std::string add_before){
    std::map<std::string,void(*)(MFE&)>::iterator check=add_in.find(file_name);
    std::fstream file_value(file_name,std::ios::in);
    std::string read_string,function_info,function_condition,function_expression,new_name,new_line,ori_file_name=file_name;
    size_t string_count_value=0,last,line=1;
    FF_pair<bool,high_precision_fraction> answer;
    high_precision stack;
    bool save_function=1;
    dynamic_array<FF_pair<std::string,std::string>> value;
    if(check!=add_in.end()){
        check->second(environment);
        return 1;
    }
    else if(!is_file){
        std::cerr<<add_before<<string_replace(file_do_not_exist_warning,{FF_pair<std::string,std::string>(::file_name,file_name)});
        return 0;
    }
    add_before+=ori_file_name+"::";
    size_t start_value;
    for(string_count_value=file_name.size();string_count_value>0&&file_name[string_count_value-1]!='/';)
        string_count_value--;
    file_name=file_name.substr(0,string_count_value);
    for(string_count_value=0;string_count_value<file_string.size();string_count_value++){
        while(string_count_value<file_string.size()&&file_string[string_count_value]!='/')
            string_count_value++;
        if(string_count_value>file_string.size())
            break;
        start_value=string_count_value;
        new_line="";
        if(file_string[string_count_value+1]=='/')
            while(string_count_value<file_string.size()&&file_string[string_count_value]!='\n')
                string_count_value++;
        else if(file_string[string_count_value+1]=='*'){
            while(string_count_value+1<file_string.size()&&(file_string[string_count_value]!='*'||file_string[string_count_value+1]!='/')){string_count_value++;new_line+=file_string[string_count_value]=='\n'?"\n":"";}
            string_count_value+=2;
        }
        file_string=file_string.substr(0,start_value)+new_line+(string_count_value<file_string.size()?file_string.substr(string_count_value):"");
        string_count_value=start_value;
    }
    size_t prev_line,prev_at;
    for(size_t at_value=0,end=file_string.size();at_value<end;at_value++){
        while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
        if(file_string.substr(at_value,3)=="add"){
            prev_at=at_value;
            at_value+=3;
            prev_line=line;
            while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
            if(file_string[at_value]!='['){
                std::cerr<<add_before<<string_replace(no_after_add_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            prev_at=last=at_value;
            prev_line=line;
            bool is_wrong=0;
            while(at_value<end){
                at_value++;
                while(at_value<end&&file_string[at_value]!=','&&file_string[at_value]!=']'&&file_string[at_value]!='['){at_value++;line+=file_string[at_value]=='\n';}
                if(at_value>=end||file_string[at_value]=='['){ is_wrong=1;break;}
                read_string=file_string.substr(last+1,at_value-last-1);
                FF_pair<bool,std::string> goto_string_val=read_file_value(read_string);
                if(goto_string_val.first){
                    read_from_file(environment,read_string,goto_string_val.second,1,add_before);
                }
                else{
                    new_name=file_name+read_string;
                    goto_string_val=read_file_value(new_name);
                    if(goto_string_val.first)read_from_file(environment,new_name,goto_string_val.second,1,add_before);
                    else read_from_file(environment,read_string,"",0,add_before);
                }
                if(file_string[at_value]==']') break;
                last=at_value++;
            }
            if(is_wrong){
                std::cerr<<add_before<<string_replace(no_matching_waring,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
        }
        else if(file_string.substr(at_value,8)=="function"){
            value(0);
            at_value+=8;
            prev_at=at_value;
            prev_line=line;
            while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
            if(file_string[at_value]!='['){
                std::cerr<<add_before<<string_replace(first_no_after_function_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            prev_at=last=at_value;
            prev_line=line;
            while(at_value<end&&file_string[at_value]!=']'){at_value++;line+=file_string[at_value]=='\n';}
            function_info=no_white(file_string.substr(last+1,at_value-last-1));
            if(function_info=="do_not_save") save_function=0;
            else if(function_info==""||function_info=="do_save") save_function=1;
            else{
                std::cerr<<add_before<<string_replace(file_wrong_expression_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            if(at_value>=end){
                std::cerr<<add_before<<string_replace(no_matching_waring,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            prev_at=++at_value;
            prev_line=line;
            while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
            if(file_string[at_value]!='='){
                std::cerr<<add_before<<string_replace(no_equal_after_function_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            last=at_value;
            while(at_value<end&&file_string[at_value]!='{'){at_value++;line+=file_string[at_value]=='\n';}
            function_info=no_white(file_string.substr(last+1,at_value-last-1));
            if(file_string[at_value]!='{'){
                std::cerr<<add_before<<string_replace(no_after_function_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                return 0;
            }
            else{
                at_value++;
                while(at_value<end&&file_string[at_value]!='}'){
                    while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
                    prev_at=at_value;
                    prev_line=line;
                    if(file_string.substr(at_value,2)=="if"){
                        at_value+=2;
                        prev_at=at_value;
                        prev_line=line;
                        while(at_value<end&&(file_string[at_value]==' '||file_string[at_value]=='\t'||file_string[at_value]=='\r'||file_string[at_value]=='\n')){at_value++;line+=file_string[at_value]=='\n';}
                        if(file_string[at_value]!='('){
                            std::cerr<<add_before<<string_replace(no_after_if_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                            return 0;
                        }
                        last=at_value++;
                        prev_at=at_value;
                        prev_line=line;
                        while(at_value<end&&(file_string[at_value]!=')'||stack)){
                            if(file_string[at_value]=='(')stack++;
                            else if(file_string[at_value]==')') stack--;
                            at_value++;
                            line+=file_string[at_value]=='\n';
                        }
                        if(at_value==end){
                            std::cerr<<add_before<<string_replace(no_maching_b_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                            return 0;
                        }
                        function_condition=no_white(file_string.substr(last+1,at_value-last-1));
                        last=at_value;
                        prev_at=at_value;
                        prev_line=line;
                        while(at_value<end&&file_string[at_value]!=';'){at_value++;line+=file_string[at_value]=='\n';}
                        function_expression=no_white(file_string.substr(last+1,at_value-last-1));
                        if(function_condition.size()&&function_expression.size()) value.push(FF_pair<std::string,std::string>(function_condition,function_expression));
                        else{
                            std::cerr<<add_before<<string_replace(empty_expression_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)+(bool)function_condition.size()))});
                            return 0;
                        }
                    }
                    else if(file_string[at_value]=='}') break;
                    else{
                        std::cerr<<add_before<<string_replace(start_no_if_warning,{FF_pair<std::string,std::string>(::file_name,ori_file_name),FF_pair<std::string,std::string>(line_number,std::to_string(prev_line)),FF_pair<std::string,std::string>(column_number,std::to_string(get_column(file_string,prev_at)))});
                        return 0;
                    }
                    at_value++;
                }
                environment.insert(function_info,value,save_function);
            }
        }
        else{
            last=at_value;
            while(at_value<end&&file_string[at_value]!='\n')
                at_value++;
            function_expression=no_white(file_string.substr(last,at_value-last));
            if(function_expression.size()){
                answer=environment.calculate(function_expression);
                if(answer.first){
                    if(expression_output) std::cout<<function_expression<<'=';
                    std::cout<<answer.second<<std::endl;
                }
            }
        }
        while(at_value<end&&file_string[at_value]!='\n')
            at_value++;
        line+=file_string[at_value]=='\n';
    }
    return 1;
}
/*
 show.hdm
 
 add[system.h,spe.hdm]
 function[do_not_save]=f(x)
{
    if(x>0|x=0) f(x-1)+f(x-2);
    if(x<2) 1;
}
 */
#endif
