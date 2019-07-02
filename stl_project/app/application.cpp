#include <stl_interface.h>
#include <stl_wrapper.h>

#define __CLASS__ "Application"
int main() {
  unsigned int container_type;
  STL_Interface *stl_intf[MAX_TYPES];
  unsigned int ops;
  stl_wrapper stl_obj;
  Error status = FAIL;

  for (int i = 0; i < MAX_TYPES; i++)
    stl_intf[i] = nullptr;

  while (1) {
  STEP1:
    std::cout << std::endl
              << "Choose a container for operation. [999 for exit]";
    stl_obj.print_container_menu();
    std::cout << std::endl << "Enter : ";
    std::cin >> container_type;

    if (container_type == 999) {
      LOG("Invalid container type %d", container_type);
      break;
    }

    if (container_type >= MAX_TYPES) {
      LOG("Invalid container type %d", container_type);
      continue;
    }

    if (stl_intf[container_type] == nullptr) {
      status = stl_obj.Create(static_cast<Type>(container_type),
                              &stl_intf[container_type]);
      if (status != SUCCESS) {
        LOG("Failed to create client %d ", container_type);
        continue;
      }
    }

  STEP2:
    std::cout << "Choose an operation [999 for exit]";
    stl_obj.print_ops_menu();
    std::cout << std::endl << "Enter : ";
    std::cin >> ops;
    if (ops == 999) {
      goto STEP1;
    }

    if (ops >= MAX_OPS) {
      LOG("Invalid ops  %d", ops);
      continue;
    }

    int value;
    int pos;
    uint32_t size;

    switch (ops) {

    case PUSH_BACK:
      std::cout << "Enter Value : ";
      std::cin >> value;
      status = stl_intf[container_type]->Push_back(value);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    case INSERT:
      std::cout << "Enter Value : ";
      std::cin >> value;
      std::cout << "Enter Pos : ";
      std::cin >> pos;
      status = stl_intf[container_type]->Insert(pos, value);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    case TRAVERSE:
      status = stl_intf[container_type]->Traverse();
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    case ERASE:
      std::cout << "Enter Pos : ";
      std::cin >> pos;
      status = stl_intf[container_type]->Erase(pos);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    case CLEAR:
      status = stl_intf[container_type]->Clear();
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    case SIZE:

      status = stl_intf[container_type]->Size(size);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }

      LOG("Size = %d", size);
      break;

    case FIND:

      std::cout << "Enter Value : ";
      std::cin >> value;
      status = stl_intf[container_type]->Find(value);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
        continue;
      }
      break;

    default:
      LOG(" Invalid Op", ops);
      break;
    }

    goto STEP2;
  }
  return 0;
}
