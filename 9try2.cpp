#include<iostream>
#include<string>
using namespace std;

class Node{
    public:
    string key,value;
    Node* left,*right;
    int height;

    Node(string k,string v){
        key=k;
        value=v;
        left=right=nullptr;
        height=1;
    }
};

class AVL{
    public:
    Node* root;

    AVL(){
        root=NULL;
    }

    int height(Node* node){
        if(!node) return 0;
        return node->height;
    }

    int getBalance(Node* node){
        if(!node) return 0;
        return height(node->left)-height(node->right);
    }

    Node* rotateRight(Node* y){
        Node* x= y->left;
        Node* T2= x->right;

        x->right=y;
        y->left=T2;

        y->height=1+max(height(y->left),height(y->right));
        x->height=1+max(height(x->left),height(x->right));

        return x;
    }
    Node* rotateLeft(Node* y){
        Node* x= y->right;
        Node* T2= x->left;

        x->left=y;
        y->right=T2;

        y->height=1+max(height(y->left),height(y->right));
        x->height=1+max(height(x->left),height(x->right));

        return x;
    }

    Node* balanceNode(Node*node,string key){
        if(!node) return nullptr;

        int balance = getBalance(node);

        if(balance>1&&key<node->left->key){
            return rotateRight(node);
        }
        if(balance<-1&&key>node->right->key){
            return rotateLeft(node);
        }
        if(balance>1&&key>node->left->key){
            node->left=rotateLeft(node->left);
            return rotateRight(node);
        }
        if(balance<-1&&key<node->left->key){
            node->right=rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;


    }

    Node* insert(Node* node, string key , string value){
        if(!node) return new Node(key,value);

        if(key<node->key){
            node->left=insert(node->left,key,value);
        }else if(key>node->key){
            node->right=insert(node->right,key,value);
        }else{
            cout<<"Already exixted!!"<<endl;
            return node;        
        }
        node->height=1+max(height(node->left),height(node->right));
        return balanceNode(node,key);

    }

    Node* del(Node* node,string key){
        if(!node) return nullptr;
        if(key<node->key){
            node->left=del(node->left,key);
        }else if(key>node->key){
            node->right=del(node->right,key);
        }else{
            if(!node->left){
                Node* temp=node->right;
                delete node;
                return temp;
            }
            if(!node->right){
                Node* temp=node->left;
                delete node;
                return temp;
            }

            Node * succ= node->right;
            while(succ->left){
                succ=succ->left;
            }

            node->key=succ->key;
            node->value=succ->value;
            node->right=del(node->right,succ->key);
        }
        node->height = 1 + max(height(node->left), height(node->right));
        return balanceNode(node, key);
    }

    void display(Node*node,bool asc){
        if(!node) return;
        if(asc){
            display(node->left,asc);
            cout<<node->key<<":"<<node->value<<" ";
            display(node->right,asc);
        }else{
            display(node->right,asc);
            cout<<node->key<<":"<<node->value<<" ";
            display(node->left,asc);

        }

    }

    Node* search(Node *node,string key){
        if(!node) return nullptr;
        if(key==node->key){
            return node;
        }else if(key<node->key){
            return search(node->left,key);
        }else if(key>node->key){
            return search(node->right,key);
        }else{
            cout<<"not found"<<endl;
            return nullptr;
        }
    }

    Node* update(Node* node,string key,string value){
        if(!node) return nullptr;
        if(key==node->key){
            node->value=value;
            return node;
        }else if(key<node->key){
             return update(node->left,key,value);
        }else if(key>node->key){
             return update(node->right,key,value);
        }else{
            cout<<"not found"<<endl;
            return nullptr;
        }
        

    }

    void insert(string key,string value){
        root=insert(root,key,value);
    }

    void displayAscending(){
        display(root,true);

    }
    void displaydescending(){
        display(root,false);

    }

    void delNode(string key){
        root=del(root,key);
    }

    void searchWord(string key){
        Node* result=search(root,key);
        if(result){
            cout<<result->key<<endl;
        }else{
            cout<<"not found"<<endl;
        }

    }

    void updateM(string key ,string value){
        Node* result=update(root,key,value);
        if(result){
            cout<<result->key<<":"<<result->value<<endl;
        }else{
            cout<<"not found"<<endl;
        }
        
        }

        void maxComparisons() {
            cout << "Maximum comparisons (tree height): " << height(root) << '\n';
        }




};

int main(){
    AVL a;

    a.insert("c","c");
    a.insert("b","b");
    a.insert("A","a");
    a.displayAscending();
    a.searchWord("A");
    a.updateM("A","mean");
    return 0;
}