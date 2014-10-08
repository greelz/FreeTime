#include <iostream>
void worth2(int * worth)
{
    *worth = *worth + 1;
}

void worth(int worth)
{
    int netWorth = 55;
    worth2(&netWorth);
    std::cout << netWorth;
}

int main()
{
    worth(10);
    return 0;
}
