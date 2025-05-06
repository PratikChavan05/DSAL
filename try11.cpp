#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student{
    
    int rollNo;
    string name;
    string div;
    string address;
    public:
    Student() : rollNo(0), name(""), div(""), address("") {}


    void input(){
        cout<<"Enter roll no: ";
        cin>>rollNo;
        cin.ignore();

        cout<<"Enter name :";
        getline(cin,name);

        cout<<"Enter div :";
        cin>>div;
        cin.ignore();

        cout<<"Enter address: ";
        getline(cin,address);


    }

    int getRoll(){
        return rollNo;
    }


    void display(){
        cout<<"Name :"<<name<<endl;
        cout<<"Roll no :"<<rollNo<<endl;
        cout<<"Division :"<<div<<endl;
        cout<<"Address :"<<address<<endl;

    }

    void writeToFile(ofstream &outFile){
        outFile<<rollNo<<","<<name<<","<<div<<","<<address<<endl;
    }

    bool readFromLine(const string &line){
        size_t p1 = line.find(',');
        size_t p2 = line.find(',',p1+1);
        size_t p3 = line.find(',',p2+1);

        if(p1==string::npos||p2==string::npos||p3==string::npos){
            return false;
        }

        rollNo = stoi(line.substr(0,p1));
        name=line.substr(p1+1,p2-p1-1);
        div=line.substr(p2+1,p3-p2-1);
        address=line.substr(p3+1);
        return true;

    }

    void addRecord(const string&filename){
        ofstream file(filename,ios::app);
        Student s;
        s.input();
        s.writeToFile(file);
        file.close();
    }

    void deleteStudent(string &fileaname , int roll){
        ifstream inFile(fileaname);
        ofstream temp("temp.txt");
        string line;
        bool found = false;

        while(getline(inFile,line)){
            Student s;
            if(s.readFromLine(line)){
                if(s.getRoll()!=roll){
                    temp<<line<<endl;
                }else{
                    found=true;
                }
            }
        }
        inFile.close();
        temp.close();

        remove(fileaname.c_str());
        rename("temp.txt",fileaname.c_str());
    if (found)
        cout << "Record deleted.\n";
    else
        cout << "Record not found.\n";

    }

    void searchStudent(string &filename, int roll){
        ifstream inFile(filename);
        string line;
        bool found =false;
        while(getline(inFile,line)){
            Student s;
            if(s.readFromLine(line)&& s.getRoll()==roll){
                s.display();
                found=true;
                break;
            }
        }
        if (!found) {
            cout << "Record not found.\n";
        }
        inFile.close();
    }

    void displayAll(string &filename){
        ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Student s;
        if (s.readFromLine(line)) {
            s.display();
            cout << "-------------------\n";
        }
    }
    file.close();

    }
};

int main(){
    string filename = "students.txt";
    int choice;
    Student s; // Create a Student object

    do {
        cout << "\n--- Student Record Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Search Student\n";
        cout << "4. Display All\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            s.addRecord(filename);  // Use object to call the function
            break;
        case 2: {
            int roll;
            cout << "Enter roll number to delete: ";
            cin >> roll;
            s.deleteStudent(filename, roll);
            break;
        }
        case 3: {
            int roll;
            cout << "Enter roll number to search: ";
            cin >> roll;
            s.searchStudent(filename, roll);
            break;
        }
        case 4:
            s.displayAll(filename);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}
