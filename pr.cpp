#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Function to perform parallel BFS
void parallelBFS(vector<vector<int>>& graph, int source, vector<bool>& visited) {
    queue<int> q;
    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Parallelize the exploration of neighbors
        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Define the graph (adjacency list representation)
    vector<vector<int>> graph(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        cout << "Enter the number of neighbors for vertex " << i << ": ";
        int numNeighbors;
        cin >> numNeighbors;
        cout << "Enter the neighbors for vertex " << i << ": ";
        for (int j = 0; j < numNeighbors; ++j) {
            int neighbor;
            cin >> neighbor;
            graph[i].push_back(neighbor);
        }
    }

    vector<bool> visited(numVertices, false);

    // Perform parallel BFS from multiple sources
    #pragma omp parallel for
    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            parallelBFS(graph, i, visited);
        }
    }

    // Output the visited nodes after BFS
    cout << "Visited nodes after BFS:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        if (visited[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}
