#include<iostream>
using namespace std;


class Student{
    string name;
    int marks;

    public:
    Student(){
        name="";
        marks=0;
    }

    void setStudent(){
        cout<<"enter the name:";
        cin>>name;
        cout<<"enter marks:";
        cin>>marks; 
    }

    int getMarks(){
        return marks;
    }
     string getName(){
        return name;
    }
     friend class MaxHeap;
};


class MaxHeap{
    Student ** heap;
    int capacity ,size;

    int parent(int i){
        return (i-1)/2;
    }
    int left(int i){
        return 2*i+1;
    }
    int right(int i){
        return 2*i+2;
    }

    void swap(Student*&a,Student*&b){
        Student*temp=a;
        a=b;
        b=temp;
    }

    void maxHeapify(int i){
        int l=left(i);
        int r=right(i);
        int largest=i;
        if(l<size&&heap[l]->getMarks()>heap[largest]->getMarks()){
            largest=l;
        }
        if(r<size&&heap[r]->getMarks()>heap[largest]->getMarks()){
            largest=r;
        }

        if(largest!=i){
            swap(heap[i],heap[largest]);
            maxHeapify(largest);
        }
    }

    public:
    MaxHeap(int cap){
        capacity=cap;
        size=0;
        heap=new Student*[capacity];
    }

    void insert(Student *s){
        if(size==capacity) return ;
        int i = size++;
        heap[i]=s;
        while(i>0&&heap[i]->marks>heap[parent(i)]->marks){
            swap(heap[i],heap[parent(i)]);
            i=parent(i);
        }
    }

    Student * extractMax(){
        if(size==0) return nullptr;
        Student *max= heap[0];
        heap[0]=heap[--size];
        maxHeapify(0);
        return max;
    }


};

void heapSort(Student * arr[],int n){
    MaxHeap maxheap(n);
    for(int i=0;i<n;i++){
        maxheap.insert(arr[i]);
    }
    for(int i=n-1;i>=0;i--){
        maxheap.extractMax();
    }
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

 
    return 0;
}
