#include<bits/stdc++.h>
using namespace std;


struct Node{
    string key,value;
    Node* next;
    public:
    Node(){
        key=value="";
        next=nullptr;
    }
    Node(string k,string v){
        key=k;
        value=v;
        next=nullptr;
    }

};

class Dictionary{
    vector<Node*>table;

    public:
    Dictionary(){
        table.resize(26,NULL);
    }

    int getHash(string key){
        return tolower(key[0]-'a');
    }

    void insert(string key,string value){
        int hash =getHash(key);
        Node*head=table[hash];
        Node* temp=head;
        while(temp){
            if(temp->key==key){
                cout<<"key already exist"<<endl;
                temp->value=value;
                return;

            }
            temp=temp->next;
        }

        Node * newNode= new Node(key,value);
        newNode->next=head;
        table[hash]=newNode;
        cout<<"inserted!!"<<endl;
        return;
    }

    void del(string key){
        int hash =getHash(key);
        Node*head=table[hash];
        Node* temp=head;
        Node*prev=NULL;
        while(temp){
            if(temp->key==key){
                
                if(prev==NULL){
                    table[hash]=temp->next;
                }else{
                    prev->next=temp->next;
                }
                delete temp;
                cout << "Deleted key: " << key << endl;
                return;

            }
            prev=temp;
            temp=temp->next;
        }
        cout<<"Not found!!"<<endl;
        
    }

    void find(string key){
        int index=getHash(key);
        Node* temp=table[index];
        while(temp){
            if(temp->key==key){
                cout<<"Found :"<<key<<" => "<<temp->value<<endl;
            }
            temp=temp->next;
        }
        cout << "Key not found in dictionary.\n";
    }

    void display(){
        cout << "\n------ Dictionary Contents ------\n";
        for(int i=0;i<26;i++){
            cout<<char('a'+i)<<" -->";
            Node* temp=table[i];
            if(!temp){
                cout<<"NULL";
            }else{
                
                    while (temp) {
                        cout << "[" << temp->key << " : " << temp->value << "] -> ";
                        temp = temp->next;
                }
                cout<<"NULL";
            
            cout << endl;
        }
        cout<<endl;
        
    }
    
}
};

int main() {
    Dictionary dict;
    int choice;
    string key, value;  

    do {
        cout << "\n====== Dictionary ADT Menu ======";
        cout << "\n1. Insert (key, value)";
        cout << "\n2. Delete (key)";
        cout << "\n3. Search (key)";
        cout << "\n4. Display Dictionary";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;

            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.del(key);
                break;

            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                dict.find(key);
                break;

            case 4:
                dict.display();
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
