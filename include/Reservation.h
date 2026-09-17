#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>

using namespace std;

class Reservation
{
private:
    int reservationId;
    int studentId;
    string reservationName;
    string resourceId;
    string reservationDate;

public:

    Reservation(int reservationId, int studentId, string reservationName,
                string resourceId, string reservationDate);


    int getReservationId() const;
    int getStudentId() const;
    string getReservationName() const;
    string getResourceId() const;
    string getReservationDate() const;

    void display() const;
};

#endif