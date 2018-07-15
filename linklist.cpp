#include <iostream>
#include <cstdlib>

using namespace std;

struct node{
    int data;
    struct node * next;
};



class LinkedList
{
    node* head;
public:
    LinkedList() {
        head = nullptr;
        cout << "constructor" <<endl;
    }

    void add_node(int value)
    {
        node *temp = new node;
        temp->data = value;
        temp->next = nullptr;

        if(head == nullptr) {
            head = temp;
        }else {
            node *temp1 = head;
            while (temp1->next != nullptr) {
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }

    }

    void show_list(){

        node * temp = this->head;

        while(temp != nullptr) {
            std::cout << temp->data <<endl;
            temp = temp->next;
        }


    }
    LinkedList operator+(const LinkedList& b) {

        LinkedList c;
        node * temp = this->head;

        while(temp->next!= nullptr) {
            temp = temp->next;
        }

        temp->next = b.head;
        c.head = this->head;
        return c;
    }
};


int main(int argc, char const *argv[])
{

    LinkedList a,  b, c;
    a.add_node(10);
    b.add_node(20);
    a.show_list();
    b.show_list();
    c = a + b;

    c.show_list();

    return 0;
}