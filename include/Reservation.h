
/*
    Reservation.h
    Represents one student's reservation of a resource on a date.
*/

#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>

using namespace std;

class Reservation
{
private:
    // Unique reservation number, such as 301.
    int reservationId;

    // ID of the student who made the reservation.
    int studentId;

    // Name of the student who made the reservation.
    string reservationName;

    // ID of the reserved resource, such as "R101".
    string resourceId;

    // Reserved date in MM/DD/YYYY format.
    string reservationDate;

public:

    // Creates a reservation with the given details.
    Reservation(int reservationId, int studentId, string reservationName,
                string resourceId, string reservationDate);


    // Returns the reservation ID.
    int getReservationId() const;

    // Returns the student ID.
    int getStudentId() const;

    // Returns the student name.
    string getReservationName() const;

    // Returns the reserved resource ID.
    string getResourceId() const;

    // Returns the reserved date.
    string getReservationDate() const;

    // Prints the reservation as one pipe-separated line.
    void display() const;
};

#endif