#include <iostream>

using namespace std;


class linklist {

int add_node(int value);
int show_list();
class linklinst *head;
private :
        int data;
        class linklist *next;

};

int linklist::show_list() {

    class linklist *temp = head;
    while(temp != nullptr)
    {

        cout << temp->data << endl;
        temp = temp->next;
    }
}

int add_node( int value) {

    class linklinst *node = new linklist();
    node->data = value;
    class linklist *temp = head;
    while(temp != nullptr)
    {


}

main()
{

    class linklist *head;

    add_node(10);
    show_list();


    return 0;

}