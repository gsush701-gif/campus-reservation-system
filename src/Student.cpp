#include "Student.h"

Student::Student(int studentId, string studentName)
{
    this->studentId = studentId;
    this->studentName = studentName;
}

int Student::getStudentId() const
{
    return studentId;
}

string Student::getStudentName() const
{
    return studentName;
}

void Student::display() const
{
    cout << studentId << "|"
         << studentName << endl;
}