#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student{
    public:
    int roll;
    string name,div, address;

    Student(){
        roll=0;
        name=div=address="";

    }

    void setData(){
        cout<<"enter roll no:";
        cin>>roll;
        cin.ignore();
        cout<<"enter name:";
        getline(cin,name);
        cout<<"enter div";
        cin>>div;
        cin.ignore();
        cout<<"enter address:";
        getline(cin,address);
    }

    void display(){
        cout<<"Roll :"<<roll<<endl;
        cout<<"Name :"<<name<<endl;
        cout<<"Div :"<<div<<endl;
        cout<<"address :"<<address<<endl;
        cout<<"----------------------"<<endl;
    }

    int getRoll (){
        return roll;
    }


    void writeToFile(ofstream &filename){
        filename<<roll<<","<<name<<","<<div<<","<<address<<endl;
    }

    bool readFromLine(const string&line){
        size_t p1 = line.find(',');
        size_t p2 = line.find(',',p1+1);
        size_t p3 = line.find(',',p2+1);

        if(p1==string::npos||p2==string::npos||p3==string::npos){
            return false;
        }

        roll = stoi(line.substr(0,p1));
        name=line.substr(p1+1,p2-p1-1);
        div=line.substr(p2+1,p3-p2-1);
        address=line.substr(p3+1);
        return true;
    }

    void insert(const string &filename){
        Student s;
        s.setData();
        ofstream file(filename,ios::app);
        s.writeToFile(file);
        file.close();
    }

    void delRecord(const string&filename){
        cout<<"enter roll no :";
        int roll;
        cin>>roll;
        ofstream temp("temp.txt");
        ifstream file(filename);
        bool found =false;
        string line;
        while(getline(file,line)){
            Student s;
            if(s.readFromLine(line)){
                if(s.roll!=roll){
                    temp<<line<<endl;
                }else{
                    found =true;
                }
            }
        }

        file.close();
        temp.close();
        remove(filename.c_str());
        rename("temp.txt",filename.c_str());
        if(found){
            cout<<"deleted"<<endl;
        }else{
            cout<<"not deleted"<<endl;
        }
    }

    void search(const string&filename){
        cout<<"enter roll no :";
        int roll;
        cin>>roll;
        ifstream file(filename);
        bool found =false;
        string line;
        while(getline(file,line)){
            Student s;
            if(s.readFromLine(line)&&s.roll==roll){
                s.display();
                found=true;
                break;
            }
        }
        if(found){
            cout<<"found"<<endl;
        }else{
            cout<<"not found"<<endl;
        }
    }
    void displayAll(const string&filename){
        
        ifstream file(filename);
        bool found =false;
        string line;
        while(getline(file,line)){
            Student s;
            if(s.readFromLine(line)){
                s.display();
                found=true;
            }
        }
        if(found){
            cout<<"found"<<endl;
        }else{
            cout<<"not found"<<endl;
        }
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
            s.insert(filename);  // Use object to call the function
            break;
        case 2: {
            int roll;
            cout << "Enter roll number to delete: ";
            cin >> roll;
            s.delRecord(filename);
            break;
        }
        case 3: {
            int roll;
            cout << "Enter roll number to search: ";
            cin >> roll;
            s.search(filename);
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
