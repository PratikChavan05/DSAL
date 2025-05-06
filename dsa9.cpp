#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key, meaning;
    Node* left, *right;
    int height;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    Node* root = nullptr;

    int height(Node* node) {
        if(!node) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if(!node) return 0;
        return height(node->left)-height(node->right);    
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* y) {
        Node* x = y->right;
        Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height =max(height(x->left), height(x->right)) + 1;
        

        return x;
    }

    Node* balanceNode(Node* node, const string& key) {
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, const string& key, const string& meaning) {
        if (!node)
            return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else {
            cout << "Keyword already exists. Use update.\n";
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        return balanceNode(node, key);
    }

    Node* deleteNode(Node* node, const string& key) {
        if (!node)
            return nullptr;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* succ = node->right;
            while(succ->left){
                succ=succ->left;
            }

            node->key=succ->key;
            node->meaning=succ->meaning;
            node->right=deleteNode(node->right,succ->key);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        return balanceNode(node, key);
    }

    void display(Node* node, bool ascending) {
        if (!node) return;

        if (ascending) {
            display(node->left, ascending);
            cout << node->key << " : " << node->meaning << '\n';
            display(node->right, ascending);
        } else {
            display(node->right, ascending);
            cout << node->key << " : " << node->meaning << '\n';
            display(node->left, ascending);
        }
    }

    Node* search(Node* node, const string& key, int& comparisons) {
        if (!node) return nullptr;

        comparisons++;
        if (key == node->key)
            return node;
        else if (key < node->key)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

    void updateMeaning(Node* node, const string& key, const string& newMeaning) {
        if (!node) {
            cout << "Keyword not found.\n";
            return;
        }

        if (key == node->key)
            node->meaning = newMeaning;
        else if (key < node->key)
            updateMeaning(node->left, key, newMeaning);
        else
            updateMeaning(node->right, key, newMeaning);
    }

public:
    void insert(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    void remove(const string& key) {
        root = deleteNode(root, key);
    }

    void displayAscending() {
        cout << "\n--- Ascending Order ---\n";
        display(root, true);
    }

    void displayDescending() {
        cout << "\n--- Descending Order ---\n";
        display(root, false);
    }

    void searchKey(const string& key) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);

        if (result)
            cout << "Found: " << result->key << " = " << result->meaning << " (Comparisons: " << comparisons << ")\n";
        else
            cout << "Not found. (Comparisons: " << comparisons << ")\n";
    }

    void update(const string& key, const string& newMeaning) {
        updateMeaning(root, key, newMeaning);
    }

    void maxComparisons() {
        cout << "Maximum comparisons (tree height): " << height(root) << '\n';
    }
};

int main() {
    AVL dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Update\n4. Display Ascending\n5. Display Descending\n";
        cout << "6. Search\n7. Max Comparisons\n8. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.insert(key, meaning);
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.remove(key);
                break;

            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.update(key, meaning);
                break;

            case 4:
                dict.displayAscending();
                break;

            case 5:
                dict.displayDescending();
                break;

            case 6:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dict.searchKey(key);
                break;

            case 7:
                dict.maxComparisons();
                break;

            case 8:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
