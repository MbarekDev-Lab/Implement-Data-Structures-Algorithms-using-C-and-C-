#include <iostream>
#include <queue>

using namespace std;

void BFS(int vtx, int A[][8], int n)
{
    queue<int> Q;      // Queue for BFS
    int visited[8]{0}; // Visited array initialized to 0

    // Initial
    cout << vtx << ", " << flush; // Visit vertex
    visited[vtx] = 1;             // Mark as visited
    Q.emplace(vtx);               // Add to queue

    // Explore
    while (!Q.empty())
    {
        int u = Q.front(); // Vertex u for exploring
        Q.pop();           // Dequeue u removal from queue

        // Check all adjacent vertices  (Check all possible neighbors (1 to n))
        for (int v = 1; v <= n; v++)
        { // Adjacent vertices of vertex u
            // If connrected and not visited
            if (A[u][v] == 1 && visited[v] == 0)
            {                               // Adjacent vertex and not visited
                cout << v << ", " << flush; // Visit vertex
                visited[v] = 1;             // Mark as visited
                Q.emplace(v);               // Add to queue
            }
        }
    }
    cout << endl;
}

int main()
{

    int A[8][8] = {
        //  0  1  2  3  4  5  6  7
        {0, 0, 0, 0, 0, 0, 0, 0}, // vertex 0 (unused)
        {0, 0, 1, 1, 1, 0, 0, 0}, // vertex 1 connects to: 2, 3, 4
        {0, 1, 0, 1, 0, 0, 0, 0}, // vertex 2 connects to: 1, 3
        {0, 1, 1, 0, 1, 1, 0, 0}, // vertex 3 connects to: 1, 2, 4, 5
        {0, 1, 0, 1, 0, 1, 0, 0}, // vertex 4 connects to: 1, 3, 5
        {0, 0, 0, 1, 1, 0, 1, 1}, // vertex 5 connects to: 3, 4, 6, 7
        {0, 0, 0, 0, 0, 1, 0, 0}, // vertex 6 connects to: 5
        {0, 0, 0, 0, 0, 1, 0, 0}  // vertex 7 connects to: 5
    };

    cout << "Vertex: 1 -> " << flush;
    BFS(1, A, 8);

    cout << "Vertex: 4 -> " << flush;
    BFS(4, A, 8);

    return 0;
}

/*

/_bfs
Vertex: 1 -> 1, 2, 3, 4, 5, 6, 7,
Vertex: 4 -> 4, 1, 3, 5, 2, 6, 7,


        1
      / | \
     2  3  4
     |  |\ |
     |  | \|
     |  |  5
     | /  /|\
     3   6 7

    1 ←→ 2
   ↓↑   ↗
   3 ←→ 4
   ↓↑   ↓↑
   5 → 6
   ↓
   7

Queue Q: empty
Visited: [0, 0, 0, 0, 0, 0, 0, 0]

Output: 1
Visited: [0, 1, 0, 0, 0, 0, 0, 0]
Queue Q: [1]

Pop 1 from queue
Check A[1][2]=1 & not visited → Visit 2, add to queue
Check A[1][3]=1 & not visited → Visit 3, add to queue
Check A[1][4]=1 & not visited → Visit 4, add to queue

Output: 1, 2, 3, 4
Visited: [0, 1, 1, 1, 1, 0, 0, 0]
Queue Q: [2, 3, 4]

Pop 1 from queue
Check A[1][2]=1 & not visited → Visit 2, add to queue
Check A[1][3]=1 & not visited → Visit 3, add to queue
Check A[1][4]=1 & not visited → Visit 4, add to queue

Output: 1, 2, 3, 4
Visited: [0, 1, 1, 1, 1, 0, 0, 0]
Queue Q: [2, 3, 4]

Pop 2 from queue
Check A[2][1]=1 but already visited → skip
Check A[2][3]=1 but already visited → skip

Output: 1, 2, 3, 4
Queue Q: [3, 4]

Pop 2 from queue
Check A[2][1]=1 but already visited → skip
Check A[2][3]=1 but already visited → skip

Output: 1, 2, 3, 4
Queue Q: [3, 4]

Pop 3 from queue
Check A[3][1]=1 but already visited → skip
Check A[3][2]=1 but already visited → skip
Check A[3][4]=1 but already visited → skip
Check A[3][5]=1 & not visited → Visit 5, add to queue

Output: 1, 2, 3, 4, 5
Visited: [0, 1, 1, 1, 1, 1, 0, 0]
Queue Q: [4, 5]


Pop 4 from queue
Check A[4][1]=1 but already visited → skip
Check A[4][3]=1 but already visited → skip
Check A[4][5]=1 but already visited → skip

Output: 1, 2, 3, 4, 5
Queue Q: [5]


Pop 5 from queue
Check A[5][3]=1 but already visited → skip
Check A[5][4]=1 but already visited → skip
Check A[5][6]=1 & not visited → Visit 6, add to queue
Check A[5][7]=1 & not visited → Visit 7, add to queue

Output: 1, 2, 3, 4, 5, 6, 7
Visited: [0, 1, 1, 1, 1, 1, 1, 1]
Queue Q: [6, 7]


Pop 6: no unvisited neighbors
Pop 7: no unvisited neighbors
Queue Q: empty → DONE!

Final Output: 1, 2, 3, 4, 5, 6, 7 
*/
