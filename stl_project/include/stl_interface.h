/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */


#ifndef __STL_INTERFACE__
#define __STL_INTERFACE__

#define FAIL 1
#define SUCCESS 0

#include <iostream>
typedef unsigned int uint32_t;
typedef unsigned int Error;
typedef struct Value {
  int key;
  int value;
} Value_s;

#define LOG_BEGIN printf(" %s BEGIN ", __FUNCTION__);
#define LOG_END printf(" %s END ", __FUNCTION__);

#define LOG(format, ...)                                                       \
  printf(" %s::%s:: " format, __CLASS__, __FUNCTION__, __VA_ARGS__);

class STL_Interface {

public:
  virtual Error Insert(uint32_t pos, void *val) = 0;
  virtual Error Push_back(uint32_t val) = 0;
  virtual Error Traverse(void) = 0;
  virtual Error Erase(uint32_t pos) = 0;
  virtual Error Size(uint32_t &size) = 0;
  virtual Error Find(uint32_t val) = 0;
  virtual Error Clear(void) = 0;
};

#endif
