/*  Objectives : 
- Create a vector of ints of size 10. Sort it . Print it. Print 5th the element
- Create a vector of string. Same as above.
- Traversing vector using iterator
*/


#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;
void forintegers();
void forstrings();
int main()
{

forstrings();
forintegers();
}

void forstrings()
{

  vector <string> vec;
  for(int i = 0 ; i<10; i ++) {
  string p;
  cout << "Enter string " << i << endl;
  cin >> p;
  vec.push_back(p);
}
for (int i=0; i<10; i++){
  cout << "vec " << "=" <<vec.at(i) <<endl;
}
cout << "vec at 5  = " <<vec.at(5) << "or " <<vec[5];



for (vector<string>::iterator it = vec.begin(); it!=vec.end(); it++) {
    cout << *it << endl;
}

}
void forintegers()
{
  return;
  vector <int> vec;
  for(int i = 0 ; i<10; i ++) {
  int p;
  cout << "Enter number " << i << endl;
  cin >> p;
  vec.push_back(p);
}
for (int i=0; i<10; i++){
  cout << "vec " << "=" <<vec.at(i) <<endl;

cout << "vec at 5  = " <<vec.at(5) << "or " <<vec[5];

}
}

