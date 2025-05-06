#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string word, meaning;
    Node* left;
    Node* right;

    Node(string w, string m){
        word =w;
        meaning=m;
        left=nullptr;
        right=nullptr;
    }
};


class Dictionary {
    Node* root;

    Node* insert(Node* node, string word, string meaning) {
        if (!node) return new Node(word, meaning);

        if (word < node->word)
            node->left = insert(node->left, word, meaning);
        else if (word > node->word)
            node->right = insert(node->right, word, meaning);
        else
            cout << "Word already exists!\n";

        return node;
    }

    void display(Node* node, bool ascending) const {
        if (!node) return;

        if (ascending) {
            display(node->left, ascending);
            cout << node->word << " : " << node->meaning << endl;
            display(node->right, ascending);
        } else {
            display(node->right, ascending);
            cout << node->word << " : " << node->meaning << endl;
            display(node->left, ascending);
        }
    }

    Node* search(Node* root, string word) const {
        if (!root || root->word == word)
            return root;

        if (word < root->word)
            return search(root->left, word);
        else
           return search(root->right, word);

        
    }

    
    Node* deleteWord(Node* root, string word) {
        if (!root) return nullptr;

        if (word < root->word)
            root->left = deleteWord(root->left, word);
        else if (word > root->word)
            root->right = deleteWord(root->right, word);
        else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* succ = root->right;
            while (succ->left)
                succ = succ->left;

            root->word = succ->word;
            root->meaning = succ->meaning;
            root->right = deleteWord(root->right, succ->word);
        }
        return root;
    }

public:
    Dictionary() : root(nullptr) {}

    void addWord() {
        string word, meaning;
        cout << "Enter word: ";
        cin >> word;
        cout << "Enter meaning: ";
        cin.ignore();
        getline(cin, meaning);
        root = insert(root, word, meaning);
    }

    void searchWord() const {
        string word;
        cout << "Enter word to search: ";
        cin >> word;
        Node* result = search(root, word);
        if (result)
            cout << "Found: " << result->word << " : " << result->meaning << endl;
        else
            cout << "Word not found.\n";
    }

    void updateMeaning() {
        string word;
        cout << "Enter word to update: ";
        cin >> word;
        Node* result = search(root, word);
        if (!result) {
            cout << "Word not found.\n";
            return;
        }
        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, result->meaning);
        cout << "Meaning updated successfully.\n";
    }

    void deleteWord() {
        string word;
        cout << "Enter word to delete: ";
        cin >> word;
        root = deleteWord(root, word);
        cout << "Deleted if found. Updated tree:\n";
        displayTree();
    }

    void displayTree(bool ascending = true) const {
        display(root, ascending);
    }
};

int main() {
    Dictionary dict;
    int choice;

    while (true) {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Add Word\n2. Display Ascending\n3. Display Descending\n";
        cout << "4. Search Word\n5. Update Meaning\n6. Delete Word\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dict.addWord(); break;
            case 2: dict.displayTree(true); break;
            case 3: dict.displayTree(false); break;
            case 4: dict.searchWord(); break;
            case 5: dict.updateMeaning(); break;
            case 6: dict.deleteWord(); break;
            case 7: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
