#include <stdio.h>
#include <stdlib.h>
// #include "Queue.h"

// ==================== QUEUE IMPLEMENTATION ====================
#define MAX 100

typedef struct Queue
{
    int data[MAX];
    int front;
    int rear;
} Queue;

Queue q;

void initQueue()
{
    q.front = -1;
    q.rear = -1;
}

int isEmpty()
{
    return q.front == -1 || q.front > q.rear;
}

void enqueue(int x)
{
    if (q.front == -1)
    {
        q.front = 0;
    }
    q.rear++;
    q.data[q.rear] = x;
    printf("      [Queue: enqueue %d]\n", x);
}

int dequeue()
{
    int x = q.data[q.front];
    q.front++;
    printf("      [Queue: dequeue %d]\n", x);
    return x;
}

// ==================== BFS (Breadth-First Search) ====================
void BFS(int G[][7], int start, int n)
{
    int i = start, j;
    int visited[7] = {0};

    printf("\n=== BFS Starting from vertex %d ===\n", start);
    printf("Using Queue (FIFO - First In First Out)\n\n");

    initQueue();

    // Step 1: Visit starting vertex
    printf("Step 1: Visit starting vertex %d\n", i);
    printf("  Output: %d\n", i);
    visited[i] = 1;
    enqueue(i);

    int step = 2;

    // Step 2+: Explore level by level
    while (!isEmpty())
    {
        i = dequeue();
        printf("\nStep %d: Exploring neighbors of vertex %d\n", step++, i);

        for (j = 1; j < n; j++)
        {
            if (G[i][j] == 1 && visited[j] == 0)
            {
                printf("  Found unvisited neighbor: %d\n", j);
                printf("  Output: %d\n", j);
                visited[j] = 1;
                enqueue(j);
            }
        }
    }
    printf("\nBFS Complete!\n");
}

// ==================== DFS (Depth-First Search) ====================
static int dfs_step = 1;
static int dfs_visited[7] = {0};

void resetDFS()
{
    for (int i = 0; i < 7; i++)
    {
        dfs_visited[i] = 0;
    }
    dfs_step = 1;
}

void DFS(int G[][7], int start, int n)
{
    int j;

    if (dfs_visited[start] == 0)
    {
        printf("Step %d: Visit vertex %d\n", dfs_step++, start);
        printf("  Output: %d\n", start);
        dfs_visited[start] = 1;

        for (j = 1; j < n; j++)
        {
            if (G[start][j] == 1 && dfs_visited[j] == 0)
            {
                printf("  → Going DEEP to neighbor %d\n", j);
                DFS(G, j, n);
                printf("  ← Backtracking from %d to %d\n", j, start);
            }
        }
    }
}

int main()
{
    int G[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 1, 1, 0, 0, 0},  // Vertex 1 connects to: 2, 3
                   {0, 1, 0, 0, 1, 0, 0},  // Vertex 2 connects to: 1, 4
                   {0, 1, 0, 0, 1, 0, 0},  // Vertex 3 connects to: 1, 4
                   {0, 0, 1, 1, 0, 1, 1},  // Vertex 4 connects to: 2, 3, 5, 6
                   {0, 0, 0, 0, 1, 0, 0},  // Vertex 5 connects to: 4
                   {0, 0, 0, 0, 1, 0, 0}}; // Vertex 6 connects to: 4

    printf("=====================================================\n");
    printf("           GRAPH VISUALIZATION\n");
    printf("=====================================================\n");
    printf("        1\n");
    printf("       /  \\\n");
    printf("      2    3\n");
    printf("       \\  /\n");
    printf("        4\n");
    printf("       / \\\n");
    printf("      5   6\n");
    printf("=====================================================\n");

    // Run BFS
    BFS(G, 4, 7);

    printf("\n\n=====================================================\n");

    // Run DFS
    printf("\n=== DFS Starting from vertex 4 ===\n");
    printf("Using Recursion/Stack (LIFO - Last In First Out)\n\n");
    resetDFS();
    DFS(G, 4, 7);
    printf("\nDFS Complete!\n");

    printf("\n=====================================================\n");
    printf("           COMPARISON\n");
    printf("=====================================================\n");
    printf("BFS Order: Level by level (like ripples in water)\n");
    printf("DFS Order: Go deep first (explore as far as possible)\n");
    printf("\nBFS Result: 4 → 2, 3, 5, 6 → 1\n");
    printf("DFS Result: 4 → 2 → 1 → 3 (back) → 5 (back) → 6\n");
    printf("=====================================================\n");

    return 0;
}

/*

    benraiss@MacBookAir graphs %  clang -std=c17 -Wall -Wextra -o _graph Graph.c && ./_graph
    =====================================================
            GRAPH VISUALIZATION
    =====================================================
          1
        /  \
        2    3
        \  /
         4
        / \
        5   6
    =====================================================

    === BFS Starting from vertex 4 ===
    Using Queue (FIFO - First In First Out)

    Step 1: Visit starting vertex 4
    Output: 4
        [Queue: enqueue 4]
        [Queue: dequeue 4]

    Step 2: Exploring neighbors of vertex 4
    Found unvisited neighbor: 2
    Output: 2
        [Queue: enqueue 2]
    Found unvisited neighbor: 3
    Output: 3
        [Queue: enqueue 3]
    Found unvisited neighbor: 5
    Output: 5
        [Queue: enqueue 5]
    Found unvisited neighbor: 6
    Output: 6
        [Queue: enqueue 6]
        [Queue: dequeue 2]

    Step 3: Exploring neighbors of vertex 2
    Found unvisited neighbor: 1
    Output: 1
        [Queue: enqueue 1]
        [Queue: dequeue 3]

    Step 4: Exploring neighbors of vertex 3
        [Queue: dequeue 5]

    Step 5: Exploring neighbors of vertex 5
        [Queue: dequeue 6]

    Step 6: Exploring neighbors of vertex 6
        [Queue: dequeue 1]

    Step 7: Exploring neighbors of vertex 1

    BFS Complete!


    =====================================================

    === DFS Starting from vertex 4 ===
    Using Recursion/Stack (LIFO - Last In First Out)

    Step 1: Visit vertex 4
    Output: 4
    → Going DEEP to neighbor 2
    Step 2: Visit vertex 2
    Output: 2
    → Going DEEP to neighbor 1
    Step 3: Visit vertex 1
    Output: 1
    → Going DEEP to neighbor 3
    Step 4: Visit vertex 3
    Output: 3
    ← Backtracking from 3 to 1
    ← Backtracking from 1 to 2
    ← Backtracking from 2 to 4
    → Going DEEP to neighbor 5
    Step 5: Visit vertex 5
    Output: 5
    ← Backtracking from 5 to 4
    → Going DEEP to neighbor 6
    Step 6: Visit vertex 6
    Output: 6
    ← Backtracking from 6 to 4

    DFS Complete!

    =====================================================
            COMPARISON
    =====================================================
    BFS Order: Level by level (like ripples in water)
    DFS Order: Go deep first (explore as far as possible)

    BFS Result: 4 → 2, 3, 5, 6 → 1
    DFS Result: 4 → 2 → 1 → 3 (back) → 5 (back) → 6
    =====================================================
    benraiss@MacBookAir graphs %



// BFS (Breadth-First Search , BFS uses a Queue (FIFO))
Graph:        1
             / \
            2   3
             \ /
              4
             / \
            5   6

Level 0: Start at 4
         Queue: [4]

Level 1: Visit all neighbors of 4
         Found: 2, 3, 5, 6
         Queue: [2, 3, 5, 6]

Level 2: Visit neighbors of 2 (first in queue)
         Found: 1
         Queue: [3, 5, 6, 1]

Level 3: Visit neighbors of 3, 5, 6, 1
         (All already visited or no new neighbors)
         Queue: empty → DONE!

BFS Order: 4 → 2, 3, 5, 6 → 1

Queue ensures we explore LEVEL BY LEVEL:

Step 1: Visit 4 → Queue: [4]
Step 2: Process 4 → Add neighbors: [2, 3, 5, 6]
Step 3: Process 2 (first added) → Add: [3, 5, 6, 1]
Step 4: Process 3 (second added) → Queue: [5, 6, 1]
...

First In = First Out → Level-by-level order!


Initial: visited = [0, 0, 0, 0, 0, 0, 0]
         Queue = []

Step 1: Visit 4
        visited = [0, 0, 0, 0, 1, 0, 0]
        Queue = [4]

Step 2: Dequeue 4, explore neighbors (2, 3, 5, 6)
        visited = [0, 0, 1, 1, 1, 1, 1]
        Queue = [2, 3, 5, 6]

Step 3: Dequeue 2, explore neighbors (1)
        visited = [0, 1, 1, 1, 1, 1, 1]
        Queue = [3, 5, 6, 1]

Step 4: Dequeue 3, no new neighbors
        Queue = [5, 6, 1]

Step 5: Dequeue 5, no new neighbors
        Queue = [6, 1]

Step 6: Dequeue 6, no new neighbors
        Queue = [1]

Step 7: Dequeue 1, no new neighbors
        Queue = [] → DONE!




-----------------------------------------------------------------------

DFS (Depth-First Search), DFS uses Recursion/Stack (LIFO)

Graph:        1
             / \
            2   3
             \ /
              4
             / \
            5   6

Start: Visit 4
  ↓ Go to first neighbor: 2
      ↓ Go to first neighbor of 2: 1
          ↓ Go to first neighbor of 1: 3
              ↓ (3 has no unvisited neighbors)
          ↑ Backtrack to 1
      ↑ Backtrack to 2
  ↑ Backtrack to 4
  ↓ Go to next neighbor: 5
      ↓ (5 has no unvisited neighbors)
  ↑ Backtrack to 4
  ↓ Go to next neighbor: 6
      ↓ (6 has no unvisited neighbors)
  ↑ Backtrack to 4

DFS Order: 4 → 2 → 1 → 3 → (back) → 5 → 6

DFS(4):
  Visit 4
  → DFS(2):
      Visit 2
      → DFS(1):
          Visit 1
          → DFS(3):
              Visit 3
              return
          ← back to DFS(1)
          return
      ← back to DFS(2)
      return
  ← back to DFS(4)
  → DFS(5):
      Visit 5
      return
  ← back to DFS(4)
  → DFS(6):
      Visit 6
      return
  ← back to DFS(4)

  Call Stack:

DFS(4) → Visit 4, visited[4]=1
  ├─ Check neighbor 2: unvisited → DFS(2)
  │    DFS(2) → Visit 2, visited[2]=1
  │      ├─ Check neighbor 1: unvisited → DFS(1)
  │      │    DFS(1) → Visit 1, visited[1]=1
  │      │      ├─ Check neighbor 2: visited ✗
  │      │      ├─ Check neighbor 3: unvisited → DFS(3)
  │      │      │    DFS(3) → Visit 3, visited[3]=1
  │      │      │      ├─ Check neighbor 1: visited ✗
  │      │      │      └─ Check neighbor 4: visited ✗
  │      │      │    return from DFS(3)
  │      │      └─ no more neighbors
  │      │    return from DFS(1)
  │      └─ Check neighbor 4: visited ✗
  │    return from DFS(2)
  ├─ Check neighbor 3: visited ✗
  ├─ Check neighbor 5: unvisited → DFS(5)
  │    DFS(5) → Visit 5, visited[5]=1
  │      └─ Check neighbor 4: visited ✗
  │    return from DFS(5)
  └─ Check neighbor 6: unvisited → DFS(6)
       DFS(6) → Visit 6, visited[6]=1
         └─ Check neighbor 4: visited ✗
       return from DFS(6)
return from DFS(4)

*/