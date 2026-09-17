#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <iostream>
#include <stack>
#include "Reservation.h"

using namespace std;

class CancellationHistory
{
private:
    stack<Reservation> history;

public:
    void pushCancellation(const Reservation& reservation);
    Reservation popCancellation();
    void displayHistory() const;
    bool isEmpty() const;
};

#endif