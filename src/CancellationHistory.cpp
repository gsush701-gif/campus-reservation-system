
/*
    CancellationHistory.cpp
    Implements the cancellation history stack.
*/

#include "CancellationHistory.h"
#include <stdexcept>

// Saves a cancelled reservation on top of the stack.
void CancellationHistory::pushCancellation(const Reservation& reservation)
{
    history.push(reservation);
}

// Removes and returns the most recent cancellation.
Reservation CancellationHistory::popCancellation()
{
    if (history.empty())
    {
        throw runtime_error("No cancelled reservations to restore.");
    }

    Reservation reservation = history.top();
    history.pop();

    return reservation;
}

// Returns true if there are no cancellations to restore.
bool CancellationHistory::isEmpty() const
{
    return history.empty();
}

// Displays cancellations from most recent to oldest.
void CancellationHistory::displayHistory() const
{
    if (history.empty())
    {
        cout << "No cancellation history." << endl;
        return;
    }

    // Walk a copy so the real history is not changed.
    stack<Reservation> temp = history;

    while (!temp.empty())
    {
        temp.top().display();
        temp.pop();
    }
}