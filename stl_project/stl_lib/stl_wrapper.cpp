#include <iostream>
#include "stl_wrapper.h"
#include "vector_stl.h"
#include "map_stl.h"
using namespace std;

Error stl_wrapper::Create(Type type, STL_Interface **intf)
{
  Error Status = FAIL;

  if(handles_[type] != nullptr) {
      cout << "Already Allocated" << "type " << type << endl;
      return FAIL;
  }

  if(type == VECTOR) {
    cout << "Creating Vector " << endl;
    handles_[type] = new vector_stl();
  } else if(type == ORDERED_MAP) { 
      cout << "Creating Map " << endl;

    handles_[type] = new map_stl();

  }
  *intf = handles_[type];

   return Status;
}

Error stl_wrapper::Destroy(Type type)
{
cout << "Destroy no op";
}

stl_wrapper::stl_wrapper() { 
  std::cout << "ctor stl_wrapper";
  for(int i=0 ; i< MAX_TYPES ; i ++) { 
    handles_[i]=nullptr;
  }
}
