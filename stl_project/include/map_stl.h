#include <map>
#include "stl_interface.h"

#ifndef __MAP_STL__
#define __MAP_STL__ 

class map_stl: public STL_Interface { 

virtual Error Insert(int pos, void *val);
virtual Error Traverse();

private:
std::map <int,int> map;
};
#endif
