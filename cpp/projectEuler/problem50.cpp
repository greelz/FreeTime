#include <math.h>
#include <vector>
#include <iostream>


bool is_prime(int value)
{
    for (int i = 2; i <= sqrt(value); ++i)
    {
        if (value % i == 0) 
            return false;
    }
    return true;
}



int main()

{

    std::vector<bool> primes(1000000, false);
    primes[2] = true;

    for (int i = 3; i < 1000000; i += 2)
    {
        if (is_prime(i))
        {
            primes[i] = true;
        }
    }

    std::cout << "generated primes\n\n";

    int max_prime = -1, sum = 0, count = 0;

    while (sum < 1000000 && count < 1000000)
    {
        if (primes[count])
            sum += count;
        if (primes[sum])
            max_prime = sum;

        count++;
    }

    std::cout << max_prime << std::endl;
    std::cout << sum << std::endl;
    std::cout << count << std::endl;

    

}
