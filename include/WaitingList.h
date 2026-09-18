#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <string>
#include <utility>

using namespace std;

class WaitingList {

private:

    queue<pair<int, string>> waitingQueue;

public:

    void enqueue(int studentId, string studentName);

    pair<int, string> dequeue();

    bool isEmpty() const;

    void display() const;
};

#endif