#include "CancellationHistory.h"
#include <stdexcept>

void CancellationHistory::pushCancellation(const Reservation& reservation)
{
    history.push(reservation);
}

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

bool CancellationHistory::isEmpty() const
{
    return history.empty();
}

void CancellationHistory::displayHistory() const
{
    if (history.empty())
    {
        cout << "No cancellation history." << endl;
        return;
    }

    stack<Reservation> temp = history;

    while (!temp.empty())
    {
        temp.top().display();
        temp.pop();
    }
}