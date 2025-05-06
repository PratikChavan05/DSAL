#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
    int V, E;
    vector<Edge> edges;

public:
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    int findParent(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = findParent(parent, parent[i]); // Path compression
        return parent[i];
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = findParent(parent, x);
        int yroot = findParent(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void kruskalMST() {
        vector<Edge> result;
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int i = 0; i < V; ++i)
            parent[i] = i;

        int e = 0, i = 0;
        while (e < V - 1 && i < edges.size()) {
            Edge next = edges[i++];
            int x = findParent(parent, next.src);
            int y = findParent(parent, next.dest);

            if (x != y) {
                result.push_back(next);
                unionSets(parent, rank, x, y);
                e++;
            }
        }

        int totalCost = 0;
        cout << "Edges in MST:\n";
        for (auto edge : result) {
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
            totalCost += edge.weight;
        }
        cout << "Total cost of MST: " << totalCost << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V, E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.kruskalMST();

    return 0;
}
