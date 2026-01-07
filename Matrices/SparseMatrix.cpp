#include <iostream>

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

    void read()
    {
        std::cout << "Enter non-zero elements (row, col, value):\n";
        for (int i = 0; i < num; i++)
        {
            std::cin >> elements[i].i >> elements[i].j >> elements[i].x;
        }
    }

    void display()
    {
        int k = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (elements[k].i == i && elements[k].j == j)
                {
                    std::cout << elements[k++].x << " ";
                }
                else
                {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Sparse s(5, 5, 5);
    /*int m, n, num;
    std::cout << "Enter rows, cols and number of non-zero elements: ";
    std::cin >> m >> n >> num;

    Sparse s(m, n, num);*/
    s.read();

    std::cout << "The sparse matrix is:\n";
    s.display();
    return 0;
}

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
