#include<iostream>
#include<stack>
using namespace std;

class Node{
    int data;
    Node* left, *right;
    friend class Tree;
    public:
        Node(int val){
            data=val;
            right=NULL;
            left=NULL;

        }

};


class Tree{
    Node* root;
    public:
    Tree(){
        root=NULL;
    }

    void setRoot(Node* node){
        root = node;
    }
    Node* getRoot(){
        return  root;
    }

    Node * create(){
        int val;
        cout << "Enter data: ";
        cin >> val;
        Node *node=new Node(val);
        char choice;
        cout << "Add left child of " << val << "? (y/n): ";
        cin>>choice;
        if(choice=='y'){
            node->left=create();
        }
        cout << "Add Right child of " << val << "? (y/n): ";
        cin>>choice;
        if(choice=='y'){
            node->right=create();
        }

        return node;

    }


    void inorder(Node* node){
        if(node){
            inorder(node->left);
            cout<<node->data<<" ";
            inorder(node->right);
        }
    }

    void preorder(Node* node){
        if(node){
            cout<<node->data<<" ";
            inorder(node->left);
            inorder(node->right);
        }
    }

    void postorder(Node* node){
        if(node){
            inorder(node->left);
            inorder(node->right);
            cout<<node->data<<" ";

        }
    }


    void inorderIterative(Node * node){
        stack<Node*>s;
        while(node ||!s.empty()){
            while(node){
                s.push(node);
                node=node->left;
            }

            node=s.top();
            s.pop();
            cout<<node->data<<" ";
            node=node->right;
        }
    }

    void preorderIterative(Node* node){
        stack<Node*> s;
        while(node||!s.empty()){
            while(node){
                cout<<node->data<<" ";
                if(node->right){
                    s.push(node->right);

                }
                node=node->left;
            }
            if(!s.empty()){
                node=s.top();
                s.pop();
            }
        }
    }

    void postorderIterative(Node* node){
        if(root ==NULL) return;

        stack<Node*> s1,s2;
        s1.push(root);
        while(!s1.empty()){
            Node* node=s1.top();
            s1.pop();
            s2.push(node);
            if(node->left) s1.push(node->left);
            if(node->right) s1.push(node->right);
        }
        while(!s2.empty()){
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
    }

    void mirror (Node* node){
        if(node){
            swap(node->left,node->right);
            mirror(node->left);
            mirror(node->right);
        }
    
    }

    int height(Node*node){
        if(!node)return 0;
        return 1+max(height(node->left),height(node->right));
    }

    void count(Node*node,int &total,int &leaf){
        if(node){
            total++;
            if(!node->left&&!node->right){
                leaf++;
                return;
            }
            count(node->left,total,leaf);
            count(node->right,total,leaf);
        }
    }

    Node* copy(Node* node){
        if(!node)return NULL;
        Node *node=new Node(node->data);
        node->left=copy(node->left);
        node->right=copy(node->right);
        return node;

    }

    void operator=(Tree &t){
        root = copy(t.root);
    };

    void erase(Node* node){
        if(node){
            erase(node->left);
            erase(node->right);
            delete node;

        }
    }

    void eraseTree(){
        erase(root);
        root=NULL;
    }

};

int main(){
    return 0;
}