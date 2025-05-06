#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int roll;
    char name[30];
    int marks;

    Student() {
        roll = 0;
        marks = 0;
        strcpy(name, "NULL");
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
        if (roll != 0 && strcmp(name, "NULL") != 0) {
            cout << "Roll: " << roll << ", Name: " << name << ", Marks: " << marks << "\n";
        }
    }

    void clear() {
        roll = 0;
        marks = 0;
        strcpy(name, "NULL");
    }
};

void insertRecord(const char* fname) {
    Student s;
    s.setData();

    fstream file(fname, ios::in | ios::out | ios::binary);
    if (!file) {
        ofstream temp(fname, ios::binary);  // create empty file
        temp.close();
        file.open(fname, ios::in | ios::out | ios::binary);
    }

    int pos = (s.roll - 1) * sizeof(Student);

    // Fill intermediate records if needed
    file.seekp(0, ios::end);
    int fileSize = file.tellp();
    if (pos >= fileSize) {
        Student empty;
        file.seekp(0, ios::end);
        while (file.tellp() < pos) {
            file.write((char*)&empty, sizeof(Student));
        }
    }

    // Check if record already exists
    Student existing;
    file.seekg(pos);
    file.read((char*)&existing, sizeof(Student));
    if (existing.roll != 0 && strcmp(existing.name, "NULL") != 0) {
        cout << "Warning: A record already exists at this roll number. It will be overwritten.\n";
    }

    // Write the new record
    file.seekp(pos);
    file.write((char*)&s, sizeof(Student));
    file.close();
}

void deleteRecord(const char* fname) {
    int roll;
    cout << "Enter Roll No to Delete: ";
    cin >> roll;

    Student empty;
    fstream file(fname, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    int pos = (roll - 1) * sizeof(Student);
    file.seekg(0, ios::end);
    if (pos >= file.tellg()) {
        cout << "Record doesn't exist.\n";
        file.close();
        return;
    }

    file.seekp(pos);
    file.write((char*)&empty, sizeof(Student));
    file.close();
    cout << "Record deleted successfully.\n";
}

void displayRecord(const char* fname) {
    ifstream file(fname, ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(Student))) {
        if (s.roll != 0 && strcmp(s.name, "NULL") != 0) {
            s.showData();
            found = true;
        }
    }

    if (!found) {
        cout << "No records to display.\n";
    }

    file.close();
}

int main() {
    const char* fname = "try1.txt";
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Record\n2. Delete Record\n3. Display Records\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertRecord(fname); break;
            case 2: deleteRecord(fname); break;
            case 3: displayRecord(fname); break;
            case 4: cout << "Exiting.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
