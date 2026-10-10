
/*
    Student.cpp
    Implements the Student class functions.
*/

#include "Student.h"

// Initializes the student's ID and name.
Student::Student(int studentId, string studentName)
{
    this->studentId = studentId;
    this->studentName = studentName;
}

// Returns the student's ID.
int Student::getStudentId() const
{
    return studentId;
}

// Returns the student's name.
string Student::getStudentName() const
{
    return studentName;
}

// Displays the student's ID and name.
void Student::display() const
{
    cout << studentId << "|"
         << studentName << endl;
}
