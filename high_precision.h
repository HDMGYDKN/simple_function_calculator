#ifndef HIGH_PRECISION_H//高精度
#define HIGH_PRECISION_H
#include <iostream>
#include <cstring>
#include <algorithm>
#include "dynamic_array.h"
class high_precision{
private:
    dynamic_array<char> _high_precision_value_dynamic_array;//高精度每一位上的值
    size_t _high_precision_size;//数字大小，即以十为底的log取下整
    bool _high_precision_negative=0;//正负 0为正1为负
    high_precision multiplication(char _high_precision_multiplication_input)const{//个位数的乘法
        high_precision ans=*this;
        char prev=0;
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_size;_high_precision_cnt++){
            ans._high_precision_value_dynamic_array[_high_precision_cnt]*=_high_precision_multiplication_input;
            ans._high_precision_value_dynamic_array[_high_precision_cnt]+=prev;
            prev=ans._high_precision_value_dynamic_array[_high_precision_cnt]/10;
            ans._high_precision_value_dynamic_array[_high_precision_cnt]%=10;
        }
        if(prev) ans._high_precision_value_dynamic_array[ans._high_precision_size++]=prev;
        return ans;
    }
public:
    high_precision(){clear();}//缺省构造函数，清空
    template<typename _high_precision_set_typename>
    high_precision(const _high_precision_set_typename& _high_precision_set_value){//拷贝初始化
        clear();//清空
        operator=(_high_precision_set_value);//调用拷贝赋值
    }
    template<typename _high_precision_set_typename>
    high_precision(_high_precision_set_typename&& _high_precision_set_value){//移动初始化
        clear();//清空
        operator=(std::forward<_high_precision_set_typename&&>(_high_precision_set_value));//调用移动赋值
    }
    void clear(){//清空类
        _high_precision_value_dynamic_array(1);
        _high_precision_value_dynamic_array={0};
        _high_precision_value_dynamic_array.set_original(0);
        _high_precision_negative=0;
        _high_precision_size=1;
    }
    void movel(size_t _high_precision_moveto=1){//乘上10的moveto次方
        if(*this==0||_high_precision_moveto==0)return;
        for(size_t _high_precision_cnt=_high_precision_size+_high_precision_moveto-1;_high_precision_cnt>=_high_precision_moveto;_high_precision_cnt--)
            _high_precision_value_dynamic_array[_high_precision_cnt]=_high_precision_value_dynamic_array[_high_precision_cnt-_high_precision_moveto];
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_moveto;_high_precision_cnt++)
            _high_precision_value_dynamic_array[_high_precision_cnt]=0;
        _high_precision_size+=_high_precision_moveto;
    }
    void mover(size_t _high_precision_moveto=1){//除以10的moveto次方（向下取整）
        if(_high_precision_moveto>=_high_precision_size){clear();return;}
        if(_high_precision_moveto==0) return;
        size_t _high_precision_end=_high_precision_size-_high_precision_moveto;
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_end;_high_precision_cnt++)
            _high_precision_value_dynamic_array[_high_precision_cnt]=_high_precision_value_dynamic_array[_high_precision_cnt+_high_precision_moveto];
        for(size_t _high_precision_cnt=_high_precision_end;_high_precision_cnt<_high_precision_size;_high_precision_cnt++)
            _high_precision_value_dynamic_array[_high_precision_cnt]=0;
        _high_precision_size-=_high_precision_moveto;
    }
    template<typename _high_precision_equal_typename>
    high_precision& operator=(_high_precision_equal_typename& _high_precision_equal_lvalue){//拷贝赋值
        _high_precision_equal_typename _high_precision_equal_rvalue=_high_precision_equal_lvalue;
        operator=(std::forward<_high_precision_equal_typename&&>(_high_precision_equal_rvalue));
        return *this;
    }
    template<>
    high_precision& operator=<high_precision>(high_precision& _high_precision_equal_lvalue){//拷贝赋值
        _high_precision_value_dynamic_array=_high_precision_equal_lvalue._high_precision_value_dynamic_array;
        _high_precision_size=_high_precision_equal_lvalue._high_precision_size;
        _high_precision_negative=_high_precision_equal_lvalue._high_precision_negative;
        return *this;
    }
    template<typename _high_precision_equal_typename>
    high_precision& operator=(const _high_precision_equal_typename&& _high_precision_equal_rvalue_input){//移动赋值
        _high_precision_equal_typename _high_precision_equal_rvalue=_high_precision_equal_rvalue_input;
        if(_high_precision_equal_rvalue<0){
            _high_precision_negative=1;
            _high_precision_equal_rvalue=-_high_precision_equal_rvalue;
        }
        size_t _high_precision_equal_cnt=0,_high_precision_last_size;
        if(!_high_precision_equal_rvalue) _high_precision_value_dynamic_array[0]=0;
        while(_high_precision_equal_rvalue){
            _high_precision_value_dynamic_array[_high_precision_equal_cnt++]=_high_precision_equal_rvalue%10;
            _high_precision_equal_rvalue/=10;
        }
        _high_precision_last_size=_high_precision_size;
        _high_precision_size=_high_precision_equal_cnt>1?_high_precision_equal_cnt:1;
        for(;_high_precision_equal_cnt<_high_precision_last_size;_high_precision_equal_cnt++)
            _high_precision_value_dynamic_array[_high_precision_equal_cnt]=0;
        return *this;
    }
    template<>
    high_precision& operator=<high_precision>(const high_precision&& _high_precision_equal_rvalue){//移动赋值
        _high_precision_value_dynamic_array=std::forward<const dynamic_array<char>&&>(_high_precision_equal_rvalue._high_precision_value_dynamic_array);
        _high_precision_size=_high_precision_equal_rvalue._high_precision_size;
        _high_precision_negative=_high_precision_equal_rvalue._high_precision_negative;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& _high_precision_out_to_value,const high_precision& _high_precision_out_from_value){//输出
        _high_precision_out_to_value<<_high_precision_out_from_value.to_string();
        return _high_precision_out_to_value;
    }
    friend std::istream& operator>>(std::istream& _high_precision_in_from_value,high_precision& _high_precision_in_to_value){//输入
        std::string _high_precision_in_to_value_string;
        _high_precision_in_from_value>>_high_precision_in_to_value_string;
        _high_precision_in_to_value.get(_high_precision_in_to_value_string);
        return _high_precision_in_from_value;
    }
    template<typename _high_precision_force_to>
    operator _high_precision_force_to()const{//强制类型转换
        _high_precision_force_to _high_precision_force_value=0;
        for(char* _high_precision_force_iterator=_high_precision_value_dynamic_array.rbegin();_high_precision_force_iterator>_high_precision_value_dynamic_array.rend();_high_precision_force_iterator--){
            _high_precision_force_value*=10;
            _high_precision_force_value+=*_high_precision_force_iterator;
        }
        if(_high_precision_negative) _high_precision_force_value=-_high_precision_force_value;
        return _high_precision_force_value;
    }
    void get(std::string _high_precision_in_to_value_string){//从字符串转换
        clear();
        size_t _string_size=_high_precision_in_to_value_string.size()-1;
        for(size_t _high_precision_dynamic_array_count=_string_size;_high_precision_dynamic_array_count>0;_high_precision_dynamic_array_count--){
            if(_high_precision_in_to_value_string[_high_precision_dynamic_array_count]>='0'&&_high_precision_in_to_value_string[_high_precision_dynamic_array_count]<='9')_high_precision_value_dynamic_array[_string_size-_high_precision_dynamic_array_count]=_high_precision_in_to_value_string[_high_precision_dynamic_array_count]-'0';
        }
        if(_high_precision_in_to_value_string[0]=='-'){
            _high_precision_negative=1;
            _high_precision_size=_string_size;
        }
        else{
            _high_precision_value_dynamic_array[_string_size]=_high_precision_in_to_value_string[0]-'0';
            _high_precision_size=_string_size+1;
        }
    }
    void get(const char* _high_precision_in_to_value_char){
        std::string _high_precision_in_to_value_string=_high_precision_in_to_value_char;
        get(_high_precision_in_to_value_string);
    }
    std::string to_string()const{
        std::string ans;
        for(size_t force_to_cnt=0,force_to_end=_high_precision_size;force_to_cnt<force_to_end;force_to_cnt++){
            ans=char(_high_precision_value_dynamic_array.read(force_to_cnt)+'0')+ans;
        }
        if(_high_precision_negative)
            ans='-'+ans;
        return ans;
    }
    template<typename _high_precision_typename>
    bool operator==(_high_precision_typename high_precision_inp)const{
        if((high_precision_inp<0)^_high_precision_negative) return false;
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_size||high_precision_inp;_high_precision_cnt++){
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt)!=high_precision_inp%10) return false;
            high_precision_inp/=10;
        }
        return true;
    }
    bool operator==(const high_precision& high_precision_inp)const{
        if(_high_precision_negative^high_precision_inp._high_precision_negative) return false;
        for(size_t _high_precision_cnt=std::max(_high_precision_size,high_precision_inp._high_precision_size);_high_precision_cnt>0;_high_precision_cnt--)
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt-1)!=high_precision_inp._high_precision_value_dynamic_array.read(_high_precision_cnt-1)) return false;
        return true;
    }
    template<typename _high_precision_typename>
    friend bool operator==(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return _high_precision_inp==high_precision_inp;}
    template<typename _high_precision_typename>
    bool operator>(_high_precision_typename high_precision_inp)const{
        if((high_precision_inp<0)^_high_precision_negative)return high_precision_inp<0;
        bool ans=0;
        if(high_precision_inp<0) high_precision_inp=-high_precision_inp;
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_size||high_precision_inp;_high_precision_cnt++){
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt)>high_precision_inp%10) ans=1;
            else if(_high_precision_value_dynamic_array.read(_high_precision_cnt)<high_precision_inp%10) ans=0;
            high_precision_inp/=10;
        }
        return ans^_high_precision_negative;
    }
    bool operator>(const high_precision& high_precision_inp)const{
        if(high_precision_inp._high_precision_negative^_high_precision_negative)return high_precision_inp._high_precision_negative;
        for(size_t _high_precision_cnt=std::max(_high_precision_size,high_precision_inp._high_precision_size);_high_precision_cnt>0;_high_precision_cnt--)
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt-1)<high_precision_inp._high_precision_value_dynamic_array.read(_high_precision_cnt-1)) return _high_precision_negative;
            else if(_high_precision_value_dynamic_array.read(_high_precision_cnt-1)>high_precision_inp._high_precision_value_dynamic_array.read(_high_precision_cnt-1)) return !_high_precision_negative;
        return false;
    }
    template<typename _high_precision_typename>
    friend bool operator<(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return _high_precision_inp>high_precision_inp;}
    template<typename _high_precision_typename>
    bool operator<(_high_precision_typename high_precision_inp)const{
        if((high_precision_inp<0)^_high_precision_negative)return _high_precision_negative;
        bool ans=0;
        if(high_precision_inp<0) high_precision_inp=-high_precision_inp;
        for(size_t _high_precision_cnt=0;_high_precision_cnt<_high_precision_size||high_precision_inp;_high_precision_cnt++){
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt)<high_precision_inp%10) ans=1;
            else if(_high_precision_value_dynamic_array.read(_high_precision_cnt)>high_precision_inp%10) ans=0;
            high_precision_inp/=10;
        }
        return ans^_high_precision_negative;
    }
    bool operator<(const high_precision& high_precision_inp)const{
        if(high_precision_inp._high_precision_negative^_high_precision_negative)return _high_precision_negative;
        for(size_t _high_precision_cnt=std::max(_high_precision_size,high_precision_inp._high_precision_size);_high_precision_cnt>0;_high_precision_cnt--)
            if(_high_precision_value_dynamic_array.read(_high_precision_cnt-1)>high_precision_inp._high_precision_value_dynamic_array.read(_high_precision_cnt-1)) return _high_precision_negative;
            else if(_high_precision_value_dynamic_array.read(_high_precision_cnt-1)<high_precision_inp._high_precision_value_dynamic_array.read(_high_precision_cnt-1)) return !_high_precision_negative;
        return false;
    }
    template<typename _high_precision_typename>
    friend bool operator>(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return _high_precision_inp<high_precision_inp;}
    template<typename _high_precision_typename>
    bool operator>=(_high_precision_typename high_precision_inp)const{return !operator<(high_precision_inp);}
    bool operator>=(const high_precision& high_precision_inp)const{return !operator<(high_precision_inp);}
    template<typename _high_precision_typename>
    friend bool operator>=(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return !(_high_precision_inp>high_precision_inp);}
    template<typename _high_precision_typename>
    bool operator<=(_high_precision_typename high_precision_inp)const{return !operator>(high_precision_inp);}
    bool operator<=(const high_precision& high_precision_inp)const{return !operator>(high_precision_inp);}
    template<typename _high_precision_typename>
    friend bool operator<=(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return !(_high_precision_inp<high_precision_inp);}
    template<typename _high_precision_typename>
    bool operator!=(_high_precision_typename high_precision_inp)const{return !operator==(high_precision_inp);}
    bool operator!=(const high_precision& high_precision_inp)const{return !operator==(high_precision_inp);}
    template<typename _high_precision_typename>
    friend bool operator!=(_high_precision_typename high_precision_inp,const high_precision& _high_precision_inp){return !(_high_precision_inp==high_precision_inp);}
    high_precision operator+()const{return *this;}
    high_precision operator-()const{
        high_precision _high_precision_operator_value=*this;
        if(_high_precision_operator_value._high_precision_size>1||_high_precision_operator_value._high_precision_value_dynamic_array[0]) _high_precision_operator_value._high_precision_negative=!_high_precision_operator_value._high_precision_negative;
        return _high_precision_operator_value;
    }
    template<typename high_precision_typename>
    high_precision operator+(high_precision_typename _high_precision_adder)const{
        high_precision ans=_high_precision_adder;
        ans=*this+ans;
        return ans;
    }
    template<typename high_precision_typename>
    friend high_precision operator+(high_precision_typename _high_precision_adder,const high_precision& _high_precision_inp){
        return _high_precision_inp+_high_precision_adder;
    }
    high_precision operator+(const high_precision& _high_precision_adder)const{
        high_precision ans;
        if(_high_precision_adder._high_precision_negative^_high_precision_negative){
            if(_high_precision_negative){
                ans=*this;
                ans._high_precision_negative=0;
                return _high_precision_adder-ans;
            }
            else{
                ans=_high_precision_adder;
                ans._high_precision_negative=0;
                return *this-ans;
            }
        }
        ans._high_precision_value_dynamic_array=_high_precision_size>_high_precision_adder._high_precision_size?_high_precision_value_dynamic_array:_high_precision_adder._high_precision_value_dynamic_array;
        ans._high_precision_size=std::max(_high_precision_size,_high_precision_adder._high_precision_size);
        size_t _high_precision_cnt=0,prev=0;
        for(size_t end=_high_precision_size<_high_precision_adder._high_precision_size?_high_precision_size:_high_precision_adder._high_precision_size;_high_precision_cnt<end;_high_precision_cnt++){
            ans._high_precision_value_dynamic_array[_high_precision_cnt]=_high_precision_value_dynamic_array.read(_high_precision_cnt)+_high_precision_adder._high_precision_value_dynamic_array.read(_high_precision_cnt)+prev;
            prev=ans._high_precision_value_dynamic_array[_high_precision_cnt]/10;
            ans._high_precision_value_dynamic_array[_high_precision_cnt]%=10;
        }
        while(prev){
            ans._high_precision_value_dynamic_array[_high_precision_cnt]+=prev;
            prev=ans._high_precision_value_dynamic_array[_high_precision_cnt]/10;
            ans._high_precision_value_dynamic_array[_high_precision_cnt++]%=10;
        }        ans._high_precision_size=std::max(ans._high_precision_size,_high_precision_cnt);
        ans._high_precision_negative=_high_precision_negative;
        return ans;
    }
    [[maybe_unused]]high_precision& operator+=(const high_precision& _high_precision_inp){return *this=*this+_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]high_precision& operator+=(_high_precision_typename _high_precision_inp){return *this=*this+_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]friend _high_precision_typename& operator+=(_high_precision_typename& _high_precision_typename_inp,const high_precision& _high_precision_inp){return _high_precision_typename_inp=_high_precision_typename_inp+_high_precision_inp;}
    [[maybe_unused]]const high_precision& operator++(){return *this+=1;}
    [[maybe_unused]]const high_precision operator++(int){
        high_precision prev=*this;
        *this+=1;
        return prev;
    }
    template<typename _high_precision_typename>
    high_precision operator-(_high_precision_typename _high_precision_subtrahend)const{
        high_precision ans=_high_precision_subtrahend;
        ans=*this-ans;
        return ans;
    }
    high_precision operator-(const high_precision& _high_precision_subtrahend)const{
        high_precision ans,*pointer;
        if(_high_precision_negative^_high_precision_subtrahend._high_precision_negative){
            ans=_high_precision_subtrahend;
            ans._high_precision_negative=_high_precision_negative;
            return *this+ans;
        }
        bool judge=*this>=_high_precision_subtrahend;
        if(_high_precision_negative) judge=!judge;
        ans=judge?*this:_high_precision_subtrahend;
        pointer=judge?const_cast<high_precision *>(&_high_precision_subtrahend):const_cast<high_precision *>(this);
        bool prev=0;
        for(size_t _high_precision_begin=0,_high_precision_end=std::max(_high_precision_size,_high_precision_subtrahend._high_precision_size);_high_precision_begin<_high_precision_end;_high_precision_begin++){
            ans._high_precision_value_dynamic_array[_high_precision_begin]-=pointer->_high_precision_value_dynamic_array.read(_high_precision_begin)+prev;
            prev=ans._high_precision_value_dynamic_array[_high_precision_begin]<0;
            if(prev)ans._high_precision_value_dynamic_array[_high_precision_begin]+=10;
        }
        if(pointer==this)ans._high_precision_negative=!ans._high_precision_negative;
        while(!ans._high_precision_value_dynamic_array[ans._high_precision_size-1]&&ans._high_precision_size>1)ans._high_precision_size--;
        return ans;
    }
    template<typename _high_precision_typename>
    friend high_precision operator-(_high_precision_typename _high_precision_typename_inp,high_precision _high_precision_inp){
        high_precision ans=_high_precision_typename_inp;
        ans=ans-_high_precision_inp;
        return ans;
    }
    [[maybe_unused]]high_precision& operator-=(const high_precision& _high_precision_inp){return *this=*this-_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]high_precision& operator-=(_high_precision_typename _high_precision_inp){return *this=*this-_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]friend _high_precision_typename& operator-=(_high_precision_typename& _high_precision_typename_inp,const high_precision& _high_precision_inp){return _high_precision_typename_inp=_high_precision_typename_inp-_high_precision_inp;}
    [[maybe_unused]]const high_precision& operator--(){return *this-=1;}
    [[maybe_unused]]const high_precision operator--(int){
        high_precision prev=*this;
        *this-=1;
        return prev;
    }
    template<typename _high_precision_typename>
    high_precision operator*(_high_precision_typename _high_precision_subtrahend)const{
        high_precision ans=_high_precision_subtrahend;
        ans=*this*ans;
        return ans;
    }
    high_precision operator*(const high_precision& high_precision_input)const{
        high_precision _high_precision_ans;
        for(size_t _high_precision_cnt=_high_precision_size;_high_precision_cnt>0;_high_precision_cnt--){
            _high_precision_ans.movel();
            _high_precision_ans+=high_precision_input.multiplication(_high_precision_value_dynamic_array.read(_high_precision_cnt-1));
        }
        _high_precision_ans._high_precision_negative=_high_precision_negative^high_precision_input._high_precision_negative;
        if(!_high_precision_ans._high_precision_value_dynamic_array[_high_precision_ans._high_precision_size-1]&&_high_precision_ans._high_precision_size>1) _high_precision_ans._high_precision_size--;
        if(!_high_precision_ans._high_precision_value_dynamic_array[0]&&_high_precision_ans._high_precision_size==1) _high_precision_ans._high_precision_negative=0;
        return _high_precision_ans;
    }
    template<typename _high_precision_typename>
    friend high_precision operator*(_high_precision_typename _high_precision_typename_inp,high_precision _high_precision_inp){
        high_precision ans=_high_precision_typename_inp;
        ans=ans*_high_precision_inp;
        return ans;
    }
    [[maybe_unused]]high_precision& operator*=(const high_precision& _high_precision_inp){return *this=*this*_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]high_precision& operator*=(_high_precision_typename _high_precision_inp){return *this=*this*_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]friend _high_precision_typename& operator*=(_high_precision_typename& _high_precision_typename_inp,const high_precision& _high_precision_inp){return _high_precision_typename_inp=_high_precision_typename_inp*_high_precision_inp;}
    template<typename _high_precision_typename>
    high_precision operator/(_high_precision_typename _high_precision_subtrahend)const{
        high_precision ans=_high_precision_subtrahend;
        ans=*this/ans;
        return ans;
    }
    high_precision operator/(const high_precision& _high_precision_input)const{
        high_precision ans,_high_precision_move=_high_precision_input,_this_change=*this;
        if(_high_precision_input._high_precision_size>_high_precision_size) return ans;
        ans._high_precision_negative=_high_precision_negative^_high_precision_input._high_precision_negative;
        ans._high_precision_size=_high_precision_size-_high_precision_input._high_precision_size+1;
        _high_precision_move.movel(ans._high_precision_size-1);
        _high_precision_move._high_precision_negative=0;
        _this_change._high_precision_negative=0;
        char left,right,middle;
        for(size_t _high_precision_cnt=ans._high_precision_size;_high_precision_cnt>0;_high_precision_cnt--){
            left=0;right=10;
            while(left<right){
                middle=(left+right+1)>>1;
                if(_high_precision_move.multiplication(middle)<=_this_change) left=middle;
                else right=middle-1;
            }
            ans._high_precision_value_dynamic_array[_high_precision_cnt-1]=left;
            _this_change-=_high_precision_move.multiplication(left);
            _high_precision_move.mover();
        }
        if(!ans._high_precision_value_dynamic_array[ans._high_precision_size-1]&&ans._high_precision_size>1) ans._high_precision_size--;
        if(!ans._high_precision_value_dynamic_array[0]&&ans._high_precision_size==1) ans._high_precision_negative=0;
        return ans;
    }
    template<typename _high_precision_typename>
    friend high_precision operator/(_high_precision_typename _high_precision_typename_inp,high_precision _high_precision_inp){
        high_precision ans=_high_precision_typename_inp;
        ans=ans/_high_precision_inp;
        return ans;
    }
    [[maybe_unused]]high_precision& operator/=(const high_precision& _high_precision_inp){return *this=*this/_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]high_precision& operator/=(_high_precision_typename _high_precision_inp){return *this=*this/_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]friend _high_precision_typename& operator/=(_high_precision_typename& _high_precision_typename_inp,const high_precision& _high_precision_inp){return _high_precision_typename_inp=_high_precision_typename_inp/_high_precision_inp;}
    template<typename _high_precision_typename>
    high_precision operator%(_high_precision_typename _high_precision_subtrahend)const{
        high_precision ans=_high_precision_subtrahend;
        ans=*this%ans;
        return ans;
    }
    high_precision operator%(const high_precision& _high_precision_input)const{
        high_precision ans;
        ans=*this-(*this/_high_precision_input)*_high_precision_input;
        ans._high_precision_negative=ans==0?0:_high_precision_negative;
        return ans;
    }
    template<typename _high_precision_typename>
    friend high_precision operator%(_high_precision_typename _high_precision_typename_inp,high_precision _high_precision_inp){
        high_precision ans=_high_precision_typename_inp;
        ans=ans%_high_precision_inp;
        return ans;
    }
    [[maybe_unused]]high_precision& operator%=(const high_precision& _high_precision_inp){return *this=*this%_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]high_precision& operator%=(_high_precision_typename _high_precision_inp){return *this=*this%_high_precision_inp;}
    template<typename _high_precision_typename>
    [[maybe_unused]]friend _high_precision_typename& operator%=(_high_precision_typename& _high_precision_typename_inp,const high_precision& _high_precision_inp){return _high_precision_typename_inp=_high_precision_typename_inp%_high_precision_inp;}
};
#endif
