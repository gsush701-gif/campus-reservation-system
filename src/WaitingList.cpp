
/*
    WaitingList.cpp
    Implements the date-aware student waiting queue.
*/

#include "WaitingList.h"
#include <iostream>

// Adds a student and requested date to the end of the queue.
void WaitingList::enqueue(int studentId, string studentName, string date)
{
    WaitingEntry student = {studentId, studentName, date};
    waitingQueue.push(student);
}

// Removes and returns the first student in the queue.
WaitingList::WaitingEntry WaitingList::dequeue()
{
    if (waitingQueue.empty())
    {
        cout << "Error: waiting list is empty." << endl;
        return {-1, "", ""};
    }

    WaitingEntry student = waitingQueue.front();
    waitingQueue.pop();

    return student;
}

// Returns true if the queue is empty.
bool WaitingList::isEmpty() const
{
    return waitingQueue.empty();
}

// Returns the number of students waiting.
int WaitingList::size() const
{
    return static_cast<int>(waitingQueue.size());
}

// Removes the first waiter for a date and preserves everyone else's order.
bool WaitingList::dequeueForDate(string date, WaitingEntry& student)
{
    queue<WaitingEntry> tempQueue;
    bool found = false;

    while (!waitingQueue.empty())
    {
        WaitingEntry current = waitingQueue.front();
        waitingQueue.pop();

        if (!found && current.date == date)
        {
            student = current;
            found = true;
        }
        else
        {
            tempQueue.push(current);
        }
    }

    waitingQueue = tempQueue;
    return found;
}

// Displays each waiting student, including their requested date.
void WaitingList::display() const
{
    if (waitingQueue.empty())
    {
        cout << "Waiting list is empty." << endl;
        return;
    }

    queue<WaitingEntry> tempQueue = waitingQueue;

    while (!tempQueue.empty())
    {
        WaitingEntry student = tempQueue.front();

        cout << "Student ID: " << student.studentId
             << " | Name: " << student.studentName
             << " | Date: " << student.date << endl;

        tempQueue.pop();
    }
}
