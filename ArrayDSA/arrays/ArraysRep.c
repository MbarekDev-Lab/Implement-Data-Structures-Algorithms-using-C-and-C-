//
//  ArraysRep.c
//  Essential
//
//  Created by M'Barek Benraiss on 18.12.25.
//

#include "ArraysRep.h"
#include <stdio.h>
#include <stdlib.h>

void arrayRepresentation()
{
  // ============================================
  // PART 1: STATIC ARRAY (Stack Allocation)
  // ============================================
  // Static arrays are allocated on the STACK
  // - Memory is automatically managed
  // - Size must be known at compile time
  // - Automatically freed when function ends
  // ============================================

  // Declare and initialize a static array
  int A[5] = {2, 4, 6, 8, 10};

  printf("=== STATIC ARRAY (Stack) ===\n");
  printf("Array A address: %p\n", (void *)A);
  printf("Array A values: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", A[i]);
  }
  printf("\n\n");

  // ============================================
  // PART 2: DYNAMIC ARRAY (Heap Allocation)
  // ============================================
  // Dynamic arrays are allocated on the HEAP
  // - Memory must be manually managed
  // - Size can be determined at runtime
  // - Must be freed with free() to prevent memory leaks
  // ============================================

  // Step 1: Declare a pointer (initially points to garbage)
  int *p = NULL; // Better practice: initialize to NULL

  // Step 2: Allocate memory on the heap
  // malloc(5 * sizeof(int)) allocates 5 * 4 = 20 bytes
  p = (int *)malloc(5 * sizeof(int));

  // Check if allocation succeeded
  if (p == NULL)
  {
    printf("Error: Memory allocation failed!\n");
    return;
  }

  printf("=== DYNAMIC ARRAY (Heap) ===\n");
  printf("Pointer p address: %p\n", (void *)p);
  printf("Pointer p points to: %p\n", (void *)p);

  // Step 3: Assign values to the dynamically allocated array
  p[0] = 3;
  p[1] = 5;
  p[2] = 7;
  p[3] = 9;
  p[4] = 11;

  printf("Array p values: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", p[i]);
  }
  printf("\n\n");

  // ============================================
  // PART 3: MEMORY MANAGEMENT
  // ============================================
  // After using dynamic memory, we MUST free it
  // Otherwise, we get a MEMORY LEAK
  // ============================================
  printf("=== MEMORY MANAGEMENT ===\n");
  printf("Freeing dynamically allocated memory...\n");
  free(p); // Release the memory back to the heap

  // Step 4: Set pointer to NULL to prevent dangling pointer bugs
  p = NULL;
  printf("Pointer p set to NULL: %p\n", (void *)p);
  printf("(Cannot access p[i] anymore - would cause crash!)\n\n");

  // ============================================
  // DEMONSTRATION: Why NULL check is important
  // ============================================
  printf("=== SAFE POINTER USAGE ===\n");
  if (p != NULL)
  {
    printf("Accessing p[i] would be safe here\n");
  }
  else
  {
    printf("✓ Correct: p is NULL, so we don't access it\n");
    printf("  (Accessing p[i] here would cause SEGMENTATION FAULT)\n");
  }
  printf("\n");

  // ============================================
  // SUMMARY: Key Differences
  // ============================================
  printf("=== SUMMARY ===\n");
  printf("Static Array (A):\n");
  printf("  - Location: Stack\n");
  printf("  - Management: Automatic\n");
  printf("  - Lifetime: Function scope\n");
  printf("  - Size: Fixed at compile time\n\n");

  printf("Dynamic Array (p):\n");
  printf("  - Location: Heap\n");
  printf("  - Management: Manual (malloc/free)\n");
  printf("  - Lifetime: Until free() is called\n");
  printf("  - Size: Can be determined at runtime\n");
}
