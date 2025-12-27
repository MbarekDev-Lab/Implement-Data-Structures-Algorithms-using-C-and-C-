#include <stdio.h>
#include "Quiz.h"

int main()
{
    // Run the comprehensive demo
    demo_array_rotations();

    // Additional custom tests
    printf("\n=== Custom Rotation Tests ===\n");

    // Test edge cases
    int arr[] = {10, 20, 30, 40, 50};
    int n = 5;

    printf("\nOriginal: ");
    print_array(arr, n);

    // Rotate by 0 (no change)
    left_rotate_reversal(arr, n, 0);
    printf("Rotate by 0: ");
    print_array(arr, n);

    // Rotate by n (full rotation, back to original)
    left_rotate_reversal(arr, n, 5);
    printf("Rotate by n: ");
    print_array(arr, n);

    // Rotate by more than n (d = 7, equivalent to 7 % 5 = 2)
    int arr2[] = {10, 20, 30, 40, 50};
    left_rotate_reversal(arr2, 5, 7);
    printf("Rotate by 7 (= 2 mod 5): ");
    print_array(arr2, 5);

    // Compare all three left rotation methods
    printf("\n=== Comparing Rotation Methods ===\n");
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int test2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int test3[] = {1, 2, 3, 4, 5, 6, 7, 8};

    left_rotate_reversal(test1, 8, 3);
    left_rotate_auxiliary(test2, 8, 3);
    left_rotate_juggling(test3, 8, 3);

    printf("Reversal method:  ");
    print_array(test1, 8);
    printf("Auxiliary method: ");
    print_array(test2, 8);
    printf("Juggling method:  ");
    print_array(test3, 8);
    printf("\n=== End Custom Rotation Tests ===\n");

    // output :
    /*
    === Array Rotation Demonstrations ===
    Original array: 1 2 3 4 5 6 7
    Left rotate by 2 (reversal): 3 4 5 6 7 1 2
    Left rotate by 3 (juggling): 4 5 6 7 1 2 3
    Right rotate by 2: 6 7 1 2 3 4 5
    Left rotate by 1: 2 3 4 5 1
    Right rotate by 1: 5 1 2 3 4
    === End Rotation Demo ===

    === Custom Rotation Tests ===
    Original: 10 20 30 40 50
    Rotate by 0: 10 20 30 40 50
    Rotate by n: 10 20 30 40 50
    Rotate by 7 (= 2 mod 5): 30 40 50 10 20
    === Comparing Rotation Methods ===

    Reversal method:  4 5 6 7 8 1 2 3
    Auxiliary method: 4 5 6 7 8 1 2 3
    Juggling method:  4 5 6 7 8 1 2 3
    */

    // Array ADT QUIZ functions
    // count_frequencies_of_scores_greater_than_50();
    count_frequencies_of_scores_greater_than_50();
    check_if_there_exist_two_distinct_elements_whose_difference();

    return 0;
}
