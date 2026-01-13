#include <iostream>

using namespace std;

class Element
{
private:
    /* data */

public:
    int i;
    int j;
    int x;

    Element() : i(0), j(0), x(0) {}
};

class Sparse
{
private:
    int m;             // rows
    int n;             // cols
    int num;           // number of non-zero elements
    Element *elements; // array of non-zero elements

public:
    Sparse(int m, int n, int num)
    {
        this->m = m;
        this->n = n;
        this->num = num;
        elements = new Element[this->num];
    }

    ~Sparse()
    {
        delete[] elements;
    }

    Sparse operator+(Sparse &s);

    friend istream &operator>>(istream &is, Sparse &s);
    friend ostream &operator<<(ostream &os, Sparse &s);
};

Sparse Sparse::operator+(Sparse &s)
{
    int i, j, k;
    if (m != s.m || n != s.n)
    {
        cout << "Matrices dimensions do not match for addition" << endl;
        return Sparse(0, 0, 0);
    }
    Sparse *sum = new Sparse(m, n, num + s.num);
    i = j = k = 0;

    while (i < num && j < s.num)
    {
        if (elements[i].i < s.elements[j].i)
        {
            sum->elements[k++] = elements[i++];
        }
        else if (elements[i].i > s.elements[j].i)
        {
            sum->elements[k++] = s.elements[j++];
        }
        else
        {
            if (elements[i].j < s.elements[j].j)
            {
                sum->elements[k++] = elements[i++];
            }
            else if (elements[i].j > s.elements[j].j)
            {
                sum->elements[k++] = s.elements[j++];
            }
            else
            {

                sum->elements[k] = elements[i];
                sum->elements[k++].x = elements[i++].x + s.elements[j++].x;
            }
        }
    }

    for (; i < num; i++)
    {
        sum->elements[k++] = elements[i];
    }
    for (; j < s.num; j++)
    {
        sum->elements[k++] = s.elements[j];
    }

    sum->num = k;
    return *sum;
}

istream &operator>>(istream &is, Sparse &s)
{
    std::cout << "Enter non-zero elements (row, col, value):\n";
    for (int i = 0; i < s.num; i++)
    {
        std::cin >> s.elements[i].i >> s.elements[i].j >> s.elements[i].x;
    }
    return is;
}

ostream &operator<<(ostream &os, Sparse &s)
{
    int k = 0;
    for (int i = 0; i < s.m; ++i)
    {
        for (int j = 0; j < s.n; ++j)
        {
            if (k < s.num && s.elements[k].i == i && s.elements[k].j == j)
            {
                std::cout << s.elements[k++].x << " ";
            }
            else
            {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }

    return os;
}

int main()
{
    /*Sparse s(5, 5, 5);
    int m, n, num;
    std::cout << "Enter rows, cols and number of non-zero elements: ";
    std::cin >> m >> n >> num;
    Sparse s(m, n, num);
    s.read();
    s.display();
    std::cin >> s;
    std::cout << "The sparse matrix is:\n";
    std::cout << s;*/

    Sparse s1(5, 5, 5);
    Sparse s2(5, 5, 5);

    cin >> s1;
    cin >> s2;

    Sparse s3 = s1 + s2;
    cout << "First Matrix:\n"
         << endl
         << s1;
    cout << "Second Matrix:\n"
         << endl
         << s2;
    cout << "Sum Matrix:\n"
         << endl
         << s3;

    return 0;
}

// Sparse Matrix Addition CPP Version
/*
enraiss@MacBookAir Matrices % ./sparce_cpp
Enter non-zero elements (row, col, value):
0 0 1
1 1
2 2 1
3 3 1
4 4 1
1 1 1
Enter non-zero elements (row, col, value):
0 05
0 1 5
0 2 5
0 3 5
0 0 5
First Matrix:

1 0 0 0 0
0 2 0 0 0
0 3 0 0 0
0 4 0 0 0
0 1 0 0 0
Second Matrix:

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
Sum Matrix:

1 0 0 0 0
0 2 0 0 0
0 3 0 0 0
0 4 0 0 0
0 1 0 0 0
benraiss@MacBookAir Matrices %
*/

/**
 *
0 0 1
1 1 1
2 2 1
3 3 1
4 4 1
The sparse matrix is:
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1
benraiss@MacBookAir Matrices % clang++ -std=c++17 -Wall -Wextra -o sparse_cpp SparseMatrix.cpp && ./sparse_cpp
 *
 *
 */
