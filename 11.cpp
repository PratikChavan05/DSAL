#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    char division;
    string address;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);
    }

    void display() {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

void addStudent() {
    Student s;
    s.input();
    ofstream outFile("students.txt", ios::app);
    outFile << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
    outFile.close();
    cout << "Student added successfully!\n";
}

void displayStudent(int roll) {
    ifstream inFile("students.txt");
    bool found = false;

    while (!inFile.eof()) {
        Student s;
        inFile >> s.rollNo;
        if (inFile.eof()) break;
        inFile >> ws;
        getline(inFile, s.name, ' ');
        inFile >> s.division >> ws;
        getline(inFile, s.address);

        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }

    inFile.close();
}

void deleteStudent(int roll) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    bool found = false;

    while (!inFile.eof()) {
        Student s;
        inFile >> s.rollNo;
        if (inFile.eof()) break;
        inFile >> ws;
        getline(inFile, s.name, ' ');
        inFile >> s.division >> ws;
        getline(inFile, s.address);

        if (s.rollNo != roll) {
            outFile << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice, roll;

    do {
        cout << "\n==== Student Information System ====\n";
        cout << "1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2:
                cout << "Enter Roll No to Search: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 3:
                cout << "Enter Roll No to Delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 4:
                cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
