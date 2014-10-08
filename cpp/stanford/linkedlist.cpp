#include <iostream>

template <class T>
class LinkedList
{

public:
    LinkedList();
    void push_back(const T &value)
    {
        if (head == NULL)
        {
            head = new _node;
            head->value = value;
        }


private: 
    struct _node
    {
        T value;
        _node *next;
    };

    _node *head = NULL;

    &_node getLastElement()
    {
        

};


int main()
{
    LinkedList x;
    return 0;
}
