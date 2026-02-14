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
 * RAT IN MAZE — PATH FINDING WITH BACKTRACKING
 * 
 * Core Concepts:
 *   • Backtracking explores a decision tree of possible moves
 *   • Mark/Unmark: Critical for enabling path exploration
 *   • Safety check: Validates moves (bounds, walls, visited)
 *   • Early termination: Prune invalid paths immediately
 * 
 * Algorithm:
 *   solve(row, col):
 *       if destination reached:
 *           return TRUE
 *       
 *       if NOT SAFE(row, col):
 *           return FALSE
 *       
 *       mark visited[row][col] = TRUE
 *       
 *       for each direction (right, down, left, up):
 *           if solve(next_row, next_col):
 *               return TRUE
 *       
 *       unmark visited[row][col] = FALSE  // BACKTRACK
 *       return FALSE
 * 
 * Time: O(4^(N²)) worst case, heavily pruned by walls
 * Space: O(N²) for recursion stack and visited matrix
 */

typedef struct {
    int rows;
    int cols;
    int **maze;
} Maze;

// Global state
Maze *current_maze = NULL;
bool visited[MAX_N][MAX_N];
bool solution[MAX_N][MAX_N];

// Statistics
long long nodes_explored = 0;
long long moves_attempted = 0;
long long moves_rejected = 0;

// Direction vectors: Right, Down, Left, Up
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
const char *dir_names[] = {"RIGHT", "DOWN", "LEFT", "UP"};

/**
 * is_safe: Check if a move to (row, col) is valid
 * 
 * Conditions:
 *   1. Inside bounds
 *   2. Not a wall (maze value == 1)
 *   3. Not already visited in this path
 */
bool is_safe(int row, int col) {
    bool in_bounds = (row >= 0 && row < current_maze->rows && 
                      col >= 0 && col < current_maze->cols);
    if (!in_bounds) return false;
    
    bool is_open = (current_maze->maze[row][col] == 1);
    if (!is_open) return false;
    
    bool not_visited = !visited[row][col];
    return not_visited;
}

/**
 * solve: Recursive backtracking solver
 * 
 * Returns TRUE if path found from (row, col) to destination
 */
bool solve(int row, int col) {
    nodes_explored++;
    
    // BASE CASE: Destination reached
    if (row == current_maze->rows - 1 && col == current_maze->cols - 1) {
        solution[row][col] = true;
        return true;
    }
    
    // SAFETY CHECK: Is this cell valid?
    if (!is_safe(row, col)) {
        moves_rejected++;
        return false;
    }
    
    // MARK: Add to current path
    visited[row][col] = true;
    solution[row][col] = true;
    
    // RECURSIVE CASE: Try each direction
    for (int dir = 0; dir < 4; dir++) {
        moves_attempted++;
        
        int next_row = row + dr[dir];
        int next_col = col + dc[dir];
        
        if (solve(next_row, next_col)) {
            return true;  // Path found!
        }
    }
    
    // BACKTRACK: No solution found via this cell
    visited[row][col] = false;      // UNMARK (Critical!)
    solution[row][col] = false;
    return false;
}

/**
 * print_maze: Display the maze grid
 */
void print_maze(void) {
    printf("\nMaze (%d×%d):\n", current_maze->rows, current_maze->cols);
    printf("  ");
    for (int c = 0; c < current_maze->cols; c++) printf("%d ", c);
    printf("\n");
    
    for (int r = 0; r < current_maze->rows; r++) {
        printf("%d ", r);
        for (int c = 0; c < current_maze->cols; c++) {
            if (current_maze->maze[r][c] == 1) {
                printf(". ");
            } else {
                printf("%sX%s ", RED, RESET);  // Wall
            }
        }
        printf("\n");
    }
}

/**
 * print_solution: Display the solution path
 */
void print_solution(void) {
    printf("\nSolution Path:\n");
    printf("  ");
    for (int c = 0; c < current_maze->cols; c++) printf("%d ", c);
    printf("\n");
    
    for (int r = 0; r < current_maze->rows; r++) {
        printf("%d ", r);
        for (int c = 0; c < current_maze->cols; c++) {
            if (solution[r][c]) {
                printf("%sP%s ", GREEN, RESET);  // Path
            } else if (current_maze->maze[r][c] == 1) {
                printf(". ");
            } else {
                printf("%sX%s ", RED, RESET);  // Wall
            }
        }
        printf("\n");
    }
}

/**
 * demonstrate_mark_unmark: Show importance of backtracking
 */
void demonstrate_mark_unmark(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           YELLOW, RESET);
    printf("%s║ MARK/UNMARK IN BACKTRACKING                               ║%s\n",
           YELLOW, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           YELLOW, RESET);
    
    printf("Why Unmarking Is Critical:\n\n");
    
    printf("❌ WITHOUT UNMARKING (Wrong):\n");
    printf("   Path 1: (0,0) → (0,1) → (1,1) [Dead end]\n");
    printf("   visited[1,1] = TRUE (marked forever)\n");
    printf("   Path 2: (0,0) → (1,0) → (1,1) [Could work!]\n");
    printf("   But (1,1) is still marked!\n");
    printf("   Result: Miss valid solutions\n\n");
    
    printf("✅ WITH UNMARKING (Correct):\n");
    printf("   Path 1: (0,0) → (0,1) → (1,1) [Dead end]\n");
    printf("   visited[1,1] = TRUE, then FALSE (unmark)\n");
    printf("   Path 2: (0,0) → (1,0) → (1,1) [Try again]\n");
    printf("   visited[1,1] is now FALSE!\n");
    printf("   Result: Find all valid solutions\n\n");
    
    printf("Algorithm:\n");
    printf("   solve(row, col):\n");
    printf("       visited[row][col] = TRUE    // MARK\n");
    printf("       solution[row][col] = TRUE\n");
    printf("       \n");
    printf("       for each direction:\n");
    printf("           if solve(next):\n");
    printf("               return TRUE\n");
    printf("       \n");
    printf("       visited[row][col] = FALSE   // UNMARK (Critical!)\n");
    printf("       solution[row][col] = FALSE\n");
    printf("       return FALSE\n\n");
}

/**
 * demonstrate_safety_check: Show bounding function
 */
void demonstrate_safety_check(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           CYAN, RESET);
    printf("%s║ SAFETY CHECK (Bounding Function)                          ║%s\n",
           CYAN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           CYAN, RESET);
    
    printf("A move to (row, col) is SAFE if ALL conditions are true:\n\n");
    
    printf("1. IN BOUNDS:\n");
    printf("   row >= 0 AND row < rows\n");
    printf("   col >= 0 AND col < cols\n");
    printf("   Why: Don't go outside the maze grid\n\n");
    
    printf("2. IS OPEN PATH:\n");
    printf("   maze[row][col] == 1\n");
    printf("   Why: Only move through open spaces, not walls (0)\n\n");
    
    printf("3. NOT VISITED:\n");
    printf("   !visited[row][col]\n");
    printf("   Why: Prevent cycles (revisiting same cell in one path)\n\n");
    
    printf("If ANY condition fails:\n");
    printf("   → move is rejected (pruned)\n");
    printf("   → branch not explored\n");
    printf("   → saves exponential time\n\n");
}

/**
 * demonstrate_recursion_tree: Show tree exploration
 */
void demonstrate_recursion_tree(void) {
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ RECURSION TREE STRUCTURE                                  ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("For a 3×3 maze with path (0,0)→(1,0)→(2,0)→(2,1)→(2,2):\n\n");
    
    printf("                    solve(0,0)\n");
    printf("                   [SAFE ✓]\n");
    printf("                   MARK it\n");
    printf("                      |\n");
    printf("         _____________|_____________\n");
    printf("        /             |             \\\n");
    printf("   solve(0,1)     solve(1,0)    solve(-1,0)\n");
    printf("   [WALL X]       [SAFE ✓]      [OUT OF BOUNDS X]\n");
    printf("   REJECT          MARK it        REJECT\n");
    printf("                      |\n");
    printf("         _____________|_____________\n");
    printf("        /             |             \\\n");
    printf("   solve(1,1)     solve(2,0)    solve(0,0)\n");
    printf("   [WALL X]       [SAFE ✓]      [VISITED X]\n");
    printf("   REJECT          MARK it        REJECT\n");
    printf("                      |\n");
    printf("         _____________|_____________\n");
    printf("        /             |             \\\n");
    printf("   solve(2,1)     solve(3,0)    solve(1,0)\n");
    printf("   [SAFE ✓]       [OUT OF BOUNDS X] [VISITED X]\n");
    printf("   MARK it         REJECT           REJECT\n");
    printf("       |\n");
    printf("     (continue exploring...)\n");
    printf("       |\n");
    printf("   solve(2,2)\n");
    printf("   [DESTINATION! ✓]\n");
    printf("   RETURN TRUE\n\n");
    
    printf("Key observations:\n");
    printf("  ✓ Many branches pruned immediately (walls, bounds)\n");
    printf("  ✓ Only safe cells explored\n");
    printf("  ✓ Visited cells prevent cycles\n");
    printf("  ✓ Destination causes immediate success\n\n");
}

/**
 * test_maze: Test the solver on a specific maze
 */
void test_maze(int n, int **maze) {
    // Allocate current maze
    current_maze = malloc(sizeof(Maze));
    current_maze->rows = n;
    current_maze->cols = n;
    current_maze->maze = maze;
    
    // Reset statistics
    nodes_explored = 0;
    moves_attempted = 0;
    moves_rejected = 0;
    memset(visited, false, sizeof(visited));
    memset(solution, false, sizeof(solution));
    
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ RAT IN MAZE TEST: %d×%d%s║%s\n",
           BLUE, n, n, n < 10 ? "  " : " ", RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Print maze
    print_maze();
    
    printf("\nSolving...\n");
    printf("  Starting position: (0, 0)\n");
    printf("  Destination: (%d, %d)\n", n-1, n-1);
    
    // Solve
    bool found = solve(0, 0);
    
    printf("\n%sResults:%s\n", YELLOW, RESET);
    if (found) {
        printf("  Status: %sSolution FOUND ✓%s\n", GREEN, RESET);
        print_solution();
    } else {
        printf("  Status: %sNo solution exists ✗%s\n", RED, RESET);
    }
    
    printf("\nAlgorithm Statistics:\n");
    printf("  Nodes explored:    %lld\n", nodes_explored);
    printf("  Moves attempted:   %lld\n", moves_attempted);
    printf("  Moves rejected:    %lld\n", moves_rejected);
    
    if (moves_attempted > 0) {
        double rejection_rate = 100.0 * moves_rejected / moves_attempted;
        printf("  Rejection rate:    %.1f%% (efficiency)\n", rejection_rate);
    }
    
    printf("\n");
    
    free(current_maze);
}

/**
 * create_maze: Allocate maze matrix
 */
int **create_maze(int n) {
    int **maze = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        maze[i] = malloc(n * sizeof(int));
    }
    return maze;
}

/**
 * free_maze: Deallocate maze matrix
 */
void free_maze(int **maze, int n) {
    for (int i = 0; i < n; i++) {
        free(maze[i]);
    }
    free(maze);
}

/**
 * main: Run comprehensive demonstrations and tests
 */
int main() {
    printf("\n%s╔════════════════════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║              RAT IN MAZE — PATH FINDING WITH BACKTRACKING                   ║%s\n",
           BLUE, RESET);
    printf("%s║   Teaching: Try → Check → Go Forward → If Stuck → Undo → Try Another Way   ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    // Demonstrations
    demonstrate_mark_unmark();
    demonstrate_safety_check();
    demonstrate_recursion_tree();
    
    // Test Case 1: 3×3 Maze (Simple)
    int **maze1 = create_maze(3);
    maze1[0][0] = 1; maze1[0][1] = 1; maze1[0][2] = 0;
    maze1[1][0] = 1; maze1[1][1] = 0; maze1[1][2] = 1;
    maze1[2][0] = 1; maze1[2][1] = 1; maze1[2][2] = 1;
    test_maze(3, maze1);
    free_maze(maze1, 3);
    
    // Test Case 2: 4×4 Maze (Medium)
    int **maze2 = create_maze(4);
    maze2[0][0] = 1; maze2[0][1] = 1; maze2[0][2] = 0; maze2[0][3] = 0;
    maze2[1][0] = 1; maze2[1][1] = 0; maze2[1][2] = 1; maze2[1][3] = 1;
    maze2[2][0] = 0; maze2[2][1] = 1; maze2[2][2] = 0; maze2[2][3] = 0;
    maze2[3][0] = 0; maze2[3][1] = 1; maze2[3][2] = 1; maze2[3][3] = 1;
    test_maze(4, maze2);
    free_maze(maze2, 4);
    
    // Test Case 3: 4×4 Maze (No Solution)
    int **maze3 = create_maze(4);
    maze3[0][0] = 1; maze3[0][1] = 0; maze3[0][2] = 0; maze3[0][3] = 0;
    maze3[1][0] = 1; maze3[1][1] = 0; maze3[1][2] = 0; maze3[1][3] = 0;
    maze3[2][0] = 0; maze3[2][1] = 0; maze3[2][2] = 0; maze3[2][3] = 0;
    maze3[3][0] = 0; maze3[3][1] = 0; maze3[3][2] = 0; maze3[3][3] = 1;
    test_maze(4, maze3);
    free_maze(maze3, 4);
    
    // Key Insights
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           GREEN, RESET);
    printf("%s║ KEY INSIGHTS                                               ║%s\n",
           GREEN, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           GREEN, RESET);
    
    printf("1️⃣  %sMark/Unmark is Critical%s\n", CYAN, RESET);
    printf("    When backtracking, must UNMARK cells\n");
    printf("    Allows different paths to use same cell\n\n");
    
    printf("2️⃣  %sSafety Check Prevents Invalid Moves%s\n", CYAN, RESET);
    printf("    Check bounds, walls, and visited status\n");
    printf("    Early rejection prunes entire branches\n\n");
    
    printf("3️⃣  %sBacktracking ≠ Brute Force%s\n", CYAN, RESET);
    printf("    Brute force: Generate all paths, check\n");
    printf("    Backtracking: Build incrementally, check early\n\n");
    
    printf("4️⃣  %sRecursion Tree Shows Decision Space%s\n", CYAN, RESET);
    printf("    Many branches pruned by safety check\n");
    printf("    Only promising cells explored\n\n");
    
    printf("5️⃣  %sTemplate Applies to Many Problems%s\n", CYAN, RESET);
    printf("    N-Queens: Place pieces\n");
    printf("    Rat in Maze: Move pieces\n");
    printf("    Sudoku: Fill cells\n");
    printf("    Knight's Tour: Move knight\n");
    printf("    Same core algorithm, different constraints\n\n");
    
    // Algorithm Structure
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ BACKTRACKING ALGORITHM STRUCTURE                           ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("bool solve(int row, int col) {\n");
    printf("    // BASE CASE\n");
    printf("    if (row == n-1 && col == n-1) {\n");
    printf("        return TRUE;  // Destination reached\n");
    printf("    }\n\n");
    
    printf("    // SAFETY CHECK (Bounding function)\n");
    printf("    if (!is_safe(row, col)) {\n");
    printf("        return FALSE;  // Invalid move\n");
    printf("    }\n\n");
    
    printf("    // MARK\n");
    printf("    visited[row][col] = TRUE;\n\n");
    
    printf("    // TRY ALL DIRECTIONS\n");
    printf("    if (solve(row, col+1)) return TRUE;  // Right\n");
    printf("    if (solve(row+1, col)) return TRUE;  // Down\n");
    printf("    if (solve(row, col-1)) return TRUE;  // Left\n");
    printf("    if (solve(row-1, col)) return TRUE;  // Up\n\n");
    
    printf("    // BACKTRACK: Unmark (Critical!)\n");
    printf("    visited[row][col] = FALSE;\n");
    printf("    return FALSE;\n");
    printf("}\n\n");
    
    // Final wisdom
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           BLUE, RESET);
    printf("%s║ FINAL WISDOM                                               ║%s\n",
           BLUE, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n\n",
           BLUE, RESET);
    
    printf("What Abdul Bari Really Wants You to Understand:\n\n");
    printf("\"Try → Check → Go Forward → If Stuck → Undo → Try Another Way\"\n\n");
    printf("This pattern solves:\n");
    printf("  • Path finding (Rat in Maze, Knight's Tour)\n");
    printf("  • Constraint satisfaction (N-Queens, Sudoku)\n");
    printf("  • Combinatorial search (Permutations, Combinations)\n");
    printf("  • Graph problems (Coloring, Cliques)\n");
    printf("  • Game AI (Game tree search, Minimax)\n\n");
    
    printf("Master this pattern.\n");
    printf("You unlock 100+ algorithmic problems.\n");
    printf("You understand how to think recursively and systematically.\n\n");
    
    printf("════════════════════════════════════════════════════════════════════════════\n\n");
    
    return 0;
}
