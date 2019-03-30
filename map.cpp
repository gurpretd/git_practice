/*  Objectives : 
- Create a map of <int,int> Sort it . Print it. Print 5th the element
- Create a map of <int,string>. Same as above.
- Traversing map using iterator
*/


#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <map>
#include <bits/stdc++.h> 
using namespace std;
void forintegers();
void forstrings();
int main()
{

forstrings();
//forintegers();
}

void forstrings()
{
  map <int,string> m;
  int size;
  cout << "enter size";
  cin >> size;
  for(int i = 0 ; i<size; i++) {
  int p;
  string p1;
  cout << "Enter number " << i << endl;
  cin >> p;
  cin >> p1;
  cout << " entered  " <<p << "  " << p1 <<endl;
  m.insert(std::pair<int,string>( p,p1));

  } 
std::map<int,string>::iterator itr;

cout << "size of map " << m.size()<< endl;
for (itr = m.begin(); itr != m.end(); ++itr){
  cout << "map " << "=" <<itr->first <<" \t " << itr->second  << endl;


}
}
void forintegers()
{
  
  map <int,int> m;
  int size;
  cout << "enter size";
  cin >> size;
  for(int i = 0 ; i<size; i++) {
  int p,p1;
  cout << "Enter number " << i << endl;
  cin >> p;
  cin >> p1;
  cout << " entered  " <<p << "  " << p1 <<endl;
  m.insert(std::pair<int,int>( p,p1));
}
std::map<int,int>::iterator itr;

cout << "size of map " << m.size()<< endl;
for (itr = m.begin(); itr != m.end(); ++itr){
  cout << "map " << "=" <<itr->first <<" \t " << itr->second  << endl;
}

}


