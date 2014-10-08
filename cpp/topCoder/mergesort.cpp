#include <iostream>


void merge(int *array, int size1, int size2)
{
    int temp[size1 + size2];
    int ptr1 = 0, ptr2 = 0;
    int *arr1 = array, *arr2 = array + size1;


    while (ptr1 + ptr2 < size1 + size2)
    {
        if (ptr1 < size1 && arr1[ptr1] <= arr2[ptr2] || ptr1 < size1 && ptr2 >= size2)
            temp[ptr1 + ptr2] = arr1[ptr1++];
        if (ptr2 < size2 && arr2[ptr2] < arr1[ptr1] || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1 + ptr2] = arr2[ptr2++];
    }

    for (int i = 0; i < size1 + size2; ++i)
    {
        std::cout << temp[i] << " ";
        array[i] = temp[i];
    }
    std::cout << std::endl;
}

template <class T>
void matt_merge(T *array, int size1, int size2)
{
    // So we should have a temp array which mimics T *array
    T temp[size1 + size2];
    int ptr1 = 0, ptr2 = 0;
    T *arr1 = array, *arr2 = array + size1;

    // Now let's walk through the lists, making sure we're "inbounds"
    while (ptr1 + ptr2 < size1 + size2)
    {
        if (ptr1 < size1 && (arr1[ptr1] <= arr2[ptr2] || ptr2 >= size2))
            temp[ptr1 + ptr2] = arr1[ptr1++];
        if (ptr2 < size2 && (arr2[ptr2] < arr1[ptr1] || ptr1 >= size1))
            temp[ptr1 + ptr2] = arr2[ptr2++];
    }


    // In the end, we're going to copy temp[i] values into array[i]
    for (int i = 0; i < size1 + size2; ++i)
    {
        array[i] = temp[i];
    }
}


class Road
{
public:
    Road()
    {
        length_ = 0;
        toughness_ = 0;
    }

    Road(int len, int toughness)
    {
        length_ = len;
        toughness = toughness;
    }

    int get_length() { return length_; }

    friend bool operator<(Road const &lhs, Road const &rhs)
    {
        return lhs.length_ < rhs.length_;
    }

    friend bool operator<=(Road const &lhs, Road const &rhs)
    {
        return lhs.length_ <= rhs.length_;
    }

private:
    int length_;
    int toughness_;
};

template <class T>
void matt_merge_sort(T *array, int size)
{
    // Recursive, so here's the base case
    if (size == 1)
        return;

    // Otherwise, split the lists recursively until you can merge
    int size1 = size / 2, size2 = size - size1;

    matt_merge_sort(array, size1);

    // The midpoint is going to be array + size1 (memory address)
    matt_merge_sort(array + size1, size2);
    matt_merge(array, size1, size2);
}



void merge_sort(int *array, int size)
{
    std::cout << "First array elem: " << *array << ", " << size << std::endl;
    if (size == 1)
        return;

    int size1 = size / 2, size2 = size - size1;
    merge_sort(array, size1);
    // Midpoint is going to be array + size1, because of pointer addresses! 
    merge_sort(array + size1, size2);
    merge(array, size1, size2);
}


int main(int argc, char ** argv)
{
    int num, input;
    std::cout << "How many roads do you want to sort: ";
    std::cin >> num;
    Road a[num];
    for (int i = 0; i < num; i++) 
    {
        std::cout << (i + 1) << ": ";
        std::cin >> input;
        Road r(input, 0);
        a[i] = r;
    }    


    // Merge sort
    matt_merge_sort(a, num);

    for (int i = 0; i < num; ++i)
    {
        std::cout << a[i].get_length() << " ";
    }

    std::cout << std::endl;

    return 0;
}
