// Pyramid scheme, new years problem
#include <list>
#include <iostream>

struct Bottle 
{
    int level;
    int number;
    int amount_full;
    std::list<Bottle> underlings;
};


int main()
{
    // Input is B, L, and N

    int b, l, n;
    std::cout << "Enter B, L, and N respectively: \n";
    std::cin >> b >> l >> n;

    std::list<Bottle> bottle_list;
    
    for (int i = 1; i < l + 1; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            Bottle *b = new Bottle;
            b->level = i;
            b->number = j + 1;
            b->amount_full = 0;
            b->underlings = *(new std::list<Bottle>);
            bottle_list.push_back(*b);
        }
    }

    for (int i = 1; i < l; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            int bottles_in_level = ((i)*(i + 1) / 2);
            b->underlings.push_back(

        

}
