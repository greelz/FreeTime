#include <string>
#include <iostream>
#include <algorithm>


// Do it iteratively first
void permutate(std::string s)
{
    std::cout << s << std::endl;
    int slength = s.length();
    int *p = new int[slength];
    int i = 1;

    while (i < slength)
    {
        if (s[i] < i)
        {
            int j = ((i % 2) == 0) ? 0 : p[i];
            std::swap(s[i], s[j]);
            std::cout << s << std::endl;
            p[i]++;
            i = 1;
        }
        else
        {
            p[i] = 0;
            i++;
        }
    }
}


int main()
{
    std::string s = "123";
    permutate(s);
    return 0;
}
