#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// STRING UTILITY FUNCTIONS
// ============================================================================

// Calculate string length
int str_length(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

// Copy string from source to destination
void str_copy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Concatenate two strings
void str_concat(char *dest, const char *src)
{
    int i = 0, j = 0;

    // Find end of dest
    while (dest[i] != '\0')
        i++;

    // Copy src to end of dest
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

// Compare two strings (returns 0 if equal, <0 if s1<s2, >0 if s1>s2)
int str_compare(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

// Reverse a string in-place
void str_reverse(char *str)
{
    int left = 0;
    int right = str_length(str) - 1;

    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// Convert string to uppercase
void str_to_upper(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

// Convert string to lowercase
void str_to_lower(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

// Toggle case of each character
void str_toggle_case(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isupper(str[i]))
            str[i] = tolower(str[i]);
        else if (islower(str[i]))
            str[i] = toupper(str[i]);
    }
}

// Count vowels in a string
int count_vowels(const char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            count++;
    }
    return count;
}

// Count consonants in a string
int count_consonants(const char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower(str[i]);
        if ((ch >= 'a' && ch <= 'z') &&
            !(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'))
            count++;
    }
    return count;
}

// Count words in a string
int count_words(const char *str)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            in_word = 0;
        }
        else if (in_word == 0)
        {
            in_word = 1;
            count++;
        }
    }
    return count;
}

// Check if string is palindrome
int is_palindrome(const char *str)
{
    int left = 0;
    int right = str_length(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

// Find first occurrence of character in string
int find_char(const char *str, char ch)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            return i;
    }
    return -1;
}

// Check if two strings are anagrams
int are_anagrams(const char *s1, const char *s2)
{
    if (str_length(s1) != str_length(s2))
        return 0;

    int freq[26] = {0};

    // Count frequency in s1
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (isalpha(s1[i]))
            freq[tolower(s1[i]) - 'a']++;
    }

    // Subtract frequency in s2
    for (int i = 0; s2[i] != '\0'; i++)
    {
        if (isalpha(s2[i]))
            freq[tolower(s2[i]) - 'a']--;
    }

    // Check if all frequencies are zero
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] != 0)
            return 0;
    }
    return 1;
}

// Remove duplicates from string
void remove_duplicates(char *str)
{
    int seen[256] = {0};
    int write = 0;

    for (int read = 0; str[read] != '\0'; read++)
    {
        if (!seen[(unsigned char)str[read]])
        {
            seen[(unsigned char)str[read]] = 1;
            str[write++] = str[read];
        }
    }
    str[write] = '\0';
}

// ============================================================================
// ADVANCED CASE CONVERSION METHODS
// ============================================================================

// Method to count words directly
void count_and_print_words_directly()
{

    char A[] = "abcd efg hijklmnop qrstuvw     xyz";

    int wCount = 1;

    for (int i = 0; A[i] != '\0'; i++)
    {
        if (A[i] == ' ' && A[i - 1] != ' ')
            wCount++;
    }
    printf("Words: %d\n", wCount);
}

// Method 1: Using ASCII arithmetic (most efficient)
void to_uppercase_ascii(char *str)
{
    // a = 97, A = 65, difference = 32
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }
    }
}

// Method 2: Using lookup tables
void to_uppercase_lookup(char *str)
{
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; str[i] != '\0'; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (str[i] == lower[j])
            {
                str[i] = upper[j];
                break;
            }
        }
    }
}

// Method 3: Using ctype.h (most portable)
void to_uppercase_ctype(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}

// Method 4: Using bitwise operation (fastest)
void to_uppercase_bitwise(char *str)
{
    // Clear the 6th bit (0x20) to convert lowercase to uppercase
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] &= ~0x20; // Clear bit 5 (0-indexed)
        }
    }
}

// Corresponding lowercase conversion methods
void to_lowercase_ascii(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
}

// Method 4: Using bitwise operation (fastest)
void to_lowercase_bitwise(char *str)
{
    // Set the 6th bit (0x20) to convert uppercase to lowercase
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] |= 0x20; // Set bit 5 (0-indexed)
        }
    }
}

// changing case of characters
char *to_uppercase(char *str)
{
    // A = 65, a = 97, difference = 32
    char A[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char a[] = "abcdefghijklmnopqrstuvwxyz";
    /*int i = 0;
    while (str[i] != '\0')
    {
        for (int j = 0; j < 26; j++)
        {
            if (str[i] == a[j])
            {
                str[i] = A[j];
                break;
            }
        }
        i++;
    }*/

    /*int i;
    for (i = 0; A[i] != '\0'; i++)
    {
        A[i] = A[i] + 32;
    }
    printf("%s", A);*/

    int i;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (A[i] > 65 && A[i] < 90) // Check for lowercase
        {
            str[i] -= 32; // Convert to uppercase
        }
    }
    return str;
}

// ============================================================================
//  VOWEL AND CONSONANT COUNTING
// ============================================================================

// Method 1: Count vowels and consonants using output parameters (modern approach)
void count_vowels_consonants(const char *str, int *vowelCount, int *consonantCount)
{
    *vowelCount = 0;
    *consonantCount = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)str[i]);

        // Check if it's a letter
        if (ch >= 'a' && ch <= 'z')
        {
            // Check if vowel
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            {
                (*vowelCount)++;
            }
            else
            {
                (*consonantCount)++;
            }
        }
    }
}

// Method 2: Standalone function that prints results directly
void count_and_print_vowels_consonants(const char *str)
{
    int vCount = 0;
    int cCount = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)str[i]);

        // Check for vowels (both cases handled by tolower)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
            vCount++;
        }
        // Check for consonants
        else if ((ch >= 'a' && ch <= 'z'))
        {
            cCount++;
        }
    }

    printf("String: \"%s\"\n", str);
    printf("Vowels: %d\n", vCount);
    printf("Consonants: %d\n", cCount);
}

// Method 3: Using lookup table (fastest for repeated checks)
void count_vowels_consonants_lookup(const char *str, int *vowelCount, int *consonantCount)
{
    // Lookup table for vowels (1 = vowel, 0 = not vowel)
    int is_vowel[26] = {
        1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, // a-m
        0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0  // n-z
    };

    *vowelCount = 0;
    *consonantCount = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)str[i]);

        if (ch >= 'a' && ch <= 'z')
        {
            if (is_vowel[ch - 'a'])
                (*vowelCount)++;
            else
                (*consonantCount)++;
        }
    }
}

// Method 4: Standalone function that prints results directly
void count_and_print_vowels_consonants_directly()
{
    char A[] = "abcd efg hijklmnop qrstuvw xyz";

    int vCount = 0;
    int cCount = 0;

    for (int i = 0; A[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)A[i]); // Normalize to lowercase

        // Only process alphabetic characters
        if ((ch >= 'a' && ch <= 'z'))
        {
            // Check if vowel
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            {
                vCount++;
            }
            else
            {
                // It's a consonant
                cCount++;
            }
        }
        // Ignore spaces, numbers, punctuation
    }

    printf("String: \"%s\"\n", A);
    printf("Vowels: %d\n", vCount);
    printf("Consonants: %d\n", cCount);
}

// count words, vowels, consonants in a string
void count_words_vowels_consonants(const char *str, int *wordCount, int *vowelCount, int *consonantCount)
{
    *wordCount = 0;
    *vowelCount = 0;
    *consonantCount = 0;

    int inWord = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)str[i]);

        // Word counting
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
            inWord = 0;
        }
        else
        {
            if (inWord == 0)
            {
                inWord = 1;
                (*wordCount)++;
            }

            // Vowel and consonant counting
            if (ch >= 'a' && ch <= 'z')
            {
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                {
                    (*vowelCount)++;
                }
                else
                {
                    (*consonantCount)++;
                }
            }
        }
    }
}

// ============================================================================
// TOGGLE CASE METHODS (Multiple Implementations)
// ============================================================================

// Method 1: Toggle using ASCII arithmetic
void toggle_case_ascii(char *str)
{
    // A = 65, a = 97, difference = 32
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            // Uppercase → Lowercase
            str[i] += 32;
        }
        else if (str[i] >= 97 && str[i] <= 122)
        {
            // Lowercase → Uppercase
            str[i] -= 32;
        }
    }
}

// Method 2: Toggle using lookup tables
void toggle_case_lookup(char *str)
{
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; str[i] != '\0'; i++)
    {
        // Check if uppercase, convert to lowercase
        for (int j = 0; j < 26; j++)
        {
            if (str[i] == upper[j])
            {
                str[i] = lower[j];
                break;
            }
            else if (str[i] == lower[j])
            {
                str[i] = upper[j];
                break;
            }
        }
    }
}

// Method 3: Toggle using ctype.h
void toggle_case_ctype(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isupper((unsigned char)str[i]))
        {
            str[i] = tolower((unsigned char)str[i]);
        }
        else if (islower((unsigned char)str[i]))
        {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

// Method 4: Toggle using bitwise XOR (fastest)
void toggle_case_bitwise(char *str)
{
    // XOR with 0x20 (32) toggles bit 5, which flips case
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z'))
        {
            str[i] ^= 0x20; // Toggle bit 5
        }
    }
}

// Method 5: Toggle using conditional operator (compact)
void toggle_case_ternary(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32
                                                                                                   : str[i];
    }
}

// ============================================================================
// VALIDATION OF STRING METHODS
// ============================================================================

// Validate string - check character types and return validation result
int validate_string_methods()
{
    char *name = "Ani?32!";
    printf("\n=== String Validation ===\n");
    printf("Original String: %s\n", name);

    int alphaCount = 0;
    int digitCount = 0;
    int specialCount = 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        char ch = name[i];

        // Check for special characters first
        if (!(ch >= 'A' && ch <= 'Z') && !(ch >= 'a' && ch <= 'z') && !(ch >= '0' && ch <= '9'))
        {
            printf("'%c' is a special character.\n", ch);
            specialCount++;
        }
        // Check for alphabetic characters
        else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            printf("'%c' is an alphabetic character.\n", ch);
            alphaCount++;
        }
        // Check for digits
        else if (ch >= '0' && ch <= '9')
        {
            printf("'%c' is a digit.\n", ch);
            digitCount++;
        }
    }

    // Print summary
    printf("\nSummary:\n");
    printf("Alphabetic characters: %d\n", alphaCount);
    printf("Digits: %d\n", digitCount);
    printf("Special characters: %d\n", specialCount);

    // Return validation result (1 = valid, 0 = has special chars)
    return (specialCount == 0) ? 1 : 0;
}

// Alternative: Check if string is valid (only letters and digits)
int is_valid_alphanumeric(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')))
        {
            return 0; // Invalid - contains non-alphanumeric
        }
    }
    return 1; // Valid - all alphanumeric
}

// Alternative: Check if string contains only letters
int is_valid_alphabetic(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')))
        {
            return 0; // Invalid - contains non-alphabetic
        }
    }
    return 1; // Valid - all alphabetic
}

// Demonstration of validation functions
void demo_string_validation()
{
    printf("\n=== String Validation Demonstration ===\n");

    // Test validate_string_methods
    int result = validate_string_methods();
    printf("\nValidation result: %s\n", result ? "VALID (no special chars)" : "INVALID (has special chars)");

    // Test different strings
    const char *test_strings[] = {
        "Hello123",
        "OnlyLetters",
        "With Spaces",
        "Special!@#",
        "Mix3d_Ch4rs"};

    printf("\n=== Testing Multiple Strings ===\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\nString: \"%s\"\n", test_strings[i]);
        printf("  Alphanumeric: %s\n", is_valid_alphanumeric(test_strings[i]) ? "YES" : "NO");
        printf("  Alphabetic only: %s\n", is_valid_alphabetic(test_strings[i]) ? "YES" : "NO");
    }
}

// ============================================================================
// STRING REVERSAL METHODS
// ============================================================================
void reverse_string_inplace(char *str)
{
    int left = 0;
    int right = str_length(str) - 1;

    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_string_new(const char *str, char *revStr)
{
    int len = str_length(str);
    int i, j;

    // Copy characters in reverse order
    for (i = len - 1, j = 0; i >= 0; i--, j++)
    {
        revStr[j] = str[i];
    }
    revStr[j] = '\0'; // Null terminate
}

void reverse_string_without_temp_arr()
{

    char A[] = "Python";
    char t;
    int i, j;

    // find length
    for (j = 0; A[j] != '\0'; j++)
    {
        ;
    }
    // i is length, so start from last character
    j = j - 1;

    for (i = 0; i < j; i++, j--)
    {
        t = A[i];
        A[i] = A[j];
        A[j] = t;
    }
    printf("Reversed string: %s\n", A);
}

void comparing_string()
{
    char A[] = "painter";
    char B[] = "Painting";

    int i, j;

    for (i = 0, j = 0; A[i] != '\0' && B[j] != '\0'; j++, i++)
    {
        if (A[i] != B[j])
            break;
    }

    if (A[i] == B[j])
        printf("Strings are equal\n");
    else if (A[i] < B[j])
        printf("String A is less than String B\n");
    else
        printf("String A is greater than String B\n");
}

void demo_string_reversal()
{
    printf("\n=== String Reversal Methods ===\n");

    // Method 1: In-place reversal
    char str1[] = "Hello World";
    printf("\nMethod 1 - In-place Reversal:\n");
    printf("Before: %s\n", str1);
    reverse_string_inplace(str1);
    printf("After:  %s\n", str1);

    // Method 2: New string reversal
    const char *original = "Programming in C";
    char reversed[50];
    printf("\nMethod 2 - Copy to New String:\n");
    printf("Original: %s\n", original);
    reverse_string_new(original, reversed);
    printf("Reversed: %s\n", reversed);

    // Method 3: Without temp array
    printf("\nMethod 3 - Without Temp Array (hardcoded):\n");
    reverse_string_without_temp_arr();

    // Show that original is unchanged
    printf("\n=== Immutability Check ===\n");
    printf("Original string unchanged: %s\n", original);
}

void demo_finding_duplicate_characters()
{
    printf("\n=== Finding Duplicate Characters in a String ===\n");

    char str[] = "programming";
    int freq[256] = {0};

    // Count frequency of each character
    for (int i = 0; str[i] != '\0'; i++)
    {
        freq[(unsigned char)str[i]]++;
    }

    // Print duplicate characters
    printf("Duplicate characters in \"%s\":\n", str);
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 1)
        {
            printf("'%c' occurs %d times\n", i, freq[i]);
        }
    }
}

void demo_finding_dublicate_brute_force_comparison_marker()
{
    char str[] = "finding"; // f i n d -1 -1 g
    int i, j, count;

    printf("Duplicate characters in \"%s\" (Brute Force using -1 marker):\n", str);

    for (i = 0; str[i] != '\0'; i++)
    {
        // Skip if this character is already marked
        if (str[i] == -1)
            continue;

        count = 1;

        // Compare with all characters after i
        for (j = i + 1; str[j] != '\0'; j++)
        {
            if (str[i] == str[j])
            {
                count++;
                str[j] = -1; // Mark duplicate so it's not counted again
            }
        }

        // Print only if duplicate exists
        if (count > 1)
            printf("'%c' appears %d times\n", str[i], count);
    }

    printf("Original string modified with markers: %s\n", str);
}

void demo_finding_dublicate_brute_force_comparison()
{
    char str[] = "findinng"; // Test string with duplicates
    int len = str_length(str);
    int processed[256] = {0}; // Track which characters we've already counted
    int i, j, count;

    printf("Duplicate characters in \"%s\" (Brute Force ):\n", str);

    for (i = 0; i < len; i++)
    {
        // Skip if already processed
        /*if (str[i] == -1)
        {
            continue;
        }*/

        // Skip if already processed
        if (processed[(unsigned char)str[i]])
        {
            continue;
        }

        count = 1;

        // Count occurrences
        for (j = i + 1; j < len; j++)
        {
            if (str[i] == str[j])
            {
                count++;
            }
        }

        // Mark as processed
        processed[(unsigned char)str[i]] = 1;

        // Print only if it appears more than once
        if (count > 1)
        {
            printf("'%c' appears %d times\n", str[i], count);
        }
    }

    printf("Original string preserved: %s\n", str);
}

// Method: Finding duplicate characters using hashing O(n)
void demo_finfing_duplicate_characters_hashing()
{

    char A[] = "finding"; // f i n d -1 -1 g

    int H[26] = {0}; // Hash table for 'a' to 'z'
    int i;
    // Initialize hash table
    for (int i = 0; A[i] != '\0'; i++)
    {
        H[A[i] - 97] += 1;
    }

    // because the ascii eng alphabet are fixed 26 english alphabet if (a b c d e f g h i j k l m n o p q r s t u v w x y z)
    for (i = 0; i < 26; i++)
    {
        //   H[i] = 0;
        /*
        | Char | ASCII | Index (ASCII − 97) |
        | ---- | ----- | ------------------ |
        | f    | 102   | 5                  |
        | i    | 105   | 8                  |
        | n    | 110   | 13                 |
        | d    | 100   | 3                  |
        | i    | 105   | 8                  |
        | n    | 110   | 13                 |
        | g    | 103   | 6                  |

        hash table

        H[3]  = 1  → d
        H[5]  = 1  → f
        H[6]  = 1  → g
        H[8]  = 2  → i
        H[13] = 2  → n

        */

        if (H[i] > 1)
        {
            printf("%c occurs ", i + 97);
            printf("%d times\n", H[i]);
        }
    }

    // Print duplicate characters
}

// ============================================================================
// BITWISE OPERATIONS, BINARY REPRESENTATION EXPLANATION
// ============================================================================

// Decimal (base 10):
// 753 = 7×10² + 5×10¹ + 3×10⁰

// Binary (base 2):
//  101101 = 1×2⁵ + 0×2⁴ + 1×2³ + 1×2² + 0×2¹ + 1×2⁰

// Example: Convert decimal 13 to binary
// Step 1: Divide by 2 and record remainders
// 13 ÷ 2 = 6, remainder 1
// 6 ÷ 2 = 3, remainder 0
// 3 ÷ 2 = 1, remainder 1
// 1 ÷ 2 = 0, remainder 1
// Decimal: 13
// Binary : 00001101

// Bitwise AND (&)
/*
    Bit A | Bit B | A & B
    ------|-------|-------
    0   |   0   |   0
    0   |   1   |   0
    1   |   0   |   0
    1   |   1   |   1

*/
// Bitwise OR (|)
/*
    Bit A | Bit B | A | B
    ------|-------|-------
    0   |   0   |   0
    0   |   1   |   1    ← One bit is 1
    1   |   0   |   1    ← One bit is 1
    1   |   1   |   1    ← Both bits are 1
  */
// Example usage in to_lowercase_bitwise() function above
// str[i] |= 0x20;  // Set bit 5 → lowercase

// Bitwise XOR (^)
/*
    Bit A | Bit B | A ^ B
    ------|-------|-------
    0   |   0   |   0    ← Same bits
    0   |   1   |   1    ← Different ✓
    1   |   0   |   1    ← Different ✓
    1   |   1   |   0    ← Same bits
*/
// Example usage in toggle_case_bitwise() function (already defined above)
// str[i] ^= 0x20;  // Toggle bit 5

// 'A' (0100 0001) ^ 0x20 = 'a' (0110 0001)
// 'a' (0110 0001) ^ 0x20 = 'A' (0100 0001)

// Bitwise NOT (~)
/*
    Bit A | ~A
    ------|----
    0   | 1
    1   | 0
*/
// Example usage in to_uppercase_bitwise() function above
// str[i] &= ~0x20;  // Clear bit 5 → uppercase

// 'a' (0110 0001) & ~0x20 (1101 1111) = 'A' (0100 0001) :

// Print binary representation of a character :
void bitwise_binary_representation(unsigned char ch)
{
    printf("Character: '%c' | ASCII: %d | Binary: ", ch, ch);

    // Print each bit from MSB (bit 7) to LSB (bit 0)
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (ch >> i) & 1);

        // Add space after every 4 bits for readability
        if (i == 4)
            printf(" ");
    }
    printf("\n");
}

// Find duplicates using bitwise hashing (for lowercase letters only)
void demo_finding_duplicates_bitwise()
{
    char A[] = "finding";
    long int H = 0; // Hash table represented as bits
    int i;

    printf("\n=== Finding Duplicates Using Bitwise Hashing ===\n");
    printf("String: \"%s\"\n\n", A);

    // Process each character
    for (i = 0; A[i] != '\0'; i++)
    {
        long int x = 1;

        // Shift 1 to the position corresponding to the character
        // 'a' -> bit 0, 'b' -> bit 1, ..., 'z' -> bit 25
        x = x << (A[i] - 97);

        // Check if this bit is already set in H
        if ((x & H) > 0)
        {
            printf("'%c' is a duplicate (bit %d is already set)\n", A[i], A[i] - 97);
        }
        else
        {
            printf("'%c' is new (setting bit %d)\n", A[i], A[i] - 97);
            H = H | x; // Set the bit for this character
        }
    }

    printf("\nFinal hash value: %ld (0x%lX)\n", H, H);
    printf("\nExplanation:\n");
    printf("- Each bit position represents a letter (0='a', 1='b', ..., 25='z')\n");
    printf("- If bit is 1, that letter has been seen\n");
    printf("- If bit is 0, that letter hasn't been seen yet\n");
}

// Check if two strings are anagrams using hash table
void checkfor_anagram_bitwise()
{
    char A[] = "decimal";
    char B[] = "medical";
    int i, H[26] = {0};

    printf("\n=== Anagram Check Using Hash Table ===\n");
    printf("String A: \"%s\"\n", A);
    printf("String B: \"%s\"\n\n", B);

    // Step 1: Count frequency of each character in first string
    for (i = 0; A[i] != '\0'; i++)
    {
        H[A[i] - 97] += 1;
        printf("'%c' -> H[%d] = %d\n", A[i], A[i] - 97, H[A[i] - 97]);
    }

    printf("\n");

    // Step 2: Decrement frequency for each character in second string
    for (i = 0; B[i] != '\0'; i++)
    {
        H[B[i] - 97] -= 1;
        printf("'%c' -> H[%d] = %d\n", B[i], B[i] - 97, H[B[i] - 97]);

        // Bug fix: Check B[i], not A[i]!
        if (H[B[i] - 97] < 0)
        {
            printf("\n Not an anagram (character '%c' appears more in B than in A)\n", B[i]);
            return;
        }
    }

    // Step 3: Verify all counts are zero
    printf("\n");
    for (i = 0; i < 26; i++)
    {
        if (H[i] != 0)
        {
            printf(" Not an anagram (character '%c' count is %d)\n", i + 97, H[i]);
            return;
        }
    }

    printf(" Strings are anagrams!\n");
    printf("\nExplanation:\n");
    printf("- First loop: Increment count for each character in string A\n");
    printf("- Second loop: Decrement count for each character in string B\n");
    printf("- If all counts are 0, strings are anagrams (same characters, same frequency)\n");
}

// ============================================================================
// BINARY SEARCH ALGORITHM
// ============================================================================

/*
Binary Search Algorithm:
========================
Searches for a key in a SORTED array by repeatedly dividing search space in half.

Time Complexity : O(log n)
Space Complexity: O(1)

Example: Search for 18 in [5, 8, 12, 15, 18, 21, 25]

Index:  0   1   2   3   4   5   6
Value:  5   8  12  15  18  21  25

Initial: low=0, high=6, n=7

Iteration 1:
  mid = (0 + 6) / 2 = 3
  A[3] = 15
  18 > 15 → search right half → low = mid + 1 = 4

Iteration 2:
  low=4, high=6
  mid = (4 + 6) / 2 = 5
  A[5] = 21
  18 < 21 → search left half → high = mid - 1 = 4

Iteration 3:
  low=4, high=4
  mid = (4 + 4) / 2 = 4
  A[4] = 18
  18 == 18 → FOUND! return 4 ✓

Precondition: Array MUST be sorted
Returns: Index of element if found, -1 if not found
*/

int binarySearch(int A[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        // Overflow-safe midpoint calculation
        int mid = low + (high - low) / 2;

        if (A[mid] == key)
            return mid; // Found!
        else if (key < A[mid])
            high = mid - 1; // Search left half
        else
            low = mid + 1; // Search right half
    }

    return -1; // Not found
}

// Demonstration of binary search
void demo_binary_search()
{
    printf("\n=== Binary Search Demonstration ===\n");

    int arr[] = {5, 8, 12, 15, 18, 21, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    // Test cases
    int keys[] = {18, 5, 25, 10, 30};

    for (int i = 0; i < 5; i++)
    {
        int result = binarySearch(arr, n, keys[i]);

        if (result != -1)
            printf("Key %d found at index %d\n", keys[i], result);
        else
            printf("Key %d NOT found in array\n", keys[i]);
    }

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║              BINARY SEARCH COMPLEXITY                      ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ Time Complexity:   O(log n)                               ║\n");
    printf("║ Space Complexity:  O(1)                                   ║\n");
    printf("║ Precondition:      Array must be SORTED                   ║\n");
    printf("║ Best Case:         O(1) - element at middle               ║\n");
    printf("║ Worst Case:        O(log n) - not found or at end         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

// ============================================================================
// STRING PERMUTATION ALGORITHMS
// ============================================================================

/*
PERMUTATION EXPLANATION:
========================
For string "ABC", all permutations are:
ABC, ACB, BAC, BCA, CAB, CBA (Total: 3! = 6 permutations)

Algorithm 1: Using Three Nested Loops (Brute Force)
----------------------------------------------------
- Works only for strings of length 3
- Time Complexity: O(n³)
- Space Complexity: O(1)

Example for "ABC":
i=0, j=1, k=2 → ABC
i=0, j=2, k=1 → ACB
i=1, j=0, k=2 → BAC
i=1, j=2, k=0 → BCA
i=2, j=0, k=1 → CAB
i=2, j=1, k=0 → CBA

Algorithm 2: Backtracking (Recursive) - Universal Solution
-----------------------------------------------------------
- Works for any string length
- Time Complexity: O(n! × n)
- Space Complexity: O(n) for recursion stack

Process for "ABC":
1. Fix 'A', permute "BC" → ABC, ACB
2. Fix 'B', permute "AC" → BAC, BCA
3. Fix 'C', permute "AB" → CAB, CBA

Key Concepts:
- Swap characters to generate different combinations
- Recursively permute remaining substring
- Backtrack (swap back) to restore original state
*/

///  Generate all permutations of a string using three nested loops
// ============================================================================
// STRING PERMUTATION ALGORITHMS
// ============================================================================

/*
PERMUTATION EXPLANATION:
========================
For string "ABC", all permutations are:
ABC, ACB, BAC, BCA, CAB, CBA (Total: 3! = 6 permutations)

Algorithm 1: Using Three Nested Loops (Brute Force)
----------------------------------------------------
- Works only for strings of length 3
- Time Complexity: O(n³)
- Space Complexity: O(1)

Example for "ABC":
i=0, j=1, k=2 → ABC
i=0, j=2, k=1 → ACB
i=1, j=0, k=2 → BAC
i=1, j=2, k=0 → BCA
i=2, j=0, k=1 → CAB
i=2, j=1, k=0 → CBA

Algorithm 2: Backtracking (Recursive) - Universal Solution
-----------------------------------------------------------
- Works for any string length
- Time Complexity: O(n! × n)
- Space Complexity: O(n) for recursion stack

Process for "ABC":
1. Fix 'A', permute "BC" → ABC, ACB
2. Fix 'B', permute "AC" → BAC, BCA
3. Fix 'C', permute "AB" → CAB, CBA

Key Concepts:
- Swap characters to generate different combinations
- Recursively permute remaining substring
- Backtrack (swap back) to restore original state
*/

// ============================================================================
// METHOD 1: Brute Force (3 Nested Loops) - Only for length 3
// ============================================================================
void permutation_brute_force()
{
    char A[] = "ABC";
    int len = str_length(A);
    int count = 0;

    printf("\n=== Permutations Using Brute Force (3 Nested Loops) ===\n");
    printf("String: \"%s\" (length = %d)\n", A, len);
    printf("Total permutations: %d! = 6\n\n", len);

    // Generate all permutations using three indices
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            for (int k = 0; k < len; k++)
            {
                // Ensure all indices are different (no repeated characters)
                if (i != j && j != k && i != k)
                {
                    printf("%d: %c%c%c\n", ++count, A[i], A[j], A[k]);
                }
            }
        }
    }

    printf("\nLimitation: This method ONLY works for strings of length 3!\n");
}

// ============================================================================
// METHOD 2: Backtracking (Recursive) - Works for any length
// ============================================================================

// Helper function to swap two characters
void swap_chars(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to generate permutations
void permute_recursive(char str[], int left, int right, int *count)
{
    // Base case: reached the end of string
    if (left == right)
    {
        printf("%d: %s\n", ++(*count), str);
    }
    else
    {
        // Try each character at position 'left'
        for (int i = left; i <= right; i++)
        {
            // Step 1: Swap current character with position 'left'
            swap_chars(&str[left], &str[i]);

            // Step 2: Recursively permute remaining substring
            permute_recursive(str, left + 1, right, count);

            // Step 3: Backtrack - restore original string
            swap_chars(&str[left], &str[i]);
        }
    }
}

// Wrapper function for recursive permutation
void permutation_backtracking()
{
    char str[] = "ABC";
    int len = str_length(str);
    int count = 0;

    printf("\n=== Permutations Using Backtracking (Recursive) ===\n");
    printf("String: \"%s\" (length = %d)\n", str, len);

    // Calculate factorial
    int factorial = 1;
    for (int i = 2; i <= len; i++)
        factorial *= i;
    printf("Total permutations: %d! = %d\n\n", len, factorial);

    permute_recursive(str, 0, len - 1, &count);

    printf("\nThis method works for ANY string length!\n");
}

// ============================================================================
// METHOD 3: Detailed Step-by-Step Backtracking with Visualization
// ============================================================================
void permute_with_visualization(char str[], int left, int right, int depth)
{
    // Indentation for visualization
    for (int i = 0; i < depth; i++)
        printf("  ");

    if (left == right)
    {
        printf("✓ Found permutation: %s\n", str);
    }
    else
    {
        printf("Level %d: Fixing position %d, trying chars: ", depth, left);
        for (int i = left; i <= right; i++)
            printf("%c ", str[i]);
        printf("\n");

        for (int i = left; i <= right; i++)
        {
            // Show swap
            for (int j = 0; j < depth; j++)
                printf("  ");
            printf("→ Swap str[%d]='%c' ↔ str[%d]='%c' → ", left, str[left], i, str[i]);

            swap_chars(&str[left], &str[i]);
            printf("%s\n", str);

            // Recurse
            permute_with_visualization(str, left + 1, right, depth + 1);

            // Show backtrack
            for (int j = 0; j < depth; j++)
                printf("  ");
            printf("← Backtrack: Swap back str[%d]='%c' ↔ str[%d]='%c' → ", left, str[left], i, str[i]);

            swap_chars(&str[left], &str[i]);
            printf("%s\n", str);
        }
    }
}

void permutation_with_steps()
{
    char str[] = "ABC";
    int len = str_length(str);

    printf("\n=== Permutations with Step-by-Step Visualization ===\n");
    printf("String: \"%s\"\n", str);
    printf("Watch how backtracking generates all permutations:\n\n");

    permute_with_visualization(str, 0, len - 1, 0);
}

// ============================================================================
// METHOD 4: Using Heap's Algorithm (Most Efficient)
// ============================================================================
void heaps_algorithm(char str[], int size, int n, int *count)
{
    if (size == 1)
    {
        printf("%d: %s\n", ++(*count), str);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        heaps_algorithm(str, size - 1, n, count);

        // If size is odd, swap first and last element
        if (size % 2 == 1)
        {
            swap_chars(&str[0], &str[size - 1]);
        }
        // If size is even, swap i-th and last element
        else
        {
            swap_chars(&str[i], &str[size - 1]);
        }
    }
}

void permutation_heaps()
{
    char str[] = "ABC";
    int len = str_length(str);
    int count = 0;

    printf("\n=== Permutations Using Heap's Algorithm ===\n");
    printf("String: \"%s\"\n", str);
    printf("(Most efficient algorithm for generating permutations)\n\n");

    heaps_algorithm(str, len, len, &count);
}

// ============================================================================
// DEMONSTRATION FUNCTION
// ============================================================================
void demo_string_permutations()
{
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║        STRING PERMUTATION ALGORITHMS COMPARISON            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    // Method 1: Brute Force (only for length 3)
    permutation_brute_force();

    // Method 2: Standard Backtracking
    permutation_backtracking();

    // Method 3: Backtracking with Visualization
    permutation_with_steps();

    // Method 4: Heap's Algorithm
    permutation_heaps();

    // Test with different string lengths
    printf("\n=== Testing with Different String Lengths ===\n");

    char test1[] = "AB";
    int count1 = 0;
    printf("\nString: \"%s\" → Permutations:\n", test1);
    permute_recursive(test1, 0, 1, &count1);

    char test2[] = "ABCD";
    int count2 = 0;
    printf("\nString: \"%s\" → Permutations:\n", test2);
    permute_recursive(test2, 0, 3, &count2);

    // Comparison table
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║              ALGORITHM COMPARISON TABLE                    ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ Method          │ Time      │ Space │ Works for any n?   ║\n");
    printf("║─────────────────┼───────────┼───────┼────────────────────║\n");
    printf("║ Brute Force     │ O(n³)     │ O(1)  │ NO (only n=3)      ║\n");
    printf("║ Backtracking    │ O(n!×n)   │ O(n)  │ YES ✓              ║\n");
    printf("║ Heap's Algo     │ O(n!)     │ O(n)  │ YES ✓ (fastest)    ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

void permutation_of_string()
{
    static char A[] = "ABC";
    static int i, j, k;

    printf("\n=== Permutations of String ===\n");
    printf("String: \"%s\"\n\n", A);

    int len = str_length(A);

    // Generate permutations using three nested loops
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len; j++)
        {
            for (k = 0; k < len; k++)
            {
                // Ensure all indices are different
                if (i != j && j != k && i != k)
                {
                    printf("%c%c%c\n", A[i], A[j], A[k]);
                }
            }
        }
    }

    printf("\nExplanation:\n");
    printf("- Three nested loops iterate over each character position\n");
    printf("- The condition ensures no character is repeated in a permutation\n");
    printf("- This method works well for small strings (length <= 3)\n");
}

void perm(char s[], int l, int h)
{
    if (l == h)
    {
        printf("%s\n", s);
    }
    else
    {
        for (int i = l; i <= h; i++)
        {
            swap_chars(&s[l], &s[i]);
            perm(s, l + 1, h);
            swap_chars(&s[l], &s[i]); // backtracking
        }
    }
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

// Demonstration of all methods:

void demo_case_conversion_methods()
{
    printf("\n=== Case Conversion Methods Demonstration ===\n");

    // Method 1: ASCII arithmetic
    char str1[] = "hello world 123";
    printf("\nMethod 1 - ASCII Arithmetic:\n");
    printf("Before: %s\n", str1);
    to_uppercase_ascii(str1);
    printf("After:  %s\n", str1);

    // Method 2: Lookup table
    char str2[] = "data structures in c";
    printf("\nMethod 2 - Lookup Table:\n");
    printf("Before: %s\n", str2);
    to_uppercase_lookup(str2);
    printf("After:  %s\n", str2);

    // Method 3: ctype.h
    char str3[] = "programming in c";
    printf("\nMethod 3 - ctype.h (toupper):\n");
    printf("Before: %s\n", str3);
    to_uppercase_ctype(str3);
    printf("After:  %s\n", str3);

    // Method 4: Bitwise operation
    char str4[] = "efficient algorithm";
    printf("\nMethod 4 - Bitwise Operation:\n");
    printf("Before: %s\n", str4);
    to_uppercase_bitwise(str4);
    printf("After:  %s\n", str4);

    // Demonstrate lowercase conversion
    char str5[] = "CONVERT TO LOWERCASE";
    printf("\nLowercase Conversion (ASCII):\n");
    printf("Before: %s\n", str5);
    to_lowercase_ascii(str5);
    printf("After:  %s\n", str5);

    char str6[] = "BITWISE LOWERCASE";
    printf("\nLowercase Conversion (Bitwise):\n");
    printf("Before: %s\n", str6);
    to_lowercase_bitwise(str6);
    printf("After:  %s\n", str6);

    // Performance comparison explanation
    printf("\n=== Performance Notes ===\n");
    printf("1. ASCII Arithmetic:   Fast, simple, readable\n");
    printf("2. Lookup Table:       O(n*26) time, educational value\n");
    printf("3. ctype.h:           Most portable, locale-aware\n");
    printf("4. Bitwise:           Fastest, ~2x faster than arithmetic\n");
}

void demo_basic_operations()
{
    printf("\n=== Basic String Operations ===\n");

    char str1[] = "Hello, World!";
    printf("Original string: %s\n", str1);
    printf("Length: %d\n", str_length(str1));

    char str2[50];
    str_copy(str2, "C Programming");
    printf("Copied string: %s\n", str2);

    char str3[100] = "Hello";
    str_concat(str3, " World");
    printf("Concatenated: %s\n", str3);
}

void demo_case_operations()
{
    printf("\n=== Case Operations ===\n");

    char str[] = "Data Structures in C";
    printf("Original: %s\n", str);

    char upper[50];
    str_copy(upper, str);
    str_to_upper(upper);
    printf("Uppercase: %s\n", upper);

    char lower[50];
    str_copy(lower, str);
    str_to_lower(lower);
    printf("Lowercase: %s\n", lower);

    char toggle[50];
    str_copy(toggle, str);
    str_toggle_case(toggle);
    printf("Toggle case: %s\n", toggle);
}

void demo_string_analysis()
{
    printf("\n=== String Analysis ===\n");

    char str[] = "Data Structures in C";
    printf("String: %s\n", str);
    printf("Vowels: %d\n", count_vowels(str));
    printf("Consonants: %d\n", count_consonants(str));
    printf("Words: %d\n", count_words(str));

    char pal1[] = "madam";
    char pal2[] = "hello";
    printf("\n'%s' is palindrome: %s\n", pal1, is_palindrome(pal1) ? "Yes" : "No");
    printf("'%s' is palindrome: %s\n", pal2, is_palindrome(pal2) ? "Yes" : "No");
}

void demo_advanced_operations()
{
    printf("\n=== Advanced Operations ===\n");

    char str[] = "hello";
    printf("Original: %s\n", str);
    str_reverse(str);
    printf("Reversed: %s\n", str);

    printf("\nAnagram check:\n");
    printf("'listen' and 'silent': %s\n", are_anagrams("listen", "silent") ? "Anagrams" : "Not anagrams");
    printf("'hello' and 'world': %s\n", are_anagrams("hello", "world") ? "Anagrams" : "Not anagrams");

    char dup[] = "programming";
    printf("\nOriginal: %s\n", dup);
    remove_duplicates(dup);
    printf("After removing duplicates: %s\n", dup);
}

void demo_comparison()
{
    printf("\n=== String Comparison ===\n");

    int cmp1 = str_compare("apple", "banana");
    int cmp2 = str_compare("hello", "hello");
    int cmp3 = str_compare("zebra", "apple");

    printf("'apple' vs 'banana': %d (negative means first is less)\n", cmp1);
    printf("'hello' vs 'hello': %d (zero means equal)\n", cmp2);
    printf("'zebra' vs 'apple': %d (positive means first is greater)\n", cmp3);
}

void demo_toggle_case_methods()
{

    // Test toggle_case_ascii function
    printf("\n=== Testing toggle_case_ascii Function ===\n");
    char test1[] = "Hello World!";
    printf("Original:     %s\n", test1);
    toggle_case_ascii(test1);

    printf("After toggle: %s\n", test1);
    toggle_case_ascii(test1);
    printf("Toggle back:  %s\n\n", test1);

    char test2[] = "ProGRamMinG In C 2024";
    printf("Original:     %s\n", test2);
    toggle_case_ascii(test2);
    printf("After toggle: %s\n", test2);

    char test3[] = "ABC123xyz";
    printf("\nOriginal:     %s\n", test3);
    toggle_case_ascii(test3);
    printf("After toggle: %s\n", test3);
};

void demo_vowel_consonant_counting()
{
    printf("\n=== Vowel and Consonant Counting Demonstration ===\n");

    // Method 1: Using output parameters
    const char *test1 = "How are you";
    int vowels, consonants;
    count_vowels_consonants(test1, &vowels, &consonants);
    printf("\nMethod 1 - Output Parameters:\n");
    printf("String: \"%s\"\n", test1);
    printf("Vowels: %d, Consonants: %d\n", vowels, consonants);

    // Method 2: Direct printing
    printf("\nMethod 2 - Direct Printing:\n");
    count_and_print_vowels_consonants("Programming in C");

    // Method 3: Lookup table
    const char *test3 = "Data Structures and Algorithms";
    count_vowels_consonants_lookup(test3, &vowels, &consonants);
    printf("\nMethod 3 - Lookup Table:\n");
    printf("String: \"%s\"\n", test3);
    printf("Vowels: %d, Consonants: %d\n", vowels, consonants);

    // Test with various strings
    printf("\n=== Multiple Test Cases ===\n");
    const char *tests[] = {
        "Hello World!",
        "AEIOU",
        "bcdfg",
        "C Programming 2024",
        "xyz123ABC"};

    for (int i = 0; i < 5; i++)
    {
        count_vowels_consonants(tests[i], &vowels, &consonants);
        printf("%-25s -> Vowels: %2d, Consonants: %2d\n",
               tests[i], vowels, consonants);
    }

    printf("\n=== Performance Comparison ===\n");
    printf("1. Output Parameters:  Flexible, can use counts elsewhere\n");
    printf("2. Direct Printing:    Simple, good for one-time use\n");
    printf("3. Lookup Table:       Fastest, O(1) vowel check per char\n");
}

void demoCountingWordsVowelsConsonants()
{
    printf("\n=== Counting Words, Vowels, and Consonants ===\n");

    const char *testStr = "Data Structures in C Programming";
    int words, vowels, consonants;

    count_words_vowels_consonants(testStr, &words, &vowels, &consonants);

    printf("String: \"%s\"\n", testStr);
    printf("Words: %d, Vowels: %d, Consonants: %d\n", words, vowels, consonants);
}

void demo_bitwise_operations()
{
    printf("\n=== Bitwise Operations Demonstration ===\n");

    // Demonstrate binary representation
    char ch = 'A';
    bitwise_binary_representation(ch);
    ch = 'a';
    bitwise_binary_representation(ch);

    // Demonstrate finding duplicates using bitwise hashing
    demo_finding_duplicates_bitwise();

    // Demonstrate anagram checking
    printf("\n");
    checkfor_anagram_bitwise();
}

// ============================================================================
// MAIN clang -o string_app Strings/String.c && ./string_app
// ============================================================================
int main(int argc, const char *argv[])
{
    printf("=== String Operations Demonstration ===\n");

    printf("\n");
    demo_basic_operations();
    printf("\n");
    demo_case_operations();
    printf("\n");
    demo_string_analysis();
    printf("\n");
    demo_advanced_operations();
    printf("\n");
    demo_comparison();
    printf("\n");
    demo_case_conversion_methods();
    printf("\n");
    demo_toggle_case_methods();
    printf("\n");
    demo_vowel_consonant_counting();
    printf("\n");
    demoCountingWordsVowelsConsonants();
    printf("\n");
    count_and_print_vowels_consonants_directly();
    printf("\n");
    count_and_print_words_directly();
    printf("\n");
    demo_string_validation();
    printf("\n");
    demo_string_reversal();
    printf("\n");
    comparing_string();
    printf("\n");
    demo_finding_duplicate_characters();
    printf("\n");
    demo_finding_dublicate_brute_force_comparison_marker();
    printf("\n");
    demo_finding_dublicate_brute_force_comparison();
    printf("\n");
    demo_finfing_duplicate_characters_hashing();
    printf("\n");

    // Bitwise demonstrations
    printf("=== Bitwise Operations Demonstrations ===\n");
    bitwise_binary_representation('A');
    bitwise_binary_representation('a');
    bitwise_binary_representation('Z');
    bitwise_binary_representation('5');
    demo_finding_duplicates_bitwise();

    // Binary Search demonstration
    printf("\n");
    demo_binary_search();

    // Permutation demonstrations
    printf("\n=== Permutation of String Demonstrations ===\n");
    char s[] = "ABC";
    perm(s, 0, 2);
    permutation_of_string();
    printf("\n");
    demo_string_permutations();
    printf("\n");

    printf("\n=== End of Program ===\n");
    return 0;
}
/*
benraiss@Mbareks-MacBook-Air data-structures-c-cpp % clang -o string_app1 Strings/String.c
benraiss@Mbareks-MacBook-Air data-structures-c-cpp % ./string_app1
=== String Operations Demonstration ===

=== Basic String Operations ===
Original string: Hello, World!
Length: 13
Copied string: C Programming
Concatenated: Hello World


=== Case Operations ===
Original: Data Structures in C
Uppercase: DATA STRUCTURES IN C
Lowercase: data structures in c
Toggle case: dATA sTRUCTURES IN c


=== String Analysis ===
String: Data Structures in C
Vowels: 6
Consonants: 11
Words: 4

'madam' is palindrome: Yes
'hello' is palindrome: No


=== Advanced Operations ===
Original: hello
Reversed: olleh

Anagram check:
'listen' and 'silent': Anagrams
'hello' and 'world': Not anagrams

Original: programming
After removing duplicates: progamin


=== String Comparison ===
'apple' vs 'banana': -1 (negative means first is less)
'hello' vs 'hello': 0 (zero means equal)
'zebra' vs 'apple': 25 (positive means first is greater)


=== Case Conversion Methods Demonstration ===

Method 1 - ASCII Arithmetic:
Before: hello world 123
After:  HELLO WORLD 123

Method 2 - Lookup Table:
Before: data structures in c
After:  DATA STRUCTURES IN C

Method 3 - ctype.h (toupper):
Before: programming in c
After:  PROGRAMMING IN C

Method 4 - Bitwise Operation:
Before: efficient algorithm
After:  EFFICIENT ALGORITHM

Lowercase Conversion (ASCII):
Before: CONVERT TO LOWERCASE
After:  convert to lowercase

Lowercase Conversion (Bitwise):
Before: BITWISE LOWERCASE
After:  bitwise lowercase

=== Performance Notes ===
1. ASCII Arithmetic:   Fast, simple, readable
2. Lookup Table:       O(n*26) time, educational value
3. ctype.h:           Most portable, locale-aware
4. Bitwise:           Fastest, ~2x faster than arithmetic


=== Testing toggle_case_ascii Function ===
Original:     Hello World!
After toggle: hELLO wORLD!
Toggle back:  Hello World!

Original:     ProGRamMinG In C 2024
After toggle: pROgrAMmINg iN c 2024

Original:     ABC123xyz
After toggle: abc123XYZ


=== Vowel and Consonant Counting Demonstration ===

Method 1 - Output Parameters:
String: "How are you"
Vowels: 5, Consonants: 4

Method 2 - Direct Printing:
String: "Programming in C"
Vowels: 4
Consonants: 10

Method 3 - Lookup Table:
String: "Data Structures and Algorithms"
Vowels: 9, Consonants: 18

=== Multiple Test Cases ===
Hello World!              -> Vowels:  3, Consonants:  7
AEIOU                     -> Vowels:  5, Consonants:  0
bcdfg                     -> Vowels:  0, Consonants:  5
C Programming 2024        -> Vowels:  3, Consonants:  9
xyz123ABC                 -> Vowels:  1, Consonants:  5

=== Performance Comparison ===
1. Output Parameters:  Flexible, can use counts elsewhere
2. Direct Printing:    Simple, good for one-time use
3. Lookup Table:       Fastest, O(1) vowel check per char


=== Counting Words, Vowels, and Consonants ===
String: "Data Structures in C Programming"
Words: 5, Vowels: 9, Consonants: 19

String: "abcd efg hijklmnop qrstuvw xyz"
Vowels: 5
Consonants: 21

Words: 5


=== String Validation Demonstration ===

=== String Validation ===
Original String: Ani?32!
'A' is an alphabetic character.
'n' is an alphabetic character.
'i' is an alphabetic character.
'?' is a special character.
'3' is a digit.
'2' is a digit.
'!' is a special character.

Summary:
Alphabetic characters: 3
Digits: 2
Special characters: 2

Validation result: INVALID (has special chars)

=== Testing Multiple Strings ===

String: "Hello123"
  Alphanumeric: YES
  Alphabetic only: NO

String: "OnlyLetters"
  Alphanumeric: YES
  Alphabetic only: YES

String: "With Spaces"
  Alphanumeric: NO
  Alphabetic only: NO

String: "Special!@#"
  Alphanumeric: NO
  Alphabetic only: NO

String: "Mix3d_Ch4rs"
  Alphanumeric: NO
  Alphabetic only: NO


=== String Reversal Methods ===

Method 1 - In-place Reversal:
Before: Hello World
After:  dlroW olleH

Method 2 - Copy to New String:
Original: Programming in C
Reversed: C ni gnimmargorP

Method 3 - Without Temp Array (hardcoded):
Reversed string: nohtyP

=== Immutability Check ===
Original string unchanged: Programming in C

String A is greater than String B


=== Finding Duplicate Characters in a String ===
Duplicate characters in "programming":
'g' occurs 2 times
'm' occurs 2 times
'r' occurs 2 times

Duplicate characters in "finding" (Brute Force using -1 marker):
'i' appears 2 times
'n' appears 2 times
Original string modified with markers: find��g

Duplicate characters in "findinng" (Brute Force ):
'i' appears 2 times
'n' appears 3 times
Original string preserved: findinng

i occurs 2 times
n occurs 2 times

=== Bitwise Operations Demonstrations ===
Character: 'A' | ASCII: 65 | Binary: 0100 0001
Character: 'a' | ASCII: 97 | Binary: 0110 0001
Character: 'Z' | ASCII: 90 | Binary: 0101 1010
Character: '5' | ASCII: 53 | Binary: 0011 0101

=== Finding Duplicates Using Bitwise Hashing ===
String: "finding"

'f' is new (setting bit 5)
'i' is new (setting bit 8)
'n' is new (setting bit 13)
'd' is new (setting bit 3)
'i' is a duplicate (bit 8 is already set)
'n' is a duplicate (bit 13 is already set)
'g' is new (setting bit 6)

Final hash value: 8552 (0x2168)

Explanation:
- Each bit position represents a letter (0='a', 1='b', ..., 25='z')
- If bit is 1, that letter has been seen
- If bit is 0, that letter hasn't been seen yet


=== Binary Search Demonstration ===
Sorted array: 5 8 12 15 18 21 25

Key 18 found at index 4
Key 5 found at index 0
Key 25 found at index 6
Key 10 NOT found in array
Key 30 NOT found in array

╔════════════════════════════════════════════════════════════╗
║              BINARY SEARCH COMPLEXITY                      ║
╠════════════════════════════════════════════════════════════╣
║ Time Complexity:   O(log n)                               ║
║ Space Complexity:  O(1)                                   ║
║ Precondition:      Array must be SORTED                   ║
║ Best Case:         O(1) - element at middle               ║
║ Worst Case:        O(log n) - not found or at end         ║
╚════════════════════════════════════════════════════════════╝

=== Permutation of String Demonstrations ===
ABC
ACB
BAC
BCA
CBA
CAB

=== Permutations of String ===
String: "ABC"

ABC
ACB
BAC
BCA
CAB
CBA

Explanation:
- Three nested loops iterate over each character position
- The condition ensures no character is repeated in a permutation
- This method works well for small strings (length <= 3)


╔════════════════════════════════════════════════════════════╗
║        STRING PERMUTATION ALGORITHMS COMPARISON            ║
╚════════════════════════════════════════════════════════════╝

=== Permutations Using Brute Force (3 Nested Loops) ===
String: "ABC" (length = 3)
Total permutations: 3! = 6

1: ABC
2: ACB
3: BAC
4: BCA
5: CAB
6: CBA

Limitation: This method ONLY works for strings of length 3!

=== Permutations Using Backtracking (Recursive) ===
String: "ABC" (length = 3)
Total permutations: 3! = 6

1: ABC
2: ACB
3: BAC
4: BCA
5: CBA
6: CAB

This method works for ANY string length!

=== Permutations with Step-by-Step Visualization ===
String: "ABC"
Watch how backtracking generates all permutations:

Level 0: Fixing position 0, trying chars: A B C
→ Swap str[0]='A' ↔ str[0]='A' → ABC
  Level 1: Fixing position 1, trying chars: B C
  → Swap str[1]='B' ↔ str[1]='B' → ABC
    ✓ Found permutation: ABC
  ← Backtrack: Swap back str[1]='B' ↔ str[1]='B' → ABC
  → Swap str[1]='B' ↔ str[2]='C' → ACB
    ✓ Found permutation: ACB
  ← Backtrack: Swap back str[1]='C' ↔ str[2]='B' → ABC
← Backtrack: Swap back str[0]='A' ↔ str[0]='A' → ABC
→ Swap str[0]='A' ↔ str[1]='B' → BAC
  Level 1: Fixing position 1, trying chars: A C
  → Swap str[1]='A' ↔ str[1]='A' → BAC
    ✓ Found permutation: BAC
  ← Backtrack: Swap back str[1]='A' ↔ str[1]='A' → BAC
  → Swap str[1]='A' ↔ str[2]='C' → BCA
    ✓ Found permutation: BCA
  ← Backtrack: Swap back str[1]='C' ↔ str[2]='A' → BAC
← Backtrack: Swap back str[0]='B' ↔ str[1]='A' → ABC
→ Swap str[0]='A' ↔ str[2]='C' → CBA
  Level 1: Fixing position 1, trying chars: B A
  → Swap str[1]='B' ↔ str[1]='B' → CBA
    ✓ Found permutation: CBA
  ← Backtrack: Swap back str[1]='B' ↔ str[1]='B' → CBA
  → Swap str[1]='B' ↔ str[2]='A' → CAB
    ✓ Found permutation: CAB
  ← Backtrack: Swap back str[1]='A' ↔ str[2]='B' → CBA
← Backtrack: Swap back str[0]='C' ↔ str[2]='A' → ABC

=== Permutations Using Heap's Algorithm ===
String: "ABC"
(Most efficient algorithm for generating permutations)

1: ABC
2: BAC
3: CAB
4: ACB
5: BCA
6: CBA

=== Testing with Different String Lengths ===

String: "AB" → Permutations:
1: AB
2: BA

String: "ABCD" → Permutations:
1: ABCD
2: ABDC
3: ACBD
4: ACDB
5: ADCB
6: ADBC
7: BACD
8: BADC
9: BCAD
10: BCDA
11: BDCA
12: BDAC
13: CBAD
14: CBDA
15: CABD
16: CADB
17: CDAB
18: CDBA
19: DBCA
20: DBAC
21: DCBA
22: DCAB
23: DACB
24: DABC

╔════════════════════════════════════════════════════════════╗
║              ALGORITHM COMPARISON TABLE                    ║
╠════════════════════════════════════════════════════════════╣
║ Method          │ Time      │ Space │ Works for any n?   ║
║─────────────────┼───────────┼───────┼────────────────────║
║ Brute Force     │ O(n³)     │ O(1)  │ NO (only n=3)      ║
║ Backtracking    │ O(n!×n)   │ O(n)  │ YES ✓              ║
║ Heap's Algo     │ O(n!)     │ O(n)  │ YES ✓ (fastest)    ║
╚════════════════════════════════════════════════════════════╝
*/

// clang -o string_app Strings/String.c && ./string_app
// gcc -std=c17 -o string_app Strings/String.c && ./string_app

// clang -o string_app String.c && ./string_app
// gcc -std=c17 -o string_app String.c && ./string_app
