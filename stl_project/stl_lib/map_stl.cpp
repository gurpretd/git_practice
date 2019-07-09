/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */
#include <map>
#include <utility>
#include "map_stl.h"

#define __CLASS__ "map_stl"
Error map_stl::Insert(uint32_t pos, void *val) {
  LOG_BEGIN;
  Value_s *value = nullptr;
  if (val == nullptr) {
    std::cout << "Insert Failure ";
    return FAIL;
  }
  value = static_cast<Value_s *>(val);
  std::cout << " Value  = " << value->value;
  std::pair<uint32_t, uint32_t> map_pair(value->key, value->value);
  map_handle.insert(map_pair);

  LOG_END;

  return SUCCESS;
}

Error map_stl::Push_back(uint32_t val) {
  LOG_BEGIN;
  LOG_END;
  return FAIL;
}

Error map_stl::Traverse() {
  LOG_BEGIN;

  std::map<uint32_t, uint32_t>::iterator itr;
  LOG(" List %s \n", "");
  for (itr = map_handle.begin(); itr != map_handle.end(); itr++) {
    LOG(" first = %d second = %d \n", itr->first, itr->second);
  }
  LOG_END;
  return SUCCESS;
}

Error map_stl::Erase(uint32_t pos) {
  LOG_BEGIN;

  LOG_END;
  return SUCCESS;
}

Error map_stl::Size(uint32_t &size) {
  LOG_BEGIN;

  LOG_END;

  return SUCCESS;
}

Error map_stl::Find(uint32_t val) {
  LOG_BEGIN;
  std::map<uint32_t, uint32_t>::iterator it;

  it = map_handle.find(val);
  if (it == map_handle.end())
    return FAIL;

  LOG("Found at %d ", std::distance(map_handle.begin(), it));

  LOG_END;
  return SUCCESS;
}

Error map_stl::Clear(void) {
  LOG_BEGIN;

  LOG_END;
  return SUCCESS;
}
