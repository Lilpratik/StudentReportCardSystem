#ifndef STUDENT_H
#define STUDENT_H
#include <string>
const int SUBJECT_COUNT = 5;

const std::string SUBJECT_NAMES[SUBJECT_COUNT] = {"Math" , "Science", "English", "History", "Computer"};

struct Student {
  std::string name;
  int rollNumber;
  int marks[SUBJECT_COUNT];
  float average;
  char grade;
  bool isActive;
};

// function prototypes
void addStudent();
void displayAllStudents();
void searchStudentByRoll();
void updateStudent();

void saveToFile();
void loadFromFile();

void askForPIN();
void findTopper();
void sortStudentsByName();
void sortStudentsByAverage();


#endif
