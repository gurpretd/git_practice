#include <iostream>
#include "stl_interface.h"
#ifndef __STL_WRAPPER__
#define __STL_WRAPPER__ 
class stl_wrapper { 

public :
Error Create(Type type, STL_Interface ** intf);
Error Destroy(Type type);
stl_wrapper();
private :
    STL_Interface *handles_[MAX_TYPES];

};

#endif
