#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

class Graph {
    map<int, vector<int>> adj;
    map<int, string> landmarks;

public:
    Graph() {
        
        landmarks[0] = "Main Gate";
        landmarks[1] = "Library";
        landmarks[2] = "Canteen";
        landmarks[3] = "Admin Block";
        landmarks[4] = "Hostel";
        landmarks[5] = "Playground";
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    void showGraph() {
        cout << "\nGraph Representation (Adjacency List):\n";
        for (auto& pair : adj) {
            cout << landmarks[pair.first] << " --> ";
            for (int neighbor : pair.second)
                cout << landmarks[neighbor] << ", ";
            cout << endl;
        }
    }

    void BFS(int start) {
        cout << "\nBFS Traversal from " << landmarks[start] << ":\n";
        set<int> visited;
        queue<int> q;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << landmarks[curr] << " ";

            for (int neighbor : adj[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFS(int start) {
        cout << "\nDFS Traversal from " << landmarks[start] << ":\n";
        set<int> visited;
        stack<int> st;

        st.push(start);

        while (!st.empty()) {
            int curr = st.top();
            st.pop();

            if (!visited.count(curr)) {
                visited.insert(curr);
                cout << landmarks[curr] << " ";
            }

            for (auto it = adj[curr].rbegin(); it != adj[curr].rend(); ++it) {
                if (!visited.count(*it)) {
                    st.push(*it);
                }
            }
        }
        cout << endl;
    }

    void displayLandmarks() {
        cout << "\nAvailable Landmarks:\n";
        for (auto& pair : landmarks) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};

int main() {
    Graph g;

    // Adding edges between landmarks (you can customize this)
    g.addEdge(0, 1); // Main Gate <-> Library
    g.addEdge(1, 2); // Library <-> Canteen
    g.addEdge(1, 3); // Library <-> Admin Block
    g.addEdge(2, 4); // Canteen <-> Hostel
    g.addEdge(3, 5); // Admin Block <-> Playground
    g.displayLandmarks();
    g.showGraph();

    int start;
    cout << "\nEnter starting point (number) for DFS and BFS: ";
    cin >> start;

    g.DFS(start);
    g.BFS(start);

    return 0;
}
