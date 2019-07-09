/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */

#include <iostream>
#include "stl_wrapper.h"
#include "map_stl.h"
#include "vector_stl.h"

#define __CLASS__ "stl_wrapper"
Error stl_wrapper::Create(Type type, STL_Interface **intf) {
  Error Status = FAIL;
  LOG("create request for type : %d \n", type);
  if (handles_[type] != nullptr) {
    std::cout << "Already Allocated"
              << "type " << type << std::endl;
    return FAIL;
  }

  if (type == VECTOR) {
    std::cout << "Creating Vector " << std::endl;
    handles_[type] = new vector_stl();
  } else if (type == ORDERED_MAP) {
    std::cout << "Creating Map " << std::endl;
    handles_[type] = new map_stl();
  }

  *intf = handles_[type];
  return SUCCESS;
}

Error stl_wrapper::Destroy(Type type) { std::cout << "Destroy no op"; }

void stl_wrapper::print_ops_menu() {
  for (int i = PUSH_BACK; i < MAX_OPS; i++) {
    std::cout << std::endl << "Press " << i << " for";

    switch (i) {
    case PUSH_BACK:
      std::cout << " PUSH_BACK ";
      break;
    case INSERT:
      std::cout << " INSERT";
      break;
    case TRAVERSE:
      std::cout << " TRAVERSE";
      break;
    case CLEAR:
      std::cout << " CLEAR";
      break;
    case ERASE:
      std::cout << " ERASE";
      break;
    case FIND:
      std::cout << " FIND";
      break;
    case SIZE:
      std::cout << " SIZE ";
      break;
    defaut:
      std::cout << "*** ERROR -  Undefined OP *** ";
    }
  }
}

void stl_wrapper::print_container_menu() {
  for (int i = VECTOR; i < MAX_TYPES; i++) {
    std::cout << std::endl << "Press " << i << " for";
    switch (i) {
    case VECTOR:
      std::cout << " VECTOR ";
      break;
    case ORDERED_MAP:
      std::cout << " JUST/ORDERED MAP";
      break;
    case UNORDERED_MAP:
      std::cout << " UNORDERED MAP";
      break;
    defaut:
      std::cout << "*** ERROR -  Undefined Container *** ";
    }
  }
}
