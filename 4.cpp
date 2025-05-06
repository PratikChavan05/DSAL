#include <bits/stdc++.h>
using namespace std;

#define SIZE 10

class Contact {
public:
    string name;
    long int number;

    Contact() {
        name = "";
        number = 0;
    }

    Contact(string name, long int number) {
        this->name = name;
        this->number = number;
    }

    friend class HashMap;
};

class HashMap {
private:
    Contact* table;

public:
    HashMap() {
        table = new Contact[SIZE];
    }

    int getHash(long int num) {
        return num % SIZE;
    }

    void insert_without_replacement(long int number, string name) {
        int hash = getHash(number);
        int attempts = 0;

        while (table[hash].name != "" && table[hash].number != 0 && attempts < SIZE) {
            hash = (hash + 1) % SIZE;
            attempts++;
        }

        if (attempts == SIZE) {
            cout << "Hash table full! Cannot insert." << endl;
            return;
        }

        table[hash].name = name;
        table[hash].number = number;
        cout << "Inserted successfully (without replacement)!" << endl;
    }

    void insert_with_replacement(long int number,string name){
        int hash=getHash(number);
        int temp = hash;

        if(table[hash].name==""&&table[hash].number==0){
            table[hash].name=name;
            table[hash].number=number;
            cout<<"Inserted Successfully!!"<<endl;
        }else{
            while(table[temp].name!=""&&table[temp].number!=0){
                temp=(temp+1)%SIZE;
            }
            table[temp].name=table[hash].name;
            table[temp].number=table[hash].number;
            table[hash].name=name;
            table[hash].number=number;
            cout<<"Inserted Successfully!!"<<endl;
        }
    }
    void search(long int number) {
        int hash = getHash(number);
        int count = 0;

        for (int i = 0; i < SIZE; i++) {
            if (table[hash].number == number) {
                cout << "Found → " << table[hash].name << " : " << table[hash].number << endl;
                cout << "Probes: " << count << endl;
                return;
            }
            hash = (hash + 1) % SIZE;
            count++;
        }

        cout << "Not found." << endl;
    }

    void remove(long int number) {
        int hash = getHash(number);

        for (int i = 0; i < SIZE; i++) {
            if (table[hash].number == number) {
                table[hash].name = "";
                table[hash].number = 0;
                cout << "Removed successfully!" << endl;
                return;
            }
            hash = (hash + 1) % SIZE;
        }

        cout << "Number not found." << endl;
    }

    void display() {
        cout << "\n----- Hash Table -----" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << i << " --> ";
            if (table[i].name != "")
                cout << table[i].name << " : " << table[i].number << endl;
            else
                cout << "[Empty]" << endl;
        }
    }
};

int main() {
    HashMap withReplacement;
    HashMap withoutReplacement;

    cout << "\n========== Main Menu ==========" << endl;
    cout << "1. Insert/Search/Delete (With Replacement)" << endl;
    cout << "2. Insert/Search/Delete (Without Replacement)" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        while (true) {
            cout << "\n----- With Replacement Menu -----" << endl;
            cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Exit" << endl;
            int ch;
            cout << "Enter your choice: ";
            cin >> ch;

            if (ch == 1) {
                string name;
                long int number;
                cout << "Enter name and number: ";
                cin >> name >> number;
                withReplacement.insert_with_replacement(number, name);
            } else if (ch == 2) {
                long int number;
                cout << "Enter number to search: ";
                cin >> number;
                withReplacement.search(number);
            } else if (ch == 3) {
                long int number;
                cout << "Enter number to remove: ";
                cin >> number;
                withReplacement.remove(number);
            } else if (ch == 4) {
                withReplacement.display();
            } else if (ch == 5) {
                break;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    } else if (choice == 2) {
        while (true) {
            cout << "\n----- Without Replacement Menu -----" << endl;
            cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Exit" << endl;
            int ch;
            cout << "Enter your choice: ";
            cin >> ch;

            if (ch == 1) {
                string name;
                long int number;
                cout << "Enter name and number: ";
                cin >> name >> number;
                withoutReplacement.insert_without_replacement(number, name);
            } else if (ch == 2) {
                long int number;
                cout << "Enter number to search: ";
                cin >> number;
                withoutReplacement.search(number);
            } else if (ch == 3) {
                long int number;
                cout << "Enter number to remove: ";
                cin >> number;
                withoutReplacement.remove(number);
            } else if (ch == 4) {
                withoutReplacement.display();
            } else if (ch == 5) {
                break;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    } else {
        cout << "Invalid main choice." << endl;
    }

    return 0;
}
