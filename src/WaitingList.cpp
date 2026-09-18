#include "WaitingList.h"
#include <iostream>

void WaitingList::enqueue(int studentId, string studentName) {

    waitingQueue.push({studentId, studentName});

}

pair<int, string> WaitingList::dequeue() {

    if (waitingQueue.empty()) {

        cout << "Error: waiting list is empty." << endl;

        return {-1, ""};
    }

    pair<int, string> student = waitingQueue.front();

    waitingQueue.pop();

    return student;

}

bool WaitingList::isEmpty() const {

    return waitingQueue.empty();

}

void WaitingList::display() const {

    if (waitingQueue.empty()) {

        cout << "Waiting list is empty." << endl;

        return;
    }

    queue<pair<int, string>> tempQueue = waitingQueue;

    while (!tempQueue.empty()) {

        cout << "Student ID: " << tempQueue.front().first
             << " | Name: " << tempQueue.front().second << endl;

        tempQueue.pop();
    }

}