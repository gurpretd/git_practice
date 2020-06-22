// C++ code to demonstrate the working of
// getline(), push_back() and pop_back()
#include<iostream>
#include<string> // for string class
using namespace std;

class Shape{
public:
    virtual void draw() = 0;
    
    public:
    string pattern = "";
    
};

class Rectangle: public Shape {
    virtual void draw() {
        cout << "Drawing Rectangle \n ";
    }
};

class Square: public Shape {
    virtual void draw() {
        cout << "Drawing Square \n";
    }
};

class Circle: public Shape {
    virtual void draw() {
        cout << "Drawing Circle \n";
    }
};

class Eclipse: public Shape {
    virtual void draw() {
        cout << "Drawing Eclipse \n";
    }
};


class AbstractFactory {

public:
    virtual Shape * create_circular_shape() = 0;
    
    virtual Shape * create_straigh_shape() = 0;
       
};


class SymmetricalShapeFactory : public AbstractFactory{
    

    Shape * create_circular_shape() {
        return new Circle;
    };
      
    Shape * create_straigh_shape() {
        return new Square;
    }
    
};

class UnSymmetricalShapeFactory : public AbstractFactory{
    
 
    Shape * create_circular_shape() {
         return new Eclipse;
    }
      
    Shape * create_straigh_shape() {
         return new Rectangle;
    }
      
    
};



int main()
{
    // Declaring string

    cout << "Abdtract Pattern \n";

// Create symmertical shapes
    
    AbstractFactory *factory1 = new SymmetricalShapeFactory();
   
    
    Shape * shape1 = factory1->create_circular_shape();
    shape1->draw();
    
    Shape * shape2 = factory1->create_straigh_shape();
    shape2->draw();
    
// create unsymmetrical shapes
    
    AbstractFactory *factory2 = new UnSymmetricalShapeFactory();

    Shape * shape3 = factory2->create_circular_shape();
    shape3->draw();

    Shape * shape4 = factory2->create_straigh_shape();
    shape4->draw();
    
    return 0;

} 
