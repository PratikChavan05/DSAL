#include<bits/stdc++.h>
using namespace std;

class Node{
    int data;
    Node* left,*right;
    friend class Tree;

    public:
    Node(int val){
        data=val;
        left=right=nullptr;
    }
};

class Tree{
    Node* root ;
    public:
    Tree(){
        root = NULL;

    }

    void setRoot(Node*node){
        root=node;
    }

    Node* getRoot(){
        return root;
    }

    Node* create(){
        int val;
        cout<<"enter value of node :";
        cin>>val;
        Node* root = new Node(val);
        cout<<"do you want to add node to left of "<<val<<" ?(y/n)"<<endl;
        char ch;
        cin>>ch;
        if(ch=='y'){
            root->left=create();
        }
        cout<<"do you want to add node to right of "<<val<<" ?(y/n)"<<endl;
        ;
        cin>>ch;
        if(ch=='y'){
            root->right=create();
        }

        return root;
    }

    void inorder(Node * node){
        if(node){
            inorder(node->left);
            cout<<node->data<<" ";
            inorder(node->right);

        }
    }
    void preorder(Node * node){
        if(node){
            cout<<node->data<<" ";
            preorder(node->left);
            preorder(node->right);

        }
    }
    void postorder(Node * node){
        if(node){
            postorder(node->left);
            postorder(node->right);
            cout<<node->data<<" ";

        }
    }

    void inorderIterative(Node* node){
        stack<Node*> s;
        while(node||!s.empty()){
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

                if(node->right) s.push(node->right);
                node=node->left;
            }

            if(!s.empty()){
                node=s.top();
                s.pop();
            }
         
        }
    }\

    void postorderIterative(Node* node){
        stack<Node*> s1,s2;
        if(!node) return;
        s1.push(node);
        while(!s1.empty()){
            Node * temp=s1.top();
            s1.pop();
            s2.push(temp);

            if(temp->left) s1.push(temp->left);
            if(temp->right) s1.push(temp->right);
        }

        while(!s2.empty()){
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
    }

    void mirror(Node* node){
        if(node){
            swap(node->left,node->right);
            mirror(node->left);
            mirror(node->right);
        }
    }

    int height(Node * node){
        if(!node) return 0;
        return 1+max(height(node->left),height(node->right));
    }

    void count(Node * node, int &total,int &leaf){
        if(node){
            total++;
            if(!node->left && !node->right){
                leaf++;
                return;
            }
            count(node->left,total,leaf);
            count(node->right,total,leaf);

        }
       
    }

    Node* copy(Node * node){
        if(!node) return NULL;
        Node* newNode= new Node(node->data);
        newNode->left=copy(node->left);
        newNode->right=copy(node->right);
        return newNode;

    }
    void operator=(Tree &t) {
        root = copy(t.root);
    }

    // void operator=(Tree &t){
    //     root=copy(t.root);
    // }

    // Delete Tree
    void erase(Node *node) {
        if (node) {
            erase(node->left);
            erase(node->right);
            delete node;
        }
    }

    void eraseTree() {
        erase(root);
        root = NULL;
    }
// Menu Functions
void displayRecursive() {
    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
}

void displayIterative() {
    cout << "Inorder: "; inorderIterative(root); cout << endl;
    cout << "Preorder: "; preorderIterative(root); cout << endl;
    cout << "Postorder: "; postorderIterative(root); cout << endl;
}
};

int main() {
Tree tree;

while (true) {
    cout << "\n---- Menu ----\n";
    cout << "1. Create Tree\n";
    cout << "2. Recursive Traversals\n";
    cout << "3. Non-Recursive Traversals\n";
    cout << "4. Mirror Tree\n";
    cout << "5. Tree Height\n";
    cout << "6. Count Nodes\n";
    cout << "7. Copy Tree\n";
    cout << "8. Erase Tree\n";
    cout << "9. Exit\n";

    int choice;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            tree.setRoot(tree.create());
            cout << "Tree Created!\n";
            break;
        case 2:
            tree.displayRecursive();
            break;
        case 3:
            tree.displayIterative();
            break;
        case 4:
            tree.mirror(tree.getRoot());
            cout << "Tree Mirrored. Inorder: ";
            tree.inorder(tree.getRoot());
            cout << endl;
            break;
        case 5:
            cout << "Height: " << tree.height(tree.getRoot()) << endl;
            break;
        case 6: {
            int total = 0, leaf = 0;
            tree.count(tree.getRoot(), total, leaf);
            cout << "Total Nodes: " << total << "\nInternal Nodes: " << total - leaf << "\nLeaf Nodes: " << leaf << endl;
            break;
        }
        case 7: {
            Tree copied;
            copied = tree;
            cout << "Copied Tree Inorder: ";
            copied.inorder(copied.getRoot());
            cout << endl;
            break;
        }
        case 8:
            tree.eraseTree();
            cout << "Tree Erased!\n";
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice.\n";
    }
}
}
