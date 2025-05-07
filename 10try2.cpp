#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    int marks;

    void input() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }
};

// Heapify function to maintain max-heap
void heapify(vector<Student>& arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].marks > arr[largest].marks)
        largest = left;
    if (right < n && arr[right].marks > arr[largest].marks)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(vector<Student>& arr) {
    int n = arr.size();

    // Build max-heap
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Move max to end
        heapify(arr, i, 0);   // Heapify reduced heap
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        students[i].input();
    }

    heapSort(students);

    cout << "\nSorted Students by Marks (Ascending):\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << students[i].name << " - " << students[i].marks << "\n";
    }

    cout << "\nTopper:\n";
    cout << "Name: " << students[n-1].name << "\n";
    cout << "Marks: " << students[n-1].marks << "\n";

    return 0;
}
