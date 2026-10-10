
/*
    Reservation.cpp
    Implements the Reservation class.
*/

#include "Reservation.h"

// Creates a reservation with the given details.
Reservation::Reservation(int reservationId, int studentId,
                         string reservationName, string resourceId,
                         string reservationDate)
{
    this->reservationId = reservationId;
    this->studentId = studentId;
    this->reservationName = reservationName;
    this->resourceId = resourceId;
    this->reservationDate = reservationDate;
}

// Returns the reservation ID.
int Reservation::getReservationId() const
{
    return reservationId;
}

// Returns the student ID.
int Reservation::getStudentId() const
{
    return studentId;
}

// Returns the student name.
string Reservation::getReservationName() const
{
    return reservationName;
}

// Returns the reserved resource ID.
string Reservation::getResourceId() const
{
    return resourceId;
}

// Returns the reserved date.
string Reservation::getReservationDate() const
{
    return reservationDate;
}

// Prints the reservation as ID|StudentID|Name|ResourceID|Date.
void Reservation::display() const
{
    cout << reservationId << "|"
         << studentId << "|"
         << reservationName << "|"
         << resourceId << "|"
         << reservationDate << endl;
}