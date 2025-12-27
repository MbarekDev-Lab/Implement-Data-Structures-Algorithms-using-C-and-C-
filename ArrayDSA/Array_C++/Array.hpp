#ifndef Array_hpp
#define Array_hpp

#include <iostream>

template <class T>
class TemplateArray
{
private:
    T *A;
    int size;
    int length;

public:
    TemplateArray()
    {
        size = 10;
        A = new T[10];
        length = 0;
    }
    
    TemplateArray(int sz)
    {
        size = sz;
        length = 0;
        A = new T[size];
    }
    
    ~TemplateArray()
    {
        delete[] A;
    }
    
    void Display();
    void Insert(int index, T x);
    T Delete(int index);
};

template <class T>
void TemplateArray<T>::Display()
{
    for (int i = 0; i < length; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;
}

template <class T>
void TemplateArray<T>::Insert(int index, T x)
{
    if (index >= 0 && index <= length)
    {
        for (int i = length - 1; i >= index; i--)
            A[i + 1] = A[i];
        A[index] = x;
        length++;
    }
}

template <class T>
T TemplateArray<T>::Delete(int index)
{
    T x = 0;
    if (index >= 0 && index < length)
    {
        x = A[index];
        for (int i = index; i < length - 1; i++)
            A[i] = A[i + 1];
        length--;
    }
    return x;
}

// Demo function that can be called from Essential.cpp
void arrayTemplateDemo()
{
    std::cout << "\n=== Template Array Demo ===\n";
    
    TemplateArray<char> arr(10);
    arr.Insert(0, 'a');
    arr.Insert(1, 'c');
    arr.Insert(2, 'd');
    
    std::cout << "Array contents: ";
    arr.Display();
    
    std::cout << "Deleted element: " << arr.Delete(0) << std::endl;
    std::cout << "Array after deletion: ";
    arr.Display();
    
    std::cout << "=== End Template Demo ===\n";
}

#endif /* Array_hpp */
