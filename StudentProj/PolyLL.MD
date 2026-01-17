# **Deep Dive: Polynomial Linked List Program Execution**

    benraiss@MacBookAir StudentProj % clang -std=c17 -Wall -Wextra -o poly_ll PolyLL.c
    benraiss@MacBookAir StudentProj % ./poly_ll
    ═══════════════════════════════════════════════════════
    POLYNOMIAL REPRESENTATION USING LINKED LIST
    ═══════════════════════════════════════════════════════

    ═══ CREATE POLYNOMIAL FROM USER INPUT ═══
    Enter number of terms: 3
    Enter terms (coefficient exponent):
    Term 1 (coeff exp): 5 3
    Term 2 (coeff exp): 4 2
    Term 3 (coeff exp): 2 1

    Your Polynomial: 5x^3 + 4x^2 + 2x
    Enter value of x to evaluate: 1
    P(1) = 11

    ═══ CREATE POLYNOMIAL FROM ARRAY ═══
    Creating Polynomial with 4 terms.
    Polynomial: 5x^3 - 3x^2 + 2x - 1
    Enter value of x to evaluate: 1
    P(1) = 3

    ═══════════════════════════════════════════════════════
    Program completed successfully!
    benraiss@MacBookAir StudentProj %

**every single step** of this program execution with memory diagrams, assembly level insights, and mathematical verification.

---

## ** PART 1: Compilation Process**

```bash
clang -std=c17 -Wall -Wextra -o poly_ll PolyLL.c
```

### **What Happens During Compilation:**

```
┌─────────────────────────────────────────────────────┐
│  COMPILATION PIPELINE                               │
├─────────────────────────────────────────────────────┤
│                                                     │
│  PolyLL.c (Source Code)                            │
│       ↓                                            │
│  [PREPROCESSING] (#include, #define expansion)      │
│       ↓                                            │
│  Expanded Source                                    │
│       ↓                                            │
│  [COMPILATION] (C → Assembly)                       │
│       ↓                                            │
│  PolyLL.s (Assembly Code)                          │
│       ↓                                            │
│  [ASSEMBLY] (Assembly → Machine Code)               │
│       ↓                                            │
│  PolyLL.o (Object File)                            │
│       ↓                                            │
│  [LINKING] (Link with libc, libm)                  │
│       ↓                                            │
│  poly_ll (Executable Binary)                       │
│                                                     │
└─────────────────────────────────────────────────────┘
```

**Flags Explained:**
- `-std=c17`: Use C17 standard (latest ISO C)
- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-o poly_ll`: Output executable named `poly_ll`

**Important:** You need `-lm` flag to link math library for `pow()`:
```bash
clang -std=c17 -Wall -Wextra -o poly_ll PolyLL.c -lm
```

---

## **📋 PART 2: Program Execution - User Input Polynomial**

### **Step 1: Program Launch**

```bash
./poly_ll
```

**Memory Layout at Start:**

```
┌──────────────────────────────────────┐
│  TEXT SEGMENT (Code)                 │  ← Read-only, executable
│  - main() instructions               │
│  - create() instructions             │
│  - display() instructions            │
│  - Eval() instructions               │
└──────────────────────────────────────┘

┌──────────────────────────────────────┐
│  DATA SEGMENT (Global Variables)     │
│  poly = NULL                         │  ← 0x0000000000000000
└──────────────────────────────────────┘

┌──────────────────────────────────────┐
│  HEAP (Dynamic Memory)               │
│  [Empty - grows upward →]            │
└──────────────────────────────────────┘

┌──────────────────────────────────────┐
│  STACK (Local Variables)             │
│  [Empty - grows downward ←]          │
└──────────────────────────────────────┘
```

---

### **Step 2: User Enters "3" for Number of Terms**

```
Enter number of terms: 3
```

**What happens in `create()` function:**

```c
void create()
{
    struct Node *t, *last = NULL;  // Line 20
    int num, i;                     // Line 21
    
    scanf("%d", &num);              // Line 24: Reads 3
```

**Stack Memory After Line 24:**

```
STACK FRAME for create():
┌─────────────────────────────┐
│ Return address: 0x7fff...   │  ← Where to return after create()
├─────────────────────────────┤
│ t    = 0x????????????       │  ← Uninitialized pointer (garbage)
│ last = NULL (0x0)           │  ← Initialized to NULL
│ num  = 3                    │  ← User input
│ i    = ????????             │  ← Uninitialized (garbage)
└─────────────────────────────┘
```

---

### **Step 3: Creating First Term (5, 3)**

```
Term 1 (coeff exp): 5 3
```

**Code Execution:**

```c
for (i = 0; i < num; i++)  // i = 0, num = 3
{
    t = (struct Node *)malloc(sizeof(struct Node));  // Line 29
    scanf("%d %d", &t->coeff, &t->exp);              // Line 31: Reads 5, 3
    t->next = NULL;                                  // Line 32
```

**Heap Allocation:**

```
HEAP MEMORY:
┌─────────────────────────────────────┐
│ Address: 0x600000004000             │  ← malloc returns this
├─────────────────────────────────────┤
│ coeff: 5        (4 bytes)           │  ← scanf sets this
│ exp:   3        (4 bytes)           │  ← scanf sets this
│ next:  NULL     (8 bytes on 64-bit) │  ← We set this
└─────────────────────────────────────┘
        ↑
        │
        t points here
```

**Stack After Malloc:**

```
STACK:
┌─────────────────────────────┐
│ t    = 0x600000004000       │  ← ✅ Points to heap
│ last = NULL                 │
│ num  = 3                    │
│ i    = 0                    │  ← Loop counter
└─────────────────────────────┘
```

**Linking First Node:**

```c
if (poly == NULL)  // True (first node)
{
    poly = last = t;  // Line 36
}
```

**Memory After Line 36:**

```
GLOBAL:
poly = 0x600000004000  ← Points to first node

STACK:
last = 0x600000004000  ← Same address

HEAP at 0x600000004000:
┌─────────────────┐
│ coeff: 5        │
│ exp:   3        │  → Represents 5x³
│ next:  NULL     │
└─────────────────┘
     ↑         ↑
   poly      last
```

---

### **Step 4: Creating Second Term (4, 2)**

```
Term 2 (coeff exp): 4 2
```

**Loop Iteration 2 (i = 1):**

```c
t = (struct Node *)malloc(sizeof(struct Node));  // New allocation
scanf("%d %d", &t->coeff, &t->exp);              // Reads 4, 2
t->next = NULL;
```

**New Heap Allocation:**

```
HEAP at 0x600000004020:  ← New address
┌─────────────────┐
│ coeff: 4        │
│ exp:   2        │  → Represents 4x²
│ next:  NULL     │
└─────────────────┘
     ↑
     t
```

**Linking Second Node:**

```c
else
{
    last->next = t;  // Line 40: Link last node to new node
    last = t;        // Line 41: Update last pointer
}
```

**Memory After Linking:**

```
         0x600000004000              0x600000004020
        ┌─────────────────┐        ┌─────────────────┐
poly →  │ coeff: 5        │     ┌→ │ coeff: 4        │
        │ exp:   3        │     │  │ exp:   2        │
        │ next:  ────────────────┘  │ next:  NULL     │
        └─────────────────┘        └─────────────────┘
                                         ↑
                                       last
```

---

### **Step 5: Creating Third Term (2, 1)**

```
Term 3 (coeff exp): 2 1
```

**Loop Iteration 3 (i = 2):**

**Final Linked List Structure:**

```
         0x...4000              0x...4020              0x...4040
        ┌───────────┐         ┌───────────┐         ┌───────────┐
poly →  │ coeff: 5  │    ┌→   │ coeff: 4  │    ┌→   │ coeff: 2  │
        │ exp:   3  │    │    │ exp:   2  │    │    │ exp:   1  │
        │ next: ────────┘     │ next: ────────┘     │ next: NULL│
        └───────────┘         └───────────┘         └───────────┘
            5x³                   4x²                    2x
                                                          ↑
                                                        last
```

---

### **Step 6: Display Polynomial**

```c
display(poly);
```

**Execution Flow:**

```c
void display(struct Node *p)  // p = poly (0x...4000)
{
    int isFirst = 1;
    
    while (p)
    {
        // Iteration 1: p points to [5, 3]
        if (p->coeff > 0 && !isFirst)  // 5 > 0 && isFirst=1 → False
            printf(" + ");
        
        int absCoeff = 5;
        printf("%dx^%d", 5, 3);  // Prints: 5x^3
        
        p = p->next;  // Move to [4, 2]
        isFirst = 0;
        
        // Iteration 2: p points to [4, 2]
        if (p->coeff > 0 && !isFirst)  // 4 > 0 && isFirst=0 → True
            printf(" + ");  // Prints: " + "
        
        printf("%dx^%d", 4, 2);  // Prints: 4x^2
        
        p = p->next;  // Move to [2, 1]
        
        // Iteration 3: p points to [2, 1]
        printf(" + ");  // Prints: " + "
        printf("%dx", 2);  // Prints: 2x (exp=1, special case)
        
        p = p->next;  // p = NULL, loop exits
    }
    printf("\n");
}
```

**Output:** `5x^3 + 4x^2 + 2x`

---

### **Step 7: Evaluate Polynomial at x = 1**

```
Enter value of x to evaluate: 1
```

**Mathematical Calculation:**

```
P(x) = 5x³ + 4x² + 2x
P(1) = 5(1)³ + 4(1)² + 2(1)
P(1) = 5·1 + 4·1 + 2·1
P(1) = 5 + 4 + 2
P(1) = 11
```

**Code Execution in `Eval()`:**

```c
long Eval(struct Node *p, int x)  // p = poly, x = 1
{
    long val = 0;
    
    while (p)
    {
        // Iteration 1: p = [5, 3]
        val += 5 * pow(1, 3);  // val = 0 + 5*1 = 5
        p = p->next;
        
        // Iteration 2: p = [4, 2]
        val += 4 * pow(1, 2);  // val = 5 + 4*1 = 9
        p = p->next;
        
        // Iteration 3: p = [2, 1]
        val += 2 * pow(1, 1);  // val = 9 + 2*1 = 11
        p = p->next;
        
        // p = NULL, loop exits
    }
    return 11;
}
```

**Output:** `P(1) = 11` 

---

### **Step 8: Free Memory**

```c
freePoly(poly);
poly = NULL;
```

**Deallocation Process:**

```c
void freePoly(struct Node *p)
{
    struct Node *temp;
    while (p)
    {
        // Free node 1: [5, 3]
        temp = p;              // temp → 0x...4000
        p = p->next;           // p → 0x...4020
        free(temp);            // Deallocate 0x...4000
        
        // Free node 2: [4, 2]
        temp = p;              // temp → 0x...4020
        p = p->next;           // p → 0x...4040
        free(temp);            // Deallocate 0x...4020
        
        // Free node 3: [2, 1]
        temp = p;              // temp → 0x...4040
        p = p->next;           // p → NULL
        free(temp);            // Deallocate 0x...4040
        
        // p = NULL, loop exits
    }
}
```

**Memory After Free:**

```
HEAP:
[All nodes deallocated - memory returned to OS]

GLOBAL:
poly = NULL  ← Set by main()
```

---

## ** PART 3: Array-Based Polynomial Creation**

```c
int coeffs[] = {5, -3, 2, -1};
int exps[] = {3, 2, 1, 0};
createPolynomial(coeffs, exps, 4);
```

**Creates:**

```
    0x...5000          0x...5020          0x...5040          0x...5060
   ┌──────────┐      ┌──────────┐      ┌──────────┐      ┌──────────┐
   │ coeff: 5 │  ┌→  │ coeff:-3 │  ┌→  │ coeff: 2 │  ┌→  │ coeff:-1 │
   │ exp:   3 │  │   │ exp:   2 │  │   │ exp:   1 │  │   │ exp:   0 │
   │ next: ──────┘   │ next: ──────┘   │ next: ──────┘   │ next:NULL│
   └──────────┘      └──────────┘      └──────────┘      └──────────┘
       5x³              -3x²              2x                 -1
```

**Display Output:** `5x^3 - 3x^2 + 2x - 1`

---

### **Evaluation at x = 1:**

```
P(x) = 5x³ - 3x² + 2x - 1
P(1) = 5(1)³ - 3(1)² + 2(1) - 1
P(1) = 5 - 3 + 2 - 1
P(1) = 3 ✅
```

**Step-by-Step in `Eval()`:**

```c
val = 0
val += 5 * pow(1, 3)   // val = 0 + 5 = 5
val += -3 * pow(1, 2)  // val = 5 - 3 = 2
val += 2 * pow(1, 1)   // val = 2 + 2 = 4
val += -1 * pow(1, 0)  // val = 4 - 1 = 3
return 3;
```

---

## ** Complete Memory Timeline**

```
TIME →

T0: Program starts
    ├─ poly = NULL
    └─ Heap empty

T1: First malloc (5x³)
    ├─ Heap: [5,3] → NULL
    └─ poly → [5,3]

T2: Second malloc (4x²)
    ├─ Heap: [5,3] → [4,2] → NULL
    └─ last → [4,2]

T3: Third malloc (2x)
    ├─ Heap: [5,3] → [4,2] → [2,1] → NULL
    └─ last → [2,1]

T4: Display traversal
    └─ Output: 5x^3 + 4x^2 + 2x

T5: Evaluation (x=1)
    └─ Returns: 11

T6: Free memory
    ├─ free([5,3])
    ├─ free([4,2])
    ├─ free([2,1])
    └─ poly = NULL

T7: Create array polynomial
    ├─ Heap: [5,3] → [-3,2] → [2,1] → [-1,0] → NULL
    └─ Output: 5x^3 - 3x^2 + 2x - 1

T8: Evaluation (x=1)
    └─ Returns: 3

T9: Free memory & exit
    └─ All memory deallocated
```

---

## ** Key Concepts Demonstrated**

1. **Dynamic Memory Allocation** - `malloc()` creates nodes on heap
2. **Linked List Traversal** - `while (p) { p = p->next; }`
3. **Pointer Manipulation** - `last->next = t`
4. **Mathematical Evaluation** - `pow(x, exp)`
5. **Memory Management** - `free()` prevents leaks
6. **Sign Handling** - Display correctly shows `-` for negative terms


Visual Representation of Your Polynomial :
Polynomial: 5x^3 + 4x^2 + 2x

Linked List Structure:
┌─────────┐    ┌─────────┐    ┌─────────┐
│ coeff: 5│ →  │ coeff: 4│ →  │ coeff: 2│ → NULL
│ exp:   3│    │ exp:   2│    │ exp:   1│
└─────────┘    └─────────┘    └─────────┘
    ↑
   poly

Graph (at x=1):
  P(x)
   |
11 |           ●  (1, 11)
   |         ,'
   |       ,'
   |     ,'
   |   ,'
   | ,'
   |'_______________
   0               x