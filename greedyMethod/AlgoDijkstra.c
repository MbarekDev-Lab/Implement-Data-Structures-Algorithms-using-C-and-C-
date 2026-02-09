#include <stdio.h>
#include <string.h>
#include <limits.h>

/**
 * DIJKSTRA'S ALGORITHM — Abdul Bari Style Implementation
 * 
 * What Abdul Bari teaches:
 * 
 * Three things you MUST maintain:
 *   1. cost[][] → Adjacency matrix (∞ if no edge)
 *   2. dist[]   → Shortest distance from source so far
 *   3. visited[] → Whether vertex is finalized
 * 
 * At every step:
 *   • Pick the unvisited vertex with minimum dist
 *   • Mark it visited (PERMANENT, never change)
 *   • Relax its adjacent vertices (update dist if better path found)
 * 
 * ⚠️  CRITICAL: Dijkstra does NOT work with negative edge weights
 */

#define I 32767   // Infinity (large value, similar to INT_MAX but safer)
#define V 7       // Number of vertices (0 to 6)

/**
 * Print the cost matrix
 */
void printCostMatrix(int cost[V][V]) {
    printf("\nCost Matrix (∞ = 32767, no edge):\n");
    printf("     ");
    for (int i = 0; i < V; i++) printf("%5d ", i);
    printf("\n");
    
    for (int i = 0; i < V; i++) {
        printf("  %d: ", i);
        for (int j = 0; j < V; j++) {
            if (cost[i][j] == I)
                printf("   ∞ ");
            else
                printf("%5d ", cost[i][j]);
        }
        printf("\n");
    }
}

/**
 * DIJKSTRA'S ALGORITHM
 * 
 * Input:
 *   cost[V][V] = adjacency matrix with edge weights
 *   source = starting vertex
 * 
 * Output:
 *   Prints shortest distance from source to each vertex
 */
void Dijkstra(int cost[V][V], int source) {
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║  DIJKSTRA'S ALGORITHM - ABDUL BARI STYLE   ║\n");
    printf("║  Source: Vertex %d                         ║\n", source);
    printf("╚═══════════════════════════════════════════╝\n");
    
    // ============ STEP 1: INITIALIZATION ============
    
    int dist[V];      // Shortest known distance from source
    int visited[V];   // Whether distance is permanent (finalized)
    
    // Initialize: all distances = ∞, no vertices visited
    for (int i = 0; i < V; i++) {
        dist[i] = I;
        visited[i] = 0;  // 0 = false (not visited)
    }
    
    // Source distance to itself = 0
    dist[source] = 0;
    
    printf("\nInitialization:\n");
    printf("dist[] = {");
    for (int i = 0; i < V; i++) {
        if (dist[i] == I)
            printf(" ∞");
        else
            printf(" %d", dist[i]);
        if (i < V - 1) printf(",");
    }
    printf(" }\n");
    
    // ============ STEP 2: MAIN LOOP (V-1 iterations) ============
    
    printf("\n════════════════════ MAIN ALGORITHM ════════════════════\n\n");
    
    for (int count = 0; count < V - 1; count++) {
        printf("Iteration %d:\n", count + 1);
        
        // ============ STEP 3: PICK MINIMUM UNVISITED DISTANCE ============
        
        int u = -1;           // Selected vertex
        int min = I;          // Minimum distance found
        
        for (int i = 0; i < V; i++) {
            // Look for unvisited vertex with smallest distance
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        
        printf("  Unvisited vertices with distances:\n");
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                printf("    Vertex %d: dist=%d", i, (dist[i] == I ? -1 : dist[i]));
                if (i == u) printf(" ← SELECTED (minimum)\n");
                else printf("\n");
            }
        }
        
        // ============ STEP 4A: MARK AS VISITED (PERMANENT) ============
        
        visited[u] = 1;  // This distance is now FINAL, never changes
        
        printf("  Mark vertex %d as visited (distance %d is PERMANENT)\n", u, dist[u]);
        
        // ============ STEP 4B: RELAX ADJACENT VERTICES ============
        
        printf("  Relaxing neighbors of vertex %d:\n", u);
        int relaxed = 0;
        
        for (int v = 0; v < V; v++) {
            // Only consider unvisited neighbors
            if (!visited[v] && cost[u][v] != I) {
                // Calculate distance through u
                int newDist = dist[u] + cost[u][v];
                
                printf("    → Neighbor %d: ", v);
                printf("dist[%d] + cost[%d][%d] = %d + %d = %d",
                       u, u, v, dist[u], cost[u][v], newDist);
                
                // Update if better path found
                if (newDist < dist[v]) {
                    printf(" < %d, UPDATE dist[%d] = %d\n",
                           (dist[v] == I ? -1 : dist[v]), v, newDist);
                    dist[v] = newDist;
                    relaxed++;
                } else {
                    printf(" >= %d, no update\n",
                           (dist[v] == I ? -1 : dist[v]));
                }
            }
        }
        
        if (relaxed == 0) {
            printf("    (no neighbors to relax)\n");
        }
        
        // Show current state
        printf("\n  Current dist[] after iteration %d:\n  ", count + 1);
        printf("dist[] = { ");
        for (int i = 0; i < V; i++) {
            if (dist[i] == I)
                printf("∞");
            else
                printf("%d", dist[i]);
            if (visited[i]) printf("*");  // * means visited
            if (i < V - 1) printf(", ");
        }
        printf(" } (* = visited/permanent)\n\n");
    }
    
    // ============ STEP 5: OUTPUT RESULTS ============
    
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║           FINAL SHORTEST DISTANCES         ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    for (int i = 0; i < V; i++) {
        printf("Distance from %d to %d = ", source, i);
        if (dist[i] == I)
            printf("∞ (unreachable)\n");
        else
            printf("%d\n", dist[i]);
    }
}

/**
 * TEST CASE 1: Abdul Bari's Example Graph (7 vertices)
 * This matches his whiteboard exactly
 */
void test_abdul_bari_graph() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║        TEST CASE 1: ABDUL BARI'S EXAMPLE GRAPH         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    int cost[V][V] = {
        //   0    1    2    3    4    5    6
        {    I,  28,   I,   I,   I,  10,   I },  // 0
        {   28,   I,  16,   I,   I,   I,  14 },  // 1
        {    I,  16,   I,  12,   I,   I,   I },  // 2
        {    I,   I,  12,   I,  22,   I,  18 },  // 3
        {    I,   I,   I,  22,   I,  25,  24 },  // 4
        {   10,   I,   I,   I,  25,   I,   I },  // 5
        {    I,  14,   I,  18,  24,   I,   I }   // 6
    };
    
    printCostMatrix(cost);
    Dijkstra(cost, 0);
}

/**
 * TEST CASE 2: Simple 4-Vertex Graph
 */
void test_simple_graph() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║         TEST CASE 2: SIMPLE 4-VERTEX GRAPH             ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // Redefine V for this test (normally would use different function)
    int tempCost[4][4] = {
        //   0   1   2   3
        {    I,  1,  4,   I },  // 0
        {    1,  I,  2,  5 },   // 1
        {    4,  2,  I,  1 },   // 2
        {    I,  5,  1,  I }    // 3
    };
    
    printf("\nCost Matrix (4 vertices):\n");
    printf("     ");
    for (int i = 0; i < 4; i++) printf("%5d ", i);
    printf("\n");
    
    for (int i = 0; i < 4; i++) {
        printf("  %d: ", i);
        for (int j = 0; j < 4; j++) {
            if (tempCost[i][j] == I)
                printf("   ∞ ");
            else
                printf("%5d ", tempCost[i][j]);
        }
        printf("\n");
    }
    
    // Manual implementation for 4-vertex case
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║  DIJKSTRA'S ALGORITHM - 4 VERTICES       ║\n");
    printf("║  Source: Vertex 0                        ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    
    int dist[4];
    int visited[4];
    
    for (int i = 0; i < 4; i++) {
        dist[i] = I;
        visited[i] = 0;
    }
    dist[0] = 0;
    
    for (int count = 0; count < 3; count++) {
        int u = -1;
        int min = I;
        
        for (int i = 0; i < 4; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        
        printf("\nIteration %d: Select vertex %d (dist=%d)\n", 
               count + 1, u, dist[u]);
        
        visited[u] = 1;
        
        for (int v = 0; v < 4; v++) {
            if (!visited[v] && tempCost[u][v] != I) {
                int newDist = dist[u] + tempCost[u][v];
                if (newDist < dist[v]) {
                    printf("  Update dist[%d] = %d\n", v, newDist);
                    dist[v] = newDist;
                }
            }
        }
    }
    
    printf("\nFinal distances from vertex 0:\n");
    for (int i = 0; i < 4; i++) {
        printf("  0 → %d: %d\n", i, dist[i]);
    }
}

/**
 * TEST CASE 3: Linear Chain (to show step-by-step clearly)
 */
void test_linear_chain() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║    TEST CASE 3: LINEAR CHAIN (0→1→2→3)                 ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    int tempCost[4][4] = {
        //   0   1   2   3
        {    I,  5,  I,  I },  // 0
        {    5,  I,  3,  I },  // 1
        {    I,  3,  I,  2 },  // 2
        {    I,  I,  2,  I }   // 3
    };
    
    printf("\nCost Matrix (linear chain):\n");
    printf("     ");
    for (int i = 0; i < 4; i++) printf("%5d ", i);
    printf("\n");
    
    for (int i = 0; i < 4; i++) {
        printf("  %d: ", i);
        for (int j = 0; j < 4; j++) {
            if (tempCost[i][j] == I)
                printf("   ∞ ");
            else
                printf("%5d ", tempCost[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEdges: 0-1(5) → 1-2(3) → 2-3(2)\n");
    printf("Expected: 0→1=5, 0→2=8, 0→3=10\n");
    
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║    DIJKSTRA'S ALGORITHM - LINEAR CHAIN    ║\n");
    printf("║    Source: Vertex 0                       ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    
    int dist[4];
    int visited[4];
    
    for (int i = 0; i < 4; i++) {
        dist[i] = I;
        visited[i] = 0;
    }
    dist[0] = 0;
    
    for (int count = 0; count < 3; count++) {
        int u = -1;
        int min = I;
        
        for (int i = 0; i < 4; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        
        printf("\nIteration %d:\n", count + 1);
        printf("  Select vertex %d (distance %d is permanent)\n", u, dist[u]);
        
        visited[u] = 1;
        
        for (int v = 0; v < 4; v++) {
            if (!visited[v] && tempCost[u][v] != I) {
                int newDist = dist[u] + tempCost[u][v];
                printf("  Relax: dist[%d] = %d + %d = %d", v, dist[u], tempCost[u][v], newDist);
                if (newDist < dist[v]) {
                    printf(" (updated)\n");
                    dist[v] = newDist;
                } else {
                    printf(" (kept %d)\n", dist[v]);
                }
            }
        }
    }
    
    printf("\nFinal distances from vertex 0:\n");
    for (int i = 0; i < 4; i++) {
        printf("  0 → %d: %d\n", i, dist[i]);
    }
}

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║      DIJKSTRA'S ALGORITHM - ABDUL BARI INTERPRETATION   ║\n");
    printf("║                                                        ║\n");
    printf("║  Key Concepts:                                         ║\n");
    printf("║    • cost[][] = Adjacency matrix (∞ if no edge)       ║\n");
    printf("║    • dist[] = Shortest known distance from source      ║\n");
    printf("║    • visited[] = Whether distance is PERMANENT         ║\n");
    printf("║                                                        ║\n");
    printf("║  Algorithm:                                            ║\n");
    printf("║    1. Pick unvisited vertex with minimum distance      ║\n");
    printf("║    2. Mark it visited (NEVER change this distance)    ║\n");
    printf("║    3. Relax all adjacent unvisited vertices            ║\n");
    printf("║    4. Repeat V-1 times                                 ║\n");
    printf("║                                                        ║\n");
    printf("║  ⚠️  CRITICAL: NO NEGATIVE EDGES ALLOWED               ║\n");
    printf("║                                                        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // Run all test cases
    test_abdul_bari_graph();
    test_simple_graph();
    test_linear_chain();
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                    ALL TESTS COMPLETE                  ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}

/*
 * ════════════════════════════════════════════════════════════════════════════
 * ABDUL BARI'S DIJKSTRA CHECKLIST — What You Must Remember
 * ════════════════════════════════════════════════════════════════════════════
 * 
 * □ Three things you maintain:
 *   ✓ cost[][] (input: adjacency matrix with ∞ for no edge)
 *   ✓ dist[] (your computation: shortest distance so far)
 *   ✓ visited[] (your control: is distance permanent?)
 * 
 * □ Loop V-1 times (or until all visited)
 * 
 * □ Each iteration:
 *   1. Find MINIMUM UNVISITED distance
 *   2. Mark it VISITED (permanent, never change)
 *   3. Relax all its adjacent unvisited neighbors
 * 
 * □ Relaxation means:
 *   if (dist[u] + cost[u][v] < dist[v])
 *       dist[v] = dist[u] + cost[u][v]
 * 
 * □ Why it works:
 *   - All edges non-negative
 *   - Once visited, that distance is best possible
 *   - No future path can improve it
 * 
 * □ Time Complexity:
 *   - O(V²) with adjacency matrix and array scanning
 *   - O((V+E)logV) with binary heap
 * 
 * □ When to use:
 *   ✓ Single source shortest paths
 *   ✓ Non-negative edges
 *   ✓ All edges should be accessible
 * 
 * □ When NOT to use:
 *   ✗ Negative edges (use Bellman-Ford)
 *   ✗ All pairs (use Floyd-Warshall)
 *   ✗ Unweighted (use BFS)
 * 
 * ════════════════════════════════════════════════════════════════════════════
 */
