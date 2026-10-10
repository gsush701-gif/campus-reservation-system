
/*
    Student.h
    Defines the Student class and its functions.
*/

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
    // Creates a student with an ID and name.
    Student(int studentId, string studentName);

    // Returns the student's ID.
    int getStudentId() const;

    // Returns the student's name.
    string getStudentName() const;

    // Displays the student's information.
    void display() const;
};

#endif
