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
        for(auto it: adj){
            cout<<landmarks[it.first]<<"-->";
            for(auto it2:it.second){
                cout<<landmarks[it2]<<",";
            }
            cout<<endl;
        }
    }

    void bfs(int s){
        vector<bool> visited(adj.size(), false);
        queue<int> q;

        visited[s]=true;
        q.push(s);
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            cout<<landmarks[curr]<<" ";

            for(auto it:adj[curr]){
                if(!visited[it]){
                    visited[it]=true;
                    q.push(it);
                }
            }
        }
        cout<<endl;

    }

    void dfs(int s){
        vector<bool> visited (adj.size(),false);
        stack<int> st;
        st.push(s);

        while(!st.empty()){
            int curr = st.top();
            st.pop();

            if(!visited[curr]){
                visited[curr]=true;
                cout<<landmarks[curr]<<" ";
            }

            for(auto it: adj[curr]){
                if(!visited[it]){
                    st.push(it);
                }
            }
        }
        cout<<endl;
    }

    void display(){
        for(auto it:landmarks){
            cout<<it.first<<":"<<it.second<<endl;
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