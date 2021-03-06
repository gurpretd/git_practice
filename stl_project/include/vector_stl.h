/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */

#include <vector>
#include "stl_interface.h"

#ifndef __VECTOR_STL__
#define __VECTOR_STL__

class vector_stl : public STL_Interface {

  virtual Error Insert(uint32_t pos, void *val);
  virtual Error Push_back(uint32_t val);
  virtual Error Traverse(void);
  virtual Error Erase(uint32_t pos);
  virtual Error Size(uint32_t &size);
  virtual Error Find(uint32_t val);
  virtual Error Clear(void);

private:
  std::vector<int> vec;
};
#endif
