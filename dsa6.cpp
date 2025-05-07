#include<bits/stdc++.h>
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
        for (auto it : adj) {
            cout << landmarks[it.first] << " --> ";
            for (auto it2 : it.second)
                cout << landmarks[it2] << ", ";
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
        cout << "\nDFS from " << landmarks[start] << ":\n";
        vector<bool> visited(adj.size(), false);
        stack<int> st;
        st.push(start);
    
        while (!st.empty()) {
            int curr = st.top();
            st.pop();
    
            if (!visited[curr]) {
                visited[curr] = true;
                cout << landmarks[curr] << " ";
            }
    
            for (int neighbor : adj[curr]) {
                if (!visited[neighbor])
                    st.push(neighbor);
            }
        }
        cout << endl;
    }
    

    void displayLandmarks() {
        cout << "\nAvailable Landmarks:\n";
        for (auto pair : landmarks) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};

int main() {
    Graph g;

    g.addEdge(0, 1); 
    g.addEdge(1, 2); 
    g.addEdge(1, 3); 
    g.addEdge(2, 4); 
    g.addEdge(3, 5); 
    g.displayLandmarks();
    g.showGraph();

    int start;
    cout << "\nEnter starting point (number) for DFS and BFS: ";
    cin >> start;

    g.DFS(start);
    g.BFS(start);

    return 0;
}
