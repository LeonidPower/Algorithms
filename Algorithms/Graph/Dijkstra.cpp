#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

// Graph class representing an adjacency list
class Graph {
private:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list (pair: {vertex, weight})

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Function to add an edge between two vertices with a weight
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // For undirected graph
    }

    // Function to perform Dijkstra's algorithm
    vector<int> dijkstra(int start) {
        vector<int> dist(V, INF); // Initialize distances with infinity
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start}); // {distance, vertex}

        while (!pq.empty()) {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();

            // If current distance is greater than already known distance, skip
            if (current_dist > dist[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    Graph g(6); // Create a graph with 6 vertices

    // Adding edges with weights
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 9);
    g.addEdge(0, 5, 14);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 11);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 5, 9);

    int start = 0;
    vector<int> distances = g.dijkstra(start);

    cout << "Shortest distances from vertex " << start << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }

    return 0;
}
