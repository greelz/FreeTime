// Example of the simplest types of graphs
// A singly-linked list 
//
//


#include <iostream>

template <class T>
class LinkedList
{

public:
    void addNode(T element)
    {
        Node *temp = new Node;
        temp->value = element;
        temp->next = NULL;
        
        if (head == NULL)
        {
            head = temp;
        }
        else 
        {
            end->next = temp;
        }
        end = temp;
    };

    void deleteNodesOfValue(T element)
    {
        // First need to check if head node is bad
        Node *temp = head, Node *next = NULL;
        while (temp != NULL)
        {
            if (temp->value == element)
            {
                // We need to delete this node, and update the pointers
                if (temp == head)
                {
                    head = NULL;
                    end = NULL;
                    delete temp;
                }
                else 
                {
                    

                }

    }


    friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& linkedList)
    {
        Node *temp = linkedList.head;
        while (temp != NULL)
        {
            out << temp->value << std::endl;
            temp = temp->next;
        }
        return out;
    }


    

private:
    struct Node
    {
        T value;
        Node *next;
    };
    Node *head = NULL;
    Node *end = NULL;

};

int main()
{
    LinkedList<int> ll;

    ll.addNode(4);
    ll.addNode(5);
    ll.addNode(6);

    std::cout << ll << std::endl;
    return 0;
}

