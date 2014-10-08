#include <iostream>
#include <vector>


int main()
{
    int num_leaves, cin_variable = 0;
    std::vector<int> jump_numbers;

    std::cin >> num_leaves;
    bool eaten_leaves[num_leaves];
    for (int i = 0; i < num_leaves + 1; ++i)
    {
        eaten_leaves[i] = false;
    }

    while (std::cin >> cin_variable)
    {
        jump_numbers.push_back(cin_variable);
    }

    for (std::vector<int>::iterator it = jump_numbers.begin();
            it != jump_numbers.end();
            ++it)
    {
        int temp_jumper = *it;
        while (temp_jumper < num_leaves + 1)
        {
            eaten_leaves[temp_jumper] = true;
            temp_jumper += *it;
        }
    }

    int uneaten_leaves_count = 0;
    for (int i = 1; i < num_leaves + 1; ++i)
    {
        if (eaten_leaves[i] == false)
            uneaten_leaves_count++;
    }

    std::cout << uneaten_leaves_count << std::endl;

    return 0;
    

}
