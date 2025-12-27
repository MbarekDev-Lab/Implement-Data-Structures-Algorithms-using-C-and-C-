//
//  ArrayMenu.hpp
//  Essential
//
//  Created by M'Barek Benraiss on 18.12.25.
//

#ifndef ArrayMenu_hpp
#define ArrayMenu_hpp

class Array
{
private:
    int *A;
    int size;
    int length;

public:
    Array(int sz);
    ~Array();

    // Copy constructor
    Array(const Array &other);

    // Copy assignment operator
    Array &operator=(const Array &other);

    void Display() const;
    void Append(int x);
    void Insert(int index, int x);
    int Delete(int index);
    int LinearSearch(int key);
    int BinarySearch(int key) const;
    int RBinSearch(int l, int h, int key) const;

    int Get(int index) const;
    void Set(int index, int x);
    int Max() const;
    int Min() const;
    int Sum() const;
    double Avg() const;
    void Reverse();
    void Reverse2();
    void InsertSort(int x);
    bool isSorted() const;
    void Rearrange();

    Array *Merge(const Array *arr2) const;
    Array *Union(const Array *arr2) const;
    Array *Intersection(const Array *arr2) const;
    Array *Difference(const Array *arr2) const;
};

void arraysMenu();

#endif /* ArrayMenu_hpp */
