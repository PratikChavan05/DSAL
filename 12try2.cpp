#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Student{
    public:
    int roll;
    char name[30];
    int marks;
    

    
        Student(){
            roll=marks=0;
            strcpy(name,"NULL");

        }

        void setData() {
            cout << "Enter Roll No: ";
            cin >> roll;
            cin.ignore();
            cout << "Enter Name: ";
            cin.getline(name, 30);
            cout << "Enter Marks: ";
            cin >> marks;
        }
    
        void showData() {
            if (roll != 0) {
                cout << "Roll: " << roll << ", Name: " << name << ", Marks: " << marks << "\n";
            }
        }
    
};

void insertRecord(const char* fname){
    Student s;
    s.setData();
    fstream file(fname,ios::in|ios::out|ios::binary);
    if(!file){
        file.open(fname,ios::out|ios::binary);
        file.close();
        file.open(fname,ios::in|ios::out|ios::binary);
    }

    int pos =(s.roll-1)*sizeof(Student);
    file.seekp(pos);
    file.write((char*)&s,sizeof(Student));
    file.close();

}

void deleteRecord(const char* fname){
    Student empty;
    cout<<"enter roll number to delete:";
    int roll;
    cin>>roll;
    fstream file(fname,ios::in|ios::out|ios::binary);
    if(!file){
        file.open(fname,ios::out|ios::binary);
        file.close();
        file.open(fname,ios::in|ios::out|ios::binary);
    }
    int pos = (roll-1)*sizeof(Student);
    file.seekp(pos);
    file.write((char*)&empty,sizeof(Student));
    file.close();

}


void display(const char* fname){
    ifstream file(fname,ios::binary);
    if(!file){
        cout<<"file not found"<<endl;
        return;
    }
    Student s;
    bool found =false;

    while(file.read((char*)&s,sizeof(Student))){
        if(s.roll!=0){
            s.showData();
            found=true;
        }

    }
    if (!found) {
        cout << "No records to display.\n";
    }

    file.close();
}


int main() {
    const char* filename = "st.txt";
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Record\n2. Delete Record\n3. Display Records\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertRecord(filename); break;
            case 2: deleteRecord(filename); break;
            case 3: display(filename); break;
            case 4: cout << "Exiting.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}