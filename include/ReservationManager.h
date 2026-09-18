#ifndef RESERVATIONMANAGER_H

#define RESERVATIONMANAGER_H

#include <iostream>

#include "Reservation.h"

using namespace std;

class ReservationManager

{

private:

    struct Node

    {

        Reservation reservation;

        Node* next;

        Node(const Reservation& reservation);

    };

    Node* head;

public:

    ReservationManager();

    ~ReservationManager();

    void addReservation(const Reservation& reservation);

    bool removeReservation(int reservationId);

    void displayReservations() const;

    Reservation* searchReservation(int reservationId);

    bool hasConflict(string resourceId, string date) const;

    bool isEmpty() const;

};

#endif
