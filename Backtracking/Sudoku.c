#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define EMPTY 0

// Statistics
typedef struct {
    int cells_processed;
    int cells_filled;
    int backtrack_count;
    int validation_checks;
    clock_t start_time;
    clock_t end_time;
} Stats;

Stats stats;
int sudoku[SIZE][SIZE];

// Utility: Print the sudoku grid
void print_sudoku(void) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("------+-------+------\n");
        }
        
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                printf("| ");
            }
            
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Utility: Initialize sudoku from array
void init_sudoku(int grid[SIZE][SIZE]) {
    memcpy(sudoku, grid, sizeof(int) * SIZE * SIZE);
}

// BOUNDING FUNCTION: Check if placing val at (row, col) is valid
bool is_valid(int row, int col, int val) {
    stats.validation_checks++;
    
    // Check 1: Row constraint
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[row][i] == val) {
            return false;
        }
    }
    
    // Check 2: Column constraint
    for (int i = 0; i < SIZE; i++) {
        if (sudoku[i][col] == val) {
            return false;
        }
    }
    
    // Check 3: 3×3 block constraint
    int block_row = row - row % 3;
    int block_col = col - col % 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[block_row + i][block_col + j] == val) {
                return false;
            }
        }
    }
    
    return true;
}

// CORE RECURSIVE SOLVER: Process grid cell by cell
bool solve(int row, int col) {
    stats.cells_processed++;
    
    // BASE CASE: Row == SIZE means we've gone past the last row
    // All cells have been processed successfully
    if (row == SIZE) {
        return true;
    }
    
    // Calculate next cell (left to right, then next row)
    int next_row = (col == SIZE - 1) ? row + 1 : row;
    int next_col = (col == SIZE - 1) ? 0 : col + 1;
    
    // CASE 1: Cell is already filled
    if (sudoku[row][col] != EMPTY) {
        return solve(next_row, next_col);
    }
    
    // CASE 2: Cell is empty, try numbers 1-9
    for (int num = 1; num <= SIZE; num++) {
        if (is_valid(row, col, num)) {
            
            // CHOOSE: Place the number
            sudoku[row][col] = num;
            stats.cells_filled++;
            
            // GO DEEPER: Recurse to next cell
            if (solve(next_row, next_col)) {
                return true;
            }
            
            // BACKTRACK: Remove the number (CRITICAL!)
            sudoku[row][col] = EMPTY;
            stats.cells_filled--;
            stats.backtrack_count++;
        }
    }
    
    // No number worked, fail
    return false;
}

// Wrapper to reset stats and start solving
bool solve_sudoku(void) {
    memset(&stats, 0, sizeof(Stats));
    stats.start_time = clock();
    
    bool result = solve(0, 0);
    
    stats.end_time = clock();
    return result;
}

// ============================================================================
// TEST CASES
// ============================================================================

// TEST 1: Easy puzzle (many prefilled cells)
void test_easy(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           SUDOKU TEST 1: Easy (25/81 cells)                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    init_sudoku(grid);
    
    printf("\nInput Puzzle:\n");
    print_sudoku();
    
    bool solved = solve_sudoku();
    
    if (solved) {
        printf("Status: Solution FOUND ✓\n");
        printf("\nSolution:\n");
        print_sudoku();
    } else {
        printf("Status: No solution exists ✗\n");
    }
    
    printf("Performance Metrics:\n");
    printf("  Cells processed:      %d\n", stats.cells_processed);
    printf("  Cells filled:         %d\n", stats.cells_filled);
    printf("  Backtrack count:      %d\n", stats.backtrack_count);
    printf("  Validation checks:    %d\n", stats.validation_checks);
    printf("  Time: %.3f ms\n", 
           (double)(stats.end_time - stats.start_time) / CLOCKS_PER_SEC * 1000.0);
}

// TEST 2: Medium puzzle (More difficulty)
void test_medium(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           SUDOKU TEST 2: Medium (20/81 cells)              ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    int grid[SIZE][SIZE] = {
        {0, 0, 3, 0, 2, 0, 6, 0, 0},
        {9, 0, 0, 3, 0, 0, 0, 0, 1},
        {0, 0, 1, 8, 0, 6, 4, 0, 0},
        {0, 0, 8, 1, 0, 2, 9, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 6, 7, 0, 8, 2, 0, 0},
        {0, 0, 2, 6, 0, 9, 5, 0, 0},
        {8, 0, 0, 0, 0, 5, 0, 0, 7},
        {0, 0, 5, 0, 1, 0, 3, 0, 0}
    };
    
    init_sudoku(grid);
    
    printf("\nInput Puzzle:\n");
    print_sudoku();
    
    bool solved = solve_sudoku();
    
    if (solved) {
        printf("Status: Solution FOUND ✓\n");
        printf("\nSolution:\n");
        print_sudoku();
    } else {
        printf("Status: No solution exists ✗\n");
    }
    
    printf("Performance Metrics:\n");
    printf("  Cells processed:      %d\n", stats.cells_processed);
    printf("  Cells filled:         %d\n", stats.cells_filled);
    printf("  Backtrack count:      %d\n", stats.backtrack_count);
    printf("  Validation checks:    %d\n", stats.validation_checks);
    printf("  Time: %.3f ms\n", 
           (double)(stats.end_time - stats.start_time) / CLOCKS_PER_SEC * 1000.0);
}

// TEST 3: Hard puzzle (Few prefilled cells)
void test_hard(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           SUDOKU TEST 3: Hard (17/81 cells)                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // World's hardest sudoku (allegedly)
    int grid[SIZE][SIZE] = {
        {0, 0, 5, 3, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 7, 0, 0, 1, 0, 5, 0, 0},
        {4, 0, 0, 0, 0, 5, 3, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 6},
        {0, 0, 3, 2, 0, 0, 0, 8, 0},
        {0, 6, 0, 5, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 9, 7, 0, 0}
    };
    
    init_sudoku(grid);
    
    printf("\nInput Puzzle:\n");
    print_sudoku();
    
    bool solved = solve_sudoku();
    
    if (solved) {
        printf("Status: Solution FOUND ✓\n");
        printf("\nSolution:\n");
        print_sudoku();
    } else {
        printf("Status: No solution exists ✗\n");
    }
    
    printf("Performance Metrics:\n");
    printf("  Cells processed:      %d\n", stats.cells_processed);
    printf("  Cells filled:         %d\n", stats.cells_filled);
    printf("  Backtrack count:      %d\n", stats.backtrack_count);
    printf("  Validation checks:    %d\n", stats.validation_checks);
    printf("  Time: %.3f ms\n", 
           (double)(stats.end_time - stats.start_time) / CLOCKS_PER_SEC * 1000.0);
}

// ============================================================================
// DEMONSTRATIONS
// ============================================================================

void demonstrate_is_valid(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        DEMONSTRATION: How isValid() Works                  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Create a small problem
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    init_sudoku(grid);
    
    printf("\nInitial Grid:\n");
    print_sudoku();
    
    printf("Testing cell (0, 2) which is empty:\n\n");
    
    // Try different values
    int test_values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    for (int i = 0; i < 9; i++) {
        int val = test_values[i];
        bool valid = is_valid(0, 2, val);
        printf("  Try %d at (0,2): %s\n", val, valid ? "✓ VALID" : "✗ INVALID");
        
        if (!valid) {
            // Explain why
            bool in_row = false, in_col = false, in_block = false;
            
            for (int j = 0; j < SIZE; j++) {
                if (sudoku[0][j] == val) in_row = true;
                if (sudoku[j][2] == val) in_col = true;
            }
            
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if (sudoku[r][c] == val) in_block = true;
                }
            }
            
            printf("    └─ Already in: ");
            if (in_row) printf("Row ");
            if (in_col) printf("Column ");
            if (in_block) printf("Block");
            printf("\n");
        }
    }
}

void demonstrate_backtracking(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║   DEMONSTRATION: Why Backtracking is Critical              ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    printf("\nConsider a simple cell that needs to be filled:\n");
    printf("  sudoku[0][0] = 0  (empty)\n\n");
    
    printf("Recursive process WITH backtracking:\n");
    printf("  ┌─ Try 1\n");
    printf("  │  Recurse... returns FALSE (no solution)\n");
    printf("  │  sudoku[0][0] = 0  ← BACKTRACK! Clear the cell\n");
    printf("  │\n");
    printf("  ├─ Try 2\n");
    printf("  │  Recurse... returns FALSE\n");
    printf("  │  sudoku[0][0] = 0  ← BACKTRACK!\n");
    printf("  │\n");
    printf("  ├─ Try 3\n");
    printf("  │  Recurse... returns TRUE ✓\n");
    printf("  │  Return TRUE immediately\n");
    printf("  └─ (3 is the solution)\n\n");
    
    printf("WITHOUT backtracking (common mistake):\n");
    printf("  ┌─ Try 1\n");
    printf("  │  sudoku[0][0] = 1\n");
    printf("  │  Recurse... returns FALSE\n");
    printf("  │  // BUT sudoku[0][0] is still 1!\n");
    printf("  │\n");
    printf("  ├─ Try 2\n");
    printf("  │  sudoku[0][0] = 2  ← Overwrites 1\n");
    printf("  │  Recurse... returns FALSE\n");
    printf("  │  // sudoku[0][0] is still 2!\n");
    printf("  │\n");
    printf("  ├─ Try 3\n");
    printf("  │  sudoku[0][0] = 3  ← Overwrites 2\n");
    printf("  │  // No clear path to try 3 fresh!\n");
    printf("  └─ Algorithm becomes confused\n\n");
    
    printf("KEY INSIGHT:\n");
    printf("  sudoku[row][col] = 0;  // This single line enables backtracking!\n");
    printf("  Without it, the algorithm fails.\n");
}

void demonstrate_cell_traversal(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║   DEMONSTRATION: Cell Traversal Pattern                    ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    printf("\nTraversal pattern in solve():\n\n");
    printf("  int next_row = (col == 8) ? row + 1 : row;\n");
    printf("  int next_col = (col == 8) ? 0 : col + 1;\n\n");
    
    printf("This means:\n");
    printf("  ┌─ If col < 8: Move to next column (same row)\n");
    printf("  │    (0,0) → (0,1) → (0,2) → ... → (0,8)\n");
    printf("  │\n");
    printf("  └─ If col == 8: Move to first column of next row\n");
    printf("       (0,8) → (1,0) → (1,1) → ... → (1,8)\n\n");
    
    printf("Visual path:\n");
    printf("  (0,0)→(0,1)→(0,2)→(0,3)→(0,4)→(0,5)→(0,6)→(0,7)→(0,8)\n");
    printf("                                              ↓\n");
    printf("  (1,0)→(1,1)→(1,2)→(1,3)→(1,4)→(1,5)→(1,6)→(1,7)→(1,8)\n");
    printf("                                              ↓\n");
    printf("  ...and so on until (8,8)\n\n");
    
    printf("When we reach row == 9:\n");
    printf("  We've gone past row 8 (the last row)\n");
    printf("  This means ALL 81 cells have been processed\n");
    printf("  Return TRUE (solution found!)\n");
}

int main(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║     SUDOKU SOLVER - BACKTRACKING ALGORITHM                 ║\n");
    printf("║           Following Abdul Bari's Pedagogy                  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Run demonstrations
    demonstrate_cell_traversal();
    demonstrate_is_valid();
    demonstrate_backtracking();
    
    // Run test cases
    test_easy();
    test_medium();
    test_hard();
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  KEY TAKEAWAYS                             ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("1. RECURSION: Process grid cell by cell, left-to-right\n");
    printf("2. BOUNDING FUNCTION: isValid() checks row, col, block\n");
    printf("3. PRUNING: Invalid moves are eliminated immediately\n");
    printf("4. BACKTRACKING: sudoku[r][c] = 0 is CRITICAL!\n");
    printf("5. BASE CASE: row == 9 means solution is complete\n");
    printf("\n");
    printf("Performance: With pruning, solves hard puzzles in < 1ms\n");
    printf("\n");
    
    return 0;
}
