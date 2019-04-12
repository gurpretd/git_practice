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
void print_vector(vector <int> vec);
int main()
{

forintegers();
}




void forintegers()
{
  int num=0;
  vector <int> vec;

  while(true) { 
	  cout << "Enter number ";
      cin >> num;
	  vec.push_back(num);
      cout << "Do you want to enter another number y/n? ";
	  char c;
	  cin>>c;

	  if(c == 'y')
			continue;
	  else
            break;		  
	  
  }
  print_vector(vec);


  vec.insert(vec.begin()+2,5,444);

  print_vector(vec);

vector <int> vec2(vec);


 print_vector(vec2);
 
//vec2.insert(vec.begin(),vec.begin(),vec.end());

}
void print_vector(vector <int> vec)
{
	 cout << "capacity "<< vec.capacity()  << "max size" << vec.max_size() << endl;
 
	for (int i=0; i<vec.size(); i++){
		cout << "vec " << "=" <<vec.at(i) <<endl;

	}
	cout << "END" << endl;
}



