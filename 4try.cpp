#include<bits/stdc++.h>
using namespace std;
#define size 10

class Contact{
    public:
    string name;
    long int number;

    Contact(){
        name="";
        number=0;
    }
    Contact(string name ,long int number){
        this->name=name;
        this->number=number;
    }

    friend class HashMap;

};

class HashMap{
    public:
    Contact * clients;
    HashMap(){
        clients= new Contact[size];
        for(int i=0;i<size;i++){
        clients[i]=Contact();
        }
    }

    int getHash(int num){
        return num%size;
    }

    void insert_without_replacement(long int number,string name){
        int hash=getHash(number);
        while(clients[hash].name!=""&&clients[hash].number!=0){
            hash=(hash+1)%size;
        }
        clients[hash].name=name;
        clients[hash].number=number;
        cout<<"Inserted Successfully!!"<<endl;
    }

    
    void insert_with_replacement(long int number,string name){
        int hash=getHash(number);
        int temp = hash;

        if(clients[hash].name==""&&clients[hash].number==0){
            clients[hash].name=name;
            clients[hash].number=number;
            cout<<"Inserted Successfully!!"<<endl;
        }else{
            while(clients[temp].name!=""&&clients[temp].number!=0){
                temp=(temp+1)%size;
            }
            clients[temp].name=clients[hash].name;
            clients[temp].number=clients[hash].number;
            clients[hash].name=name;
            clients[hash].number=number;
            cout<<"Inserted Successfully!!"<<endl;
        }
    }

    void search(long int number){
        int hash=getHash(number);
        int count=0;
        for(int i=0;i<size;i++){
            if(clients[hash].number==number){
                cout<<"Found -->"<<clients[hash].name<<":"<<clients[hash].number<<endl;
                cout<<"Number of Counts:"<<count<<endl;
                return;

            }else{
                hash=(hash+1)%size;
                count++;
            }
        }
        cout<<"Not found"<<endl;


    }

    void remove (long int number){
        int hash =getHash(number);
        for(int i=0;i<size;i++){
            if(clients[hash].number==number){
                clients[hash].number=0;
                clients[hash].name="";
                return;
            }else{
                hash=(hash+1)%size;
            }
        }

        cout<<"No such Number found"<<endl;
    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<clients[i].name<<" : "<<clients[i].number<<endl;
        }
    }
};


int main(){
    HashMap hmap_with_replacement;
    HashMap hmap_without_replacement;

    cout<<"\n-----------------Menu----------------------"<<endl
        <<"1.For with replacement "<<endl
        <<"2.For without replacement\n"<<endl;

    int choice;
    cout<<"Enter Your choice: ";
    cin>>choice;

    if(choice == 1){
        while(1){
            cout<<"---------Menu 1-----------\n"<<endl
                <<"1.For Inserting value"<<endl
                <<"2.For Searching value"<<endl
                <<"3.For Removing value"<<endl
                <<"4.For Displaying list"<<endl;

            int choice;
            cout<<"Enter your choice :";
            cin>>choice;

            if(choice == 1){
                string name;
                long int phoneno;

                cout<<"Enter name and then phone number"<<endl;
                cin>>name;
                cin>>phoneno;
                hmap_with_replacement.insert_with_replacement(phoneno,name);
            }
            else if(choice == 2){
                long int phoneno;

                cout<<"Enter phone number"<<endl;
                cin>>phoneno;

                hmap_with_replacement.search(phoneno);
            }
            else if(choice == 3){
                long int phoneno;

                cout<<"Enter phone number"<<endl;
                cin>>phoneno;

                hmap_with_replacement.remove(phoneno);
            }
            else if(choice == 4){
                hmap_with_replacement.display();
            }
            else{
                cout<<"Invalid choice"<<endl;
            }
        }
    }
    else if(choice == 2){
        while(1){
            cout<<"---------Menu 2-----------\n"<<endl
                <<"1.For Inserting value"<<endl
                <<"2.For Searching value"<<endl
                <<"3.For Removing value"<<endl
                <<"4.For Displaying list"<<endl;

            int choice;
            cout<<"Enter your choice :";
            cin>>choice;

            if(choice == 1){
                string name;
                long int phoneno;

                cout<<"Enter name and then phone number"<<endl;
                cin>>name;
                cin>>phoneno;
                hmap_without_replacement.insert_without_replacement(phoneno,name);
            }
            else if(choice == 2){
                long int phoneno;

                cout<<"Enter phone number"<<endl;
                cin>>phoneno;

                hmap_without_replacement.search(phoneno);
            }
            else if(choice == 3){
                long int phoneno;

                cout<<"Enter phone number"<<endl;
                cin>>phoneno;

                hmap_without_replacement.remove(phoneno);
            }
            else if(choice == 4){
                hmap_without_replacement.display();
            }
            else{
                cout<<"Invalid choice"<<endl;
            }
        }
    }
    
    return 0;
}