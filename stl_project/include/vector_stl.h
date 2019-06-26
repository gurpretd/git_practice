#include <vector>
#include "stl_interface.h"

#ifndef __VECTOR_STL__
#define __VECTOR_STL__ 

class vector_stl: public STL_Interface { 

virtual Error Insert(int pos, void *val);
virtual Error Traverse();

private:
std::vector <int> vec;
};
#endif
