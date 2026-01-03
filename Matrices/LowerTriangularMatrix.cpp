// Lower Triangular Matrix Implementation (Row-Major Mapping)
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

// ============================================================================
// LOWER TRIANGULAR MATRIX CLASS (ROW-MAJOR)
// ============================================================================
/*
 * Lower Triangular Matrix: All elements above diagonal are 0
 * 
 * Example (5×5):
 * [ a11  0    0    0    0  ]
 * [ a21  a22  0    0    0  ]
 * [ a31  a32  a33  0    0  ]
 * [ a41  a42  a43  a44  0  ]
 * [ a51  a52  a53  a54  a55]
 * 
 * Storage: Only stores n(n+1)/2 elements instead of n²
 * 
 * Row-Major Mapping Formula (1-based indexing):
 * Index(i,j) = (i-1)i/2 + (j-1)   where i ≥ j
 * 
 * Key Intuition:
 * - Row 1 has 1 element
 * - Row 2 has 2 elements
 * - Row i has i elements
 * - Elements before row i: 1+2+...+(i-1) = (i-1)i/2
 * - Position in row i: (j-1)
 */

class LowerTriangular
{
private:
    int *A;     // 1D array storing only lower triangle elements
    int n;      // Dimension of square matrix (n×n)

    // Private helper: Convert 2D (i,j) to 1D index using row-major formula
    int Index(int i, int j) const
    {
        // Row-major: Index = (i-1)i/2 + (j-1)
        // Valid only when i >= j (lower triangle)
        if (i >= j)
            return (i - 1) * i / 2 + (j - 1);
        else
            return -1; // Invalid for upper triangle
    }

public:
    // Constructors
    LowerTriangular();
    explicit LowerTriangular(int n);
    LowerTriangular(const LowerTriangular &other);
    LowerTriangular(LowerTriangular &&other) noexcept;

    // Destructor
    ~LowerTriangular();

    // Assignment operators
    LowerTriangular &operator=(const LowerTriangular &other);
    LowerTriangular &operator=(LowerTriangular &&other) noexcept;

    // Core operations
    void Set(int i, int j, int x);
    int Get(int i, int j) const;
    void Display() const;
    void Input();

    // Mathematical operations
    int Trace() const;
    int Determinant() const;
    bool IsSymmetric() const;
    
    // Utility
    int GetDimension() const { return n; }
    int GetStoredElements() const { return n * (n + 1) / 2; }
    void Initialize(int value);
    void Clear();
    bool IsEmpty() const { return A == nullptr || n == 0; }

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const LowerTriangular &lt);
};

// ============================================================================
// CONSTRUCTORS
// ============================================================================

LowerTriangular::LowerTriangular() : A(nullptr), n(0) {}

LowerTriangular::LowerTriangular(int n) : A(nullptr), n(0)
{
    if (n < 0)
        throw std::invalid_argument("Matrix dimension cannot be negative");

    if (n > 0)
    {
        this->n = n;
        int size = n * (n + 1) / 2;  // Number of elements in lower triangle
        A = new int[size]();          // Zero-initialized
    }
}

LowerTriangular::LowerTriangular(const LowerTriangular &other) : A(nullptr), n(other.n)
{
    if (n > 0)
    {
        int size = n * (n + 1) / 2;
        A = new int[size];
        for (int i = 0; i < size; i++)
            A[i] = other.A[i];
    }
}

LowerTriangular::LowerTriangular(LowerTriangular &&other) noexcept : A(other.A), n(other.n)
{
    other.A = nullptr;
    other.n = 0;
}

// ============================================================================
// DESTRUCTOR
// ============================================================================

LowerTriangular::~LowerTriangular()
{
    delete[] A;
    A = nullptr;
}

// ============================================================================
// ASSIGNMENT OPERATORS
// ============================================================================

LowerTriangular &LowerTriangular::operator=(const LowerTriangular &other)
{
    if (this != &other)
    {
        delete[] A;
        A = nullptr;
        n = other.n;

        if (n > 0)
        {
            int size = n * (n + 1) / 2;
            A = new int[size];
            for (int i = 0; i < size; i++)
                A[i] = other.A[i];
        }
    }
    return *this;
}

LowerTriangular &LowerTriangular::operator=(LowerTriangular &&other) noexcept
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

void LowerTriangular::Set(int i, int j, int x)
{
    if (i < 1 || i > n || j < 1 || j > n)
    {
        std::cerr << "Index out of bounds (" << i << ", " << j << ")\n";
        return;
    }

    if (i >= j)  // Lower triangle (including diagonal)
    {
        int index = Index(i, j);
        A[index] = x;
    }
    else if (x != 0)  // Upper triangle: only allow zeros
    {
        std::cerr << "Cannot store non-zero value " << x 
                  << " in upper triangle at (" << i << ", " << j << ")\n";
    }
}

int LowerTriangular::Get(int i, int j) const
{
    if (i < 1 || i > n || j < 1 || j > n)
        return 0;

    if (i >= j)  // Lower triangle
    {
        int index = Index(i, j);
        return A[index];
    }
    else  // Upper triangle
    {
        return 0;
    }
}

void LowerTriangular::Display() const
{
    if (IsEmpty())
    {
        std::cout << "Empty matrix\n";
        return;
    }

    std::cout << "Lower Triangular Matrix (" << n << "×" << n << "):\n";
    std::cout << "Storing " << GetStoredElements() << " elements instead of " 
              << (n * n) << "\n";
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cout << std::setw(4) << Get(i, j);
        }
        std::cout << '\n';
    }
}

void LowerTriangular::Input()
{
    if (IsEmpty())
    {
        std::cout << "Cannot input to empty matrix. Initialize first.\n";
        return;
    }

    std::cout << "Enter lower triangular elements (row by row):\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)  // Only j <= i (lower triangle)
        {
            int value;
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> value;
            Set(i, j, value);
        }
    }
}

// ============================================================================
// MATHEMATICAL OPERATIONS
// ============================================================================

int LowerTriangular::Trace() const
{
    if (IsEmpty())
        return 0;

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += Get(i, i);  // Sum of diagonal elements
    }
    return sum;
}

int LowerTriangular::Determinant() const
{
    if (IsEmpty())
        return 0;

    // For triangular matrices: det = product of diagonal elements
    int det = 1;
    for (int i = 1; i <= n; i++)
    {
        det *= Get(i, i);
    }
    return det;
}

bool LowerTriangular::IsSymmetric() const
{
    if (IsEmpty())
        return false;

    // Lower triangular is symmetric only if it's diagonal
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (Get(i, j) != 0)
                return false;
        }
    }
    return true;
}

// ============================================================================
// UTILITY
// ============================================================================

void LowerTriangular::Initialize(int value)
{
    if (!IsEmpty())
    {
        int size = n * (n + 1) / 2;
        for (int i = 0; i < size; i++)
            A[i] = value;
    }
}

void LowerTriangular::Clear()
{
    Initialize(0);
}

// ============================================================================
// FRIEND FUNCTIONS
// ============================================================================

std::ostream &operator<<(std::ostream &os, const LowerTriangular &lt)
{
    if (lt.IsEmpty())
    {
        os << "Empty matrix";
        return os;
    }

    os << "Lower Triangular Matrix (" << lt.n << "×" << lt.n << "):\n";
    for (int i = 1; i <= lt.n; i++)
    {
        for (int j = 1; j <= lt.n; j++)
        {
            os << std::setw(4) << lt.Get(i, j);
        }
        os << '\n';
    }
    return os;
}

// ============================================================================
// MAIN FUNCTION - DEMONSTRATING ROW-MAJOR MAPPING
// ============================================================================

int main()
{
    try
    {
        std::cout << "=== Lower Triangular Matrix (Row-Major) Demo ===\n\n";

        // Create 5×5 lower triangular matrix
        LowerTriangular lt(5);

        std::cout << "Matrix dimensions: 5×5\n";
        std::cout << "Storage needed: " << lt.GetStoredElements() 
                  << " elements (instead of 25)\n\n";

        // Fill with example values (like Abdul Bari's lecture)
        int value = 1;
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                lt.Set(i, j, value++);
            }
        }

        std::cout << "Matrix after filling:\n";
        std::cout << lt << "\n";

        // Demonstrate the mapping
        std::cout << "=== Index Mapping Demonstration ===\n";
        std::cout << "Formula: Index(i,j) = (i-1)i/2 + (j-1)\n\n";

        std::cout << "Element [4][3]:\n";
        std::cout << "  Elements before row 4: 1+2+3 = 6\n";
        std::cout << "  Position in row 4: 3-1 = 2\n";
        std::cout << "  1D Index = 6 + 2 = 8\n";
        std::cout << "  Value = " << lt.Get(4, 3) << "\n\n";

        // Mathematical properties
        std::cout << "=== Matrix Properties ===\n";
        std::cout << "Trace (sum of diagonal): " << lt.Trace() << "\n";
        std::cout << "Determinant: " << lt.Determinant() << "\n";
        std::cout << "Is symmetric? " << (lt.IsSymmetric() ? "Yes" : "No") << "\n\n";

        // Try to set upper triangle (should fail)
        std::cout << "=== Testing Upper Triangle Protection ===\n";
        lt.Set(2, 4, 99);  // Should print error

        std::cout << "\n=== Demo Complete ===\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

/*
=== Expected Output ===

Lower Triangular Matrix (Row-Major) Demo

Matrix dimensions: 5×5
Storage needed: 15 elements (instead of 25)

Matrix after filling:
Lower Triangular Matrix (5×5):
Storing 15 elements instead of 25
   1   0   0   0   0
   2   3   0   0   0
   4   5   6   0   0
   7   8   9  10   0
  11  12  13  14  15

Index Mapping Demonstration
Formula: Index(i,j) = (i-1)i/2 + (j-1)

Element [4][3]:
  Elements before row 4: 1+2+3 = 6
  Position in row 4: 3-1 = 2
  1D Index = 6 + 2 = 8
  Value = 9

Matrix Properties
Trace (sum of diagonal): 35
Determinant: 1890
Is symmetric? No

Testing Upper Triangle Protection
Cannot store non-zero value 99 in upper triangle at (2, 4)

Demo Complete
*/
