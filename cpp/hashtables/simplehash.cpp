#include <string>
#include <iostream>
#include <stdlib.h>

// This file implements a simple hash table
// A hash table should have O(1) get, insert, and remove
// In this example, let's store information about people

struct Person
{
    std::string name;
    std::string phone;
    Person *next;
};

class PersonTable
{
public:
    PersonTable(int size)
    {
        PersonTable::TABLE_SIZE = size;
        table = new Person*[TABLE_SIZE];
    }

    int get_table_size() { return TABLE_SIZE; }

    void put(const std::string &name, const std::string &phone)
    {
        int hash_value = hashing_function(name);
        Person *bucket = table[hash_value];
        Person *previous = NULL;
        
        while (bucket != NULL && bucket->name != name)
        {
            previous = bucket;
            bucket = bucket->next;
        }
        // If there's no previous, then it's in its own bucket
        if (previous == NULL)
        {
            bucket = new Person;
            bucket->name = name;
            bucket->phone = phone;
            bucket->next = NULL;
            table[hash_value] = bucket;
        }
        else
        {
            // Either we need to overwrite, or insert the node
            // We will overwrite if bucket->name == name
            if (bucket->name == name)
            {
                bucket->phone = phone;
            }
            else
            {
                bucket = new Person;
                bucket->name = name;
                bucket->phone = phone;
                bucket->next = NULL;
                previous->next = bucket;
            }
        }
    }

    bool get(const std::string &name, std::string &out)
    {
        Person *bucket = table[hashing_function(name)];
        if (bucket == NULL)
        {
            return false;
        }
        else 
        {
            while (bucket != NULL && bucket->name != name)
            {
                bucket = bucket->next;
            }
            if (bucket == NULL)
            {
                return false;
            }
            else 
            {
                out = bucket->phone;
                return true;
            }
        }
    }
    

private:
    int TABLE_SIZE;
    Person **table;
    int hashing_function(const std::string &key)
    {
        return (91 * key[0] * '0') % TABLE_SIZE;
    }

};



int main()
{
    PersonTable p(100);    
    p.put("jim", "9894888470");
    std::string number;
    p.get("jim", number);
    std::cout << number << std::endl;

    p.put("jim", "234234");
    p.get("jim", number);
    std::cout << number << std::endl;
    
    return 0;
}

