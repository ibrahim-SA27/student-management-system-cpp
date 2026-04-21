#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    int age;
    char course[50];

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Course: ";
        cin.ignore();
        cin.getline(course, 50);
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nCourse: " << course << endl;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "\nStudent Added Successfully!\n";
}

// Display Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "------------------";
    }

    file.close();
}

// Search Student
void searchStudent(int id) {
    Student s;
    ifstream file("students.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

// Delete Student
void deleteStudent(int id) {
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "\nStudent Deleted Successfully!\n";
}

// Update Student
void updateStudent(int id) {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nEnter New Details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            found = true;
            break;
        }
    }

    file.close();

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

// Main Menu
int main() {
    int choice, id;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter ID: ";
                cin >> id;
                searchStudent(id);
                break;
            case 4:
                cout << "Enter ID: ";
                cin >> id;
                updateStudent(id);
                break;
            case 5:
                cout << "Enter ID: ";
                cin >> id;
                deleteStudent(id);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}