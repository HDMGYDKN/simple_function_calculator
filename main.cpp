#include <iostream>//主函数
#include <stdlib.h>
#include "HDM.h"
#include "HDM_STL.h"
#include "high_precision_fraction.h"//引入文件
using namespace std;
#define add_answer(answer_name_string_value,answer_to_value) environment.static_given_input.push(FF_pair<std::string,high_precision_fraction>(answer_name_string_value,answer_to_value));
string read_file_string="add:";
string read_function_string="file:";
string end_string="end";
string break_string="break";
string file_read_in_success_string="File read in successfully.\n";
string is_out="Is out.\n";//定义指令前缀
MFE environment;//环境
int main(){
    string file_name,calculate_string,fin_file_name,every,val;
    FF_pair<bool,high_precision_fraction> answer;
    FF_pair<bool,string> string_ans;
    size_t file_string_size=read_file_string.size(),func_string_size=read_function_string.size(),sta=0;
    init_string();
    add_in_pointer_function();
    change_string();//初始化
    while(1){
    start_calculation:
        getline(cin,calculate_string);
        if(calculate_string.substr(0,file_string_size)==read_file_string){//文件加入指令执行
            fin_file_name=calculate_string.substr(file_string_size);
            string_ans=read_file_value(fin_file_name);
            if(read_from_file(environment,fin_file_name,string_ans.second,string_ans.first,""))
                cout<<file_read_in_success_string;
        }
        else if(calculate_string.substr(0,func_string_size)==read_function_string){//终端中临时文件的创建与加入的指令执行
            val=calculate_string.substr(func_string_size)+'\n';
            while(getline(cin,every)){
                if(every==end_string) break;
                else if(every==break_string){
                    cout<<is_out;
                    goto start_calculation;//退出
                }
                val+=every+'\n';
            }
            if(read_from_file(environment,"",val,1,""))
                cout<<file_read_in_success_string;//成功
        }
        else if(calculate_string.substr(0,9)=="function["){//函数定义指令
            val=calculate_string;
            sta=0;
            for(size_t i=0,end=calculate_string.size();i<end;i++)
                if(calculate_string[i]=='{')sta++;
                else if(calculate_string[i]=='}') sta--;//括号影响加入
            while(getline(cin,every)){
                if(every=="break"){
                    cout<<is_out;
                    goto start_calculation;//退出
                }
                for(size_t i=0,end=every.size();i<end;i++)
                    if(every[i]=='{')sta++;
                    else if(every[i]=='}') sta--;//括号的影响加入
                val+='\n'+every;
                if(!sta) break;
            }
            if(read_from_file(environment,"",val,1,""))
                cout<<file_read_in_success_string;//成功
        }
        else{
            calculate_string=no_white(calculate_string);//进行计算
            if(calculate_string=="") continue;
            answer=environment.calculate(calculate_string);
            if(answer.first) cout<<answer.second<<endl;
            add_answer("ANSWER",answer.second);
            add_answer("Answer",answer.second);
            add_answer("answer",answer.second);
            add_answer("ANS",answer.second);
            add_answer("Ans",answer.second);
            add_answer("ans",answer.second);
        }
    }
    return 0;
}
