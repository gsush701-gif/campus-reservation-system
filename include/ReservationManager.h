
/*
    ReservationManager.h
    Manages reservations using a singly linked list.
    Supports adding, removing, searching, displaying, and counting reservations.
*/

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

        // Creates a node containing a reservation.
        Node(const Reservation& reservation);
    };

    Node* head;

public:
    // Creates an empty reservation manager.
    ReservationManager();

    // Releases all nodes in the linked list.
    ~ReservationManager();

    // Adds a reservation to the end of the list.
    void addReservation(const Reservation& reservation);

    // Removes a reservation by ID and returns whether it was found.
    bool removeReservation(int reservationId);

    // Displays all reservations in the list.
    void displayReservations() const;

    // Finds a reservation by ID and returns its address or nullptr.
    Reservation* searchReservation(int reservationId);

    // Returns true if the resource is reserved on the specified date.
    bool hasConflict(string resourceId, string date) const;

    // Returns true if the list contains no reservations.
    bool isEmpty() const;

    // Returns the number of reservations for a resource ID.
    int countReservationsForResource(string resourceId) const;

    // Returns the total number of reservations.
    int countReservations() const;

    // Returns the number of reservations belonging to a student.
    int countReservationsForStudent(int studentId) const;

    // Displays a student's reservations and returns how many were found.
    int displayReservationsForStudent(int studentId) const;
};

#endif
