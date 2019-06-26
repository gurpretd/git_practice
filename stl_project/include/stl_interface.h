#ifndef __STL_INTERFACE__
#define __STL_INTERFACE__

#define FAIL 1
#define SUCCESS 0

#include <iostream>

typedef unsigned int Error;


enum Type { 
VECTOR,
ORDERED_MAP,
UNORDERED_MAP,
MAX_TYPES

};

class STL_Interface { 

public :
    virtual Error Insert(int pos, void *val) = 0;
    virtual Error Traverse() = 0;

};

#endif
