#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Array
{
private:
    T *A;
    int size;
    int length;

public:
    Array()
    {
        size = 10;
        length = 0;
        A = new T[size];
    }

    Array(int sz)
    {
        size = sz;
        length = 0;
        A = new T[size];
    }

    // Copy constructor
    Array(const Array &other) : size(other.size), length(other.length)
    {
        A = new T[size];
        for (int i = 0; i < length; i++)
            A[i] = other.A[i];
    }

    // Assignment operator
    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            delete[] A;
            size = other.size;
            length = other.length;
            A = new T[size];
            for (int i = 0; i < length; i++)
                A[i] = other.A[i];
        }
        return *this;
    }

    ~Array()
    {
        delete[] A;
    }

    void Display() const;
    void Append(T x);
    void Insert(int index, T x);
    T Delete(int index);
    int LinearSearch(T key);
    int BinarySearch(T key) const;
    T Get(int index) const;
    void Set(int index, T x);
    T Max() const;
    T Min() const;
    T Sum() const;
    double Avg() const;
    void Reverse();
    void Reverse2();
    void InsertSort(T x);
    bool isSorted() const;
    void Rearrange();
    Array<T> *Merge(const Array<T> &arr2) const;
    Array<T> *Union(const Array<T> &arr2) const;
    Array<T> *Intersection(const Array<T> &arr2) const;
    Array<T> *Difference(const Array<T> &arr2) const;
};

template <class T>
void Array<T>::Display() const
{
    cout << "\nElements are\n";
    for (int i = 0; i < length; i++)
        cout << A[i] << " ";
    cout << endl;
}

template <class T>
void Array<T>::Append(T x)
{
    if (length < size)
        A[length++] = x;
    else
        cerr << "Array is full!\n";
}

template <class T>
void Array<T>::Insert(int index, T x)
{
    if (index >= 0 && index <= length && length < size)
    {
        for (int i = length; i > index; i--)
            A[i] = A[i - 1];
        A[index] = x;
        length++;
    }
    else
    {
        cerr << "Invalid index or array is full!\n";
    }
}

template <class T>
T Array<T>::Delete(int index)
{
    if (index >= 0 && index < length)
    {
        T x = A[index];
        for (int i = index; i < length - 1; i++)
            A[i] = A[i + 1];
        length--;
        return x;
    }
    cerr << "Invalid index!\n";
    return T();
}

template <class T>
int Array<T>::LinearSearch(T key)
{
    for (int i = 0; i < length; i++)
    {
        if (key == A[i])
        {
            swap(A[i], A[0]);
            return i;
        }
    }
    return -1;
}

template <class T>
int Array<T>::BinarySearch(T key) const
{
    int l = 0;
    int h = length - 1;

    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

template <class T>
T Array<T>::Get(int index) const
{
    if (index >= 0 && index < length)
        return A[index];
    return T();
}

template <class T>
void Array<T>::Set(int index, T x)
{
    if (index >= 0 && index < length)
        A[index] = x;
}

template <class T>
T Array<T>::Max() const
{
    if (length == 0)
        return T();

    T max = A[0];
    for (int i = 1; i < length; i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

template <class T>
T Array<T>::Min() const
{
    if (length == 0)
        return T();

    T min = A[0];
    for (int i = 1; i < length; i++)
    {
        if (A[i] < min)
            min = A[i];
    }
    return min;
}

template <class T>
T Array<T>::Sum() const
{
    T s = T();
    for (int i = 0; i < length; i++)
        s += A[i];
    return s;
}

template <class T>
double Array<T>::Avg() const
{
    if (length == 0)
        return 0.0;
    return static_cast<double>(Sum()) / length;
}

template <class T>
void Array<T>::Reverse()
{
    T *B = new T[length];

    for (int i = length - 1, j = 0; i >= 0; i--, j++)
        B[j] = A[i];

    for (int i = 0; i < length; i++)
        A[i] = B[i];

    delete[] B;
}

template <class T>
void Array<T>::Reverse2()
{
    for (int i = 0, j = length - 1; i < j; i++, j--)
    {
        swap(A[i], A[j]);
    }
}

template <class T>
void Array<T>::InsertSort(T x)
{
    if (length == size)
    {
        cerr << "Array is full!\n";
        return;
    }

    int i = length - 1;
    while (i >= 0 && A[i] > x)
    {
        A[i + 1] = A[i];
        i--;
    }
    A[i + 1] = x;
    length++;
}

template <class T>
bool Array<T>::isSorted() const
{
    for (int i = 0; i < length - 1; i++)
    {
        if (A[i] > A[i + 1])
            return false;
    }
    return true;
}

template <class T>
void Array<T>::Rearrange()
{
    int i = 0;
    int j = length - 1;

    while (i < j)
    {
        while (i < length && A[i] < 0)
            i++;
        while (j >= 0 && A[j] >= 0)
            j--;
        if (i < j)
            swap(A[i], A[j]);
    }
}

template <class T>
Array<T> *Array<T>::Merge(const Array<T> &arr2) const
{
    Array<T> *arr3 = new Array<T>(length + arr2.length);

    int i = 0, j = 0, k = 0;

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }

    while (i < length)
        arr3->A[k++] = A[i++];

    while (j < arr2.length)
        arr3->A[k++] = arr2.A[j++];

    arr3->length = k;
    return arr3;
}

template <class T>
Array<T> *Array<T>::Union(const Array<T> &arr2) const
{
    Array<T> *arr3 = new Array<T>(length + arr2.length);

    int i = 0, j = 0, k = 0;

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if (arr2.A[j] < A[i])
            arr3->A[k++] = arr2.A[j++];
        else
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }

    while (i < length)
        arr3->A[k++] = A[i++];

    while (j < arr2.length)
        arr3->A[k++] = arr2.A[j++];

    arr3->length = k;
    return arr3;
}

template <class T>
Array<T> *Array<T>::Intersection(const Array<T> &arr2) const
{
    Array<T> *arr3 = new Array<T>(min(length, arr2.length));

    int i = 0, j = 0, k = 0;

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            i++;
        else if (arr2.A[j] < A[i])
            j++;
        else
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }

    arr3->length = k;
    return arr3;
}

template <class T>
Array<T> *Array<T>::Difference(const Array<T> &arr2) const
{
    Array<T> *arr3 = new Array<T>(length);

    int i = 0, j = 0, k = 0;

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if (arr2.A[j] < A[i])
            j++;
        else
        {
            i++;
            j++;
        }
    }

    while (i < length)
        arr3->A[k++] = A[i++];

    arr3->length = k;
    return arr3;
}

int main()
{
    Array<int> *arr1;
    int ch, sz;
    int x, index;

    cout << "Enter Size of Array: ";
    cin >> sz;
    arr1 = new Array<int>(sz);

    do
    {
        cout << "\n\nMenu\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Sum\n";
        cout << "5. Display\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter element and index: ";
            cin >> x >> index;
            arr1->Insert(index, x);
            break;

        case 2:
            cout << "Enter index: ";
            cin >> index;
            x = arr1->Delete(index);
            cout << "Deleted Element is " << x << endl;
            break;

        case 3:
            cout << "Enter element to search: ";
            cin >> x;
            index = arr1->LinearSearch(x);
            cout << "Element index: " << index << endl;
            break;

        case 4:
            cout << "Sum is " << arr1->Sum() << endl;
            break;

        case 5:
            arr1->Display();
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (ch != 6);

    delete arr1;
    return 0;
}