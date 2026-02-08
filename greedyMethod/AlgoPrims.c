#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

/**
 * Prim's Algorithm - Minimum Spanning Tree
 * 
 * Time Complexity: O(V²) with matrix representation
 * Space Complexity: O(V²) for cost matrix
 * 
 * Algorithm idea:
 *   - Start with one vertex
 *   - Repeatedly add the cheapest unvisited vertex
 *   - One connected component growing from start to finish
 *   - No cycle checking needed (by design)
 */

typedef struct {
    int cost[MAX_VERTICES][MAX_VERTICES];
    int n;  // number of vertices
} Graph;

typedef struct {
    int u;      // source vertex (in tree)
    int v;      // destination vertex (added to tree)
    int weight; // edge weight
} Edge;

// Function prototypes
void initializeGraph(Graph *g, int n);
void addEdge(Graph *g, int u, int v, int weight);
void primMST(Graph *g, int start);
void printMST(Edge mst[], int edgeCount, int totalCost);

/**
 * Initialize graph with n vertices
 * All edges initially set to INF (no connection)
 */
void initializeGraph(Graph *g, int n) {
    g->n = n;
    
    // Set all costs to infinity
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->cost[i][j] = INF;
        }
        g->cost[i][i] = 0;  // Cost to itself is 0
    }
}

/**
 * Add undirected edge between vertices u and v with given weight
 */
void addEdge(Graph *g, int u, int v, int weight) {
    g->cost[u][v] = weight;
    g->cost[v][u] = weight;  // Undirected
}

/**
 * Prim's Algorithm Implementation
 * 
 * Core idea:
 *   1. Start with one vertex in the MST
 *   2. Maintain which vertices are inside/outside the tree
 *   3. For each outside vertex, track the cheapest way to add it
 *   4. Repeatedly pick the cheapest outside vertex and add it
 *   5. Update costs for neighbors when new vertex is added
 */
void primMST(Graph *g, int start) {
    int n = g->n;
    
    // visited[i] = 1 if vertex i is in MST, 0 otherwise
    int visited[MAX_VERTICES] = {0};
    
    // near[i] = which vertex in MST is closest to vertex i
    //           (i.e., which vertex should i connect to if added)
    int near[MAX_VERTICES];
    
    // key[i] = minimum cost to add vertex i to MST
    int key[MAX_VERTICES];
    
    // For tracking the edges in MST
    Edge mst[MAX_VERTICES];
    int edgeCount = 0;
    int totalCost = 0;
    
    // ============ INITIALIZATION ============
    visited[start] = 1;  // Start with this vertex in MST
    
    // Initialize: all other vertices connect through start vertex
    for (int i = 0; i < n; i++) {
        near[i] = start;
        key[i] = g->cost[start][i];
    }
    
    // ============ MAIN LOOP ============
    // Need to add n-1 more vertices (we started with 1)
    for (int count = 1; count < n; count++) {
        
        // STEP A: Find the unvisited vertex with minimum cost
        int minCost = INF;
        int u = -1;
        
        for (int v = 0; v < n; v++) {
            if (visited[v] == 0 && key[v] < minCost) {
                minCost = key[v];
                u = v;
            }
        }
        
        // Edge case: disconnected graph
        if (u == -1) {
            printf("Graph is disconnected!\n");
            return;
        }
        
        // STEP B: Add this vertex to MST
        visited[u] = 1;
        totalCost += minCost;
        
        // Record the edge
        mst[edgeCount].u = near[u];
        mst[edgeCount].v = u;
        mst[edgeCount].weight = minCost;
        edgeCount++;
        
        printf("Iteration %d: Add vertex %d via edge (%d, %d) with cost %d\n",
               count, u, near[u], u, minCost);
        
        // STEP C: Update key[v] and near[v] for all unvisited vertices
        // The newly added vertex u might be a better neighbor
        for (int v = 0; v < n; v++) {
            if (visited[v] == 0) {
                // If the edge from u to v is cheaper than current route
                if (g->cost[u][v] < key[v]) {
                    key[v] = g->cost[u][v];
                    near[v] = u;
                }
            }
        }
    }
    
    // Print result
    printf("\n");
    printMST(mst, edgeCount, totalCost);
}

/**
 * Print the MST result
 */
void printMST(Edge mst[], int edgeCount, int totalCost) {
    printf("=== MINIMUM SPANNING TREE ===\n");
    printf("Edges in MST:\n");
    printf("From | To | Weight\n");
    printf("-----|----|---------\n");
    
    for (int i = 0; i < edgeCount; i++) {
        printf("  %d  | %d  |   %d\n", 
               mst[i].u, mst[i].v, mst[i].weight);
    }
    
    printf("\nTotal edges: %d\n", edgeCount);
    printf("Total MST cost: %d\n", totalCost);
    printf("=============================\n");
}

/**
 * TEST CASES
 */

// Test 1: Simple 7-vertex graph (from whiteboard)
void test_7vertex_graph() {
    printf("\n========== TEST 1: 7-Vertex Graph ==========\n");
    
    Graph g;
    initializeGraph(&g, 7);
    
    // Add edges (0-indexed)
    addEdge(&g, 0, 1, 28);
    addEdge(&g, 0, 5, 10);
    addEdge(&g, 1, 2, 16);
    addEdge(&g, 1, 6, 14);
    addEdge(&g, 2, 3, 12);
    addEdge(&g, 3, 4, 22);
    addEdge(&g, 3, 6, 18);
    addEdge(&g, 4, 5, 25);
    addEdge(&g, 4, 6, 24);
    
    printf("Starting Prim's algorithm from vertex 0\n\n");
    primMST(&g, 0);
}

// Test 2: Small 4-vertex graph
void test_4vertex_graph() {
    printf("\n========== TEST 2: 4-Vertex Graph ==========\n");
    
    Graph g;
    initializeGraph(&g, 4);
    
    // Create a simple connected graph
    addEdge(&g, 0, 1, 1);
    addEdge(&g, 0, 2, 4);
    addEdge(&g, 1, 2, 2);
    addEdge(&g, 1, 3, 5);
    addEdge(&g, 2, 3, 3);
    
    printf("Starting Prim's algorithm from vertex 0\n\n");
    primMST(&g, 0);
}

// Test 3: Complete graph (every vertex connected to every other)
void test_complete_graph() {
    printf("\n========== TEST 3: Complete 5-Vertex Graph ==========\n");
    
    Graph g;
    initializeGraph(&g, 5);
    
    // Complete graph
    int weights[5][5] = {
        {0,  2, 4, 6, 8},
        {2,  0, 3, 5, 7},
        {4,  3, 0, 1, 9},
        {6,  5, 1, 0, 4},
        {8,  7, 9, 4, 0}
    };
    
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            addEdge(&g, i, j, weights[i][j]);
        }
    }
    
    printf("Starting Prim's algorithm from vertex 0\n\n");
    primMST(&g, 0);
}

// Test 4: Starting from different vertex
void test_different_start() {
    printf("\n========== TEST 4: Same Graph, Different Start ==========\n");
    
    Graph g;
    initializeGraph(&g, 4);
    
    addEdge(&g, 0, 1, 1);
    addEdge(&g, 0, 2, 4);
    addEdge(&g, 1, 2, 2);
    addEdge(&g, 1, 3, 5);
    addEdge(&g, 2, 3, 3);
    
    printf("Starting from vertex 2 (instead of 0)\n\n");
    primMST(&g, 2);
}

int main() {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║      PRIM'S ALGORITHM - C IMPLEMENTATION   ║\n");
    printf("║    Minimum Spanning Tree (MST) Builder     ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    // Run tests
    test_7vertex_graph();
    test_4vertex_graph();
    test_complete_graph();
    test_different_start();
    
    printf("\n✓ All tests completed!\n");
    
    return 0;
}

/*
 * EXPLANATION OF KEY DATA STRUCTURES:
 * 
 * visited[v]:
 *   - 1 if vertex v is in MST
 *   - 0 if vertex v is still outside
 *   - Prim maintains exactly one connected tree (always)
 * 
 * near[v]:
 *   - For outside vertex v, this stores which MST vertex is closest
 *   - Encodes the greedy decision: "if I add v, connect it to near[v]"
 *   - Allows O(n) finding of best vertex to add (vs. O(n²))
 * 
 * key[v]:
 *   - Cost to add vertex v to MST
 *   - Initially g->cost[start][v]
 *   - Updated when new vertices join MST (may find cheaper path)
 * 
 * ALGORITHM FLOW:
 * 
 * 1. Start: visited[start] = 1, all others = 0
 * 2. Initialize: near[v] = start, key[v] = cost[start][v]
 * 3. Loop n-1 times:
 *    a. Find unvisited v with minimum key[v]
 *    b. Mark visited[v] = 1, add edge (near[v], v) to MST
 *    c. For each unvisited neighbor k of v:
 *       - If cost[v][k] < key[k]: update key[k] and near[k]
 * 
 * TIME COMPLEXITY:
 *   - Finding minimum: O(n) per iteration
 *   - Updating neighbors: O(n) per iteration
 *   - n iterations total
 *   - Total: O(n²)
 * 
 * SPACE COMPLEXITY:
 *   - Cost matrix: O(n²)
 *   - Arrays (visited, near, key): O(n)
 *   - Total: O(n²)
 * 
 * WHEN TO USE PRIM:
 *   ✓ Dense graphs (many edges)
 *   ✓ Already have adjacency matrix
 *   ✓ Want connected tree from start
 *   ✗ Sparse graphs (Kruskal better)
 */
