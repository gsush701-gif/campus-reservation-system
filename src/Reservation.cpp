#include "Reservation.h"

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

int Reservation::getReservationId() const
{
    return reservationId;
}

int Reservation::getStudentId() const
{
    return studentId;
}

string Reservation::getReservationName() const
{
    return reservationName;
}

string Reservation::getResourceId() const
{
    return resourceId;
}

string Reservation::getReservationDate() const
{
    return reservationDate;
}

void Reservation::display() const
{
    cout << reservationId << "|"
         << studentId << "|"
         << reservationName << "|"
         << resourceId << "|"
         << reservationDate << endl;
}