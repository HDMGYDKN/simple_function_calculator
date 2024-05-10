#ifndef STRING_REPLACE_H
#define STRING_REPLACE_H
#include <string.h>
#include "dynamic_array.h"
#include "FF_pair.h"
//HDM.h
std::string file_do_not_exist_warning="file_name do not exist.\n";
std::string no_after_add_warning="No '[' after add at line line_number column column_number in file file_name. \n";
std::string no_matching_waring="Can't find a ']' to match the '[' at line line_number column column_number in file file_name. \n";
std::string no_maching_b_warning="Can't find a ')' to match the '(' at line line_number column column_number in file file_name. \n";
std::string first_no_after_function_warning="No '[' after \"function\" at line line_number column column_number in file file_name. \n";
std::string no_after_function_warning="No '{' after \"function\" at line line_number column column_number in file file_name. \n";
std::string file_wrong_expression_warning="Wrong expression at line line_number column column_number in file_name, expression isn't do_save or do_not_save! \n";
std::string start_no_if_warning="Expression isn't starting with \"if\" at line line_number column column_number in file_name.\n";
std::string no_after_if_warning="No '(' after if at line line_number column column_number in file_name.\n";
std::string no_equal_after_function_warning="No '=' after function at line line_number column column_number in file_name. \n";
std::string empty_expression_warning="Empty expression at line line_number column column_number in file_name.\n";
std::string file_name="file_name";
std::string line_number="line_number";
std::string column_number="column_number";

//high_precition_fraction.h
std::string divisor_warning="high_precision_fraction:Divisor can't be zero in first_value / second_value.\n";
std::string square_root_warning="high_precision_fraction:can't get real solution with (first_value)^(second_value)\n";
std::string first_value="first_value";
std::string second_value="second_value";

//MFE.h
std::string read_wrong_warning="MFE:can't read function_info properly. \n";
std::string do_not_exist_warning="MFE:function function_name with function_parameter_amount parameters don't exist! \n";
std::string value_do_not_exist_warning="MFE:variable variable_name don't exist! \n";
std::string wrong_expression_warning="MFE:can't understand the expression \"expression_string\", calculation false! \n";
std::string can_not_calculate_warning="MFE:function function_name whih function_parameter_amount parameters do not have a legal expression with \"variable_value\". \n";
std::string no_char_function_warning="MFE:unknown character char_operator. \n";
std::string no_left_bracket_warning="MFE:No left bracket to match the right one in expression \"expression_string\". \n";
std::string no_right_bracket_warning="MFE:No right bracket to match the left one in expression \"expression_string\". \n";
std::string function_info="function_info";
std::string function_name="function_name";
std::string function_parameter_amount="function_parameter_amount";
std::string variable_name="variable_name";
std::string variable_value="variable_value";
std::string expression_string="expression_string";
std::string char_operator="char_operator";
std::string string_replace(const std::string& ori_value,dynamic_array<FF_pair<std::string,std::string>> replace_value){
    bool judge,in_judge;
    std::string ans_value;
    for(size_t cnt_val=0,end=ori_value.size();cnt_val<end;cnt_val++){
        in_judge=0;
        for(FF_pair<std::string,std::string> eve_val:replace_value){
            judge=1;
            if(end-cnt_val-1<eve_val.first.size())
                continue;
            for(size_t curr_val=0,end=eve_val.first.size();curr_val<end;curr_val++){
                if(ori_value[cnt_val+curr_val]!=eve_val.first[curr_val]){
                    judge=0;
                    break;
                }
            }
            if(judge){
                ans_value+=eve_val.second;
                cnt_val+=eve_val.first.size()-1;
                in_judge=1;
                break;
            }
        }
        if(!in_judge) ans_value+=ori_value[cnt_val];
    }
    return ans_value;
}
std::string hash_s[256];
void init_string(){
    hash_s['n']="\n";
    hash_s['w']=" ";
    hash_s[',']=",";
}
std::string get_normal(const std::string& input_string){
    std::string answer_string;
    for(size_t i=0,end=input_string.size();i<end;i++){
        if(input_string[i]=='\\') answer_string+=hash_s[(size_t)input_string[++i]];
        else answer_string+=input_string[i];
    }
    return answer_string;
}
#endif
