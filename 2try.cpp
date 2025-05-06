#include<bits/stdc++.h>
using namespace std;

class Node{
    public:

    string word,meaning;
    Node*left,*right;

    Node(string w,string m){
        word=w;
        meaning=m;
        left=right=nullptr;
    }

};

class Dictionary{
    Node*root;

    Node* insert(Node* node, string word ,string meaning )const{
        if(!node) return new Node(word,meaning);
        if(word<node->word){
            node->left=insert(node->left,word,meaning);

        }else if(word>node->word){
            node->right=insert(node->right,word,meaning);
        }else{
            cout<<"word already exist"<<endl;
            
        }

        return node;
    }

    Node * display(Node* node,bool ascending)const{
        if(!node) return nullptr;
        if(ascending){
            node->left=display(node->left,ascending);
            cout<<node->word<<":"<<node->meaning<<endl;
            node->right=display(node->right,ascending);
        }else{
            node->right=display(node->right,ascending);
            cout<<node->word<<":"<<node->meaning<<endl;
            node->left=display(node->left,ascending);
        }

    }

    Node * search(Node* node,string word)const{
        if(!node||node->word==word) return node;

        if(word<node->word){
            return search(node->left,word);
        }else{
            return search(node->right,word);
        }
    }

    Node * deleteWord(Node* node,string word){
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
            else if(!node->right){
                Node* temp=node->left;
                delete node;
                return temp;
            }

            Node* succ = node->right;
            while(succ->left){
                succ=succ->left;
            }

            node->word=succ->word;
            node->meaning=succ->meaning;
            node->right=deleteWord(node->right,succ->word);
        }

        return node;
    }

    public:
        Dictionary(){
            root=nullptr;
        }

        void addWord(){
            string word,meaning;
            cout<<"enter the word:";
            cin>>word;
            cout<<"enter the meaning:";
            cin>>meaning;
            root=insert(root,word,meaning);
        }

        void searchWord(){
            string word;
            cout<<"enter the word to search:";
            cin>>word;
            Node* result=search(root,word);
            if(result){
                cout<<"found-->"<<result->word<<":"<<result->meaning<<endl;

            }else{
                cout<<"no word found"<<endl;
            }
        }

        void updateMeaning(){
            string word;
            cout<<"enter the word to change meaning:";
            cin>>word;
            Node* result=search(root,word);
            if(result){
                cout<<"found-->"<<result->word<<":"<<result->meaning<<endl;
                string meaning;
                cout<<"enter the meaning :";
                cin>>meaning;
                result->meaning=meaning;
                cout<<"Changed to-->"<<result->word<<":"<<result->meaning<<endl;


            }else{
                cout<<"no word found"<<endl;
            }
        }

        void deleteWord(){
            string word;
            cout<<"enter the word to delete:";
            cin>>word;
            deleteWord(root,word);
            cout << "Deleted if found. Updated tree:\n";
            displayTree();

        }

        void displayTree(bool ascending=true){
            display(root,ascending);
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
