# Complete Guide to C Format Specifiers (`printf` & `scanf`)

## 📖 Table of Contents

1. [Introduction](#introduction)
2. [Integer Format Specifiers](#integer-format-specifiers)
3. [Floating Point Format Specifiers](#floating-point-format-specifiers)
4. [Character & String Format Specifiers](#character--string-format-specifiers)
5. [Pointer & Hexadecimal Format Specifiers](#pointer--hexadecimal-format-specifiers)
6. [Width Specifiers](#width-specifiers)
7. [Precision Specifiers](#precision-specifiers)
8. [Flags](#flags)
9. [Real-World Examples](#real-world-examples)
10. [Common Mistakes](#common-mistakes)
11. [Quick Reference Card](#quick-reference-card)

---

## Introduction

**Format specifiers** are special sequences in C that tell `printf()` and `scanf()` functions:

- What **type of data** to expect
- How to **format** the output

**Syntax:**

```
%[flags][width][.precision][length]specifier
```

**Example:**

```c
printf("%d", 42);        // Print integer
printf("%s", "Hello");   // Print string
printf("%.2f", 3.14159); // Print float with 2 decimal places
```

---

## Integer Format Specifiers

### Basic Integer Types

| Specifier | Type           | Description                                | Example              | Output |
| --------- | -------------- | ------------------------------------------ | -------------------- | ------ |
| `%d`      | `int`          | Signed decimal integer                     | `printf("%d", 42);`  | `42`   |
| `%i`      | `int`          | Signed decimal integer (identical to `%d`) | `printf("%i", -15);` | `-15`  |
| `%u`      | `unsigned int` | Unsigned decimal integer                   | `printf("%u", 42);`  | `42`   |
| `%o`      | `int`          | Octal (base 8)                             | `printf("%o", 8);`   | `10`   |
| `%x`      | `int`          | Hexadecimal (lowercase)                    | `printf("%x", 255);` | `ff`   |
| `%X`      | `int`          | Hexadecimal (uppercase)                    | `printf("%X", 255);` | `FF`   |

### Size Modifiers for Integers

| Specifier | Type                 | Description                     | Example                                    | Output                 |
| --------- | -------------------- | ------------------------------- | ------------------------------------------ | ---------------------- |
| `%hd`     | `short`              | Short signed integer            | `printf("%hd", (short)100);`               | `100`                  |
| `%hu`     | `unsigned short`     | Short unsigned integer          | `printf("%hu", (unsigned short)100);`      | `100`                  |
| `%ld`     | `long`               | Long signed integer             | `printf("%ld", 1000000L);`                 | `1000000`              |
| `%lu`     | `unsigned long`      | Long unsigned integer           | `printf("%lu", 1000000UL);`                | `1000000`              |
| `%lld`    | `long long`          | Long long signed integer (C99+) | `printf("%lld", 9223372036854775807LL);`   | `9223372036854775807`  |
| `%llu`    | `unsigned long long` | Long long unsigned integer      | `printf("%llu", 18446744073709551615ULL);` | `18446744073709551615` |

### Integer Examples

```c
int x = 42;
unsigned int y = 4294967295U;
long z = 1000000L;
short s = 100;

printf("Integer: %d\n", x);              // Integer: 42
printf("Unsigned: %u\n", y);             // Unsigned: 4294967295
printf("Long: %ld\n", z);                // Long: 1000000
printf("Short: %hd\n", s);               // Short: 100
printf("Hex (lowercase): %x\n", x);      // Hex (lowercase): 2a
printf("Hex (uppercase): %X\n", x);      // Hex (uppercase): 2A
printf("Octal: %o\n", x);                // Octal: 52
```

---

## Floating Point Format Specifiers

| Specifier | Type           | Description                            | Example                    | Output                 |
| --------- | -------------- | -------------------------------------- | -------------------------- | ---------------------- |
| `%f`      | `float/double` | Decimal floating point                 | `printf("%f", 3.14);`      | `3.140000`             |
| `%F`      | `float/double` | Decimal floating point (same as `%f`)  | `printf("%F", 3.14);`      | `3.140000`             |
| `%e`      | `float/double` | Scientific notation (lowercase)        | `printf("%e", 1234.5);`    | `1.234500e+03`         |
| `%E`      | `float/double` | Scientific notation (uppercase)        | `printf("%E", 1234.5);`    | `1.234500E+03`         |
| `%g`      | `float/double` | Shortest of `%f` or `%e`               | `printf("%g", 0.0001);`    | `0.0001`               |
| `%G`      | `float/double` | Shortest of `%f` or `%E`               | `printf("%G", 1000000.0);` | `1e+06`                |
| `%a`      | `float/double` | Hexadecimal floating point (lowercase) | `printf("%a", 3.14);`      | `0x1.91eb851eb851fp+1` |
| `%A`      | `float/double` | Hexadecimal floating point (uppercase) | `printf("%A", 3.14);`      | `0X1.91EB851EB851FP+1` |

### Size Modifiers for Floats

| Specifier | Type          | Description                             | Usage                   |
| --------- | ------------- | --------------------------------------- | ----------------------- |
| `%f`      | `double`      | For `printf` (float promoted to double) | `printf("%f", 3.14);`   |
| `%lf`     | `double`      | For `scanf` (required for double)       | `scanf("%lf", &d);`     |
| `%Lf`     | `long double` | Long double                             | `printf("%Lf", 3.14L);` |

### Floating Point Examples

```c
float f = 3.14159f;
double d = 2.718281828;
long double ld = 3.141592653589793238L;

printf("Float: %f\n", f);                // Float: 3.141590
printf("Double: %f\n", d);               // Double: 2.718282
printf("Long double: %Lf\n", ld);        // Long double: 3.141593

// Precision control
printf("2 decimals: %.2f\n", f);         // 2 decimals: 3.14
printf("5 decimals: %.5f\n", f);         // 5 decimals: 3.14159

// Scientific notation
printf("Scientific: %e\n", 1234.5);      // Scientific: 1.234500e+03
printf("Scientific: %E\n", 1234.5);      // Scientific: 1.234500E+03

// Shortest representation
printf("%%g: %g\n", 0.0001);             // %g: 0.0001
printf("%%g: %g\n", 1000000.0);          // %g: 1e+06
```

---

## Character & String Format Specifiers

| Specifier | Type    | Description            | Example                  | Output  |
| --------- | ------- | ---------------------- | ------------------------ | ------- |
| `%c`      | `char`  | Single character       | `printf("%c", 'A');`     | `A`     |
| `%s`      | `char*` | Null-terminated string | `printf("%s", "Hello");` | `Hello` |

### Character & String Examples

```c
char c = 'X';
char str[] = "Hello, World!";
char name[50] = "Alice";

printf("Character: %c\n", c);            // Character: X
printf("String: %s\n", str);             // String: Hello, World!
printf("Name: %s\n", name);              // Name: Alice

// ASCII value of character
printf("ASCII of '%c': %d\n", c, c);     // ASCII of 'X': 88

// Limited string output
printf("First 5 chars: %.5s\n", str);    // First 5 chars: Hello
```

---

## Pointer & Hexadecimal Format Specifiers

| Specifier | Type    | Description                              | Example                      | Output              |
| --------- | ------- | ---------------------------------------- | ---------------------------- | ------------------- |
| `%p`      | `void*` | Pointer address (implementation-defined) | `printf("%p", ptr);`         | `0x7ffeeb3c8a10`    |
| `%n`      | `int*`  | Write number of chars printed so far     | `printf("Hello%n", &count);` | (stores 5 in count) |

### Pointer Examples

```c
int x = 42;
int *ptr = &x;
struct Node *node = malloc(sizeof(struct Node));

printf("Address of x: %p\n", (void*)&x);     // Address of x: 0x7ffeeb3c8a10
printf("Pointer value: %p\n", (void*)ptr);   // Pointer value: 0x7ffeeb3c8a10
printf("Node address: %p\n", (void*)node);   // Node address: 0x7ffeeb3c8b20

// Count characters printed
int count;
printf("Hello%n World\n", &count);           // Hello World
printf("Characters printed: %d\n", count);   // Characters printed: 5
```

### Special Characters

| Specifier | Description          | Example                     | Output           |
| --------- | -------------------- | --------------------------- | ---------------- |
| `%%`      | Literal percent sign | `printf("100%%");`          | `100%`           |
| `\n`      | Newline              | `printf("Line 1\nLine 2");` | Line 1<br>Line 2 |
| `\t`      | Tab                  | `printf("Col1\tCol2");`     | Col1 Col2        |
| `\r`      | Carriage return      | `printf("Hello\rX");`       | Xello            |
| `\\`      | Backslash            | `printf("C:\\path");`       | C:\path          |
| `\"`      | Double quote         | `printf("Say \"Hi\"");`     | Say "Hi"         |
| `\'`      | Single quote         | `printf("It\'s OK");`       | It's OK          |

---

## Width Specifiers

Width specifiers set the **minimum number of characters** to output.

### Syntax

```c
%[width]specifier
```

### Examples

```c
int x = 42;

// Right-aligned (default)
printf("%5d", x);        // →    42  (3 spaces + 42)
printf("%10d", x);       // →        42  (8 spaces + 42)

// Left-aligned (use - flag)
printf("%-5d", x);       // → 42     (42 + 3 spaces)
printf("%-10d", x);      // → 42        (42 + 8 spaces)

// Zero-padding (use 0 flag)
printf("%05d", x);       // → 00042
printf("%010d", x);      // → 0000000042
```

### Practical Example: Table Formatting

```c
printf("%-10s %5s %8s\n", "Name", "Age", "Salary");
printf("%-10s %5d %8.2f\n", "Alice", 30, 75000.50);
printf("%-10s %5d %8.2f\n", "Bob", 25, 60000.00);
printf("%-10s %5d %8.2f\n", "Charlie", 35, 85000.75);

/* Output:
Name         Age   Salary
Alice         30  75000.50
Bob           25  60000.00
Charlie       35  85000.75
*/
```

---

## Precision Specifiers

Precision controls:

- For **floating point**: number of digits after decimal
- For **strings**: maximum characters to print
- For **integers**: minimum digits (zero-padded)

### Syntax

```c
%[.precision]specifier
```

### Floating Point Precision

```c
float pi = 3.14159265359;

printf("%.2f", pi);      // → 3.14
printf("%.5f", pi);      // → 3.14159
printf("%.0f", pi);      // → 3
printf("%10.2f", pi);    // →       3.14  (width 10, precision 2)
```

### String Precision

```c
char str[] = "Hello, World!";

printf("%.5s\n", str);   // → Hello
printf("%.8s\n", str);   // → Hello, W
printf("%10.5s\n", str); // →      Hello  (width 10, max 5 chars)
```

### Integer Precision

```c
int x = 42;

printf("%.5d\n", x);     // → 00042  (min 5 digits, zero-padded)
printf("%.10d\n", x);    // → 0000000042
printf("%10.5d\n", x);   // →      00042  (width 10, min 5 digits)
```

---

## Flags

Flags modify the output format.

| Flag        | Description                   | Example                | Output       |
| ----------- | ----------------------------- | ---------------------- | ------------ |
| `-`         | Left-align within field       | `printf("%-10d", 42);` | `42        ` |
| `+`         | Always show sign (+ or -)     | `printf("%+d", 42);`   | `+42`        |
| ` ` (space) | Space for positive numbers    | `printf("% d", 42);`   | ` 42`        |
| `0`         | Zero-pad instead of space-pad | `printf("%05d", 42);`  | `00042`      |
| `#`         | Alternate form                | `printf("%#x", 255);`  | `0xff`       |

### Flag Examples

```c
int x = 42;
int y = -15;

// Left-align
printf("'%-5d'\n", x);       // '42   '
printf("'%-5d'\n", y);       // '-15  '

// Always show sign
printf("%+d\n", x);          // +42
printf("%+d\n", y);          // -15

// Space for positive
printf("% d\n", x);          // ' 42'
printf("% d\n", y);          // '-15'

// Zero-padding
printf("%05d\n", x);         // 00042
printf("%05d\n", y);         // -0015

// Alternate form (hex/octal)
printf("%#x\n", 255);        // 0xff
printf("%#X\n", 255);        // 0XFF
printf("%#o\n", 8);          // 010

// Alternate form (float - always show decimal)
printf("%#.0f\n", 5.0);      // 5.

// Combining flags
printf("%+010d\n", x);       // +000000042
printf("%-+10d\n", x);       // +42
```

---

## Real-World Examples

### Example 1: Linked List Node Display

```c
struct Node {
    int data;
    struct Node *next;
};

void display(struct Node *p) {
    while (p != NULL) {
        printf("%d -> ", p->data);
        //     ││  │
        //     ││  └─ Literal string
        //     │└──── p->data (integer)
        //     └───── Decimal integer format
        p = p->next;
    }
    printf("NULL\n");
}

// Output: 10 -> 20 -> 30 -> NULL
```

### Example 2: Debug Output with Pointers

```c
struct Node *node = malloc(sizeof(struct Node));
node->data = 42;

printf("Node at address %p contains data: %d\n", (void*)node, node->data);
// Output: Node at address 0x7ffeeb3c8a10 contains data: 42

printf("Next pointer: %p\n", (void*)node->next);
// Output: Next pointer: (nil)
```

### Example 3: Matrix Display

```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

printf("Matrix:\n");
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        printf("%4d ", matrix[i][j]);  // Width 4, right-aligned
    }
    printf("\n");
}

/* Output:
Matrix:
   1    2    3
   4    5    6
   7    8    9
*/
```

### Example 4: Financial Report

```c
printf("╔══════════════════════════════════════════╗\n");
printf("║         MONTHLY FINANCIAL REPORT         ║\n");
printf("╠══════════════════════════════════════════╣\n");
printf("║ %-20s %15s ║\n", "Category", "Amount");
printf("╠══════════════════════════════════════════╣\n");
printf("║ %-20s $%14.2f ║\n", "Revenue", 125000.50);
printf("║ %-20s $%14.2f ║\n", "Expenses", 87500.25);
printf("╠══════════════════════════════════════════╣\n");
printf("║ %-20s $%14.2f ║\n", "Profit", 37500.25);
printf("╚══════════════════════════════════════════╝\n");

/* Output:
╔══════════════════════════════════════════╗
║         MONTHLY FINANCIAL REPORT         ║
╠══════════════════════════════════════════╣
║ Category                         Amount ║
╠══════════════════════════════════════════╣
║ Revenue              $     125000.50 ║
║ Expenses             $      87500.25 ║
╠══════════════════════════════════════════╣
║ Profit               $      37500.25 ║
╚══════════════════════════════════════════╝
*/
```

### Example 5: Progress Bar

```c
void print_progress(int percent) {
    int width = 50;
    int filled = (percent * width) / 100;

    printf("\rProgress: [");
    for (int i = 0; i < width; i++) {
        if (i < filled)
            printf("█");
        else
            printf(" ");
    }
    printf("] %3d%%", percent);
    fflush(stdout);
}

// Usage:
for (int i = 0; i <= 100; i += 10) {
    print_progress(i);
    sleep(1);
}

// Output: Progress: [█████████████████████████                         ]  50%
```

### Example 6: Binary, Octal, Hex Display

```c
int num = 255;

printf("Number: %d\n", num);
printf("Binary: ");
for (int i = 7; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
}
printf("\n");
printf("Octal: %o\n", num);
printf("Hex (lowercase): %x\n", num);
printf("Hex (uppercase): %X\n", num);
printf("Hex (with 0x): %#x\n", num);

/* Output:
Number: 255
Binary: 11111111
Octal: 377
Hex (lowercase): ff
Hex (uppercase): FF
Hex (with 0x): 0xff
*/
```

---

## Common Mistakes

### ❌ Mistake 1: Wrong Specifier for Type

```c
// WRONG: %f expects double, not int
int x = 42;
printf("%f", x);  // ⚠️ Undefined behavior!

// CORRECT:
printf("%d", x);
```

### ❌ Mistake 2: Missing Arguments

```c
// WRONG: Missing 2nd argument
printf("Values: %d, %d\n", 10);  // ⚠️ Undefined behavior!

// CORRECT:
printf("Values: %d, %d\n", 10, 20);
```

### ❌ Mistake 3: Type Mismatch

```c
// WRONG: float vs double in scanf
double d;
scanf("%f", &d);  // ⚠️ Wrong! Use %lf for double

// CORRECT:
scanf("%lf", &d);

// NOTE: printf uses %f for both float and double
printf("%f", d);  // ✅ Correct
```

### ❌ Mistake 4: Forgetting Address Operator in scanf

```c
int x;

// WRONG: Missing & operator
scanf("%d", x);   // ⚠️ Wrong! Undefined behavior

// CORRECT:
scanf("%d", &x);
```

### ❌ Mistake 5: Buffer Overflow with %s

```c
char name[10];

// DANGEROUS: No limit on input
scanf("%s", name);  // ⚠️ Can overflow buffer!

// SAFER:
scanf("%9s", name);  // Limit to 9 chars + null terminator
```

### ❌ Mistake 6: Using %lf in printf (Unnecessary)

```c
double d = 3.14;

// Works but unnecessary (both are equivalent)
printf("%lf", d);  // ⚠️ Redundant 'l' modifier
printf("%f", d);   // ✅ Better

// NOTE: scanf REQUIRES %lf for double!
scanf("%lf", &d);  // ✅ Correct
```

### ❌ Mistake 7: Not Casting Pointer for %p

```c
int *ptr;

// May produce warnings
printf("%p", ptr);  // ⚠️ Some compilers warn

// CORRECT:
printf("%p", (void*)ptr);  // ✅ Cast to void*
```

---

## Quick Reference Card

### 📊 Essential Specifiers

```
═══════════════════════════════════════════════════════════════
                    INTEGER TYPES
═══════════════════════════════════════════════════════════════
%d, %i      Signed decimal integer
%u          Unsigned decimal integer
%ld         Long signed integer
%lld        Long long signed integer
%hd         Short signed integer
%o          Octal
%x, %X      Hexadecimal (lowercase/uppercase)

═══════════════════════════════════════════════════════════════
                    FLOATING POINT
═══════════════════════════════════════════════════════════════
%f          Decimal floating point (default 6 decimals)
%e, %E      Scientific notation (lowercase/uppercase)
%g, %G      Shortest of %f or %e
%lf         Double (scanf only)
%Lf         Long double

═══════════════════════════════════════════════════════════════
                    CHAR & STRING
═══════════════════════════════════════════════════════════════
%c          Single character
%s          Null-terminated string

═══════════════════════════════════════════════════════════════
                    POINTER & SPECIAL
═══════════════════════════════════════════════════════════════
%p          Pointer address
%n          Store number of chars printed
%%          Literal % character

═══════════════════════════════════════════════════════════════
                    WIDTH & PRECISION
═══════════════════════════════════════════════════════════════
%5d         Minimum width 5 (right-aligned)
%-5d        Minimum width 5 (left-aligned)
%05d        Zero-padded width 5
%.2f        2 decimal places
%10.2f      Width 10, 2 decimal places
%.5s        Max 5 characters from string

═══════════════════════════════════════════════════════════════
                         FLAGS
═══════════════════════════════════════════════════════════════
-           Left-align within field
+           Always show sign (+ or -)
(space)     Space for positive numbers
0           Zero-pad instead of space-pad
#           Alternate form (0x for hex, 0 for octal)

═══════════════════════════════════════════════════════════════
```

### 🎯 Common Patterns

```c
// Integers
printf("%d", x);              // 42
printf("%5d", x);             // "   42"
printf("%-5d", x);            // "42   "
printf("%05d", x);            // "00042"
printf("%+d", x);             // "+42"

// Floats
printf("%f", f);              // 3.140000
printf("%.2f", f);            // 3.14
printf("%10.2f", f);          // "      3.14"
printf("%e", f);              // 3.140000e+00

// Strings
printf("%s", str);            // "Hello"
printf("%10s", str);          // "     Hello"
printf("%-10s", str);         // "Hello     "
printf("%.3s", str);          // "Hel"

// Pointers
printf("%p", (void*)ptr);     // 0x7ffeeb3c8a10

// Hex
printf("%x", 255);            // ff
printf("%X", 255);            // FF
printf("%#x", 255);           // 0xff
```

---

## 📚 Practice Problems

### Problem 1: Format a Table

Create a formatted table of students with columns: Name (15 chars), Age (3 chars), GPA (5 chars with 2 decimals).

**Expected Output:**

```
Name              Age   GPA
Alice              20  3.85
Bob                22  3.67
Charlie            21  3.92
```

**Solution:**

```c
printf("%-15s %3s %5s\n", "Name", "Age", "GPA");
printf("%-15s %3d %5.2f\n", "Alice", 20, 3.85);
printf("%-15s %3d %5.2f\n", "Bob", 22, 3.67);
printf("%-15s %3d %5.2f\n", "Charlie", 21, 3.92);
```

### Problem 2: Display Memory Address

Print a node's address and data in this format: `Node[0x7ffeeb3c8a10] = 42`

**Solution:**

```c
struct Node *node = malloc(sizeof(struct Node));
node->data = 42;
printf("Node[%p] = %d\n", (void*)node, node->data);
```

### Problem 3: Right-Aligned Numbers

Print numbers 1-10 right-aligned in a column of width 5.

**Solution:**

```c
for (int i = 1; i <= 10; i++) {
    printf("%5d\n", i);
}
```

---

## 📖 Additional Resources

### Abdul Bari's Teaching Style Applied

When learning format specifiers, follow Abdul Bari's approach:

1. **Understand the Concept**: What is a format specifier?
2. **See the Syntax**: `%[flags][width][.precision][length]specifier`
3. **Trace Examples**: Step through printf execution
4. **Practice**: Use in real data structures (linked lists, arrays, etc.)
5. **Apply**: Use in your own programs

### Recommended Practice

```c
// Create a test file to experiment
#include <stdio.h>

int main()
{
    int i = 42;
    long l = 1000000L;
    unsigned int u = 4294967295U;
    float f = 3.14159f;
    double d = 2.718281828;
    char c = 'X';
    char str[] = "Hello";
    int *ptr = &i;

    printf("=== INTEGER ===\n");
    printf("%%d:  %d\n", i);
    printf("%%i:  %i\n", i);
    printf("%%u:  %u\n", u);
    printf("%%ld: %ld\n", l);
    printf("%%x:  %x\n", i);
    printf("%%X:  %X\n", i);
    printf("%%o:  %o\n\n", i);

    printf("=== FLOAT ===\n");
    printf("%%f:    %f\n", f);
    printf("%%.2f:  %.2f\n", f);
    printf("%%e:    %e\n", f);
    printf("%%g:    %g\n\n", f);

    printf("=== CHAR & STRING ===\n");
    printf("%%c: %c\n", c);
    printf("%%s: %s\n\n", str);

    printf("=== POINTER ===\n");
    printf("%%p: %p\n\n", (void*)ptr);

    printf("=== FORMATTING ===\n");
    printf("%%10d:  %10d\n", i);
    printf("%%-10d: %-10d\n", i);
    printf("%%05d:  %05d\n", i);
    printf("%%+d:   %+d\n", i);
    printf("%% d:   % d\n\n", i);

    printf("=== WIDTH & PRECISION ===\n");
    printf("%%10.2f:  %10.2f\n", d);
    printf("%%-10.2f: %-10.2f\n", d);
    printf("%%.5s:    %.5s\n", str);

    return 0;
}
```

---

## 🎓 Summary

**Key Takeaways:**

1. ✅ **Format specifiers** tell printf/scanf what data type to expect
2. ✅ Use `%d` for int, `%f` for float/double, `%c` for char, `%s` for string
3. ✅ Width controls minimum characters: `%10d`
4. ✅ Precision controls decimals/max chars: `%.2f`, `%.5s`
5. ✅ Flags modify alignment and padding: `%-10d`, `%05d`, `%+d`
6. ✅ Always match specifier with data type to avoid undefined behavior
7. ✅ Use `%p` for pointers (cast to `void*`)
8. ✅ Remember: `scanf` needs `%lf` for double, `printf` uses `%f`

---

## 📝 License

This guide is created for educational purposes following Abdul Bari's teaching methodology.

**Created by:** Ben Raiss  
**Date:** January 14, 2026  
**Repository:** MbarekDev-Lab/Implement-Data-Structures-Algorithms-using-C-and-C-

---

**Happy Coding! 🚀**

# **Complete Guide to C Format Specifiers (`printf` & `scanf`)**

## **What are Format Specifiers?**

Format specifiers tell `printf` and `scanf` **what type of data** to expect and **how to format it**.

---

## **📊 Common Format Specifiers**

### **Integer Types**

| Specifier | Type                 | Description                           | Example                                       |
| --------- | -------------------- | ------------------------------------- | --------------------------------------------- |
| `%d`      | `int`                | Signed decimal integer                | `printf("%d", 42);` → `42`                    |
| `%i`      | `int`                | Signed decimal integer (same as `%d`) | `printf("%i", 42);` → `42`                    |
| `%u`      | `unsigned int`       | Unsigned decimal integer              | `printf("%u", 42);` → `42`                    |
| `%ld`     | `long`               | Long signed integer                   | `printf("%ld", 1000000L);` → `1000000`        |
| `%lu`     | `unsigned long`      | Long unsigned integer                 | `printf("%lu", 1000000UL);` → `1000000`       |
| `%lld`    | `long long`          | Long long signed integer              | `printf("%lld", 9223372036854775807LL);`      |
| `%llu`    | `unsigned long long` | Long long unsigned integer            | `printf("%llu", 18446744073709551615ULL);`    |
| `%hd`     | `short`              | Short signed integer                  | `printf("%hd", (short)100);` → `100`          |
| `%hu`     | `unsigned short`     | Short unsigned integer                | `printf("%hu", (unsigned short)100);` → `100` |

---

### **Floating Point Types**

| Specifier | Type           | Description                     | Example                                  |
| --------- | -------------- | ------------------------------- | ---------------------------------------- |
| `%f`      | `float/double` | Decimal floating point          | `printf("%f", 3.14);` → `3.140000`       |
| `%lf`     | `double`       | Double precision (scanf only)   | `scanf("%lf", &d);`                      |
| `%e`      | `float/double` | Scientific notation (lowercase) | `printf("%e", 1234.5);` → `1.234500e+03` |
| `%E`      | `float/double` | Scientific notation (uppercase) | `printf("%E", 1234.5);` → `1.234500E+03` |
| `%g`      | `float/double` | Shortest of `%f` or `%e`        | `printf("%g", 0.0001);` → `0.0001`       |
| `%G`      | `float/double` | Shortest of `%f` or `%E`        | `printf("%G", 0.0001);` → `0.0001`       |

---

### **Character & String Types**

| Specifier | Type    | Description              | Example                            |
| --------- | ------- | ------------------------ | ---------------------------------- |
| `%c`      | `char`  | Single character         | `printf("%c", 'A');` → `A`         |
| `%s`      | `char*` | String (null-terminated) | `printf("%s", "Hello");` → `Hello` |

---

### **Pointer & Hexadecimal**

| Specifier | Type    | Description             | Example                                 |
| --------- | ------- | ----------------------- | --------------------------------------- |
| `%p`      | `void*` | Pointer address         | `printf("%p", ptr);` → `0x7ffeeb3c8a10` |
| `%x`      | `int`   | Hexadecimal (lowercase) | `printf("%x", 255);` → `ff`             |
| `%X`      | `int`   | Hexadecimal (uppercase) | `printf("%X", 255);` → `FF`             |
| `%o`      | `int`   | Octal                   | `printf("%o", 8);` → `10`               |

---

### **Special**

| Specifier | Type   | Description                   | Example                      |
| --------- | ------ | ----------------------------- | ---------------------------- |
| `%%`      | N/A    | Literal `%` character         | `printf("100%%");` → `100%`  |
| `%n`      | `int*` | Write number of chars printed | `printf("Hello%n", &count);` |

---

## **🎯 Format Modifiers (Width, Precision, Flags)**

### **1. Width Specifier**

```c
printf("%5d", 42);      // →    42  (5 chars wide, right-aligned)
printf("%-5d", 42);     // → 42     (5 chars wide, left-aligned)
printf("%05d", 42);     // → 00042  (pad with zeros)
```

### **2. Precision Specifier**

```c
printf("%.2f", 3.14159);    // → 3.14  (2 decimal places)
printf("%.5s", "Hello");    // → Hello (max 5 chars)
printf("%10.2f", 3.14);     // →       3.14 (10 chars wide, 2 decimals)
```

### **3. Flags**

| Flag        | Description        | Example                               |
| ----------- | ------------------ | ------------------------------------- |
| `-`         | Left-align         | `printf("%-10d", 42);` → `42        ` |
| `+`         | Always show sign   | `printf("%+d", 42);` → `+42`          |
| ` ` (space) | Space for positive | `printf("% d", 42);` → ` 42`          |
| `0`         | Pad with zeros     | `printf("%05d", 42);` → `00042`       |
| `#`         | Alternate form     | `printf("%#x", 255);` → `0xff`        |

---

## **📝 Real-World Examples**

### **Example 1: Your Circular Linked List**

```c
printf("%d -> ", h->data);
//     ↑↑
//     ||
//     |└─ Format specifier: decimal integer
//     └── Start of format specifier
```

**Breakdown:**

- `%` - Start of format specifier
- `d` - **Decimal integer** (prints `h->data` as integer)

**Output:** `10 -> 20 -> 30 -> `

---

### **Example 2: Pointer Addresses**

```c
struct Node *p = Head;
printf("Node address: %p, Data: %d\n", (void*)p, p->data);
// Output: Node address: 0x7ffeeb3c8a10, Data: 10
```

---

### **Example 3: Formatted Table**

```c
printf("%-10s %5s %8s\n", "Name", "Age", "Salary");
printf("%-10s %5d %8.2f\n", "Alice", 30, 75000.50);
printf("%-10s %5d %8.2f\n", "Bob", 25, 60000.00);

// Output:
// Name         Age   Salary
// Alice         30  75000.50
// Bob           25  60000.00
```

---

### **Example 4: Multiple Variables**

```c
int x = 10;
float y = 3.14;
char c = 'A';
char *str = "Hello";

printf("Integer: %d, Float: %.2f, Char: %c, String: %s\n", x, y, c, str);
// Output: Integer: 10, Float: 3.14, Char: A, String: Hello
```

---

## **⚠️ Common Mistakes**

### **1. Wrong Specifier for Type**

```c
// ❌ WRONG
int x = 42;
printf("%f", x);  // Undefined behavior! %f expects double, not int

// ✅ CORRECT
printf("%d", x);
```

### **2. Missing Arguments**

```c
// ❌ WRONG
printf("Value: %d, %d\n", 10);  // Missing 2nd argument!

// ✅ CORRECT
printf("Value: %d, %d\n", 10, 20);
```

### **3. Using `%lf` in `printf` (unnecessary)**

```c
double d = 3.14;

// ⚠️ Works but unnecessary
printf("%lf", d);

// ✅ Better (same result)
printf("%f", d);

// Note: scanf REQUIRES %lf for double!
scanf("%lf", &d);  // ✅ Correct
```

---

## **🔬 Complete Example: All Specifiers**

```c
#include <stdio.h>

int main()
{
    int i = 42;
    long l = 1000000L;
    unsigned int u = 4294967295U;
    float f = 3.14159f;
    double d = 2.718281828;
    char c = 'X';
    char str[] = "Hello";
    int *ptr = &i;

    printf("=== INTEGER ===\n");
    printf("%%d:  %d\n", i);
    printf("%%i:  %i\n", i);
    printf("%%u:  %u\n", u);
    printf("%%ld: %ld\n", l);
    printf("%%x:  %x\n", i);
    printf("%%X:  %X\n", i);
    printf("%%o:  %o\n\n", i);

    printf("=== FLOAT ===\n");
    printf("%%f:    %f\n", f);
    printf("%%.2f:  %.2f\n", f);
    printf("%%e:    %e\n", f);
    printf("%%g:    %g\n\n", f);

    printf("=== CHAR & STRING ===\n");
    printf("%%c: %c\n", c);
    printf("%%s: %s\n\n", str);

    printf("=== POINTER ===\n");
    printf("%%p: %p\n\n", (void*)ptr);

    printf("=== FORMATTING ===\n");
    printf("%%10d:  %10d\n", i);
    printf("%%-10d: %-10d\n", i);
    printf("%%05d:  %05d\n", i);
    printf("%%+d:   %+d\n", i);
    printf("%% d:   % d\n\n", i);

    printf("=== WIDTH & PRECISION ===\n");
    printf("%%10.2f:  %10.2f\n", d);
    printf("%%-10.2f: %-10.2f\n", d);
    printf("%%.5s:    %.5s\n", str);

    return 0;
}
```

---

## **📚 Quick Reference Card**

```
INTEGERS           FLOATS           CHAR/STRING
%d  - int          %f  - float      %c - char
%i  - int          %lf - double     %s - string
%u  - unsigned     %e  - scientific
%ld - long         %g  - shortest   POINTER
%lld- long long                     %p - pointer

HEXADECIMAL        WIDTH            FLAGS
%x  - lowercase    %5d  - min 5     %-  left-align
%X  - uppercase    %-5d - left 5    %+  show sign
%o  - octal        %05d - pad 0     %0  pad zeros
                   %.2f - 2 decimals %# alternate
```

---

## ** Code Fixed with Explanation**

```c
void DisplayCircularLinkedList(struct Node *h)
{
    struct Node *p = h;
    if (h == NULL)
        return;

    do
    {
        printf("%d -> ", p->data);
        //     ││  │
        //     ││  └─ Literal string " -> "
        //     │└──── p->data (integer value)
        //     └───── Format specifier: decimal integer
        p = p->next;
    } while (p != h);

    printf("(head: %d)\n", h->data);
    //            ││  ││
    //            ││  │└─ Newline character
    //            ││  └── Literal string
    //            │└───── h->data (head's value)
    //            └────── Format specifier: decimal integer
}
```

**Output:**

```
10 -> 20 -> 30 -> 40 -> 50 -> (head: 10)
```
