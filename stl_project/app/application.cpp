#include <iostream>
#include <stl_interface.h>
#include <stl_wrapper.h>
using namespace std;
int main()
{
    Error Status = FAIL;
    stl_wrapper stl_obj;
    Type type = VECTOR;
    STL_Interface *intfs[MAX_TYPES];
    intfs[type] = nullptr;
    stl_obj.Create(type, &intfs[type]);
    if(intfs[type] != nullptr)
        cout << "Initialized Successfully" << endl;
    else
        cout << "Not Initialized Successfully" << endl;
    int a=10;
    intfs[type]->Insert(0, (void *)&a);
    stl_obj.Destroy(type);


    

   type = ORDERED_MAP;
  stl_obj.Create(type, &intfs[type]);
  if(intfs[type] != nullptr)
      cout << "Initialized Successfully" << endl;
  else
      cout << "Not Initialized Successfully" << endl;
  intfs[type]->Insert(0, (void *)&a);
  stl_obj.Destroy(type);


  //  stl_obj.print_info(10);
    return 0;

}






























