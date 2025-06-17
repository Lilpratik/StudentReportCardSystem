#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include "student.h"
#include <algorithm>
using namespace std;

vector<Student> students;  // storing all data in this vector

// function prototypes
void addStudent();
void displayAllStudents();
void searchStudentByRoll();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void askForPIN();
void sortStudentsByName();
void sortStudentsByAverage();


int main() {
  askForPIN();
  loadFromFile();
  int choice;

  while (true) {
    cout << "\n=== Student Report Card ===\n";
    cout << "1. Add Student\n";
    cout << "2. Show All Students\n";
    cout << "3. Search Student By Roll Number\n";
    cout << "4. Update Student By Roll Number\n";
    cout << "5. Delete Student\n";
    cout << "6. Show Topper(s)\n";
    cout << "7. Sort by Name(A-Z)\n";
    cout << "8. Sort by Average (High to Low)\n";
    cout << "9. Exit\n";
    cout << "Enter your choice:";
    cin >> choice;

    switch(choice) {
    case 1: addStudent(); saveToFile(); break;
    case 2: displayAllStudents(); break;
    case 3: searchStudentByRoll(); break;
    case 4: updateStudent(); saveToFile(); break;
    case 5: deleteStudent(); saveToFile();break;
    case 6: findTopper(); break;
    case 7: sortStudentsByName(); break;
    case 8: sortStudentsByAverage(); break;
    case 9: cout << "Thanks for usign our system!\n"; return 0;
    default: cout << "Invalid input. PLease choice a valid option and Try again.\n";return -1;
    }
  }
}

void addStudent() {
  Student s;

  cout << "Enter Student Name: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, s.name);

  cout << "Enter Student Roll Number: ";
  cin >> s.rollNumber;

  int total = 0;

  cout << "Enter Student Marks for 5-Subjects\n";
  for (int i = 0; i < SUBJECT_COUNT; ++i) {
    cout << SUBJECT_NAMES[i] << ": ";
    cin >> s.marks[i];
    total += s.marks[i];
  }

  s.average  = total / (float)SUBJECT_COUNT;

  // Assign grade
  if (s.average >= 75)
    s.grade = 'A';
  else if (s.average >= 60)
    s.grade = 'B';
  else if (s.average >= 40)
    s.grade = 'C';
  else
    s.grade = 'F';


  s.isActive = true;
  students.push_back(s);

  cout << "Student added successfully!\n";

}


void displayAllStudents() {

  if (students.empty()) {
    cout << "No Student record found.\n";
    return;
  }

  cout << "\n=== Sutdent Report Card ===\n";
  cout << "Roll\tName\tAverage\tGrade\n";
  cout << "-----------------------------------------------\n";

  for (const Student& s : students) {
    if(s.isActive) {
      cout <<s.rollNumber <<  s.name << "\t" << "\t" << s.average << "\t" << s.grade << "\n";

    }
  }
}

void searchStudentByRoll() {
  if (students.empty()) {
    cout << "No Student record found.\n";
    return;
  }

  int roll;
  cout << "Enter Roll Number of the Student: ";
  cin >> roll;

  bool found = false;

  for (const Student& s : students) {
    if (s.rollNumber == roll && s.isActive) {
      found = true;
      cout << "\n=== Student Found ===\n";
      cout << "Name: " << s.name << endl;
      cout << "Roll Number: "<< s.rollNumber << endl;
      cout << "Marks: ";
      for (int i = 0; i < SUBJECT_COUNT; ++i) {
	cout << s.marks[i] << " ";
      }
      cout << "\nAverage: " << s.average << endl;
      cout << "Grade: " << s.grade << endl;
      break;
    }
  }

  if (!found) {
    cout << "Student with roll number " << roll << " not found.\n";
  }
}


void updateStudent() {
  if (students.empty()) {
    cout << "No student record found.\n";
    return;
  }

  int roll;
  cout << "Enter roll number to update: ";
  cin >> roll;

  bool found = false;

  for (Student& s : students) {
    if (s.rollNumber == roll && s.isActive) {
      found = true;

      cout << "\n=== Updating Student: " << s.name << " ===\n";
      cout << "Enter new name (or press enter to keep same): ";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      string newName;
      getline(cin, newName);
      if (!newName.empty()) {
	s.name = newName;
      }

      cout << "Enter new marks for 5 subjects:\n";
      int total = 0;
      for (int i = 0; i < SUBJECT_COUNT; ++i){
	cout << SUBJECT_NAMES[i] << ": ";
	cin >> s.marks[i];
	total += s.marks[i];
      }

      s.average = total / (float)SUBJECT_COUNT;

      if (s.average >= 75)
	s.grade = 'A';
      else if (s.average >= 60)
	s.grade = 'B';
      else if (s.average >= 40)
	s.grade = 'C';
      else
	s.grade = 'F';

      cout << "Student updated successfully!\n";
      break;
    }
  }

  if (!found) {
    cout << "Student with roll number " << roll << " not found.\n";
  }

}


void deleteStudent() {
  if (students.empty()) {
    cout << "No student records found.\n";
    return;
  }

  int roll;
  cout << "Enter roll number to delete: ";
  cin >> roll;

  for (Student& s : students) {
    if (s.rollNumber == roll && s.isActive) {
      char confirm;
      cout << "Are you sure you want to delete " << s.name << "? (y/n): ";
      cin >> confirm;

      if (confirm == 'y' || confirm == 'Y') {
	s.isActive = false;
	cout << "Student deleted (deactivated) successfully.\n";
      } else {
	cout << "Deletion cancelled\n";
      }

      return;
    }
  }

  cout << "Student with roll number " << roll << " not found.\n";
}

void saveToFile() {
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Error opening file for saving.\n";
        return;
    }

    for (const Student& s : students) {
        outFile << s.rollNumber << "\n"
                << s.name << "\n";
        for (int i = 0; i < SUBJECT_COUNT; ++i)
            outFile << s.marks[i] << " ";
        outFile << "\n"
                << s.average << "\n"
                << s.grade << "\n"
                << s.isActive << "\n";
    }

    outFile.close();
    cout << "All student records saved to file.\n";
}


void loadFromFile() {
  ifstream inFile("students.txt");
  if (!inFile) {
    cout << "No existing student data found.\n";
    return;
  }

  students.clear();
  while (!inFile.eof()) {
    Student s;
    inFile >> s.rollNumber;
    inFile.ignore(); // consime newline
    getline(inFile, s.name);
    for (int i = 0; i < SUBJECT_COUNT; ++i)
      inFile >> s.marks[i];
    inFile >> s.average;
    inFile >> s.grade;
    inFile >> s.isActive;
    inFile.ignore(); // skip any newline

    if (inFile)    // to avoid last empty record due to eof
      students.push_back(s);
  }

  inFile.close();
  cout << "Loaded " << students.size() << " student records from file.\n";
}


void askForPIN() {
  const string correctPIN = "1234"; // Harcoded for now
  string inputPIN;

  cout << "===== Admin Login Required =====\n";

  while (true) {
    cout << "Enter 4-digit PIN: ";
    cin >> inputPIN;

    if (inputPIN == correctPIN) {
      cout << "Access granted ✅\n";
      break;
    } else {
      cout << "Incorrect PIN ❌. Try again.\n";
    }
  }
}

void findTopper() {
  if (students.empty()) {
    cout << "No student records found.\n";
    return;
  }

  float highestAvg = -1.0;
  vector<Student> toppers;

  for (const Student& s : students) {
    if (s.isActive) {
      if (s.average > highestAvg) {
	highestAvg = s.average;
	toppers.clear();
	toppers.push_back(s);
      } else if (s.average == highestAvg) {
	toppers.push_back(s);
      }
    }
  }

  if (toppers.empty()) {
    cout << "No active students found.\n";
    return;
  }

  cout << "\n === Topper(s) ===\n";
  for (const Student& s : toppers) {
    cout << "Name: " << s.name << endl;
    cout << "Roll Number: " << s.rollNumber << endl;
    cout << "Marks: ";
    for (int i = 0; i < SUBJECT_COUNT; ++i)
      cout << SUBJECT_NAMES[i] << ": " << s.marks[i] << " ";
    cout << "\nAverage: " << s.average << endl;
    cout << "Grade: " << s.grade << "\n\n";
  }
}


void sortStudentsByName() {
  if (students.empty()) {
    cout << "No student records available.\n";
    return;
  }

  sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    return a.name < b.name;
  });

  cout << "\n Students sorted by name (A-Z):\n";
  displayAllStudents();
}


void sortStudentsByAverage() {
  if (students.empty()) {
    cout << "No student records found.\n";
    return;
  }

  sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    return a.average > b.average;
  });

  cout << "\n Students sorted by average (high to low):\n";
  displayAllStudents();
}
