/////////////////////////////////////////////
// @author: Matt Greeley                   //
// @algorithm: Longest common subsequence  //
// @date: Spring 2014                      //
/////////////////////////////////////////////


// Dynamic Programming Solution


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


// Returns the contents from a file if the file 
// can be opened. Returns an empty string otherwise.
std::string getFileContents(std::string filename)
{

    std::ifstream myFile (filename.c_str());
    std::string contents = "";
    std::string str;

    while(std::getline(myFile, str))
    {
        contents += str + "\n";
    }

    return contents;
}


// Generic std::cout overload on a std::vector <std::vector<T> >
template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector< std::vector<T> > &M)
{
    for (typename std::vector< std::vector<T> >::iterator it = M.begin();
            it != M.end();
            ++it)
    {
        for (typename std::vector<T>::iterator innerIt = (*it).begin();
                innerIt != (*it).end();
                ++innerIt)
        {
            out << *innerIt << " ";
        }
        out << "\n";
    }
    return out;
}


// Fast comparison of three unsigned ints
static inline unsigned int min(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}


// Edit Distance Alignment Backtrace 
// Returns a std::pair of strings from the backtrace of the Edit distance table
std::pair<std::string, std::string> nwAlignment(std::vector< std::vector<int > > table,
        std::string string1,
        std::string string2)
{
    // Backtrace
    // Follow the table values backwards, because we know that an 'up'
    // is an insert for string1, and a 'left' is an insert for string2

    int length1 = string1.length();
    int length2 = string2.length();

    // Loop until you hit the edge of the matrix, then 
    // just add more '---' to the proper string
    while (length1 > 0 && length2 > 0)
    {
        unsigned int smallest = min(table[length1 - 1][length2 - 1], 
                table[length1 - 1][length2], table[length1][length2 - 1]);

        // Do nothing - the letters matched up
        if (table[length1 - 1][length2 - 1] == smallest)
        {
            length1--;
            length2--;
        }
        // If we are travelling 'up' the table, string2 is 
        // requiring a '-'
        else if (table[length1 - 1][length2] == smallest)
        {
            string2.insert(length2, 1, '-');
            length1--;
        }
        // Otherwise, string1 gets the '-'
        else
        {
            string1.insert(length1, 1, '-');
            length2--;
        }
    }


    // Fill the final values, checking if length1 or length2 > 0
    if (length1 > 0)
    {
        for (int i = 0; i < length1; ++i)
        {
            string2.insert(0, 1, '-');
        }
    }
    else if (length2 > 0)
    {
        for (int i = 0; i < length2; ++i)
        {
            string1.insert(0, 1, '-');
        }
    }

    return std::pair<std::string, std::string>(string1, string2);


}


// Needlemen-Wunsch is a fairly rigorous dynamic solution
//
// Feel free to read up on it on Wikipedia:
// http://en.wikipedia.org/wiki/Edit_distance
//
// It returns a value which states the global alignment of two strings
// (generally used in bioinformatics)
long needlemenWunsch(std::string string1, std::string string2)
{

    // This is what the table looks like after initialization
    // s1: hello
    // s2: mynameismatt
    //       M  Y  N  A  M  E  I  S  M  A   T   T 
    //   [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    // H [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    // E [2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    // L [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    // L [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    // O [5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    int lengthS1 = string1.length();
    int lengthS2 = string2.length();
    int insertCost = 1, deleteCost = 1, substitutionCost = 1;

    std::vector< std::vector<int> > table(lengthS1 + 1, std::vector<int>(lengthS2 + 1));

    for (int i = 0; i < lengthS1 + 1; ++i)
    {
        table[i][0] = i;
    }
    for (int j = 0; j < lengthS2 + 1; ++j)
    {
        table[0][j] = j;
    }


    // Here's the DP algorithm... quite elegant
    for (int i = 1; i < lengthS1 + 1; ++i)
    {
        for (int j = 1; j < lengthS2 + 1; ++j)
        {
            if (string1[i - 1] == string2[j - 1])
            {
                table[i][j] = table[i - 1][j - 1];
            }
            else
            {
                table[i][j] = min(table[i - 1][j] + insertCost, 
                        table[i][j - 1] + deleteCost, 
                        table[i - 1][j - 1] + substitutionCost);
            }
        }
    }


    // I choose to get the actual alignment here as well
    std::pair<std::string, std::string> alignment = nwAlignment(table, string1, string2);
    std::cout << alignment.first << "\n" << alignment.second << "\n";

    // Edit distance is the bottom RHS value
    return table[lengthS1][lengthS2];

}


// Longest-common-subsequence: Dynamic Programming
std::vector< std::vector<int> > lcs(std::string s1, std::string s2)
{
    std::vector< std::vector<int> > table;

    for (int j = 0; j < s2.length() + 1; ++j)
    {
        table.push_back(std::vector<int>(s2.length() + 1));
    }

    // Dynamic solution:
    // LCS at http://en.wikipedia.org/wiki/Longest_common_subsequence_problem

    for (int i = 0; i < s1.length() + 1; ++i)
    {
        for (int j = 0; j < s2.length() + 1; ++j)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            else if (s1[i - 1] == s2[j - 1])
            {
                table[i][j] = table[i - 1][j - 1] + 1;
            }
            else
            {
                table[i][j] = std::max(table[i][j - 1], table[i - 1][j]);
            }
        }
    }
    return table;
}


std::string lcsBacktrack(std::vector< std::vector<int> > table,
        std::string s1, 
        std::string s2)
{
    std::string finalString = "";
    int i = s1.length();
    int j = s2.length();
    // Swap if necessary
    if (i > j)
    {
        int t = i;
        j = i;
        i = t;
    }
    while (i != 0 && j != 0)
    {
        if (table[i][j] == table[i - 1][j])
        {
            i--;
        }
        else if (table[i][j] == table[i][j - 1])
        {
            j--;
        }
        else 
        {
            finalString = s1[i - 1] + finalString;
            i--;
            j--;
        }
    }
    return finalString;
}

int main(int argc, char ** argv)
{
    // If argc == 3, then the user wants to compare
    // two filenames, which are the two parameters

    std::string text1 = "";
    std::string text2 = "";
    if (argc == 3)
    {
        text1 = getFileContents(argv[1]);
        text2 = getFileContents(argv[2]);
    }
    else 
    {
        std::cout << "String 1: " << std::flush;
        std::getline(std::cin, text1);
        std::cout << "String 2: " << std::flush;
        std::getline(std::cin, text2);
    }

    std::cout << needlemenWunsch(text1, text2) << std::endl;

    std::cout << lcsBacktrack(lcs(text1, text2), text1, text2) << std::endl;

    return 0;

}
