/*
 * Copyright (c) 2019, Dhami's
 * Copyright 2019
 */

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

    int value = 0;
    int pos = 0;
    uint32_t size = 0;
    int key = 0;
    switch (ops) {
    case PUSH_BACK:
      std::cout << "Enter Value : ";
      std::cin >> value;
      status = stl_intf[container_type]->Push_back(value);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }
      break;

    case INSERT:

      if (container_type == ORDERED_MAP) {
        std::cout << "Enter Key : ";
        std::cin >> key;
      }
      std::cout << "Enter Value : ";
      std::cin >> value;

      if (container_type == VECTOR) {
        std::cout << "Enter Pos : ";
        std::cin >> pos;
      }
      Value_s val;
      val.key = key;
      val.value = value;
      status = stl_intf[container_type]->Insert(pos, &val);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }
      break;

    case TRAVERSE:
      status = stl_intf[container_type]->Traverse();
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }
      break;

    case ERASE:
      std::cout << "Enter Pos : ";
      std::cin >> pos;
      status = stl_intf[container_type]->Erase(pos);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }
      break;

    case CLEAR:
      status = stl_intf[container_type]->Clear();
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }
      break;

    case SIZE:

      status = stl_intf[container_type]->Size(size);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
      }

      LOG("Size = %d", size);
      break;

    case FIND:
      if (container_type == ORDERED_MAP) {
        std::cout << "Enter Key : ";
      } else {
        std::cout << "Enter Value : ";
      }

      std::cin >> value;
      status = stl_intf[container_type]->Find(value);
      if (status != SUCCESS) {
        LOG("Failed operation %d \n", ops);
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
