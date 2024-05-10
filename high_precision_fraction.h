#ifndef HIGH_PRECISION_FRACTION
#define HIGH_PRECISION_FRACTION
#include <iostream>
#include <algorithm>
#include <cstring>
#include "high_precision.h"
#include "string_replace.h"
#define DO_REDUCTION 1
#define NOT_DO_REDUCTION 0
#define FRACTION_STYLE 1
#define DECIMAL_STYLE 0
bool do_reduction=DO_REDUCTION,output_style=FRACTION_STYLE;
high_precision save_decimal_point=0;
class high_precision_fraction{
public:
    high_precision high_precision_fraction_up_value,high_precision_fraction_down_value;
    static high_precision gcd(const high_precision& high_precision_first_input_value,const high_precision& high_precision_second_input_value){
        high_precision high_precision_large_value=high_precision_first_input_value,high_precision_small_value=high_precision_second_input_value,high_precision_mid_value;
        if(high_precision_first_input_value<high_precision_second_input_value)std::swap(high_precision_small_value,high_precision_large_value);
        while(high_precision_small_value!=0){
            high_precision_mid_value=high_precision_small_value;
            high_precision_small_value=high_precision_large_value%high_precision_small_value;
            high_precision_large_value=high_precision_mid_value;
        }
        return high_precision_large_value;
    }
public:
    high_precision_fraction(){clear();}
    high_precision_fraction(const high_precision_fraction& high_precision_fraction_init_value){operator=(high_precision_fraction_init_value);}
    high_precision_fraction(high_precision_fraction&& high_precision_fraction_init_value){operator=(std::forward<high_precision_fraction&&>(high_precision_fraction_init_value));}
    high_precision_fraction(const high_precision& high_precision_fraction_init_value){operator=(high_precision_fraction_init_value);reduction(1);}
    high_precision_fraction(const high_precision& high_precision_fraction_init_up_value,const high_precision& high_precision_fraction_init_down_value){clear();operator()(high_precision_fraction_init_up_value,high_precision_fraction_init_down_value);}
    high_precision_fraction& operator()(const high_precision& equal_up_value,const high_precision& equal_down_value){if(equal_down_value==0){std::cerr<<string_replace(divisor_warning,{FF_pair<std::string,std::string>(first_value,equal_up_value.to_string()),FF_pair<std::string,std::string>(second_value,equal_down_value.to_string())});return *this;}high_precision_fraction_up_value=equal_up_value;high_precision_fraction_down_value=equal_down_value;reduction(1);return *this;}
    void clear(){high_precision_fraction_up_value=0;high_precision_fraction_down_value=1;}
    const high_precision& show_up()const{return high_precision_fraction_up_value;}
    const high_precision& show_down()const{return high_precision_fraction_down_value;}
    void set_up(const high_precision& high_precision_fraction_change_up_high_precision_value){high_precision_fraction_up_value=high_precision_fraction_change_up_high_precision_value;reduction(1);}
    void set_down(const high_precision& high_precision_fraction_change_down_high_precision_value){if(high_precision_fraction_change_down_high_precision_value==0) std::cerr<<string_replace(divisor_warning,{FF_pair<std::string,std::string>(first_value,high_precision_fraction_up_value.to_string()),FF_pair<std::string,std::string>(second_value,high_precision_fraction_change_down_high_precision_value.to_string())});else{high_precision_fraction_down_value=high_precision_fraction_change_down_high_precision_value;reduction(1);}}
    void reduction(bool high_precision_fraction_reduction_is_in_class_bool_value=0){
        if(!do_reduction&&high_precision_fraction_reduction_is_in_class_bool_value) return;
        if(high_precision_fraction_down_value<0){high_precision_fraction_up_value=-high_precision_fraction_up_value;high_precision_fraction_down_value=-high_precision_fraction_down_value;}
        high_precision greatest_common_factor=gcd(high_precision_fraction_up_value,high_precision_fraction_down_value);
        if(greatest_common_factor<0) greatest_common_factor=-greatest_common_factor;
        if(greatest_common_factor==1) return;
        high_precision_fraction_up_value/=greatest_common_factor;
        high_precision_fraction_down_value/=greatest_common_factor;
    }
    std::string to_string()const{return high_precision_fraction_up_value.to_string()+(high_precision_fraction_down_value==1?"":("/"+high_precision_fraction_down_value.to_string()));}
    std::string to_string(const high_precision& save_value_type)const{auto get_s=[](const std::string& value_string)->std::string{return value_string[0]=='-'?value_string.substr(1):value_string;};std::string final_answer,add_zero;high_precision change_up_value=high_precision_fraction_up_value;change_up_value.movel(save_value_type);final_answer=(change_up_value/high_precision_fraction_down_value).to_string();bool _is_negetive=final_answer[0]=='-';if(_is_negetive) final_answer=get_s(final_answer);for(high_precision count_value=final_answer.size();count_value<save_value_type;count_value++)add_zero+='0';return (_is_negetive?"-":"")+get_s((high_precision_fraction_up_value/high_precision_fraction_down_value).to_string())+(save_value_type>0?".":"")+add_zero+final_answer.substr(final_answer.size()>=save_value_type?final_answer.size()-save_value_type:(high_precision)0);}
    friend std::ostream& operator<<(std::ostream& ostream_output_to_value,const high_precision_fraction& high_precision_fraction_out_put_value){if(output_style) return ostream_output_to_value<<high_precision_fraction_out_put_value.to_string();else return ostream_output_to_value<<high_precision_fraction_out_put_value.to_string(save_decimal_point);}
    void get(std::string high_precision_fraction_get_string_input_value){
        high_precision first_position=high_precision_fraction_get_string_input_value.find('.');
        if(first_position!=high_precision_fraction_get_string_input_value.npos){
            high_precision_fraction_up_value.get(high_precision_fraction_get_string_input_value.substr(0,first_position)+high_precision_fraction_get_string_input_value.substr(first_position+1));
            high_precision_fraction_down_value=1;
            high_precision_fraction_down_value.movel(high_precision_fraction_get_string_input_value.size()-first_position-1);}
        else{
            first_position=high_precision_fraction_get_string_input_value.find('/');
            if(first_position!=high_precision_fraction_get_string_input_value.npos){high_precision_fraction_up_value.get(high_precision_fraction_get_string_input_value.substr(0,first_position));high_precision_fraction_down_value.get(high_precision_fraction_get_string_input_value.substr(first_position+1));}
            else{high_precision_fraction_up_value.get(high_precision_fraction_get_string_input_value);high_precision_fraction_down_value=1;}
        }
        reduction(1);
    }
    friend std::istream& operator>>(std::istream& istream_input_from_value,high_precision_fraction& high_precision_fraction_input_value){
        std::string input_to_string_value;
        istream_input_from_value>>input_to_string_value;
        high_precision_fraction_input_value.get(input_to_string_value);
        return istream_input_from_value;
    }
    high_precision_fraction& operator=(const high_precision_fraction& high_precision_fraction_other_value){high_precision_fraction_up_value=high_precision_fraction_other_value.high_precision_fraction_up_value;high_precision_fraction_down_value=high_precision_fraction_other_value.high_precision_fraction_down_value;return *this;}
    high_precision_fraction& operator=(high_precision_fraction&& high_precision_fraction_other_rvalue){high_precision_fraction_up_value=std::forward<high_precision&&>(high_precision_fraction_other_rvalue.high_precision_fraction_up_value);high_precision_fraction_down_value=std::forward<high_precision&&>(high_precision_fraction_other_rvalue.high_precision_fraction_down_value);return *this;}
    high_precision_fraction& operator=(const high_precision& high_precision_up_value_input){high_precision_fraction_up_value=(high_precision_up_value_input);high_precision_fraction_down_value=1;return *this;}
    high_precision_fraction operator+(void)const{return high_precision_fraction(high_precision_fraction_up_value,high_precision_fraction_down_value);}
    high_precision_fraction operator-(void)const{return high_precision_fraction(-high_precision_fraction_up_value,high_precision_fraction_down_value);}
    high_precision_fraction operator+(const high_precision_fraction& high_precision_fraction_other_value)const{high_precision_fraction answer_value(high_precision_fraction_up_value*high_precision_fraction_other_value.high_precision_fraction_down_value+high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_up_value,high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_down_value);return answer_value;}
    template<typename high_precision_fraction_operator_plus_other_value_typename>friend high_precision_fraction operator+(high_precision_fraction_operator_plus_other_value_typename other_value,const high_precision_fraction& high_precision_fraction_value){return (high_precision_fraction)other_value+high_precision_fraction_value;}
    high_precision_fraction& operator+=(const high_precision_fraction& high_precision_fraction_other_value){return *this=*this+high_precision_fraction_other_value;}
    high_precision_fraction operator-(const high_precision_fraction& high_precision_fraction_other_value)const{high_precision_fraction answer_value(high_precision_fraction_up_value*high_precision_fraction_other_value.high_precision_fraction_down_value-high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_up_value,high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_down_value);return answer_value;}
    template<typename high_precision_fraction_operator_plus_other_value_typename>friend high_precision_fraction operator-(high_precision_fraction_operator_plus_other_value_typename other_value,const high_precision_fraction& high_precision_fraction_value){return (high_precision_fraction)other_value-high_precision_fraction_value;}
    high_precision_fraction& operator-=(const high_precision_fraction& high_precision_fraction_other_value){return *this=*this-high_precision_fraction_other_value;}
    high_precision_fraction operator*(const high_precision_fraction& high_precision_fraction_other_value)const{high_precision_fraction answer_value(high_precision_fraction_up_value*high_precision_fraction_other_value.high_precision_fraction_up_value,high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_down_value);return answer_value;}
    template<typename high_precision_fraction_operator_plus_other_value_typename>friend high_precision_fraction operator*(high_precision_fraction_operator_plus_other_value_typename other_value,const high_precision_fraction& high_precision_fraction_value){return (high_precision_fraction)other_value*high_precision_fraction_value;}
    high_precision_fraction& operator*=(const high_precision_fraction& high_precision_fraction_other_value){return *this=*this*high_precision_fraction_other_value;}
    high_precision_fraction operator/(const high_precision_fraction& high_precision_fraction_other_value)const{high_precision_fraction answer_value(high_precision_fraction_up_value*high_precision_fraction_other_value.high_precision_fraction_down_value,high_precision_fraction_down_value*high_precision_fraction_other_value.high_precision_fraction_up_value);return answer_value;}
    template<typename high_precision_fraction_operator_plus_other_value_typename>friend high_precision_fraction operator/(high_precision_fraction_operator_plus_other_value_typename other_value,const high_precision_fraction& high_precision_fraction_value){return (high_precision_fraction)other_value/high_precision_fraction_value;}
    high_precision_fraction& operator/=(const high_precision_fraction& high_precision_fraction_other_value){return *this=*this/high_precision_fraction_other_value;}
    high_precision_fraction operator%(const high_precision_fraction& high_precision_fraction_other_value){high_precision_fraction answer_value=operator/(high_precision_fraction_other_value),second_answer_value(answer_value.high_precision_fraction_up_value/answer_value.high_precision_fraction_down_value);return operator-(second_answer_value*high_precision_fraction_other_value);}
    template<typename high_precision_fraction_operator_plus_other_value_typename>friend high_precision_fraction operator%(high_precision_fraction_operator_plus_other_value_typename other_value,const high_precision_fraction& high_precision_fraction_value){return (high_precision_fraction)other_value%high_precision_fraction_value;}
    high_precision_fraction& operator%=(const high_precision_fraction& high_precision_fraction_other_value){return *this=*this%high_precision_fraction_other_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator>(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value>this_value;}
    bool operator>(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value>other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator<(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value<this_value;}
    bool operator<(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value<other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator>=(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value>=this_value;}
    bool operator>=(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value>=other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator<=(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value<=this_value;}
    bool operator<=(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value<=other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator==(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value==this_value;}
    bool operator==(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value==other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    template<typename high_precision_fraction_compare_function_typename>friend bool operator!=(const high_precision_fraction_compare_function_typename& other_value,const high_precision_fraction& this_value){return (high_precision_fraction)other_value!=this_value;}
    bool operator!=(const high_precision_fraction& other_value)const{return high_precision_fraction_up_value*other_value.high_precision_fraction_down_value!=other_value.high_precision_fraction_up_value*high_precision_fraction_down_value;}
    high_precision_fraction pow(const high_precision_fraction& high_precision_fraction_pow_input){
        bool is_reverse=0;
        high_precision_fraction high_precision_fraction_pow_change_input=high_precision_fraction_pow_input;
        auto fast_pow_function=[](high_precision fast_pow_base,high_precision fast_pow_index)->high_precision{
            high_precision answer_value=1;
            while(fast_pow_index>0){
                if(fast_pow_index%2) answer_value*=fast_pow_base;
                fast_pow_base*=fast_pow_base;
                fast_pow_index/=2;
            }
            return answer_value;
        };
        auto get_sqrt=[&fast_pow_function,&high_precision_fraction_pow_input,this](high_precision& left_value,high_precision& right_value,const high_precision& with_value,const high_precision& to_value){
            if(with_value==1){left_value=right_value=to_value;return;}
            if(with_value==0||(to_value<0&&with_value%2==0)){std::cerr<<string_replace(square_root_warning,{FF_pair<std::string,std::string>(first_value,output_style?this->to_string():this->to_string(save_decimal_point)),FF_pair<std::string,std::string>(second_value,output_style?high_precision_fraction_pow_input.to_string():high_precision_fraction_pow_input.to_string(save_decimal_point))});return;}
            bool spe=to_value<0;
            high_precision middle_value;
            while(left_value<right_value){
                middle_value=(left_value+right_value-spe)/2;
                if((middle_value.to_string().size()-1)*with_value>=to_value.to_string().size()){right_value=middle_value;continue;}
                else if(middle_value.to_string().size()*with_value<to_value.to_string().size()){ left_value=middle_value+1;continue;}
                if(fast_pow_function(middle_value,with_value)>to_value) right_value=middle_value;
                else left_value=middle_value+1;
            }
            if(to_value>0&&fast_pow_function(left_value,with_value)>to_value) left_value--;
        };
        if(high_precision_fraction_pow_change_input.high_precision_fraction_up_value<0){
            high_precision_fraction_pow_change_input.high_precision_fraction_up_value=-high_precision_fraction_pow_change_input.high_precision_fraction_up_value;
            is_reverse=1;
        }
        high_precision answer_up_value=fast_pow_function(high_precision_fraction_up_value,high_precision_fraction_pow_change_input.high_precision_fraction_up_value),answer_down_value=fast_pow_function(high_precision_fraction_down_value,high_precision_fraction_pow_change_input.high_precision_fraction_up_value),left_value,right_value,output_down_value=1;
        high_precision_fraction up_answer,down_answer;
        answer_up_value.movel(high_precision_fraction_pow_change_input.high_precision_fraction_down_value*save_decimal_point);
        answer_down_value.movel(high_precision_fraction_pow_change_input.high_precision_fraction_down_value*save_decimal_point);
        output_down_value.movel(save_decimal_point);
        if(answer_up_value>0){left_value=0;right_value=answer_up_value;}
        else{left_value=answer_up_value;right_value=0;}
        get_sqrt(left_value,right_value,high_precision_fraction_pow_change_input.high_precision_fraction_down_value,answer_up_value);
        up_answer(left_value,output_down_value);
        left_value=0;
        right_value=answer_down_value;
        get_sqrt(left_value,right_value,high_precision_fraction_pow_change_input.high_precision_fraction_down_value,answer_down_value);
        down_answer(left_value,output_down_value);
        return is_reverse?down_answer/up_answer:up_answer/down_answer;
    }
};
high_precision_fraction to_fraction(std::string input){
    high_precision_fraction answer;
    answer.get(input);
    return answer;
}
#endif
