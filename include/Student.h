#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Student
{
private:
    int studentId;
    string studentName;

public:
    Student(int studentId, string studentName);

    int getStudentId() const;
    string getStudentName() const;

    void display() const;
};

#endif