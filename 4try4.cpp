#include<bits/stdc++.h>
using namespace std;
#define size 10

class Contact{
    public:
    int num;
    string name;

    Contact(){
        num=0;
        name="";
    }
    friend class HashMap;
};

class HashMap{
    Contact *clients;

    public:
    HashMap(){
        clients=new Contact[size];
        for(int i;i<size;i++){
            clients[i] = Contact();
        }
    }

    int getHash(int num){
        return num%size;
    }

    void insert_without_replacemet(int num,string name){
        int hash=getHash(num);
        while(clients[hash].name!=""&&clients[hash].num!=0){
            hash=(hash+1)%size;
        }

        clients[hash].name=name;
        clients[hash].num=num;
        cout<<"inserted"<<endl;
    }

    
    void insert_with_replacemet(int num,string name){
        int hash=getHash(num);
        int temp =hash;
        if(clients[hash].name==""&&clients[hash].num==0){
            clients[hash].name=name;
            clients[hash].num=num;
            cout<<"inserted"<<endl;
            return;
        }
        while(clients[temp].name!=""&&clients[temp].num!=0){
            temp=(temp+1)%size;
        }

        clients[temp].name=clients[hash].name;
        clients[temp].num=clients[hash].num;
        clients[hash].name=name;
        clients[hash].num=num;
        
        cout<<"inserted"<<endl;
    }

    void search(int num){
        int hash=getHash(num);
        for(int i=0;i<size;i++){
            if(clients[hash].num==num){
                cout<<"name"<<clients[hash].name<<endl;
                cout<<"number"<<clients[hash].num<<endl;
                
                return;
            }else{
                hash=(hash+1)%size;
            }
        }
        cout<<"Not found"<<endl;


    }

    void remove(int num){
        int hash=getHash(num);
        for(int i=0;i<size;i++){
            if(clients[hash].num==num){
                clients[hash].name="";
                clients[hash].num=0;
                return;
            }else{
                hash=(hash+1)%size;
            }
        }
        cout<<"Not found"<<endl;
        

    }

    void display(){
        for(int i=0;i<size;i++){
            cout<<clients[i].name<<" : "<<clients[i].num<<endl;
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
                hmap_with_replacement.insert_with_replacemet(phoneno,name);
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
                hmap_without_replacement.insert_without_replacemet(phoneno,name);
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
