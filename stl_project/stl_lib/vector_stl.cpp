#include "vector_stl.h"

using namespace std;
#define __CLASS__ "vector_stl"
Error vector_stl::Insert(uint32_t pos, uint32_t val) {
  LOG_BEGIN;
  vec.insert(vec.begin() + pos, val);

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

  for (it = vec.begin(); it < vec.end(); it++) {
    if (*it == val)
      break;
  }

  if (it == vec.end())
    return FAIL;

  LOG("Found at %d ", std::distance(vec.begin(), it));
  return SUCCESS;
}

Error vector_stl::Clear(void) {
  vec.clear();
  return SUCCESS;
}
