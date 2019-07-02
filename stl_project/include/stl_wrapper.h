#include "stl_interface.h"
#include <iostream>
#ifndef __STL_WRAPPER__
#define __STL_WRAPPER__

enum Type { VECTOR, ORDERED_MAP, UNORDERED_MAP, MAX_TYPES };

enum Operations {
  PUSH_BACK,
  INSERT,
  TRAVERSE,
  ERASE,
  CLEAR,
  FIND,
  SIZE,
  MAX_OPS
};

class stl_wrapper {

public:
  Error Create(Type type, STL_Interface **intf);
  Error Destroy(Type type);
  void print_ops_menu();
  void print_container_menu();

  stl_wrapper() {
    std::cout << "ctor stl_wrapper";
    for (int i = 0; i < MAX_TYPES; i++) {
      handles_[i] = nullptr;
    }
  }

private:
  STL_Interface *handles_[MAX_TYPES];
};

#endif
