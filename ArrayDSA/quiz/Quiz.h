//
//  Quiz.h
//  Essential
//
//  Created by M'Barek Benraiss on 18.12.25.
//

#ifndef Quiz_h
#define Quiz_h

int f(int n);
void foo(int n, int *sum);
void count_frequencies_of_scores_greater_than_50();
void check_if_there_exist_two_distinct_elements_whose_difference();

// Array Rotation Functions
void left_rotate_reversal(int arr[], int n, int d);
void left_rotate_auxiliary(int arr[], int n, int d);
void left_rotate_juggling(int arr[], int n, int d);
void right_rotate_reversal(int arr[], int n, int d);
void left_rotate_by_one(int arr[], int n);
void right_rotate_by_one(int arr[], int n);
void cyclic_rotate(int arr[], int n);
void print_array(int arr[], int n);
void demo_array_rotations();

#endif /* Quiz_h */
