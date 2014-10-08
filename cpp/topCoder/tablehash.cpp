#include <string>
#include <iostream>


template <class K, class V>
struct HashNode
{
    K key;
    V value;
    HashNode next[];
};


int hashing_function(const std::string &key)
{
    return key[0] * '0';
}


int main()
{
    HashNode<std::string, int> phone_numbers[];
    

}
