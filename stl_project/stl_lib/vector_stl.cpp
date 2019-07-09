/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */

#include <vector>
#include <algorithm>
#include "vector_stl.h"

#define __CLASS__ "vector_stl"
Error vector_stl::Insert(uint32_t pos, void *val) {
  LOG_BEGIN;
  Value_s *value = nullptr;
  if (val == nullptr) {
    std::cout << "Insert Failure ";
    return FAIL;
  }
  value = static_cast<Value_s *>(val);
  std::cout << " Value  = " << value->value;
  vec.insert(vec.begin() + pos, value->value);

  LOG_END;
  return SUCCESS;
}

Error vector_stl::Push_back(uint32_t val) {
  vec.push_back(val);
  return SUCCESS;
}

Error vector_stl::Traverse() {
  std::vector<int>::iterator it;
  int i = 0;
  for (it = vec.begin(); it < vec.end(); it++) {
    i++;
    LOG("Element[%d] = %d \n", i, *it);
  }

  return SUCCESS;
}

Error vector_stl::Erase(uint32_t pos) {
  vec.erase(vec.begin() + pos);
  return SUCCESS;
}

Error vector_stl::Size(uint32_t &size) {
  LOG_BEGIN;
  size = vec.size();

  return SUCCESS;
}

Error vector_stl::Find(uint32_t val) {
  std::vector<int>::iterator it;
// std:vector does not provide any direct function find.
  it = std::find(vec.begin(), vec.end(), val);
  if (it == vec.end())
    return FAIL;

  LOG("Found at %d ", std::distance(vec.begin(), it));
  return SUCCESS;
}

Error vector_stl::Clear(void) {
  vec.clear();
  return SUCCESS;
}
