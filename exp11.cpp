#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int rno;
    string name;
    string div;
    string add;

public:
    Student() : rno(0), name(""), div(""), add("") {}

    void input() {
        cout << "\nEnter rno: ";
        cin >> rno;
        cin.ignore();  // Clear the newline from previous input
        cout << "\nEnter name: ";
        getline(cin, name);  // Allow spaces in name
        cout << "\nEnter div: ";
        getline(cin, div);  // Allow spaces in division (optional, could be single char)
        cout << "\nEnter address: ";
        getline(cin, add);  // Allow spaces in address
    }

    int getRno() const {
        return rno;
    }

    void display() const {
        cout << "\nrno= " << rno;
        cout << "\nname= " << name;
        cout << "\ndiv= " << div;
        cout << "\nadd= " << add << endl;
    }

    void writeToFile(ofstream &outfile) const {
        outfile << rno << "," << name << "," << div << "," << add << endl;
    }

    bool readFromLine(const string &line) {
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) {
            return false;
        }

        rno = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        div = line.substr(p2 + 1, p3 - p2 - 1);
        add = line.substr(p3 + 1);
        return true;
    }
};

void addRecord(const string &filename) {
    ofstream file(filename, ios::app);
    Student s;
    s.input();
    s.writeToFile(file);
    file.close();
}

void deleteStudent(const string &filename, int rollToDelete) {
    ifstream inFile(filename);
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Student s;
        if (s.readFromLine(line)) {
            if (s.getRno() != rollToDelete) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
    }

    inFile.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found)
        cout << "Record deleted.\n";
    else
        cout << "Record not found.\n";
}

void searchStudent(const string &filename, int rollToSearch) {
    ifstream file(filename);
    string line;
    bool found = false;
    while (getline(file, line)) {
        Student s;
        if (s.readFromLine(line) && s.getRno() == rollToSearch) {
            s.display();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Record not found.\n";
    }
    file.close();
}

void displayAll(const string &filename) {
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

int main() {
    string filename = "students.txt";
    int choice;

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
            addRecord(filename);
            break;
        case 2: {
            int roll;
            cout << "Enter roll number to delete: ";
            cin >> roll;
            deleteStudent(filename, roll);
            break;
        }
        case 3: {
            int roll;
            cout << "Enter roll number to search: ";
            cin >> roll;
            searchStudent(filename, roll);
            break;
        }
        case 4:
            displayAll(filename);
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
