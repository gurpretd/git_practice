// C++ program to demonstrate shared_ptr
#include<iostream>
#include<memory>
using namespace std;
 
class A
{
public:
    void show()
    {
        cout<<"A::show()"<<endl;
    }


	~A()
		{
		cout << "Destructor";
		}
};
 
int main()
{


// Shared Pointer 
# if 0
    shared_ptr<A> p1 (new A);
    cout << p1.get() << endl;
    p1->show();
	cout << "p1 usecount  " << p1.use_count() << endl;
	

	shared_ptr<A> p2;

	p2 = p1;
    p2->show();
    cout << p1.get() << endl;
    cout << p2.get() << endl;
 
    // Returns the number of shared_ptr objects
    //referring to the same managed object.
    cout << "p1 usecount  " << p1.use_count() << endl;
    cout << "p2 usecount  " <<p2.use_count() << endl;
 
    // Relinquishes ownership of p1 on the object
    //and pointer becomes NULL
    p1.reset();
    
    cout << "Reset \n P1.get " << p1.get() << endl;
   
    cout << "p1 usecount  " << p1.use_count() << endl;
    cout << "p2 usecount  " <<p2.use_count() << endl;
    cout << " P2.get " << p2.get() << endl;
    p2.reset();

#endif

    unique_ptr<A> p1 (new A);
    p1->show();

	unique_ptr<A> p2  = move(p1);

    p2->show();
    cout << p1.get() << endl;
    cout << p2.get() << endl;
 
    p2.reset();





    cout << " Finish "; 
    return 0;
}

