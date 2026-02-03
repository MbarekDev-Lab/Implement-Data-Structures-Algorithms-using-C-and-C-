#include <iostream>
#define SIZE 10
#define PRIME 7 // Prime number < SIZE for second hash
#define EMPTY 0

using namespace std;

template <class T>
void Print(T &vec, int n, string s)
{
    cout << s << ": [" << flush;
    for (int i = 0; i < n; i++)
    {
        cout << vec[i] << flush;
        if (i < n - 1)
        {
            cout << ", " << flush;
        }
    }
    cout << "]" << endl;
}

// Primary hash function
int Hash(int key)
{
    return key % SIZE;
}

// Secondary hash function (must never return 0!)
// Formula: PRIME - (key % PRIME)
int PrimeHash(int key)
{
    return PRIME - (key % PRIME);
}

// Double Hashing probe
// Formula: (h1(key) + i * h2(key)) % SIZE
int DoubleHashProbe(int H[], int key, int &probes)
{
    int h1 = Hash(key);      // Primary hash
    int h2 = PrimeHash(key); // Secondary hash (step size)
    int i = 0;

    probes = 0;

    cout << "  Double hashing for key " << key << ":" << endl;
    cout << "    h1(" << key << ") = " << h1 << endl;
    cout << "    h2(" << key << ") = " << h2 << " (step size)" << endl;

    // Formula: (h1 + i * h2) % SIZE
    while (H[(h1 + i * h2) % SIZE] != EMPTY)
    {
        probes++;
        cout << "    Probe " << i << ": index " << (h1 + i * h2) % SIZE
             << " occupied" << endl;
        i++;

        // Safety check
        if (i >= SIZE)
        {
            cout << "    Table full!" << endl;
            return -1;
        }
    }

    int final_idx = (h1 + i * h2) % SIZE;
    probes++;
    cout << "    Found empty slot at index " << final_idx
         << " (probe " << i << ")" << endl;
    return final_idx;
}

void Insert(int H[], int key)
{
    int idx = Hash(key);
    int probes = 0;

    cout << "\nInserting " << key << ":" << endl;

    if (H[idx] != EMPTY)
    {
        idx = DoubleHashProbe(H, key, probes);
        if (idx == -1)
        {
            cout << "  Cannot insert - table full!" << endl;
            return;
        }
    }
    else
    {
        cout << "  Direct insert at index " << idx << " (no collision)" << endl;
    }

    H[idx] = key;
}

int Search(int H[], int key)
{
    int h1 = Hash(key);
    int h2 = PrimeHash(key);
    int i = 0;

    // Double hash probe: (h1 + i * h2) % SIZE
    while (H[(h1 + i * h2) % SIZE] != key)
    {
        i++;

        // If we hit empty slot, key doesn't exist
        if (H[(h1 + i * h2) % SIZE] == EMPTY)
        {
            return -1;
        }

        // Safety check
        if (i >= SIZE)
        {
            return -1;
        }
    }
    return (h1 + i * h2) % SIZE;
}

int main()
{
    cout << "=== DOUBLE HASHING ===" << endl;
    cout << "SIZE = " << SIZE << ", PRIME = " << PRIME << endl;

    int A[] = {5, 25, 15, 35, 95};
    int n = sizeof(A) / sizeof(A[0]);
    Print(A, n, "\nInput Array");

    // Hash Table
    int HT[SIZE] = {EMPTY};

    cout << "\n--- INSERTION PHASE ---" << endl;
    for (int i = 0; i < n; i++)
    {
        Insert(HT, A[i]);
    }

    cout << "\n--- FINAL HASH TABLE ---" << endl;
    Print(HT, SIZE, "HT");

    cout << "\n--- SEARCH PHASE ---" << endl;

    int key = 25;
    int index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    key = 35;
    index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    key = 100; // Non-existent key
    index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air hashing %  clang++ -std=c++17 -Wall -Wextra -o _dhash DoubleHashing.cpp && ./_dhash
    === DOUBLE HASHING ===
    SIZE = 10, PRIME = 7

    Input Array: [5, 25, 15, 35, 95]

    --- INSERTION PHASE ---

    Inserting 5:
    Direct insert at index 5 (no collision)

    Inserting 25:
    Double hashing for key 25:
        h1(25) = 5
        h2(25) = 3 (step size)
        Probe 0: index 5 occupied
        Found empty slot at index 8 (probe 1)

    Inserting 15:
    Double hashing for key 15:
        h1(15) = 5
        h2(15) = 6 (step size)
        Probe 0: index 5 occupied
        Found empty slot at index 1 (probe 1)

    Inserting 35:
    Double hashing for key 35:
        h1(35) = 5
        h2(35) = 7 (step size)
        Probe 0: index 5 occupied
        Found empty slot at index 2 (probe 1)

    Inserting 95:
    Double hashing for key 95:
        h1(95) = 5
        h2(95) = 3 (step size)
        Probe 0: index 5 occupied
        Probe 1: index 8 occupied
        Probe 2: index 1 occupied
        Found empty slot at index 4 (probe 3)

    --- FINAL HASH TABLE ---
    HT: [0, 15, 35, 0, 95, 5, 0, 0, 25, 0]

    --- SEARCH PHASE ---
    Key 25 found at index: 8
    Key 35 found at index: 2
    Key 100 NOT found
    benraiss@Mbareks-MacBook-Air hashing %


    HT: [0, 15, 35, 0, 95, 5, 0, 0, 25, 0]
     0  1   2   3  4   5  6  7  8   9

    All 5 keys with hash=5 are distributed across:
    5 → index 5 (original)
    25 → index 8 (step 3)
    15 → index 1 (step 6)
    35 → index 2 (step 7)
    95 → index 4 (step 3, multiple probes)
*/