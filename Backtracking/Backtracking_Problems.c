#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

/**
 * ════════════════════════════════════════════════════════════════════════════
 * BACKTRACKING: Universal Problem-Solving Technique
 * 
 * Three Different Problems, Same Core Pattern:
 * 1. Sudoku Solver      — Constraint Satisfaction
 * 2. Permutations       — Combinatorics
 * 3. Rat in Maze        — Path Finding
 * 
 * Master Template:
 *   void backtrack(state, choices):
 *       if complete:
 *           return
 *       for each choice:
 *           if valid(choice):
 *               apply(choice)
 *               backtrack(new_state)
 *               undo(choice)  ← BACKTRACK STEP
 * ════════════════════════════════════════════════════════════════════════════
 */

// ════════════════════════════════════════════════════════════════════════════
// PROBLEM 1: SUDOKU SOLVER — Constraint Satisfaction
// ════════════════════════════════════════════════════════════════════════════

#define SUDOKU_SIZE 9
#define SUBGRID_SIZE 3
#define EMPTY 0

typedef struct {
    int board[SUDOKU_SIZE][SUDOKU_SIZE];
    int calls;
} SudokuState;

bool is_safe_sudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE], int row, int col, int num) {
    // Check row
    for(int c = 0; c < SUDOKU_SIZE; c++) {
        if(board[row][c] == num) return false;
    }
    
    // Check column
    for(int r = 0; r < SUDOKU_SIZE; r++) {
        if(board[r][col] == num) return false;
    }
    
    // Check 3x3 box
    int box_row = (row / SUBGRID_SIZE) * SUBGRID_SIZE;
    int box_col = (col / SUBGRID_SIZE) * SUBGRID_SIZE;
    for(int r = box_row; r < box_row + SUBGRID_SIZE; r++) {
        for(int c = box_col; c < box_col + SUBGRID_SIZE; c++) {
            if(board[r][c] == num) return false;
        }
    }
    
    return true;
}

bool solve_sudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE], SudokuState *state) {
    state->calls++;
    
    // BASE CASE: Find next empty cell
    for(int row = 0; row < SUDOKU_SIZE; row++) {
        for(int col = 0; col < SUDOKU_SIZE; col++) {
            if(board[row][col] == EMPTY) {
                // RECURSIVE CASE: Try numbers 1-9
                for(int num = 1; num <= 9; num++) {
                    // CONSTRAINT: Check if number is valid
                    if(is_safe_sudoku(board, row, col, num)) {
                        // APPLY: Place number
                        board[row][col] = num;
                        
                        // EXPLORE: Recursively solve
                        if(solve_sudoku(board, state)) {
                            return true;
                        }
                        
                        // BACKTRACK: Remove number
                        board[row][col] = EMPTY;
                    }
                }
                return false;  // No valid number found
            }
        }
    }
    
    return true;  // All cells filled (solution found)
}

void print_sudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE]) {
    for(int row = 0; row < SUDOKU_SIZE; row++) {
        if(row % 3 == 0 && row != 0) printf("------+-------+------\n");
        for(int col = 0; col < SUDOKU_SIZE; col++) {
            if(col % 3 == 0 && col != 0) printf("| ");
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }
}

// ════════════════════════════════════════════════════════════════════════════
// PROBLEM 2: PERMUTATIONS — Combinatorics
// ════════════════════════════════════════════════════════════════════════════

typedef struct {
    int *arr;
    int length;
    int perm_count;
} PermutationState;

void print_permutation(int arr[], int n) {
    printf("[");
    for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n - 1) printf(", ");
    }
    printf("] ");
}

void generate_permutations(int arr[], int start, int n, PermutationState *state) {
    // BASE CASE: Reached end of array
    if(start == n - 1) {
        state->perm_count++;
        print_permutation(arr, n);
        if(state->perm_count % 6 == 0) printf("\n");
        return;
    }
    
    // RECURSIVE CASE: Try swapping each element with current position
    for(int i = start; i < n; i++) {
        // APPLY: Swap
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        
        // EXPLORE: Recursively permute rest
        generate_permutations(arr, start + 1, n, state);
        
        // BACKTRACK: Swap back
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
    }
}

// ════════════════════════════════════════════════════════════════════════════
// PROBLEM 3: RAT IN MAZE — Path Finding
// ════════════════════════════════════════════════════════════════════════════

#define MAZE_SIZE 5
#define FREE 0
#define BLOCKED 1

typedef struct {
    int grid[MAZE_SIZE][MAZE_SIZE];
    int visited[MAZE_SIZE][MAZE_SIZE];
    int final_path[MAZE_SIZE * MAZE_SIZE][2];
    int final_path_length;
    int solutions_found;
} MazeState;

bool is_safe_maze(int grid[MAZE_SIZE][MAZE_SIZE], 
                  int visited[MAZE_SIZE][MAZE_SIZE], 
                  int row, int col) {
    return (row >= 0 && row < MAZE_SIZE &&
            col >= 0 && col < MAZE_SIZE &&
            grid[row][col] == FREE &&
            visited[row][col] == 0);
}

bool solve_maze(int grid[MAZE_SIZE][MAZE_SIZE],
                int visited[MAZE_SIZE][MAZE_SIZE],
                int row, int col,
                int path[MAZE_SIZE * MAZE_SIZE][2],
                int *path_length,
                MazeState *state) {
    
    // BASE CASE: Reached destination
    if(row == MAZE_SIZE - 1 && col == MAZE_SIZE - 1) {
        path[*path_length][0] = row;
        path[*path_length][1] = col;
        (*path_length)++;
        
        // Save the successful path
        memcpy(state->final_path, path, (*path_length) * sizeof(path[0]));
        state->final_path_length = *path_length;
        state->solutions_found++;
        
        (*path_length)--;  // Backtrack before returning
        return true;
    }
    
    // BOUNDARY & VALIDITY CHECK
    if(!is_safe_maze(grid, visited, row, col)) {
        return false;
    }
    
    // APPLY: Mark as visited and add to path
    visited[row][col] = 1;
    path[*path_length][0] = row;
    path[*path_length][1] = col;
    (*path_length)++;
    
    // EXPLORE: Try all 4 directions (Down, Right, Up, Left)
    bool found = false;
    
    // DOWN
    if(solve_maze(grid, visited, row + 1, col, path, path_length, state)) {
        found = true;
    }
    
    // RIGHT
    if(!found && solve_maze(grid, visited, row, col + 1, path, path_length, state)) {
        found = true;
    }
    
    // UP
    if(!found && solve_maze(grid, visited, row - 1, col, path, path_length, state)) {
        found = true;
    }
    
    // LEFT
    if(!found && solve_maze(grid, visited, row, col - 1, path, path_length, state)) {
        found = true;
    }
    
    // BACKTRACK: Unmark visited and remove from path
    (*path_length)--;
    visited[row][col] = 0;
    
    return found;
}

void print_maze(int grid[MAZE_SIZE][MAZE_SIZE]) {
    for(int row = 0; row < MAZE_SIZE; row++) {
        for(int col = 0; col < MAZE_SIZE; col++) {
            if(row == 0 && col == 0) printf("S ");  // Start
            else if(row == MAZE_SIZE - 1 && col == MAZE_SIZE - 1) printf("E ");  // End
            else printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

void print_maze_path(int path[MAZE_SIZE * MAZE_SIZE][2], int path_length) {
    printf("Path: ");
    for(int i = 0; i < path_length; i++) {
        printf("(%d,%d)", path[i][0], path[i][1]);
        if(i < path_length - 1) printf(" → ");
    }
    printf("\n");
}

// ════════════════════════════════════════════════════════════════════════════
// MAIN: Demonstrate all three backtracking problems
// ════════════════════════════════════════════════════════════════════════════

int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║        BACKTRACKING: Universal Problem-Solving Technique                   ║%s\n",
           BLUE, RESET);
    printf("%s║  Same Pattern → Different Problems → Same Core Logic                       ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // ════════════════════════════════════════════════════════════════════════════
    // DEMO 1: SUDOKU SOLVER
    // ════════════════════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ PROBLEM 1: SUDOKU SOLVER (Constraint Satisfaction)             ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Easy Sudoku puzzle (some cells given)
    int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {
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
    
    printf("Initial Sudoku:\n");
    print_sudoku(sudoku);
    
    SudokuState sudoku_state = {0};
    memcpy(sudoku_state.board, sudoku, sizeof(sudoku));
    sudoku_state.calls = 0;
    
    printf("\n%sSolving...%s\n\n", YELLOW, RESET);
    if(solve_sudoku(sudoku_state.board, &sudoku_state)) {
        printf("%sSolved Sudoku:%s\n", GREEN, RESET);
        print_sudoku(sudoku_state.board);
        printf("\n%sStats: %d recursive calls%s\n\n", YELLOW, sudoku_state.calls, RESET);
    } else {
        printf("%sNo solution found%s\n\n", RED, RESET);
    }
    
    // ════════════════════════════════════════════════════════════════════════════
    // DEMO 2: PERMUTATIONS
    // ════════════════════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ PROBLEM 2: PERMUTATIONS (Combinatorics)                        ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    int arr[] = {1, 2, 3};
    int n = 3;
    
    printf("Generating all permutations of [1, 2, 3]:\n\n");
    
    PermutationState perm_state = {arr, n, 0};
    generate_permutations(arr, 0, n, &perm_state);
    
    printf("\n\n%sTotal permutations: %d (expected n! = 3! = 6)%s\n\n",
           YELLOW, perm_state.perm_count, RESET);
    
    // ════════════════════════════════════════════════════════════════════════════
    // DEMO 3: RAT IN MAZE
    // ════════════════════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ PROBLEM 3: RAT IN MAZE (Path Finding)                          ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Clearer maze with guaranteed simple path
    int maze[MAZE_SIZE][MAZE_SIZE] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    printf("Maze (0=free, 1=blocked, S=start, E=end):\n");
    printf("S ");
    for(int c = 1; c < MAZE_SIZE; c++) printf("%d ", maze[0][c]);
    printf("\n");
    for(int r = 1; r < MAZE_SIZE; r++) {
        for(int c = 0; c < MAZE_SIZE; c++) {
            if(r == MAZE_SIZE - 1 && c == MAZE_SIZE - 1) printf("E ");
            else printf("%d ", maze[r][c]);
        }
        printf("\n");
    }
    
    printf("\n%sFinding path from (0,0) to (4,4)...%s\n\n", YELLOW, RESET);
    
    int visited[MAZE_SIZE][MAZE_SIZE] = {0};
    int path[MAZE_SIZE * MAZE_SIZE][2];
    int path_length = 0;
    
    MazeState maze_state = {0};
    memcpy(maze_state.grid, maze, sizeof(maze));
    maze_state.solutions_found = 0;
    
    if(solve_maze(maze, visited, 0, 0, path, &path_length, &maze_state)) {
        printf("%sPath found!%s\n", GREEN, RESET);
        print_maze_path(maze_state.final_path, maze_state.final_path_length);
        printf("\nPath length: %d steps\n\n", maze_state.final_path_length);
    } else {
        printf("%sNo path found%s\n\n", RED, RESET);
    }
    
    // ════════════════════════════════════════════════════════════════════════════
    // COMPARISON: Show the universal pattern
    // ════════════════════════════════════════════════════════════════════════════
    
    printf("%s╔════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ THE UNIVERSAL BACKTRACKING PATTERN                             ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("Regardless of problem domain:\n\n");
    printf("void backtrack(state, choices):\n");
    printf("    // BASE CASE\n");
    printf("    if state is complete:\n");
    printf("        process solution\n");
    printf("        return\n");
    printf("    \n");
    printf("    // RECURSIVE CASE\n");
    printf("    for each candidate in choices:\n");
    printf("        // CONSTRAINT CHECK\n");
    printf("        if is_valid(candidate):\n");
    printf("            // APPLY\n");
    printf("            apply(candidate)\n");
    printf("            \n");
    printf("            // EXPLORE\n");
    printf("            backtrack(new_state, remaining)\n");
    printf("            \n");
    printf("            // BACKTRACK (THE KEY!)\n");
    printf("            undo(candidate)\n");
    printf("\n");
    
    printf("%sComparison Table:%s\n\n", YELLOW, RESET);
    printf("| Aspect   | Sudoku           | Permutation      | Maze            |\n");
    printf("|----------|------------------|------------------|------------------|\n");
    printf("| Goal     | Fill all cells   | All arrangements | Reach end        |\n");
    printf("| Try      | Numbers 1-9      | Unused elements  | 4 directions     |\n");
    printf("| Check    | Row/Col/Box      | Not used yet     | In bounds+free   |\n");
    printf("| Undo     | Remove number    | Remove from perm | Unmark visited   |\n");
    printf("| Depth    | ~40 (cells)      | n (elements)     | ~n² (path)       |\n");
    printf("| Result   | O(n!) solvable   | All n! found     | Paths found      |\n");
    printf("\n");
    
    printf("%s════════════════════════════════════════════════════════════════════════════%s\n",
           GREEN, RESET);
    printf("KEY INSIGHT: The skeleton is IDENTICAL.\n");
    printf("Only the details (what to try, what to check, what to undo) differ.\n");
    printf("Master the pattern → Solve ANY backtracking problem.\n");
    printf("%s════════════════════════════════════════════════════════════════════════════%s\n\n",
           GREEN, RESET);
    
    return 0;
}
