/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */

#include <map>
#include "stl_interface.h"

#ifndef __MAP_STL_H__
#define __MAP_STL_H__

class map_stl : public STL_Interface {

  virtual Error Insert(uint32_t pos, void *val);
  virtual Error Push_back(uint32_t val);
  virtual Error Traverse();
  virtual Error Erase(uint32_t pos);
  virtual Error Size(uint32_t &size);
  virtual Error Find(uint32_t val);
  virtual Error Clear(void);

private:
  std::map<uint32_t, uint32_t> map_handle;
};
#endif  // __MAP_STL_H__

