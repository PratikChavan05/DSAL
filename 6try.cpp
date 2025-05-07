#include<bits/stdc++.h>
using namespace std;

class Graph{
    map<int,vector<int>> adj;
    map<int ,string> landmarks;

    public:
    Graph(){
        landmarks[0] = "Main Gate";
        landmarks[1] = "Library";
        landmarks[2] = "Canteen";
        landmarks[3] = "Admin Block";
        landmarks[4] = "Hostel";
        landmarks[5] = "Playground";
    }

    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void show(){
        for(auto it:adj){
            cout<<landmarks[it.first]<<"--> ";
            for(auto it2: it.second){
                cout<<landmarks[it2]<<" ,";
            }
            cout<<endl;
        }
    }

    void bfs(int start){
        cout << "\nBFS from " << landmarks[start] << ":\n";
        vector<bool> visited (adj.size(),false);
        queue<int>q;

        visited[start]=true;
        q.push(start);

        while(!q.empty()){
            int curr = q.front();
            q.pop();
            cout<<landmarks[curr]<<" ";

            for(auto it : adj[curr]){
                if(!visited[it]){
                    visited[it]=true;
                    q.push(it);
                }
            }
        }
        cout<<endl;
    }


    void dfs(int start){
        cout << "\nDFS from " << landmarks[start] << ":\n";
        vector<bool> visited(adj.size(),false);
        stack<int> s;
        s.push(start);

        while(!s.empty()){
            int curr=s.top();
            s.pop();
            if(!visited[curr]){
                visited[curr]=true;
                cout<<landmarks[curr]<<" ";
            }
            for(auto it : adj[curr]){
                if(!visited[it]){
                    s.push(it);
                }
            }
        }
        cout<<endl;

    }

    void display(){
        for (auto pair : landmarks) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }


};


int main(){
    Graph g;
    g.addEdge(0, 1); 
    g.addEdge(1, 2); 
    g.addEdge(1, 3); 
    g.addEdge(2, 4); 
    g.addEdge(3, 5); 
    g.display();
    g.show();

    int start;
    cout << "\nEnter starting point (number) for DFS and BFS: ";
    cin >> start;

    g.dfs(start);
    g.bfs(start);

    return 0;
}