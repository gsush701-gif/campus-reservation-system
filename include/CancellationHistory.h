
/*
    CancellationHistory.h
    Stores cancelled reservations in a stack so the latest can be undone.
*/

#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <iostream>
#include <stack>
#include "Reservation.h"

using namespace std;

class CancellationHistory
{
private:
    // Cancelled reservations, with the most recent on top.
    stack<Reservation> history;

public:
    // Saves a cancelled reservation so it can be restored later.
    void pushCancellation(const Reservation& reservation);

    // Removes and returns the most recent cancellation.
    // Throws runtime_error if the history is empty.
    Reservation popCancellation();

    // Displays cancellations from most recent to oldest.
    void displayHistory() const;

    // Returns true if there are no cancellations to restore.
    bool isEmpty() const;
};

#endif