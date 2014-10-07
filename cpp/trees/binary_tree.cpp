#include <stdlib.h>
#include <iostream>


template <class T>
struct BinaryNode
{
    BinaryNode *left;
    BinaryNode *right;
    T value;
};


template <class T>
class btree
{

public:
    btree()
    {
        root = NULL;
    }
    void insert(const T item)
    {
        if (root == NULL)
        {
            root = new BinaryNode<T>;
            root->value = item;
            root->left = NULL;
            root->right = NULL;
        }
        else
        {
            insert(root, item);
        }

    }


    void inordertraverse()
    {
        inordertraverse(root);
    }
    void preordertraverse()
    {
        preordertraverse(root);
    }
    void postordertraverse()
    {
        postordertraverse(root);
    }



private:
    BinaryNode<T> *root;


    void inordertraverse(BinaryNode<T> *node)
    {
        if (node)
        {
            inordertraverse(node->left);
            std::cout << node->value << " ";
            inordertraverse(node->right);

        }
    }


    void preordertraverse(BinaryNode<T> *node)
    {
        if (node)
        {
            std::cout << node->value << " ";
            preordertraverse(node->left);
            preordertraverse(node->right);
        }
    }

    void postordertraverse(BinaryNode<T> *node)
    {
        if (node) 
        {
            postordertraverse(node->left);
            postordertraverse(node->right);
            std::cout << node->value << " ";
        }
    }

    void insert(BinaryNode<T> *current, const T item)
    {
        if (item < current->value)
        {
            if (current->left == NULL)
            {
                BinaryNode<T> *new_node = new BinaryNode<T>;
                new_node->value = item;
                new_node->right = NULL;
                new_node->left = NULL;
                current->left = new_node;
            }
            else
            {
                insert(current->left, item);
            }
        }
        else
        {
            if (current->right == NULL)
            {
                BinaryNode<T> *new_node = new BinaryNode<T>;
                new_node->value = item;
                new_node->right = NULL;
                new_node->left = NULL;
                current->right = new_node;
            }
            else
            {
                insert(current->right, item);
            }
        }
    }

};


int main() 
{
    // A binary tree looks like this:
    //               6
    //            4     8
    //          2  5   7  10
    // 
    // The root node 

    btree<int> my_tree;

    // This is dumb, because the tree doesn't re-order itself.
    // It will end up looking like this:
    //     0
    //       1
    //         2
    //           3
    //             4
    //               .
    //               .
    //               .
    //               .
    //                 1000
    for (int i = 0; i < 1000; ++i)
    {
        my_tree.insert(i);
    }

}

