#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Student{
    public:
    int roll, marks;
    char name[30];

    Student(){
        roll=marks=0;
        strcpy(name,"NULL");

    }

    void setData(){
        cout<<"enter roll no:";
        cin>>roll;
        cin.ignore();
        cout<<"enter the name:";
        cin.getline(name,30);
        cout<<"enter the marks:";
        cin>>marks;


    }

    void showData(){
        if(roll!=0){
            cout<<"roll:"<<roll<<endl;
            cout<<"name:"<<name<<endl;
            cout<<"marks:"<<marks<<endl;
            cout<<"----------------------"<<endl;

        }
    }

    
};

void insert(const string & fname){
    Student s;
    s.setData();
    fstream file(fname,ios::in|ios::out|ios::binary);
    if(!file){
        file.open(fname,ios::out|ios::binary);
        file.close();
        file.open(fname,ios::in|ios::out|ios::binary);
    }

    int pos = (s.roll-1)*sizeof(Student);
    file.seekp(pos);
    file.write((char*)&s,sizeof(Student));
    file.close();

}

void del(const string & fname){
    int roll;
    cout<<"enter roll to delete:";
    cin>>roll;

    Student s;
    fstream file(fname,ios::in|ios::out|ios::binary);
    if(!file){
       cout<<"not found"<<endl;
       return;
    }

    int pos = (roll-1)*sizeof(Student);
    file.seekp(pos);
    file.write((char*)&s,sizeof(Student));
    file.close();

}

void display(const string& fname){
    ifstream file(fname, ios::binary);
    Student s;
    bool found = false;
    while(file.read((char*)&s,sizeof(Student))){
        if(s.roll!=0){
            s.showData();
            found=true;
        }
    }

    if(!found){
        cout<<"Not found"<<endl;
    }
}


int main(){
    const char* filename = "students1.txt";
    int ch;
    
    do{
        cout<<"1.insert"<<endl;
        cout<<"2.delete"<<endl;
        cout<<"3.display"<<endl;
        cout<<"4.exit"<<endl;
        cout<<"enter choice";
        cin>>ch;
        switch(ch){
            case 1:
                insert(filename);
                break;
            case 2:
                del(filename);
                break;
            case 3:
                display(filename);
                break;
            case 4:
                cout<<"-------";
                break;
            default:
                cout<<"-------";
                break;


        }
    }while(ch!=4);
    return 0;
}
