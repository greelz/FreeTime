// A hashmap is composed of <K, V, F>, with key, value, and hashing function
//
// We should create hash nodes which a hash map will accept
//
#include <stdlib.h>
#include <string>
#include <iostream>

static const int TABLE_SIZE = 128;

template <class K, class V>
class HashNode 
{

public:
    HashNode(const K& key, const V& value) :
        key(key), value(value), next(NULL) { }

    K get_key() const { return key; }
    V get_value() const { return value; }

    void set_value(const V& value)
    {
        HashNode::value = value;
    }

    HashNode *get_next() const
    {
        return next;
    }

    void set_next(HashNode *next)
    {
        HashNode::next = next;
    }

private:
    K key;
    V value;
    // Pointer to the next node with the same key
    HashNode *next;
};


template <class K>
struct KeyHash
{
    unsigned long operator()(const K& key) const 
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};



// A hash map class contains a hash table (**) and 
// get(key), put(key, value), remove(key)

template <class K, class V, class F = KeyHash<K> >
class HashMap 
{

public:
    HashMap()
    {
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode<K, V> *row = table[i];
            while (row != NULL)
            {
                HashNode<K, V> *current_node = row;
                row = row->get_next();
                delete current_node;
            }
            table[i] = NULL;
        }

        delete [] table;
    }
    

    bool get(const K &key, V &value)
    {
        unsigned long hash_value = hash_function(key);
        HashNode<K, V> *row = table[hash_value];

        while (row != NULL)
        {
            if (row->get_key() == key)
            {
                value = row->get_value();
                return true;
            }
            row = row->get_next();
        }
        return false;
    }

    void put(const K &key, const V &value)
    {
        unsigned long hash_value = hash_function(key);
        
        // Iterate until we are at a free node in the hash function
        HashNode<K, V> *row = table[hash_value];
        HashNode<K, V> *current_node = NULL;

        while (row != NULL && row->get_key() != key)
        {
            current_node = row;
            row = row->get_next();
        }

        // Either we are overwriting a value, or we are inserting a new HashNode
        // If row == NULL, insert a new one
        if (row == NULL)
        {
            HashNode<K, V> *new_node = new HashNode<K, V>(key, value);
            // Check to see if we're in a new bucket, or if we should
            // link the previous node
            if (current_node == NULL)
            {
                table[hash_value] = new_node;
            }
            else
            {
                current_node->set_next(new_node);
            }
        }
        else
        {
            // Update the value
            row->set_value(value);
        }
    }

    // To remove a key, get the hash_func and iterate until we find the key
    void remove(const K &key)
    {
        unsigned long hash_value = hash_function(key);
        HashNode<K, V> *row = table[hash_value];
        HashNode<K, V> *previous = NULL;

        while (row != NULL && row->get_key() != key)
        {
            previous = row;
            row = row->get_next();
        }
        
        // Key wasn't found
        if (row == NULL) 
        {
            return;
        }
        else
        {
            // Key was found
            // To delete the key:
            // 1. It's in it's own bucket
            // 2. It's not 

            if (previous == NULL)
            {
                table[hash_value] = row->get_next();
            }
            else 
            {
                previous->set_next(row->get_next());
            }
            delete row;
        }

    }

private:
    HashNode<K, V> **table;
    F hash_function;
};



struct MyKeyHash
{
    unsigned long operator()(const std::string &key) const
    {
        return key[0] * '0';
    }
};


int main()
{

    HashMap<std::string, std::string, MyKeyHash> hash_map;

    hash_map.put("hello", "tim");
    std::string value;
    if (hash_map.get("hello", value))
        std::cout << value;
    hash_map.put("this", "testing, one, two, three");
    return 0;
}



