#include <iostream>
#define SIZE 10
#define EMPTY 0 // Marker for empty slot

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

int Hash(int key)
{
    return key % SIZE;
}

// Quadratic Probing: idx + i^2
// Reduces clustering compared to linear probing
int QuadraticProbe(int H[], int key, int &probes)
{
    int idx = Hash(key);
    int i = 0;
    probes = 0;

    cout << "  Quadratic probing for key " << key << " (hash = " << idx << "):" << endl;

    while (H[(idx + i * i) % SIZE] != EMPTY)
    {
        probes++;
        cout << "    Try index " << (idx + i * i) % SIZE << " (i=" << i << "): occupied" << endl;
        i++;

        // Safety: prevent infinite loop
        if (i >= SIZE)
        {
            cout << "    Table full or no slot found!" << endl;
            return -1;
        }
    }

    int final_idx = (idx + i * i) % SIZE;
    probes++;
    cout << "    Found empty slot at index " << final_idx << " (i=" << i << ")" << endl;
    return final_idx;
}

void Insert(int H[], int key)
{
    int idx = Hash(key);
    int probes = 0;

    cout << "\nInserting " << key << ":" << endl;

    if (H[idx] != EMPTY)
    {
        idx = QuadraticProbe(H, key, probes);
        if (idx == -1)
        {
            cout << "  Cannot insert " << key << " - table full!" << endl;
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
    int idx = Hash(key);
    int i = 0;

    // Quadratic probe until key found or empty slot reached
    while (H[(idx + i * i) % SIZE] != key)
    {
        i++;

        // If we hit an empty slot, key doesn't exist
        if (H[(idx + i * i) % SIZE] == EMPTY)
        {
            return -1;
        }

        // Safety: prevent infinite loop
        if (i >= SIZE)
        {
            return -1;
        }
    }
    return (idx + i * i) % SIZE;
}

int main()
{
    int A[] = {26, 30, 45, 23, 25, 43, 74, 19, 29};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "=== QUADRATIC PROBING HASH TABLE ===" << endl;
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

    // Search existing keys
    cout << "\n--- SEARCH PHASE ---" << endl;

    int key = 25;
    int index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    key = 35; // This key doesn't exist!
    index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    key = 43;
    index = Search(HT, key);
    if (index != -1)
        cout << "Key " << key << " found at index: " << index << endl;
    else
        cout << "Key " << key << " NOT found" << endl;

    return 0;
}

/*

    benraiss@Mbareks-MacBook-Air hashing %  clang++ -std=c++17 -Wall -Wextra -o _quad QuadraticProbing.cpp && ./_quad
    === QUADRATIC PROBING HASH TABLE ===

    Input Array: [26, 30, 45, 23, 25, 43, 74, 19, 29]

    --- INSERTION PHASE ---

    Inserting 26:
    Direct insert at index 6 (no collision)

    Inserting 30:
    Direct insert at index 0 (no collision)

    Inserting 45:
    Direct insert at index 5 (no collision)

    Inserting 23:
    Direct insert at index 3 (no collision)

    Inserting 25:
    Quadratic probing for key 25 (hash = 5):
        Try index 5 (i=0): occupied
        Try index 6 (i=1): occupied
        Found empty slot at index 9 (i=2)

    Inserting 43:
    Quadratic probing for key 43 (hash = 3):
        Try index 3 (i=0): occupied
        Found empty slot at index 4 (i=1)

    Inserting 74:
    Quadratic probing for key 74 (hash = 4):
        Try index 4 (i=0): occupied
        Try index 5 (i=1): occupied
        Found empty slot at index 8 (i=2)

    Inserting 19:
    Quadratic probing for key 19 (hash = 9):
        Try index 9 (i=0): occupied
        Try index 0 (i=1): occupied
        Try index 3 (i=2): occupied
        Try index 8 (i=3): occupied
        Try index 5 (i=4): occupied
        Try index 4 (i=5): occupied
        Try index 5 (i=6): occupied
        Try index 8 (i=7): occupied
        Try index 3 (i=8): occupied
        Try index 0 (i=9): occupied
        Table full or no slot found!
    Cannot insert 19 - table full!

    Inserting 29:
    Quadratic probing for key 29 (hash = 9):
        Try index 9 (i=0): occupied
        Try index 0 (i=1): occupied
        Try index 3 (i=2): occupied
        Try index 8 (i=3): occupied
        Try index 5 (i=4): occupied
        Try index 4 (i=5): occupied
        Try index 5 (i=6): occupied
        Try index 8 (i=7): occupied
        Try index 3 (i=8): occupied
        Try index 0 (i=9): occupied
        Table full or no slot found!
    Cannot insert 29 - table full!

    --- FINAL HASH TABLE ---
    HT: [30, 0, 0, 23, 43, 45, 26, 0, 74, 25]

    --- SEARCH PHASE ---
    Key 25 found at index: 9
    Key 35 NOT found
    Key 43 found at index: 4
    benraiss@Mbareks-MacBook-Air hashing %+

    i=0: Try (5 + 0²) % 10 = 5  → occupied (45)
    i=1: Try (5 + 1²) % 10 = 6  → occupied (26)
    i=2: Try (5 + 2²) % 10 = 9  → EMPTY! Insert at 9

*/