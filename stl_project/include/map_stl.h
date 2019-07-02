#include "stl_interface.h"
#include <map>

#ifndef __MAP_STL__
#define __MAP_STL__

class map_stl : public STL_Interface {

  virtual Error Insert(uint32_t pos, uint32_t val);
  virtual Error Push_back(uint32_t val);
  virtual Error Traverse();
  virtual Error Erase(uint32_t pos);
  virtual Error Size(uint32_t &size);
  virtual Error Find(uint32_t val);
  virtual Error Clear(void);

private:
  std::map<int, int> map;
};
#endif
