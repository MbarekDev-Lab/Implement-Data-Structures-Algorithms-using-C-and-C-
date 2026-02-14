#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * PERMUTATIONS & BACKTRACKING WITH BRANCH & BOUND
 * 
 * Core Concepts:
 *   • A permutation is an arrangement of items
 *   • Backtracking explores a tree of partial solutions
 *   • Bounding function decides which branches to prune
 *   • Pruning is what makes exponential problems tractable
 * 
 * Template:
 *   solve(position):
 *       if position == n:
 *           record solution
 *           return
 *       
 *       for each candidate:
 *           if (bounding_function(candidate)):
 *               apply(candidate)
 *               solve(position + 1)
 *               undo(candidate)
 */

// Global state
int n_elements;
int perm[MAX_N];
bool used[MAX_N];

// Statistics
long long solution_count = 0;
long long nodes_explored = 0;
long long branches_pruned = 0;

/**
 * bounding_function: Decides if we should continue
 * 
 * For permutations: Element must not be already used
 * This prevents duplicate elements
 */
bool bounding_function(int element) {
    return !used[element];  // Valid if NOT used
}

/**
 * generate_permutation: Generate all permutations with backtracking
 * 
 * Position: Current position in permutation
 * Demonstrates the classic backtracking template
 */
void generate_permutation(int position) {
    nodes_explored++;
    
    // BASE CASE: All positions filled
    if (position == n_elements) {
        solution_count++;
        return;
    }
    
    // RECURSIVE CASE: Try each element at this position
    for (int i = 0; i < n_elements; i++) {
        
        // BOUNDING FUNCTION: Check if element is available
        if (bounding_function(i)) {
            
            // APPLY: Choose this element
            perm[position] = i + 1;
            used[i] = true;
            
            // RECURSE: Fill next position
            generate_permutation(position + 1);
            
            // UNDO: Restore state (CRITICAL!)
            used[i] = false;
        } else {
            branches_pruned++;
        }
    }
}

/**
 * print_permutation: Display a specific permutation
 */
void print_permutation(int perm[]) {
    printf("  [");
    for (int i = 0; i < n_elements; i++) {
        printf("%d%s", perm[i], i < n_elements - 1 ? ", " : "");
    }
    printf("]\n");
}

/**
 * demonstrate_recursion_tree: Show the decision tree structure
 */
void demonstrate_recursion_tree(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ RECURSION TREE STRUCTURE (Permutations of 3 elements)      ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Decision Tree:\n\n");
    printf("                         [empty]\n");
    printf("            /              |              \\\n");
    printf("           1              2              3         (Position 0)\n");
    printf("          / \\            / \\            / \\\n");
    printf("         2   3          1   3          1   2       (Position 1)\n");
    printf("        /     \\        /     \\        /     \\\n");
    printf("       3       2      3       1      2       1      (Position 2)\n");
    printf("       ↓       ↓      ↓       ↓      ↓       ↓\n");
    printf("   [1,2,3] [1,3,2] [2,1,3] [2,3,1] [3,1,2] [3,2,1]  (Solutions)\n\n");
    
    printf("Key observations:\n");
    printf("  • Depth = n (number of positions)\n");
    printf("  • Branching at level k = (n - k) remaining elements\n");
    printf("  • Leaves = n! permutations\n");
    printf("  • With bounding: Some branches pruned (if constraint fails)\n\n");
}

/**
 * demonstrate_bounding_function: Show how bounding prunes branches
 */
void demonstrate_bounding_function(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ BOUNDING FUNCTION IN ACTION                               ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("For Permutations:\n\n");
    printf("Bounding Function: \"Is this element already used?\"\n\n");
    
    printf("Example: Building permutation at Position 0\n");
    printf("  Try element 1:\n");
    printf("    used[0] = false → %sAccept ✓%s\n", GREEN, RESET);
    printf("    Mark used[0] = true\n");
    printf("    Recurse to Position 1\n");
    printf("    Unmark used[0] = false (backtrack)\n\n");
    
    printf("  Try element 1 again (already used in subtree):\n");
    printf("    used[0] = true → %sPrune ✗%s\n", RED, RESET);
    printf("    Skip this branch\n\n");
    
    printf("Result:\n");
    printf("  Without bounding: Generate [1,1,2], [1,1,3], etc. (INVALID)\n");
    printf("  With bounding: Only valid permutations\n\n");
}

/**
 * test_permutation_generation: Run tests
 */
void test_permutation_generation(int n) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ PERMUTATION GENERATION: n=%d%s║%s\n",
           BLUE, n, n < 10 ? "  " : " ", RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    n_elements = n;
    solution_count = 0;
    nodes_explored = 0;
    branches_pruned = 0;
    
    memset(used, false, sizeof(used));
    
    printf("Problem: Generate all permutations of [1, 2, ..., %d]\n", n);
    printf("Expected: %d! = ", n);
    
    // Calculate factorial
    long long factorial = 1;
    for (int i = 2; i <= n; i++) factorial *= i;
    printf("%lld permutations\n\n", factorial);
    
    // Generate all permutations
    generate_permutation(0);
    
    printf("Results:\n");
    printf("  %sSolutions found: %lld%s\n", GREEN, solution_count, RESET);
    printf("  Nodes explored:  %lld\n", nodes_explored);
    printf("  Branches pruned: %lld\n", branches_pruned);
    printf("  Total nodes:     %lld\n", nodes_explored + branches_pruned);
    
    if (nodes_explored > 0) {
        double pruning_rate = 100.0 * branches_pruned / (nodes_explored + branches_pruned);
        printf("  Pruning rate:    %.1f%%\n", pruning_rate);
    }
    
    printf("\n");
}

/**
 * demonstrate_algorithm_structure: Show the code structure
 */
void demonstrate_algorithm_structure(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ BACKTRACKING ALGORITHM STRUCTURE                           ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("void generate_permutation(int position) {\n");
    printf("    nodes_explored++;\n");
    printf("    \n");
    printf("    // BASE CASE: All positions filled\n");
    printf("    if (position == n) {\n");
    printf("        solution_count++;\n");
    printf("        return;\n");
    printf("    }\n\n");
    
    printf("    // RECURSIVE CASE: Try each element\n");
    printf("    for (int i = 0; i < n; i++) {\n");
    printf("        \n");
    printf("        // BOUNDING FUNCTION: Is element available?\n");
    printf("        if (bounding_function(i)) {  // !used[i]\n");
    printf("            \n");
    printf("            perm[position] = i + 1;   // APPLY\n");
    printf("            used[i] = true;\n");
    printf("            \n");
    printf("            generate_permutation(position + 1);  // RECURSE\n");
    printf("            \n");
    printf("            used[i] = false;           // UNDO\n");
    printf("        } else {\n");
    printf("            branches_pruned++;         // Prune branch\n");
    printf("        }\n");
    printf("    }\n");
    printf("}\n\n");
    
    printf("Pattern: %sTry → Check → Recurse → Undo%s\n\n", YELLOW, RESET);
}

/**
 * complexity_analysis: Show complexity theory
 */
void complexity_analysis(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           CYAN, RESET);
    printf("%s║ COMPLEXITY ANALYSIS                                        ║%s\n",
           CYAN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           CYAN, RESET);
    
    printf("Time Complexity:\n");
    printf("  Worst case: O(n!) — All permutations are valid\n");
    printf("  With pruning: O(k) where k = solutions found + pruned branches\n\n");
    
    printf("Space Complexity:\n");
    printf("  Recursion stack: O(n) — Maximum depth is n\n");
    printf("  Used array: O(n) — Track which elements are used\n");
    printf("  Permutation array: O(n) — Store current arrangement\n");
    printf("  Total: O(n)\n\n");
    
    printf("Comparison:\n\n");
    printf("| Approach | Generation | Filtering | Total Time | Space |\n");
    printf("|----------|---|---|---|---|\n");
    printf("| Brute Force | Generate all n! | Filter | O(n! + filter) | O(n!) |\n");
    printf("| Backtracking | Build incrementally | Check during | O(n! or less) | O(n) |\n");
    printf("| With Bounding | Skip invalid early | Impossible paths pruned | Much better | O(n) |\n\n");
    
    printf("Example (n=8):\n");
    printf("  Brute Force: Generate 40,320, filter them\n");
    printf("  Backtracking: Explore ~40,320 or fewer nodes\n");
    printf("  With constraints: Could be 1,000 or fewer nodes (95 percent pruning)\n\n");
}

/**
 * master_template: Explain the universal template
 */
void master_template(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ UNIVERSAL BACKTRACKING TEMPLATE                            ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("This template solves most backtracking problems:\n\n");
    
    printf("void solve(state) {\n");
    printf("    // BASE CASE\n");
    printf("    if (is_complete(state)) {\n");
    printf("        record_solution(state);\n");
    printf("        return;\n");
    printf("    }\n\n");
    
    printf("    // RECURSIVE CASE\n");
    printf("    for (each candidate) {\n");
    printf("        // BOUNDING FUNCTION (KEY!)\n");
    printf("        if (is_valid(candidate, state)) {\n");
    printf("            apply(candidate, state);       // CHOOSE\n");
    printf("            solve(new_state);              // RECURSE\n");
    printf("            remove(candidate, state);      // UNDO\n");
    printf("        }\n");
    printf("        // else: Branch is pruned\n");
    printf("    }\n");
    printf("}\n\n");
    
    printf("Customization:\n");
    printf("  Problem | Candidates | Bounding Check | State Variables\n");
    printf("  ---------|-------------|----------------|------------\n");
    printf("  Permutations | Unused elements | !used[i] | used[]\n");
    printf("  N-Queens | Rows in column | Check conflicts | row[], diag[]\n");
    printf("  Sudoku | Digits 1-9 | Check cell rules | row[], col[], box[]\n");
    printf("  Combinations | Remaining items | Avoid duplicates | start_idx\n");
    printf("  Word Search | Neighbors | Check visited | visited[]\n\n");
}

/**
 * key_insights: Pedagogical points
 */
void key_insights(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ KEY INSIGHTS                                               ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("1️⃣  %sPermutation is just ordered arrangement%s\n", CYAN, RESET);
    printf("    Items: {1, 2, 3}\n");
    printf("    Arrangements: [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]\n");
    printf("    Total: 3! = 6\n\n");
    
    printf("2️⃣  %sBacktracking explores a decision tree%s\n", CYAN, RESET);
    printf("    Not brute force (generate all then filter)\n");
    printf("    Build incrementally (try-check-continue-undo)\n");
    printf("    Actual nodes explored ≤ nodes in decision tree\n\n");
    
    printf("3️⃣  %sBounding function is the magic%s\n", CYAN, RESET);
    printf("    It answers: \"Should I continue exploring this branch?\"\n");
    printf("    Without it: Generate invalid permutations\n");
    printf("    With it: Skip entire subtrees instantly\n\n");
    
    printf("4️⃣  %sUndo step is critical%s\n", CYAN, RESET);
    printf("    Many beginners forget this!\n");
    printf("    After recursing, must restore state completely\n");
    printf("    Enables trying next candidate from clean state\n\n");
    
    printf("5️⃣  %sThis appears everywhere%s\n", CYAN, RESET);
    printf("    N-Queens (constrain permutations + diagonals)\n");
    printf("    Sudoku (constrain permutations + row/col/box)\n");
    printf("    Graph coloring (assign colors with constraints)\n");
    printf("    AI game trees (prune with heuristics)\n");
    printf("    Operations research (Branch & Bound optimization)\n\n");
}

/**
 * main: Run comprehensive demonstrations
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║      PERMUTATIONS & BRANCH & BOUND — BACKTRACKING FOUNDATIONS              ║%s\n",
           BLUE, RESET);
    printf("%s║   Teaching: How to search exponential spaces intelligently                 ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Demonstrations
    demonstrate_recursion_tree();
    demonstrate_bounding_function();
    demonstrate_algorithm_structure();
    
    // Tests
    test_permutation_generation(3);
    test_permutation_generation(4);
    test_permutation_generation(5);
    
    // Analysis
    complexity_analysis();
    
    // Templates and insights
    master_template();
    key_insights();
    
    // Final summary
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ FINAL WISDOM                                               ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("What You Now Understand:\n\n");
    
    printf("✅ %sPermutations%s are arrangements; n! of them exist\n", GREEN, RESET);
    printf("✅ %sBacktracking%s explores a decision tree incrementally\n", GREEN, RESET);
    printf("✅ %sBounding functions%s prune invalid branches early\n", GREEN, RESET);
    printf("✅ %sUndo step%s restores state for trying next candidate\n", GREEN, RESET);
    printf("✅ %sThis framework%s solves 100+ different problems\n", GREEN, RESET);
    printf("✅ %sThe key insight%s: Explore only promising branches\n\n", GREEN, RESET);
    
    printf("From Here:\n\n");
    printf("Next step: Add constraints to permutations\n");
    printf("  • N-Queens: Permutations with diagonal constraints\n");
    printf("  • Sudoku: Permutations with row/col/box constraints\n");
    printf("  • Combinations: Permutations with ordering constraint\n\n");
    
    printf("The template NEVER changes.\n");
    printf("Only the bounding function and candidates change.\n");
    printf("This is the beauty of algorithmic thinking.\n\n");
    
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("Master this pattern. You unlock exponential problem solving.\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
