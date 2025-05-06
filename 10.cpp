#include <iostream>
using namespace std;

class Student {
    string name;
    int marks;

public:
    void setStudent() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    int getMarks() const { return marks; }
    string getName() const { return name; }

    friend class MaxHeap;
};

class MaxHeap {
    Student** heap;
    int capacity, size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void swap(Student*& a, Student*& b) {
        Student* temp = a;
        a = b;
        b = temp;
    }

    void maxHeapify(int i) {
        int l = left(i), r = right(i), largest = i;
        if (l < size && heap[l]->marks > heap[largest]->marks) largest = l;
        if (r < size && heap[r]->marks > heap[largest]->marks) largest = r;
        if (largest != i) {
            swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    MaxHeap(int cap) : capacity(cap), size(0) {
        heap = new Student*[capacity];
    }

    void insert(Student* s) {
        if (size == capacity) return;
        int i = size++;
        heap[i] = s;
        while (i > 0 && heap[i]->marks > heap[parent(i)]->marks) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    Student* extractMax() {
        if (size == 0) return nullptr;
        Student* max = heap[0];
        heap[0] = heap[--size];
        maxHeapify(0);
        return max;
    }

    ~MaxHeap() {
        delete[] heap;
    }
};

void heapSort(Student* arr[], int n) {
    MaxHeap maxHeap(n);
    for (int i = 0; i < n; ++i) maxHeap.insert(arr[i]);
    for (int i = n - 1; i >= 0; --i) arr[i] = maxHeap.extractMax();
}

int main() {
    int numStudents;
    cout << "Enter number of students: ";
    cin >> numStudents;

    Student* students[numStudents];

    bool running = true;
    while (running) {
        int ch;
        cout << "\n===== Heap Sort Menu =====\n";
        cout << "1. Add Students\n2. Sort Students\n3. Max Marks\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                for (int i = 0; i < numStudents; ++i) {
                    students[i] = new Student();
                    students[i]->setStudent();
                }
                cout << "Students Added!\n";
                break;

            case 2:
                heapSort(students, numStudents);
                cout << "\nSorted Students:\n";
                for (int i = 0; i < numStudents; ++i)
                    cout << i + 1 << ". " << students[i]->getName() << " - " << students[i]->getMarks() << "\n";
                break;

            case 3:
                if (numStudents > 0) {
                    cout << "Student with Max Marks:\n";
                    cout << "Name: " << students[numStudents-1]->getName() << "\n";
                    cout << "Marks: " << students[numStudents-1]->getMarks() << "\n";
                }
                break;

            case 4:
                cout << "Exiting...\n";
                running = false;
                break;

            default:
                cout << "Invalid input.\n";
        }
    }

    // Free memory
    for (int i = 0; i < numStudents; ++i)
        delete students[i];

    return 0;
}
