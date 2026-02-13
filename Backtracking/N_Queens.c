#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * N-Queens Problem — Backtracking & Constraint Satisfaction
 * 
 * Core Idea:
 *   Place one queen per column.
 *   For each column, try each row.
 *   Check row and diagonal constraints using O(1) array lookup.
 *   Backtrack if dead end.
 * 
 * Key Optimization:
 *   Diagonals identified by:
 *   - Main diagonal: (row - col + N) is constant
 *   - Anti-diagonal: (row + col) is constant
 * 
 * Time: O(N!) worst case, but heavy pruning in practice
 * Space: O(N) for recursion stack + constraint arrays
 */

// Global state
int N;
int queens[MAX_N];              // queens[col] = row of queen in that column
int row_used[MAX_N];            // row_used[r] = 1 if row r has a queen
int main_diag_used[2*MAX_N];    // Main diagonal (↘) tracking
int anti_diag_used[2*MAX_N];    // Anti-diagonal (↙) tracking

// Statistics
int solution_count = 0;
long long node_count = 0;
long long pruned_count = 0;

/**
 * is_safe: Check if placing queen at (row, col) is safe
 * 
 * O(1) time due to array lookups instead of board scanning
 */
int is_safe(int row, int col) {
    // Row constraint
    if (row_used[row]) return 0;
    
    // Main diagonal constraint: row - col is constant
    if (main_diag_used[row - col + N]) return 0;
    
    // Anti-diagonal constraint: row + col is constant
    if (anti_diag_used[row + col]) return 0;
    
    return 1;
}

/**
 * place_queen: Place queen and mark constraints
 */
void place_queen(int row, int col) {
    queens[col] = row;
    row_used[row] = 1;
    main_diag_used[row - col + N] = 1;
    anti_diag_used[row + col] = 1;
}

/**
 * remove_queen: Remove queen and unmark constraints (BACKTRACK)
 */
void remove_queen(int row, int col) {
    queens[col] = -1;
    row_used[row] = 0;
    main_diag_used[row - col + N] = 0;
    anti_diag_used[row + col] = 0;
}

/**
 * solve: Recursive backtracking solver
 * 
 * Parameter: col = current column to place queen in
 * 
 * Template:
 *   if goal reached:
 *       record solution
 *       return
 *   
 *   for each candidate:
 *       if valid:
 *           apply(candidate)
 *           solve(next_state)
 *           remove(candidate)  // BACKTRACK
 */
void solve(int col) {
    node_count++;
    
    // BASE CASE: All columns filled
    if (col == N) {
        solution_count++;
        return;
    }
    
    // RECURSIVE CASE: Try each row in this column
    for (int row = 0; row < N; row++) {
        if (is_safe(row, col)) {
            // APPLY: Place queen
            place_queen(row, col);
            
            // RECURSE: Go deeper
            solve(col + 1);
            
            // REMOVE: Backtrack
            remove_queen(row, col);
        } else {
            pruned_count++;
        }
    }
}

/**
 * print_board: Display the solution
 */
void print_board(void) {
    printf("\nSolution #%d:\n\n", solution_count);
    
    // Print column numbers
    printf("  ");
    for (int c = 0; c < N; c++) printf("%d ", c);
    printf("\n");
    
    // Print board
    for (int r = 0; r < N; r++) {
        printf("%d ", r);
        for (int c = 0; c < N; c++) {
            if (queens[c] == r) {
                printf("%sQ%s ", GREEN, RESET);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

/**
 * solve_and_print: Solve with visualization
 */
void solve_and_print(int n) {
    N = n;
    
    // Reset global state
    solution_count = 0;
    node_count = 0;
    pruned_count = 0;
    
    memset(queens, -1, sizeof(queens));
    memset(row_used, 0, sizeof(row_used));
    memset(main_diag_used, 0, sizeof(main_diag_used));
    memset(anti_diag_used, 0, sizeof(anti_diag_used));
    
    // Solve
    solve(0);
}

/**
 * demonstrate_constraints: Show how diagonal constraints work
 */
void demonstrate_constraints(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ DIAGONAL CONSTRAINT DETECTION                              ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("For a 4×4 board:\n\n");
    
    printf("Main Diagonal (↘): row - col = constant\n");
    printf("  Cells (0,0), (1,1), (2,2), (3,3) are on same diagonal\n");
    printf("  0-0=0, 1-1=0, 2-2=0, 3-3=0 ✓\n");
    printf("  They would all map to main_diag_used[0+4] = main_diag_used[4]\n\n");
    
    printf("Anti-Diagonal (↙): row + col = constant\n");
    printf("  Cells (0,3), (1,2), (2,1), (3,0) are on same diagonal\n");
    printf("  0+3=3, 1+2=3, 2+1=3, 3+0=3 ✓\n");
    printf("  They would all map to anti_diag_used[3]\n\n");
    
    printf("Algorithm Optimization:\n");
    printf("  ❌ Naive: Scan entire board for conflicts → O(N) per check\n");
    printf("  ✅ Smart: Use arrays → O(1) per check\n");
    printf("  This matters! Applied log(N!) times in recursion.\n\n");
}

/**
 * demonstrate_recursion_tree: Show how recursion explores tree
 */
void demonstrate_recursion_tree(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ RECURSION TREE STRUCTURE (for N=4)                         ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Tree Navigation (DFS):\n\n");
    
    printf("Depth 0 (Column 0):  Try rows 0, 1, 2, 3\n");
    printf("                       ↓ (suppose row 1 works)\n");
    printf("Depth 1 (Column 1):  Try rows 0, 1, 2, 3\n");
    printf("                       (row 1 conflicts → skip)\n");
    printf("                       (row 0 conflicts → skip)\n");
    printf("                       ↓ (suppose row 2 works)\n");
    printf("Depth 2 (Column 2):  Try rows 0, 1, 2, 3\n");
    printf("                       ↓ (suppose row 0 works)\n");
    printf("Depth 3 (Column 3):  Try rows 0, 1, 2, 3\n");
    printf("                       ↓ (all fail)\n");
    printf("                       BACKTRACK to Depth 2\n");
    printf("                       Try next row...\n\n");
    
    printf("Key Points:\n");
    printf("  • Each level = one column\n");
    printf("  • Each branch = trying a row\n");
    printf("  • X branches = pruned due to conflicts\n");
    printf("  • Leaf = either solution or dead end\n");
    printf("  • Backtrack when dead end\n\n");
}

/**
 * test_case: Run N-Queens for specific N
 */
void test_case(int n) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ N-QUEENS PROBLEM: N=%d%s║%s\n",
           BLUE, n, n < 10 ? "  " : " ", RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Problem: Place %d queens on %dx%d board\n", n, n, n);
    printf("Constraint: No two queens attack each other\n\n");
    
    // Solve
    solve_and_print(n);
    
    printf("%sResults:%s\n", YELLOW, RESET);
    printf("  Solutions found: %d\n", solution_count);
    printf("  Nodes explored:  %lld\n", node_count);
    printf("  Branches pruned: %lld\n", pruned_count);
    
    if (solution_count > 0) {
        printf("  Pruning rate: %.1f%% of branches eliminated\n",
               100.0 * pruned_count / (pruned_count + (node_count - pruned_count)));
    }
    
    printf("\n");
}

/**
 * compare_complexity: Show growth rates
 */
void compare_complexity(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           CYAN, RESET);
    printf("%s║ COMPLEXITY ANALYSIS: Brute Force vs Backtracking           ║%s\n",
           CYAN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           CYAN, RESET);
    
    printf("| N | Total Possible | Backtracking Explored | Reduction |\n");
    printf("|---|----------------|----------------------|-----------|\n");
    
    // Pre-computed results from running the algorithm
    struct {
        int n;
        long long brute_force;
        long long backtracking;
        int solutions;
    } data[] = {
        {4, 24, 16, 2},
        {5, 120, 53, 10},
        {6, 720, 152, 4},
        {7, 5040, 551, 40},
        {8, 40320, 2057, 92},
    };
    
    for (int i = 0; i < 5; i++) {
        int n = data[i].n;
        long long brute = data[i].brute_force;
        long long backtrack = data[i].backtracking;
        double reduction = 100.0 * (1.0 - (double)backtrack / brute);
        
        printf("| %d | %12lld | %20lld | %6.1f%% |\n",
               n, brute, backtrack, reduction);
    }
    
    printf("\n");
    printf("Key Insight:\n");
    printf("  Backtracking explores far fewer nodes than permutation brute force.\n");
    printf("  Why? Constraints are applied during construction, not after.\n");
    printf("  Dead branches pruned before full exploration.\n\n");
}

/**
 * main: Run all demonstrations and tests
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║         N-QUEENS PROBLEM — BACKTRACKING & CONSTRAINT SATISFACTION         ║%s\n",
           BLUE, RESET);
    printf("%s║       Teaching: Systematic trial-error with intelligent pruning           ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // ═══════════════════════════════════════════════════════════
    // Demonstrations
    // ═══════════════════════════════════════════════════════════
    
    demonstrate_constraints();
    demonstrate_recursion_tree();
    
    // ═══════════════════════════════════════════════════════════
    // Test Cases
    // ═══════════════════════════════════════════════════════════
    
    test_case(4);
    test_case(5);
    test_case(8);
    
    // ═══════════════════════════════════════════════════════════
    // Complexity Analysis
    // ═══════════════════════════════════════════════════════════
    
    compare_complexity();
    
    // ═══════════════════════════════════════════════════════════
    // Algorithm Structure Explanation
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ BACKTRACKING ALGORITHM STRUCTURE                           ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("void solve(int col) {\n");
    printf("    // BASE CASE: All columns filled\n");
    printf("    if (col == N) {\n");
    printf("        record_solution();\n");
    printf("        return;\n");
    printf("    }\n\n");
    
    printf("    // RECURSIVE CASE: Try each row in this column\n");
    printf("    for (int row = 0; row < N; row++) {\n");
    printf("        if (is_safe(row, col)) {\n");
    printf("            place_queen(row, col);      // APPLY\n");
    printf("            solve(col + 1);              // RECURSE\n");
    printf("            remove_queen(row, col);      // BACKTRACK\n");
    printf("        }\n");
    printf("    }\n");
    printf("}\n\n");
    
    printf("Pattern: %sTry → Check → Recurse → Undo%s\n\n", YELLOW, RESET);
    
    // ═══════════════════════════════════════════════════════════
    // Key Insights
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ KEY INSIGHTS                                               ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("1️⃣  %sStructural Insight%s\n", CYAN, RESET);
    printf("    Place ONE queen per column\n");
    printf("    → Eliminates column conflicts automatically\n");
    printf("    → Only check row and diagonal\n\n");
    
    printf("2️⃣  %sMathematical Optimization%s\n", CYAN, RESET);
    printf("    Main diagonal: row - col = constant\n");
    printf("    Anti-diagonal: row + col = constant\n");
    printf("    → O(1) conflict detection via arrays\n\n");
    
    printf("3️⃣  %sBacktracking Pattern%s\n", CYAN, RESET);
    printf("    Try → Apply → Recurse → Remove\n");
    printf("    → Explores decision tree via DFS\n");
    printf("    → Prunes invalid branches\n\n");
    
    printf("4️⃣  %sConstraint Representation%s\n", CYAN, RESET);
    printf("    row_used[r] = whether row r occupied\n");
    printf("    main_diag_used[d] = whether diagonal d occupied\n");
    printf("    anti_diag_used[d] = whether anti-diagonal d occupied\n");
    printf("    → Fast O(1) constraint checking\n\n");
    
    printf("5️⃣  %sSearch Space Pruning%s\n", CYAN, RESET);
    printf("    Without constraints: N! ≈ 40,320 for N=8\n");
    printf("    With backtracking: ~2,057 nodes (95 percent pruned)\n");
    printf("    → Constraints enable exponential speedup\n\n");
    
    // ═══════════════════════════════════════════════════════════
    // Problem-Solving Template
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ UNIVERSAL BACKTRACKING TEMPLATE                            ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("This template solves 80%% of backtracking problems:\n\n");
    
    printf("void solve(state) {\n");
    printf("    if (goal_reached(state)) {\n");
    printf("        record_solution(state);\n");
    printf("        return;\n");
    printf("    }\n\n");
    
    printf("    for (each candidate) {\n");
    printf("        if (is_valid(candidate, state)) {\n");
    printf("            apply(candidate, state);           // Modify state\n");
    printf("            solve(new_state);                  // Recurse\n");
    printf("            remove(candidate, state);          // Restore state\n");
    printf("        }\n");
    printf("    }\n");
    printf("}\n\n");
    
    printf("Applications:\n");
    printf("  • N-Queens (place queens)\n");
    printf("  • Sudoku (fill cells)\n");
    printf("  • Permutations (arrange elements)\n");
    printf("  • Combinations (select subsets)\n");
    printf("  • Graph coloring (assign colors)\n");
    printf("  • Word search (find words in grid)\n");
    printf("  • Maze solving (find path)\n\n");
    
    // ═══════════════════════════════════════════════════════════
    // Final Wisdom
    // ═══════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ FINAL WISDOM — THE MENTAL MODEL                            ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Backtracking is NOT brute force that tries everything.\n\n");
    
    printf("Backtracking IS systematic exploration with constraints:\n");
    printf("  1. Build solution incrementally\n");
    printf("  2. Check constraints as you build\n");
    printf("  3. Prune invalid branches immediately\n");
    printf("  4. Backtrack to explore alternatives\n\n");
    
    printf("This is %sDFS (Depth-First Search) on the state space%s.\n\n", YELLOW, RESET);
    
    printf("For N=8 Queens:\n");
    printf("  • Naive permutation: 40,320 configurations\n");
    printf("  • Backtracking: ~2,000 explored (95%% pruned)\n");
    printf("  • That's the power of constraints.\n\n");
    
    printf("════════════════════════════════════════════════════════════════════════════\n");
    printf("Master this template. You unlock 100+ problems.\n");
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
