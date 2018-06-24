#include<iostream>
using namespace std;
 
class Point
{
private:
    int x, y;
public:
    Point(int x1, int y1) { x = x1; y = y1; }
 
    // Copy constructor


	Point(const Point &P2){
    x = P2.x;
	y = P2.y;
	cout << "copy constructo";
	}

    Point()
	{
    	x = 0;
		y = 0;
		
    }

    int getX() { 
	return x;
    }
	int getY()
	{
		return y;
    }

	Point operator + (Point const &P2) {
    Point P3;
	P3.x = x + P2.x;
	P3.y = y + P2.y;
	cout << "operator  + ";
    return P3;
    }

Point  operator = (Point const &P2) {
    Point P3(1,2);
	x =  P2.x;
	y =  P2.y;
	cout << "\noperator = ";
    return P3;
    }
	
};
 
int main()
{
    Point p1(10, 15); // Normal constructor is called here
    Point p2 = p1; // Copy constructor is called here
    Point p3 = p1 + p2;
	Point p4;
    // Let us access values assigned by constructors
    cout << "p1.x = " << p1.getX() << ", p1.y = " << p1.getY();
    cout << "\np2.x = " << p2.getX() << ", p2.y = " << p2.getY();
    cout << "\np3.x = " << p3.getX() << ", p3.y = " << p3.getY();
	
	p4 = p1;
    cout << "\np4.x = " << p4.getX() << ", p4.y = " << p4.getY();
 
    return 0;
}

