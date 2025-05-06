#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student{
    int roll;
    string name,div,address;
    public:
    Student(){
        roll=0;
        name=div=address="";
    }

    void insert(){
        cout<<"enter roll :";
        cin>>roll;
        cin.ignore();
        cout<<"enter name :";
        getline(cin,name);
        
        cout<<"enter div :";
        cin>>div;
        cin.ignore();
        
        cout<<"enter address :";
        getline(cin,address);

    }

    void display(){
        cout<<"Roll no:"<<roll<<endl;
        cout<<"Name:"<<name<<endl;
        cout<<"div:"<<div<<endl;
        cout<<"address:"<<address<<endl;
    }

    int getRoll(){
        return roll;
    }

    void writeToFile(ofstream &outFile){
        outFile<<roll<<","<<name<<","<<div<<","<<address<<endl;
    }

    bool readFromFile(const string &line){
        size_t p1 = line.find(',');
        size_t p2 = line.find(',',p1+1);
        size_t p3 = line.find(',',p2+1);

        if(p1==string::npos||p2==string::npos||p3==string::npos){
            return false;
        }

        roll = stoi(line.substr(0,p1));
        name = (line.substr(p1+1,p2-p1-1));
        div = (line.substr(p2+1,p3-p2-1));
        address = (line.substr(p3+1));
        return true;

    }

    void addRecord(const string &filename){
        ofstream file(filename,ios::app);
        Student s;
        s.insert();
        s.writeToFile(file);
        file.close();
    }

    void deleteRecord(const string &filename,int roll){
        
        ofstream temp("temp.txt");
        ifstream file(filename);
        string line ;
        bool found = false;

        while(getline(file,line)){
            Student s;
            if(s.readFromFile(line)){
                if(roll!=s.getRoll()){
                    temp<<line<<endl;
            }else{
                found=true;
            }
        }
        }
        temp.close();
        file.close();

        remove(filename.c_str());
        rename("temp.txt",filename.c_str());

        if (found)
        cout << "Record deleted.\n";
        else
        cout << "Record not found.\n";

    }

    void search(const string& filename,int roll){
        ifstream file(filename);
        string line;
        bool found =false;

        while(getline(file,line)){
            Student s;
            if(s.readFromFile(line)&&roll==s.getRoll()){
                s.display();
                found=true;
                break;
            }
        }
        if (found)
        cout << "Record found.\n";
        else
        cout << "Record not found.\n";
        file.close();
    }

    void displayAll(const string& filename){
        ifstream file(filename);
        string line;
        while(getline(file,line)){
            Student s;
           if(s.readFromFile(line)){
            s.display();
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
            s.deleteRecord(filename, roll);
            break;
        }
        case 3: {
            int roll;
            cout << "Enter roll number to search: ";
            cin >> roll;
            s.search(filename, roll);
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
