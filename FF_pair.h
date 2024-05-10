#ifndef FF_PAIR_H
#define FF_PAIR_H
template<typename first_typename,typename second_typename>
struct FF_pair{
    first_typename first;
    second_typename second;
    FF_pair(){}
    FF_pair(const first_typename& init_first,const second_typename& init_second){first=init_first;second=init_second;}
    FF_pair(const FF_pair& other_value){first=other_value.first;second=other_value.second;};
    bool operator==(const FF_pair& other_value)const{return first==other_value.first&&second==other_value.second;}
    bool operator!=(const FF_pair& other_value)const{return first!=other_value.first||second!=other_value.second;}
    bool operator>(const FF_pair& other_value)const{return first>other_value.first||(first==other_value.first&&second>other_value.second);}
    bool operator<(const FF_pair& other_value)const{return first<other_value.first||(first==other_value.first&&second<other_value.second);}
    bool operator>=(const FF_pair& other_value)const{return first>other_value.first||(first==other_value.first&&second>=other_value.second);}
    bool operator<=(const FF_pair& other_value)const{return first<other_value.first||(first==other_value.first&&second<=other_value.second);}
};
#endif
