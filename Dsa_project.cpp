#include <iostream>
#include <string>
using namespace std;

// 1. Student Class
class Student {
public:
    string name;
    int rollNumber;
    float marks;

    Student(string n, int r, float m) : name(n), rollNumber(r), marks(m) {}
};

// 2. Node for Linked List (Storing Students)
struct Node {
    Student* student;
    Node* next;

    Node(Student* s) : student(s), next(nullptr) {}
};

// 3. LinkedList Class (For storing students)
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add student to the list
    void addStudent(Student* student) {
        Node* newNode = new Node(student);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display all students
    void displayStudents() {
        if (!head) {
            cout << "No students found!" << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << "Name: " << temp->student->name
                 << ", Roll No: " << temp->student->rollNumber
                 << ", Marks: " << temp->student->marks << endl;
            temp = temp->next;
        }
    }

    // Remove student by roll number
    void removeStudent(int rollNumber) {
        if (!head) {
            cout << "No students found!" << endl;
            return;
        }
        // Special case: Removing the first student
        if (head->student->rollNumber == rollNumber) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Student with Roll Number " << rollNumber << " has been removed." << endl;
            return;
        }
        // Search for student to remove
        Node* temp = head;
        while (temp->next && temp->next->student->rollNumber != rollNumber) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Student with Roll Number " << rollNumber << " has been removed." << endl;
        } else {
            cout << "Student not found!" << endl;
        }
    }
};

// 4. Queue Class (For student processing)
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Enqueue operation (Add student to queue)
    void enqueue(Student* student) {
        Node* newNode = new Node(student);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    // Dequeue operation (Process and remove student from queue)
    void dequeue() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front) {  // If the queue is now empty, reset rear to nullptr
            rear = nullptr;
        }
        delete temp;
        cout << "Student has been processed." << endl;
    }

    // Display the queue
    void displayQueue() {
        if (!front) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Queue (Waiting for Principal): " << endl;
        while (temp) {
            cout << "Name: " << temp->student->name
                 << ", Roll No: " << temp->student->rollNumber
                 << endl;
            temp = temp->next;
        }
    }
};

// 5. Main Program
int main() {
    LinkedList studentList;
    Queue studentQueue;

    int choice;
    do {
        cout << "\n------ Student Management System ------\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Display Students\n";
        cout << "4. Add Student to Queue\n";
        cout << "5. Process Student (Dequeue)\n";
        cout << "6. Display Queue\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int rollNumber;
            float marks;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter marks: ";
            cin >> marks;

            Student* student = new Student(name, rollNumber, marks);
            studentList.addStudent(student);
            cout << "Student added successfully!" << endl;

        } else if (choice == 2) {
            int rollNumber;
            cout << "Enter roll number of student to remove: ";
            cin >> rollNumber;
            studentList.removeStudent(rollNumber);

        } else if (choice == 3) {
            cout << "Displaying all students:\n";
            studentList.displayStudents();

        } else if (choice == 4) {
            string name;
            int rollNumber;
            float marks;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter marks: ";
            cin >> marks;

            Student* student = new Student(name, rollNumber, marks);
            studentQueue.enqueue(student);
            cout << "Student added to queue!" << endl;

        } else if (choice == 5) {
            studentQueue.dequeue();

        } else if (choice == 6) {
            studentQueue.displayQueue();

        } else if (choice == 7) {
            cout << "Exiting the system...\n";
            break;
        } else {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 7);

    return 0;
}
