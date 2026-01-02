// Diagonal Matrix Implementation
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

// ============================================================================
// DIAGONAL MATRIX CLASS
// ============================================================================

class Diagonal
{
private:
    int *A;
    int n;

public:
    // Constructors
    Diagonal();
    explicit Diagonal(int n);
    Diagonal(const Diagonal &other);
    Diagonal(Diagonal &&other) noexcept;

    // Destructor
    ~Diagonal();

    // Assignment operators
    Diagonal &operator=(const Diagonal &other);
    Diagonal &operator=(Diagonal &&other) noexcept;

    // Core operations
    void Set(int i, int j, int x);
    int Get(int i, int j) const;
    void Display() const;
    void Input();

    // Operator overloading - Arithmetic
    int operator[](int index) const;
    int &operator[](int index);
    Diagonal operator+(const Diagonal &other) const;
    Diagonal operator-(const Diagonal &other) const;
    Diagonal operator*(const Diagonal &other) const;
    Diagonal operator*(int scalar) const;

    // Operator overloading - Comparison
    bool operator==(const Diagonal &other) const;
    bool operator!=(const Diagonal &other) const;

    // Mathematical operations
    int Trace() const;
    int Determinant() const;
    Diagonal Inverse() const;
    Diagonal Transpose() const { return *this; } // Diagonal matrix is its own transpose

    // Matrix properties
    bool IsSymmetric() const { return true; } // Diagonal matrices are always symmetric
    bool IsDiagonal() const { return true; }
    bool IsIdentity() const;
    bool IsSingular() const;

    // Utility
    int GetDimension() const { return n; }
    void Initialize(int value);
    void Clear();
    bool IsEmpty() const { return A == nullptr || n == 0; }

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const Diagonal &d);
    friend Diagonal operator*(int scalar, const Diagonal &d);
};

// ============================================================================
// CONSTRUCTORS
// ============================================================================

Diagonal::Diagonal() : A(nullptr), n(0) {}

Diagonal::Diagonal(int n) : A(nullptr), n(0)
{
    if (n < 0)
        throw std::invalid_argument("Matrix dimension cannot be negative");

    if (n > 0)
    {
        this->n = n;
        A = new int[n](); // zero initialized
    }
}

Diagonal::Diagonal(const Diagonal &other) : A(nullptr), n(other.n)
{
    if (n > 0)
    {
        A = new int[n];
        for (int i = 0; i < n; i++)
            A[i] = other.A[i];
    }
}

Diagonal::Diagonal(Diagonal &&other) noexcept : A(other.A), n(other.n)
{
    other.A = nullptr;
    other.n = 0;
}

// ============================================================================
// DESTRUCTOR
// ============================================================================

Diagonal::~Diagonal()
{
    delete[] A;
    A = nullptr;
}

// ============================================================================
// ASSIGNMENT OPERATORS
// ============================================================================

Diagonal &Diagonal::operator=(const Diagonal &other)
{
    if (this != &other)
    {
        delete[] A;
        A = nullptr;
        n = other.n;

        if (n > 0)
        {
            A = new int[n];
            for (int i = 0; i < n; i++)
                A[i] = other.A[i];
        }
    }
    return *this;
}

Diagonal &Diagonal::operator=(Diagonal &&other) noexcept
{
    if (this != &other)
    {
        delete[] A;
        A = other.A;
        n = other.n;

        other.A = nullptr;
        other.n = 0;
    }
    return *this;
}

// ============================================================================
// CORE OPERATIONS
// ============================================================================

void Diagonal::Set(int i, int j, int x)
{
    if (i < 1 || i > n || j < 1 || j > n)
    {
        std::cerr << "Index out of bounds (" << i << ", " << j << ")\n";
        return;
    }

    if (i == j)
        A[i - 1] = x;
    else if (x != 0)
        std::cerr << "Cannot store non-zero value " << x << " at position (" << i << ", " << j << ")\n";
}

int Diagonal::Get(int i, int j) const
{
    if (i < 1 || i > n || j < 1 || j > n)
        return 0;

    return (i == j) ? A[i - 1] : 0;
}

void Diagonal::Display() const
{
    if (IsEmpty())
    {
        std::cout << "Empty matrix\n";
        return;
    }

    std::cout << "Diagonal Matrix (" << n << "x" << n << "):\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cout << std::setw(4)
                      << ((i == j) ? A[i - 1] : 0);
        }
        std::cout << '\n';
    }
}

void Diagonal::Input()
{
    if (IsEmpty())
    {
        std::cout << "Cannot input to empty matrix. Initialize first.\n";
        return;
    }

    std::cout << "Enter " << n << " diagonal elements:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << "Element [" << (i + 1) << "]: ";
        std::cin >> A[i];
    }
}

// ============================================================================
// OPERATOR OVERLOADING - ARITHMETIC
// ============================================================================

int Diagonal::operator[](int index) const
{
    if (index < 0 || index >= n)
    {
        std::cerr << "Index out of range: " << index << "\n";
        return 0;
    }
    return A[index];
}

int &Diagonal::operator[](int index)
{
    if (index < 0 || index >= n)
        throw std::out_of_range("Index out of range");
    return A[index];
}

Diagonal Diagonal::operator+(const Diagonal &other) const
{
    if (n != other.n)
    {
        std::cerr << "Matrix dimensions don't match for addition\n";
        return Diagonal();
    }

    Diagonal result(n);
    for (int i = 0; i < n; i++)
        result.A[i] = A[i] + other.A[i];

    return result;
}

Diagonal Diagonal::operator-(const Diagonal &other) const
{
    if (n != other.n)
    {
        std::cerr << "Matrix dimensions don't match for subtraction\n";
        return Diagonal();
    }

    Diagonal result(n);
    for (int i = 0; i < n; i++)
        result.A[i] = A[i] - other.A[i];

    return result;
}

Diagonal Diagonal::operator*(const Diagonal &other) const
{
    if (n != other.n)
    {
        std::cerr << "Matrix dimensions don't match for multiplication\n";
        return Diagonal();
    }

    Diagonal result(n);
    for (int i = 0; i < n; i++)
        result.A[i] = A[i] * other.A[i];

    return result;
}

Diagonal Diagonal::operator*(int scalar) const
{
    Diagonal result(n);
    for (int i = 0; i < n; i++)
        result.A[i] = A[i] * scalar;

    return result;
}

// ============================================================================
// OPERATOR OVERLOADING - COMPARISON
// ============================================================================

bool Diagonal::operator==(const Diagonal &other) const
{
    if (n != other.n)
        return false;

    for (int i = 0; i < n; i++)
    {
        if (A[i] != other.A[i])
            return false;
    }
    return true;
}

bool Diagonal::operator!=(const Diagonal &other) const
{
    return !(*this == other);
}

// ============================================================================
// MATHEMATICAL OPERATIONS
// ============================================================================

int Diagonal::Trace() const
{
    if (IsEmpty())
        return 0;

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];

    return sum;
}

int Diagonal::Determinant() const
{
    if (IsEmpty())
        return 0;

    int det = 1;
    for (int i = 0; i < n; i++)
        det *= A[i];

    return det;
}

Diagonal Diagonal::Inverse() const
{
    if (IsEmpty())
    {
        std::cerr << "Cannot invert empty matrix\n";
        return Diagonal();
    }

    // Check if matrix is singular
    for (int i = 0; i < n; i++)
    {
        if (A[i] == 0)
        {
            std::cerr << "Matrix is singular, cannot compute inverse\n";
            return Diagonal();
        }
    }

    Diagonal result(n);
    for (int i = 0; i < n; i++)
        result.A[i] = 1 / A[i]; // For integer division, this will truncate

    return result;
}

bool Diagonal::IsIdentity() const
{
    if (IsEmpty())
        return false;

    for (int i = 0; i < n; i++)
    {
        if (A[i] != 1)
            return false;
    }
    return true;
}

bool Diagonal::IsSingular() const
{
    if (IsEmpty())
        return true;

    for (int i = 0; i < n; i++)
    {
        if (A[i] == 0)
            return true;
    }
    return false;
}

// ============================================================================
// UTILITY
// ============================================================================

void Diagonal::Initialize(int value)
{
    if (!IsEmpty())
    {
        for (int i = 0; i < n; i++)
            A[i] = value;
    }
}

void Diagonal::Clear()
{
    Initialize(0);
}

// ============================================================================
// FRIEND FUNCTIONS
// ============================================================================

std::ostream &operator<<(std::ostream &os, const Diagonal &d)
{
    if (d.IsEmpty())
    {
        os << "Empty matrix";
        return os;
    }

    os << "Diagonal Matrix (" << d.n << "x" << d.n << "):\n";
    for (int i = 1; i <= d.n; i++)
    {
        for (int j = 1; j <= d.n; j++)
        {
            os << std::setw(4) << ((i == j) ? d.A[i - 1] : 0);
        }
        os << '\n';
    }
    return os;
}

Diagonal operator*(int scalar, const Diagonal &d)
{
    return d * scalar;
}

// ============================================================================
// MAIN FUNCTION (EXAMPLE USAGE)
// ============================================================================

int main()
{
    try
    {
        std::cout << "=== Diagonal Matrix Implementation Demo ===\n\n";

        // Create diagonal matrices
        Diagonal d1(4);
        d1[0] = 2;
        d1[1] = 3;
        d1[2] = 4;
        d1[3] = 5;

        std::cout << "Matrix D1:\n"
                  << d1 << "\n";

        // Create another matrix
        Diagonal d2(4);
        d2.Initialize(2);

        std::cout << "Matrix D2 (initialized with 2):\n"
                  << d2 << "\n";

        // Addition
        Diagonal d3 = d1 + d2;
        std::cout << "D1 + D2:\n"
                  << d3 << "\n";

        // Subtraction
        Diagonal d4 = d1 - d2;
        std::cout << "D1 - D2:\n"
                  << d4 << "\n";

        // Multiplication
        Diagonal d5 = d1 * d2;
        std::cout << "D1 * D2 (element-wise):\n"
                  << d5 << "\n";

        // Scalar multiplication
        Diagonal d6 = d1 * 3;
        std::cout << "D1 * 3:\n"
                  << d6 << "\n";

        // Mathematical properties
        std::cout << "Trace of D1: " << d1.Trace() << "\n";
        std::cout << "Determinant of D1: " << d1.Determinant() << "\n";
        std::cout << "Is D1 identity? " << (d1.IsIdentity() ? "Yes" : "No") << "\n";
        std::cout << "Is D1 singular? " << (d1.IsSingular() ? "Yes" : "No") << "\n\n";

        // Comparison
        Diagonal d7 = d1;
        std::cout << "D7 == D1? " << (d7 == d1 ? "Yes" : "No") << "\n";
        std::cout << "D7 != D2? " << (d7 != d2 ? "Yes" : "No") << "\n\n";

        // Move semantics
        Diagonal d8 = std::move(d7);
        std::cout << "After moving D7 to D8:\n"
                  << d8 << "\n";

        std::cout << "=== Demo Complete ===\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

/*
=== Diagonal Matrix Implementation Demo ===
Matrix D1:
Diagonal Matrix (4x4):
   2   0   0   0
   0   3   0   0
   0   0   4   0
   0   0   0   5

Matrix D2 (initialized with 2):
Diagonal Matrix (4x4):
   2   0   0   0
   0   2   0   0
   0   0   2   0
   0   0   0   2

D1 + D2:
Diagonal Matrix (4x4):
   4   0   0   0
   0   5   0   0
   0   0   6   0
   0   0   0   7

D1 - D2:
Diagonal Matrix (4x4):
   0   0   0   0
   0   1   0   0
   0   0   2   0
   0   0   0   3

D1 * D2 (element-wise):
Diagonal Matrix (4x4):
   4   0   0   0
   0   6   0   0
   0   0   8   0
   0   0   0  10

D1 * 3:
Diagonal Matrix (4x4):
   6   0   0   0
   0   9   0   0
   0   0  12   0
   0   0   0  15

Trace of D1: 14
Determinant of D1: 120
Is D1 identity? No
Is D1 singular? No

D7 == D1? Yes
D7 != D2? Yes

After moving D7 to D8:
Diagonal Matrix (4x4):
   2   0   0   0
   0   3   0   0
   0   0   4   0
   0   0   0   5

=== Demo Complete ===

*/
