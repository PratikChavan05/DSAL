#include<iostream>
using namespace std;

class Node{
    public:
    Node *next;
    int data;
public:
    Node(int d){
        data=d;
        next=nullptr;
    }
};

class Linkedlist{
    public:
    Node* head;
    Linkedlist(){
        head=nullptr;
    }

    void append(int val){
        Node *newNode=new Node(val);
        if(!head){
            head=newNode;
            return;
        }
        Node *temp=head;
        while ((temp->next!=nullptr))
        {
            temp=temp->next;
        }
        temp->next=newNode;
    }

    void display(){
        if(head==nullptr){
            return;
        }
        Node *temp=head;
        while(temp!=nullptr){
            cout<<temp->data<<"->";
            temp=temp->next;
        }
        cout<<endl;
    }
};

class Graph{
    Node** adjlist;
    int vertices;
    public:
    Graph(int v){
        vertices=v;
        adjlist=new Node*[v];
        for(int i=0;i<v;i++){
            adjlist[i]=nullptr;
        }
    }

    void addEdge(int src,int dest){
        Node* newNode=new Node(dest);
        newNode->next=adjlist[src];
        adjlist[src]=newNode;

        newNode=new Node(src);
        newNode->next=adjlist[dest];
        adjlist[dest]=newNode;
    }

    void display(){
        for(int i=0;i<vertices;i++){
            cout<<i<<": ";
            Node *temp=adjlist[i];
            while(temp){
                cout<<temp->data<<" ";
                temp=temp->next;

            }
            cout<<endl;
        }
    }

    void bfs(int start){
        bool* visited=new bool[vertices]{false};
        Linkedlist queue;
        queue.append(start);
        while(queue.head){
            int node=queue.head->data;
            queue.head=queue.head->next;
            if(!visited[node]){
                cout<<node<<" ";
                visited[node]=true;
                Node *temp=adjlist[node];
                while(temp){
                    if(!visited[temp->data]){
                        queue.append(temp->data);
                    }
                    temp=temp->next;
                }
            }
        }

    }

    void dfsUtil(int node,bool visited[]){
        visited[node]=true;
        cout<<node<<" ";
        Node *temp=adjlist[node];
        while(temp){
            if(!visited[temp->data]){
                dfsUtil(temp->data,visited);
            }
            temp=temp->next;
        }

    }

    void dfs(int start){
        bool *visited=new bool[vertices]{false};
        dfsUtil(start,visited);
        delete visited;
    }
};
int main() {
	int n,x,y;
	cout<<"Enter number of nodes: ";
	cin>>n;
	cout<<endl;
	Graph g(n);
	for(int i=0;i<n;i++){
		cout<<"Enter source: ";
		cin>>x;
		cout<<endl;
		cout<<"Enter destination: ";
		cin>>y;
		cout<<endl;
		g.addEdge(x,y);
	}
	g.display();
	cout<<"BFS Traversal: ";
	g.bfs(0);
	cout<<endl;
	cout<<"DFS Traversal: ";
	g.dfs(0);

	return 0;
}