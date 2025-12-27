#include <stdio.h>

// Recursive function example
int f(int n)
{
  static int i = 1;
  if (n >= 5)
    return n;

  n = n + i;
  i++;
  return f(n);
}

// Recursive function to sum digits and print them in reverse
void foo(int n, int *sum)
{
  if (n == 0)
    return;

  int k = n % 10; // last digit
  int j = n / 10; // remaining number
  *sum += k;

  foo(j, sum);
  printf("%d", k);
}

// Count frequencies of scores greater than 50
void count_frequencies_of_scores_greater_than_50()
{
  int freq[50] = {0}; // for scores 51 to 100
  int score;

  for (int i = 0; i < 500; i++)
  {
    scanf("%d", &score);

    if (score > 50 && score <= 100)
    {
      freq[score - 51]++;
    }
  }

  for (int i = 0; i < 50; i++)
  {
    if (freq[i] > 0)
    {
      printf("Score %d : %d\n", i + 51, freq[i]);
    }
  }
}

// Check if there exist two distinct elements with difference s
void check_if_two_elements_have_difference(int s)
{
  int a[] = {1, 3, 5, 8, 12, 15}; // sorted array
  int n = sizeof(a) / sizeof(a[0]);
  int i = 0, j = 1;

  while (j < n)
  {
    int diff = a[j] - a[i];

    if (diff < s)
    {
      j++;
    }
    else if (diff == s)
    {
      printf("Yes\n");
      return;
    }
    else
    {
      i++;
    }
  }

  printf("No\n");
}

// ============================================================================
// ARRAY ROTATION FUNCTIONS
// ============================================================================

// Helper function to reverse a portion of an array
static void reverse_array(int arr[], int start, int end)
{
  while (start < end)
  {
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    start++;
    end--;
  }
}

// Helper function to swap elements
static void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Method 1: Left rotate by d positions using reversal algorithm
// Time: O(n), Space: O(1)
void left_rotate_reversal(int arr[], int n, int d)
{
  if (d == 0 || d == n || n == 0)
    return;

  d = d % n; // Handle d > n

  // Reversal algorithm: reverse first d, reverse last n-d, reverse all
  reverse_array(arr, 0, d - 1);       // Reverse first d elements
  reverse_array(arr, d, n - 1);       // Reverse remaining n-d elements
  reverse_array(arr, 0, n - 1);       // Reverse entire array
}

// Method 2: Left rotate by d positions using auxiliary array
// Time: O(n), Space: O(d)
void left_rotate_auxiliary(int arr[], int n, int d)
{
  if (d == 0 || d == n || n == 0)
    return;

  d = d % n;
  int temp[d];

  // Store first d elements in temp
  for (int i = 0; i < d; i++)
    temp[i] = arr[i];

  // Shift remaining elements to the left
  for (int i = 0; i < n - d; i++)
    arr[i] = arr[i + d];

  // Copy temp elements to end
  for (int i = 0; i < d; i++)
    arr[n - d + i] = temp[i];
}

// Method 3: Left rotate by d positions using juggling algorithm
// Time: O(n), Space: O(1) - Best for multiple rotations
void left_rotate_juggling(int arr[], int n, int d)
{
  if (d == 0 || d == n || n == 0)
    return;

  d = d % n;

  // GCD calculation
  int gcd = 1;
  int a = n, b = d;
  while (b != 0)
  {
    int temp = b;
    b = a % b;
    a = temp;
  }
  gcd = a;

  // Move elements in sets
  for (int i = 0; i < gcd; i++)
  {
    int temp = arr[i];
    int j = i;

    while (1)
    {
      int k = j + d;
      if (k >= n)
        k = k - n;

      if (k == i)
        break;

      arr[j] = arr[k];
      j = k;
    }
    arr[j] = temp;
  }
}

// Right rotate by d positions using reversal algorithm
// Time: O(n), Space: O(1)
void right_rotate_reversal(int arr[], int n, int d)
{
  if (d == 0 || d == n || n == 0)
    return;

  d = d % n;

  // Right rotation is same as left rotation by (n - d)
  left_rotate_reversal(arr, n, n - d);
}

// Rotate by one position to the left (single step)
void left_rotate_by_one(int arr[], int n)
{
  if (n <= 1)
    return;

  int first = arr[0];
  for (int i = 0; i < n - 1; i++)
    arr[i] = arr[i + 1];
  arr[n - 1] = first;
}

// Rotate by one position to the right (single step)
void right_rotate_by_one(int arr[], int n)
{
  if (n <= 1)
    return;

  int last = arr[n - 1];
  for (int i = n - 1; i > 0; i--)
    arr[i] = arr[i - 1];
  arr[0] = last;
}

// Cyclic rotation: rotate array cyclically
void cyclic_rotate(int arr[], int n)
{
  right_rotate_by_one(arr, n);
}

// Print array helper
void print_array(int arr[], int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Demo function to test all rotation methods
void demo_array_rotations()
{
  printf("\n=== Array Rotation Demonstrations ===\n");

  int arr1[] = {1, 2, 3, 4, 5, 6, 7};
  int n1 = sizeof(arr1) / sizeof(arr1[0]);

  printf("\nOriginal array: ");
  print_array(arr1, n1);

  // Test left rotation by 2 using reversal
  int test1[] = {1, 2, 3, 4, 5, 6, 7};
  left_rotate_reversal(test1, 7, 2);
  printf("Left rotate by 2 (reversal): ");
  print_array(test1, 7);

  // Test left rotation by 3 using juggling
  int test2[] = {1, 2, 3, 4, 5, 6, 7};
  left_rotate_juggling(test2, 7, 3);
  printf("Left rotate by 3 (juggling): ");
  print_array(test2, 7);

  // Test right rotation by 2
  int test3[] = {1, 2, 3, 4, 5, 6, 7};
  right_rotate_reversal(test3, 7, 2);
  printf("Right rotate by 2: ");
  print_array(test3, 7);

  // Test single left rotation
  int test4[] = {1, 2, 3, 4, 5};
  left_rotate_by_one(test4, 5);
  printf("Left rotate by 1: ");
  print_array(test4, 5);

  // Test single right rotation
  int test5[] = {1, 2, 3, 4, 5};
  right_rotate_by_one(test5, 5);
  printf("Right rotate by 1: ");
  print_array(test5, 5);

  printf("\n=== End Rotation Demo ===\n");
}
