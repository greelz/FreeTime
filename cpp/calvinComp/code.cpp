#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <chrono>
#include <string>
#include <climits>


// Helper Classes 

// Generic function to sum a vector 
template<typename Type>
Type sum(std::vector<Type> vectorToSum)
{
    Type sumValue = 0;
    for (typename std::vector<Type>::iterator it = vectorToSum.begin(); 
            it != vectorToSum.end(); it++)
    {
        sumValue += *it;
    }
    return sumValue;
}

// Calculate time taken in [ms], given two high_resolution time_points
long long timeTaken(std::chrono::high_resolution_clock::time_point start,
    std::chrono::high_resolution_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Return the GCD(m, n)
int greatestCommonDivisor(int m, int n)
{
    if (m < 0) m = -m;
    if (n < 0) n = -n;

    if ((m == 0) || (n == 0)) return 0;

    // Euclidean algorithm
    int remainder;
    while (1)
    {
        remainder = m % n;
        if (remainder == 0)
            return n;
        m = n;
        n = remainder;
    }
}

// Returns T/F on coprimeness
bool areCoprime(int a, int b)
{
    return greatestCommonDivisor(a, b) == 1;
}


// Retrieve a list of proper divisors of a number
std::vector<int> getProperDivisors(int n)
{
    // Loop through all numbers < sqrt(n)
    // If they divide cleanly, add i, and i's complement
    // Also, 1 is always a divisor

    std::vector<int> properDivisors;
    properDivisors.push_back(1);

    for (unsigned i = 2; i <= std::sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            properDivisors.push_back(i);
            if (n / i != i) properDivisors.push_back(n / i);
        }
    }

    return properDivisors;
}





// Check if a number is palindromic by comparing from the 
// outside in
bool isPalindrome(std::string n)
{
    for (unsigned i = 0; i < n.length() / 2; ++i)
    {
        if (n[i] != n[n.length() - i - 1])
            return false;
    }
    return true;
}

// Check if a number is palindromic.. more like a wrapper class
// for the legitimate function (which accepts a string)
bool isPalindrome(int n)
{
    std::string number = std::to_string(n);
    return isPalindrome(number);
}


// Convert a base10 number to base2
std::string base10toBase2(int n)
{
    std::string base2 = "";
    do
    {
        if ((n & 1) == 0)
            base2 = "0" + base2;
        else
            base2 = "1" + base2;
        n >>= 1;

    } while (n);

    return base2;
}



// End of helper classes 




// Problems that I solved

// ProjectEuler.net, problem21
void Problem21()
{
    // Amicable Numbers
    // d(n) == sum(proper_divisors(n))
    // if d(a) == d(b), where a != b, then a, b are amicable numbers.

    // Find the sum of all amicable numbers below 10,000

    int propDivisorSum, count;
    std::vector<int> properDivisorSums(10000), amicableNumbers;

    for (unsigned a = 2; a < 10000; ++a)
    {
        propDivisorSum = sum(getProperDivisors(a));
        properDivisorSums[a] = propDivisorSum;

        if (propDivisorSum < 10000)
        {
            if (properDivisorSums[propDivisorSum] == a &&
                a != propDivisorSum)
            {
                amicableNumbers.push_back(propDivisorSum);
                amicableNumbers.push_back(a);
            }
        }
    }

    std::cout << sum(amicableNumbers);
}


// Problem 36 from ProjectEuler.net
void Problem36()
{
    int sumOfDoublePalindromes = 0;

    for (unsigned i = 0; i < 1000000; ++i)
    {
        if (isPalindrome(i))
        {
            if (isPalindrome(base10toBase2(i)))
                sumOfDoublePalindromes += i;
        }
    }
    std::cout << sumOfDoublePalindromes;
}



void Problem75()
{
    // Generate primitive primes from Euclid's formula
    // a = m^2 - n^2, b = 2mn, c = m^2 + n^2
    // Triple is primitive iff m & n are coprime, and m - n is odd

    std::vector<int> prims(1500001);
    int a, b, c, k, values = 0;
    int upperLimit = (int)sqrt(1500000 / 2);
    for (int m = 2; m < upperLimit; m++)
    {
        for (int n = 1; n < m; ++n)
        {
            if (areCoprime(m, n) && ((m + n) % 2 != 0))
            {
                a = m * m - n * n;
                b = 2 * m * n;
                c = m * m + n * n;

                // Euclid's formula doesn't calculate further possiblities
                // So we find them by adding k to itself iteratively
                k = a + b + c;
                while (k < 1500001)
                {
                    // If it's unique, then it deserves an iteration of the 
                    // value counter
                    prims[k]++;
                    if (prims[k] == 1)
                    {
                        values++;
                    }
                    // If we end up creating this number again, take away
                    // the value we added previously
                    else if (prims[k] == 2)
                    {
                        values--;
                    }
                    k += a + b + c;
                }
            }
        }
    }

    std::cout << values;

}


// This problem isn't completely finished... but it does the correct operations
// It might finish if you let it run for .. probably 3 hours. I realize it's inefficient but
// at least it works? :) 
void Problem138()
{
    long long a, b, c, k, values = 0;
    long long upperLimit = 1500000;
    // The concept is similar to the other triangle problem
    // Generate right triangles, but this time don't check their coprime-ness
    // Instead, check if they fulfill the property the question asks
    for (long long m = 2; m < LLONG_MAX; m++)
    {
        for (long long n = 1; n < m; ++n)
        {
            a = m * m - n * n;
            b = 2 * m * n;
            // Just switch b and a if b's > a
            if (b > a)
            {
                long long t = b;
                b = a;
                a = t;
            }
            // Check if it fulfills the property...
            if ((a == b * 2 - 1) || (a == b * 2 + 1))
            {
                c = m * m + n * n;
                std::cout << c << std::endl;
            }
        }
    }
}



// I threw all the problems in one .cpp file. Hope that makes sense for you.

// I solved problems:
// 21
// 38
// 75

// I kinda solved problems:
// 138


int main(int argc, char ** argv)
{

    // Just uncomment the problems you'd like to run. 
    // Generally, Ctrl-K-U uncomments a section.
    auto clock = std::chrono::high_resolution_clock();


    // Problem 21
    std::cout << "\n\nStarting Problem 21...\n";
    auto start = clock.now();
    Problem21();
    std::cout << "\nTime to get the answer [ms]: " << timeTaken(start, clock.now()) << std::endl;
    


    // Problem 36
    std::cout << "\n\nStarting Problem 36...\n";
    start = clock.now();
    Problem36();
    std::cout << "\nTime to get the answer [ms]: " << timeTaken(start, clock.now()) << std::endl;

    // Problem 75
    std::cout << "\n\nStarting Problem 75...\n";
    start = clock.now();
    Problem75();
    std::cout << "\nTime to get the answer [ms]: " << timeTaken(start, clock.now()) << std::endl;


    // Problem 138
    std::cout << "\n\nStarting Problem 138...\n";
    start = clock.now();
    Problem138();
    std::cout << "\nTime to get the answer [ms]: " << timeTaken(start, clock.now()) << std::endl;

    // Obviously, you won't be able to finish the last problem.
    // Unless you're crazy, and wait like 3 hours. Maybe days.
}

