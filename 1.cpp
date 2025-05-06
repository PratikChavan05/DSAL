#include <iostream>
#include <stack>
using namespace std;

class Node {
    int data;
    Node *left, *right;
    friend class Tree;

public:
    Node(int val=0){
        data=val;
        left=NULL;
        right=NULL;
    }
};

class Tree {
    Node *root;

public:
    Tree() : root(NULL) {}

    void setRoot(Node *node) { root = node; }
    Node *getRoot() const { return root; }

    Node *create() {
        int val;
        cout << "Enter data: ";
        cin >> val;
        Node *node = new Node(val);

        char choice;
        cout << "Add left child of " << val << "? (y/n): ";
        cin >> choice;
        if (choice == 'y') node->left = create();

        cout << "Add right child of " << val << "? (y/n): ";
        cin >> choice;
        if (choice == 'y') node->right = create();

        return node;
    }

    // Recursive Traversals
    void inorder(Node *node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node *node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node *node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    // Non-Recursive Traversals
    void inorderIterative(Node *node) {
        stack<Node *> s;
        while (node || !s.empty()) {
            while (node) {
                s.push(node);
                node = node->left;
            }
            node = s.top(); s.pop();
            cout << node->data << " ";
            node = node->right;
        }
    }

    void preorderIterative(Node *node) {
        stack<Node *> s;
        while (node || !s.empty()) {
            while (node) {
                cout << node->data << " ";
                if (node->right) s.push(node->right);
                node = node->left;
            }
            if (!s.empty()) {
                node = s.top(); s.pop();
            }
        }
    }

    void postorderIterative(Node* root) {
        if (root == NULL) return;
    
        stack<Node*> s1, s2;
        s1.push(root);
    
        while (!s1.empty()) {
            Node* node = s1.top();
            s1.pop();
            s2.push(node);
    
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }
    
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }
    

    // Mirror Tree
    void mirror(Node *node) {
        if (node) {
            swap(node->left, node->right);
            mirror(node->left);
            mirror(node->right);
        }
    }

    // Tree Height
    int height(Node *node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Count Nodes
    void count(Node *node, int &total, int &leaf) {
        if (node) {
            total++;
            if (!node->left && !node->right) {
                leaf++;
                return;
            }
            count(node->left, total, leaf);
            count(node->right, total, leaf);
        }
    }

    // Copy Tree
    Node *copy(Node *node) {
        if (!node) return NULL;
        Node *newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void operator=(Tree &t) {
        root = copy(t.root);
    }

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
