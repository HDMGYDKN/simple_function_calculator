#ifndef DM_ARRAY
#define DM_ARRAY
#include <cstdarg>
#include <set>
#include <algorithm>
#include "dynamic_array.h"
#include "FF_pair.h"
template<typename dmarray_typename>
class dm_array{
private:
    dynamic_array<std::set<FF_pair<size_t,dmarray_typename>>> val;
    dynamic_array<dynamic_array<size_t>> have;
    dmarray_typename orival;
public:
    dm_array(){have[0]=dynamic_array<size_t>(0);}
    void set_original(dmarray_typename inp){orival=inp;}
    size_t insert(size_t dimension,dynamic_array<size_t> array_size){
        for(size_t i=0,end=array_size.size();i<end;i++)
            array_size[i+1]=array_size[i];
        array_size[0]=dimension;
        array_size.push(1);
        for(size_t i=dimension-1;i>0;i--)
            array_size[i]*=array_size[i+1];
        have.push(array_size);
        return have.size()-1;
    }
    dmarray_typename& at(size_t make,dynamic_array<size_t> pos){
        size_t size=have[make][0],visit=pos[0]*have[make][1];
        for(size_t i=2;i<=size;i++)
            visit+=pos[i-1]*have[make][i];
        auto check=val[visit].lower_bound(FF_pair<size_t,dmarray_typename>(make,orival));
        if(check->first==make&&val[visit].size())return *const_cast<dmarray_typename*>(&check->second);
        return *const_cast<dmarray_typename*>(&val[visit].insert(FF_pair<size_t,dmarray_typename>(make,orival)).first->second);
    }
};
#endif
