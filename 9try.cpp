#include<iostream>
#include<string>
using namespace std;

class Node{
    
    public:
    string word ,value;
    Node* left,*right;
    int height;

    Node(string w,string m){
        word=w;
        value=m;
        right=left=nullptr;
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
        if(node){
            return height(node->left)-height(node->right);
        }  
    }


    Node *rotateRight(Node* y){
        if(!y) return nullptr;
        Node * x= y->left;
        Node* T2= x->right;

        x->right=y;
        y->left=T2;

        y->height=1+max(height(y->left),height(y->right));
        x->height=1+max(height(x->left),height(x->right));

        return x;
    }

    Node * rotateLeft(Node* y){
        if(!y) return nullptr;
        Node* x=y->right;
        Node *T2=x->left;

        x->left=y;
        y->right=T2;

        y->height=1+max(height(y->left),height(y->right));
        x->height=1+max(height(x->left),height(x->right));

        return x;
    }

    Node* balanceNode(Node* node,const string& word){
        if(!node) return nullptr;
        int balance =getBalance(node);
        if(balance>1 && word<node->left->word){
            return rotateRight(node);
        }
        if(balance<-1&&word>node->right->word){
            return rotateLeft(node);
        }
        if(balance>1 && word>node->left->word){
            node->left=rotateLeft(node->left);
            return rotateRight(node);
        }
        if(balance<-1 && word<node->right->word){
            node->right=rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, const string& word,const string& value){
        if(!node) return new Node(word,value);

        if(word<node->word){
            node->left=insert(node->left,word,value);
        }
        else if(word>node->word){
            node->right=insert(node->right,word,value);
        }else{
            cout<<"already exist"<<endl;
            return node;
        }
        node->height= 1+max(height(node->left),height(node->right));

        return balanceNode(node,word);
    }

    Node * deleteWord(Node* node,const string&word){
        if(!node) return nullptr;

        if(word<node->word){
            node->left=deleteWord(node->left,word);
        }else if(word>node->word){
            node->right=deleteWord(node->right,word);
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

            Node * succ=node->right;
            while(succ->left){
                succ=succ->left;
            }

            node->word=succ->word;
            node->value=succ->value;
            node->right=deleteWord(node->right,succ->word);
        }
            node->height = 1 + max(height(node->left), height(node->right));
            return balanceNode(node, word);

        
    }

    void display(Node* node,bool asc){
        if(!node) return;

        if(asc){
            display(node->left,asc);
            cout<<node->word<<" : "<<node->value<<endl;
            display(node->right,asc);
        }else{
            display(node->right,asc);
            cout<<node->word<<" : "<<node->value<<endl;
            display(node->left,asc);

        }
    }

    Node * search(Node* node,const string& word){
        if(!node) return nullptr;
        if(word==node->word){
            return node;
        }else if(word < node->word ){
            return search(node->left,word);
        }else if(word>node->word){
            return search(node->right ,word);
        }else{
            cout<<"not found";
            return nullptr;
        }
    }

    void updateMeaning(Node * node,const string& word,const string&meaning){
        if(!node) return;
        if(word==node->word){
            node->value=meaning;
        }else if(word<node->word){
            updateMeaning (node->left,word,meaning);
        }else{
            updateMeaning(node->right,word,meaning);
        }
    }
    public:

    void insert(const string& word,const string & value){
        root=insert(root,word,value);
    }

    void remove(const string& key) {
        root = deleteWord(root, key);
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
        Node* result = search(root, key);

        if (result)
            cout << "Found: " << result->word << " = " << result->value<< " (Comparisons: " << comparisons << ")\n";
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

