
/*
    WaitingList.h
    Manages students waiting for reservations on specific dates.
*/

#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <string>

using namespace std;

class WaitingList
{
public:
    struct WaitingEntry
    {
        int studentId;
        string studentName;
        string date;
    };

    // Adds a student and requested date to the queue.
    void enqueue(int studentId, string studentName, string date);

    // Removes and returns the first student in the queue.
    WaitingEntry dequeue();

    // Returns true if the queue is empty.
    bool isEmpty() const;

    // Returns the number of students waiting.
    int size() const;

    // Removes the first waiter for a date and returns whether one was found.
    bool dequeueForDate(string date, WaitingEntry& student);

    // Displays the waiting students and their requested dates.
    void display() const;

private:
    queue<WaitingEntry> waitingQueue;
};

#endif
