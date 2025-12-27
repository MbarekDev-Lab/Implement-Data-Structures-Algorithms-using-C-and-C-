#include "ArrayMenu.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

Array::Array(int sz) : size(sz), length(0)
{
  A = new int[size];
}

Array::~Array()
{
  delete[] A;
}

// Copy constructor
Array::Array(const Array &other) : size(other.size), length(other.length)
{
  A = new int[size];
  std::copy(other.A, other.A + length, A);
}

// Copy assignment operator
Array &Array::operator=(const Array &other)
{
  if (this != &other)
  {
    delete[] A;
    size = other.size;
    length = other.length;
    A = new int[size];
    std::copy(other.A, other.A + length, A);
  }
  return *this;
}

void Array::Display() const
{
  std::cout << "\nElements are\n";
  if (length == 0)
  {
    std::cout << "(Array is empty)\n";
    return;
  }
  for (int i = 0; i < length; i++)
    std::cout << A[i] << " ";
  std::cout << "\n";
}

void Array::Append(int x)
{
  if (length < size)
    A[length++] = x;
  else
    std::cerr << "Array is full! Cannot append.\n";
}

void Array::Insert(int index, int x)
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
    std::cerr << "Invalid index! Valid range is 0 to " << length << "\n";
  }
}

int Array::Delete(int index)
{
  if (index >= 0 && index < length)
  {
    int x = A[index];
    for (int i = index; i < length - 1; i++)
      A[i] = A[i + 1];
    length--;
    return x;
  }

  std::cerr << "Invalid index for deletion!\n";
  return 0;
}

int Array::LinearSearch(int key)
{
  for (int i = 0; i < length; i++)
  {
    if (key == A[i])
    {
      std::swap(A[i], A[0]);
      return i;
    }
  }
  return -1;
}

int Array::BinarySearch(int key) const
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

int Array::RBinSearch(int l, int h, int key) const
{
  if (l <= h)
  {
    int mid = (l + h) / 2;
    if (key == A[mid])
      return mid;
    else if (key < A[mid])
      return RBinSearch(l, mid - 1, key);
    else
      return RBinSearch(mid + 1, h, key);
  }
  return -1;
}

int Array::Get(int index) const
{
  if (index >= 0 && index < length)
    return A[index];
  return -1;
}

void Array::Set(int index, int x)
{
  if (index >= 0 && index < length)
    A[index] = x;
}

int Array::Max() const
{
  if (length == 0)
    return 0;

  int max = A[0];
  for (int i = 1; i < length; i++)
  {
    if (A[i] > max)
      max = A[i];
  }
  return max;
}

int Array::Min() const
{
  if (length == 0)
    return 0;

  int min = A[0];
  for (int i = 1; i < length; i++)
  {
    if (A[i] < min)
      min = A[i];
  }
  return min;
}

int Array::Sum() const
{
  int s = 0;
  for (int i = 0; i < length; i++)
    s += A[i];
  return s;
}

double Array::Avg() const
{
  if (length == 0)
    return 0.0;
  return static_cast<double>(Sum()) / length;
}

void Array::Reverse()
{
  int *B = new int[length];

  for (int i = length - 1, j = 0; i >= 0; i--, j++)
    B[j] = A[i];

  for (int i = 0; i < length; i++)
    A[i] = B[i];

  delete[] B;
}

void Array::Reverse2()
{
  for (int i = 0, j = length - 1; i < j; i++, j--)
  {
    std::swap(A[i], A[j]);
  }
}

void Array::InsertSort(int x)
{
  if (length == size)
  {
    std::cerr << "Array is full! Cannot insert.\n";
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

bool Array::isSorted() const
{
  for (int i = 0; i < length - 1; i++)
  {
    if (A[i] > A[i + 1])
      return false;
  }
  return true;
}

void Array::Rearrange()
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
      std::swap(A[i], A[j]);
  }
}

Array *Array::Merge(const Array *arr2) const
{
  Array *arr3 = new Array(length + arr2->length);

  int i = 0, j = 0, k = 0;

  while (i < length && j < arr2->length)
  {
    if (A[i] < arr2->A[j])
      arr3->A[k++] = A[i++];
    else
      arr3->A[k++] = arr2->A[j++];
  }

  while (i < length)
    arr3->A[k++] = A[i++];

  while (j < arr2->length)
    arr3->A[k++] = arr2->A[j++];

  arr3->length = k;
  return arr3;
}

Array *Array::Union(const Array *arr2) const
{
  Array *arr3 = new Array(length + arr2->length);

  int i = 0, j = 0, k = 0;

  while (i < length && j < arr2->length)
  {
    if (A[i] < arr2->A[j])
      arr3->A[k++] = A[i++];
    else if (arr2->A[j] < A[i])
      arr3->A[k++] = arr2->A[j++];
    else
    {
      arr3->A[k++] = A[i++];
      j++;
    }
  }

  while (i < length)
    arr3->A[k++] = A[i++];

  while (j < arr2->length)
    arr3->A[k++] = arr2->A[j++];

  arr3->length = k;
  return arr3;
}

Array *Array::Intersection(const Array *arr2) const
{
  Array *arr3 = new Array(std::min(length, arr2->length));

  int i = 0, j = 0, k = 0;

  while (i < length && j < arr2->length)
  {
    if (A[i] < arr2->A[j])
      i++;
    else if (arr2->A[j] < A[i])
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

Array *Array::Difference(const Array *arr2) const
{
  Array *arr3 = new Array(length);

  int i = 0, j = 0, k = 0;

  while (i < length && j < arr2->length)
  {
    if (A[i] < arr2->A[j])
      arr3->A[k++] = A[i++];
    else if (arr2->A[j] < A[i])
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

// ============================================================================
// MAIN DEMO FUNCTION :
// ============================================================================
void arraysMenu()
{
  int size, ch, x, index;

  std::cout << "Enter Size of Array: ";
  std::cin >> size;

  Array arr1(size);

  do
  {
    std::cout << "\n\nMenu\n";
    std::cout << "1. Insert\n";
    std::cout << "2. Delete\n";
    std::cout << "3. Search\n";
    std::cout << "4. Sum\n";
    std::cout << "5. Display\n";
    std::cout << "6. Exit\n";

    std::cout << "Enter your choice: ";
    std::cin >> ch;

    switch (ch)
    {
    case 1:
      std::cout << "Enter element value and index (e.g., 10 0): ";
      std::cin >> x >> index;
      arr1.Insert(index, x);
      break;
    case 2:
      std::cout << "Enter index: ";
      std::cin >> index;
      x = arr1.Delete(index);
      std::cout << "Deleted Element is " << x << "\n";
      break;
    case 3:
      std::cout << "Enter element to search: ";
      std::cin >> x;
      index = arr1.LinearSearch(x);
      std::cout << "Element index: " << index << "\n";
      break;
    case 4:
      std::cout << "Sum is " << arr1.Sum() << "\n";
      break;
    case 5:
      arr1.Display();
      break;
    case 6:
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice!\n";
    }
  } while (ch != 6);
}
