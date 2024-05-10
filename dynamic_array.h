#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <initializer_list>
std::string already_empty_warning="dynamic_array:The array is already empty, can't do operation \"pop\"! \n";
template<typename _dynamic_array_typename>
class dynamic_array{
private:
    _dynamic_array_typename _original_type_value,*_dynamic_array_value_begin_pointer=NULL;
    size_t _dynamic_array_size=0,_dynamic_array_greatest_visit_subscript=0;
public:
    dynamic_array(){}
    dynamic_array(size_t _start_size,std::initializer_list<_dynamic_array_typename> _start_value={}){(*this)(_start_size)=_start_value;}
    dynamic_array(size_t _start_size,std::initializer_list<_dynamic_array_typename> _start_value,_dynamic_array_typename _original_type_value_input){
        _original_type_value=_original_type_value_input;
        (*this)(_start_size)=_start_value;
    }
    dynamic_array(std::initializer_list<_dynamic_array_typename> _start_value){(*this)(_start_value.size())=_start_value;}
    dynamic_array(const dynamic_array& _dynamic_array_start_lvalue){*this=_dynamic_array_start_lvalue;}
    dynamic_array(dynamic_array&& _dynamic_array_start_rvalue){*this=std::forward<dynamic_array&&>(_dynamic_array_start_rvalue);}
    ~dynamic_array(){delete[] _dynamic_array_value_begin_pointer;}
    void set_original(_dynamic_array_typename _dynamic_array_set_original_value_input){_original_type_value=_dynamic_array_set_original_value_input;}
    [[maybe_unused]] dynamic_array& operator()(size_t _new_dynamic_array_size){
        _dynamic_array_typename* _new_dynamic_array_value_begin_pointer=new _dynamic_array_typename[_new_dynamic_array_size];
        for(size_t _dynamic_array_count=0;_dynamic_array_count<_new_dynamic_array_size;_dynamic_array_count++)
            if(_dynamic_array_count<_dynamic_array_size) *(_new_dynamic_array_value_begin_pointer+_dynamic_array_count)=*(_dynamic_array_value_begin_pointer+_dynamic_array_count);
            else *(_new_dynamic_array_value_begin_pointer+_dynamic_array_count)=_original_type_value;
        delete[] _dynamic_array_value_begin_pointer;
        _dynamic_array_value_begin_pointer=_new_dynamic_array_value_begin_pointer;
        _dynamic_array_size=_new_dynamic_array_size;
        if(_dynamic_array_greatest_visit_subscript>_new_dynamic_array_size)_dynamic_array_greatest_visit_subscript=_new_dynamic_array_size;
        return *this;
    }
    _dynamic_array_typename& operator[](size_t _dynamic_array_visit_subscript){
        while(_dynamic_array_visit_subscript>=_dynamic_array_size)(*this)((_dynamic_array_size<<1)+1);
        if(_dynamic_array_greatest_visit_subscript<_dynamic_array_visit_subscript+1) _dynamic_array_greatest_visit_subscript=_dynamic_array_visit_subscript+1;
        return *(_dynamic_array_value_begin_pointer+_dynamic_array_visit_subscript);
    }
    [[maybe_unused]] dynamic_array& operator=(std::initializer_list<_dynamic_array_typename> _dynamic_array_equal_value){
        while(_dynamic_array_equal_value.size()>_dynamic_array_size) (*this)((_dynamic_array_size<<1)+1);
        _dynamic_array_greatest_visit_subscript=_dynamic_array_equal_value.size();
        for(size_t _dynamic_array_value_cnt=0;_dynamic_array_value_cnt<_dynamic_array_size;_dynamic_array_value_cnt++)
            if(_dynamic_array_value_cnt<_dynamic_array_equal_value.size())*(_dynamic_array_value_begin_pointer+_dynamic_array_value_cnt)=*(_dynamic_array_equal_value.begin()+_dynamic_array_value_cnt);
            else *(_dynamic_array_value_begin_pointer+_dynamic_array_value_cnt)=_original_type_value;
        return *this;
    }
    [[maybe_unused]] dynamic_array& operator=(const dynamic_array& _dynamic_array_equal_lvalue){
        if(&_dynamic_array_equal_lvalue==this) return *this;
        while(_dynamic_array_equal_lvalue._dynamic_array_size>_dynamic_array_size)
            (*this)((_dynamic_array_size<<1)+1);
        for(size_t _dynamic_array_value_count=0;_dynamic_array_value_count<_dynamic_array_size;_dynamic_array_value_count++)
            if(_dynamic_array_value_count<_dynamic_array_equal_lvalue._dynamic_array_size) *(_dynamic_array_value_begin_pointer+_dynamic_array_value_count)=*(_dynamic_array_equal_lvalue._dynamic_array_value_begin_pointer+_dynamic_array_value_count);
            else *(_dynamic_array_value_begin_pointer+_dynamic_array_value_count)=_original_type_value;
        _original_type_value=_dynamic_array_equal_lvalue._original_type_value;
        _dynamic_array_greatest_visit_subscript=_dynamic_array_equal_lvalue._dynamic_array_greatest_visit_subscript;
        return *this;
    }
    [[maybe_unused]] dynamic_array& operator=(dynamic_array&& _dynamic_array_equal_rvalue){
        delete[] _dynamic_array_value_begin_pointer;
        _dynamic_array_value_begin_pointer=_dynamic_array_equal_rvalue._dynamic_array_value_begin_pointer;
        _dynamic_array_size=_dynamic_array_equal_rvalue._dynamic_array_size;
        _original_type_value=_dynamic_array_equal_rvalue._original_type_value;
        _dynamic_array_equal_rvalue._dynamic_array_value_begin_pointer=NULL;
        _dynamic_array_greatest_visit_subscript=_dynamic_array_equal_rvalue._dynamic_array_greatest_visit_subscript;
        return *this;
    }
    _dynamic_array_typename read(size_t _dynamic_array_visit_subscript)const{return _dynamic_array_visit_subscript>=_dynamic_array_size?0:*(_dynamic_array_value_begin_pointer+_dynamic_array_visit_subscript);}
    _dynamic_array_typename* begin()const{return _dynamic_array_value_begin_pointer;}
    _dynamic_array_typename* rbegin()const{return _dynamic_array_value_begin_pointer+_dynamic_array_greatest_visit_subscript-1;}
    size_t size()const{return _dynamic_array_greatest_visit_subscript;}
    _dynamic_array_typename* end()const{return _dynamic_array_value_begin_pointer+_dynamic_array_greatest_visit_subscript;}
    _dynamic_array_typename* rend()const{return _dynamic_array_value_begin_pointer-1;}
    size_t useable_size()const{return _dynamic_array_size;}
    void push(_dynamic_array_typename _dynamic_push_back_input){operator[](_dynamic_array_greatest_visit_subscript)=_dynamic_push_back_input;}
    _dynamic_array_typename& top(){return operator[](_dynamic_array_greatest_visit_subscript-1);}
    void pop(){if(!_dynamic_array_greatest_visit_subscript) std::cerr<<already_empty_warning; else _dynamic_array_greatest_visit_subscript--;}
    bool empty(){return !_dynamic_array_greatest_visit_subscript;}
};
#endif
