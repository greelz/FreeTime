#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>


// Brute force solution
int my_maximum(int number)
{
    // Set a vector of the values and sort it by max
    std::vector<int> values;

    // Grab values, one by one

    while (number > 0)
    {
        values.push_back(number % 10);
        number = number / 10;
    }


    std::sort(values.begin(), values.end());
    int return_value = 0, iteration = 0;
    for (std::vector<int>::iterator it = values.begin();
            it != values.end();
            ++it)
    {
        return_value += (*it) * pow(10, iteration);
        iteration++;
    }

    return return_value;
}



// Cooler solution?
int my_maximum_fast(int number)
{
    // Longest integer is 8 bits, which is 10 digits 
    int max_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while (number > 0)
    {
        max_array[number % 10]++;
        number = number / 10;
    }
    
    int return_number = 0, iterations = 0;
    for (int i = 0; i != 10; ++i)
    {
        for (int j = 0; j < max_array[i]; j++)
        {
            return_number += i * pow(10, iterations);
            iterations++;
        }
    }
    return return_number;

}
int main()
{
    std::vector<int> values; 
    int file_value;

    std::ifstream in ("random");
    if (in.is_open())
    {
        while (in.good())
        {
            in >> file_value;
            values.push_back(file_value);
        }
    }


    for (std::vector<int>::iterator it = values.begin();
            it != values.end();
            ++it)
    {
        my_maximum(*it);
    }

    
}
