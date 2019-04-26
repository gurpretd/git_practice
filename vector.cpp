/*  Objectives :

- Practice
*/

#include <iostream>
#include <vector>

using namespace std;
class vector_practice {
private:
  vector<int> vec;

public:
  void vec_add(void);
  void vec_list(void);
  void vec_insert();
  // void vec_assign();
  // void vec_push_back();
  // void vec_emplace_back();
  // void vec_erase();
  // void vec_clear();
};

void vector_practice::vec_add(void) {
  int num;
  while (1) {
    cout << "insert elements" << endl;
    cin >> num;

    if (num == 0)
      break;

    vec.push_back(num);
  }
}

void vector_practice::vec_list(void) {
  cout << "******** List is ****** " << endl;
  for (int i = 0; i < vec.size(); i++)
    cout << vec.at(i) << endl;
}
void vector_practice::vec_insert(void) {
  int pos, value;
  cout << "Enter position to insert between 0 and " << vec.size() << endl;
  cin >> pos;
  cout << "Enter value";
  cin >> value;

  vec.insert(vec.begin() + pos, value);
}
int main() {

  vector_practice vec_practice;
  int choice;
  while (1) {
    cout << "choose option " << endl;
    cout << "1 "
         << "Add elements with push_back" << endl;
    cout << "2 "
         << "Add elements with insert" << endl;

    cout << "3 "
         << "List Elements" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
      vec_practice.vec_add();
      break;

    case 2:

      vec_practice.vec_insert();
      break;

    case 3:
      vec_practice.vec_list();
      break;
    }
  }
  return 1;
}
