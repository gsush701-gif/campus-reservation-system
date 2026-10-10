
/*
    ReservationManager.cpp
    Implements reservation management using a singly linked list.
    Includes methods for searching, displaying, and counting reservations.
*/

#include "ReservationManager.h"

// Creates a node containing a reservation and no next node.
ReservationManager::Node::Node(const Reservation& reservation)
    : reservation(reservation), next(nullptr)
{
}

// Initializes an empty reservation list.
ReservationManager::ReservationManager()
{
    head = nullptr;
}

// Deletes every node to release dynamically allocated memory.
ReservationManager::~ReservationManager()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// Adds a reservation to the end of the linked list.
void ReservationManager::addReservation(const Reservation& reservation)
{
    Node* newNode = new Node(reservation);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* current = head;

    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
}

// Removes a reservation by ID and returns true if it was removed.
bool ReservationManager::removeReservation(int reservationId)
{
    if (head == nullptr)
    {
        return false;
    }

    if (head->reservation.getReservationId() == reservationId)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr)
    {
        if (current->next->reservation.getReservationId() == reservationId)
        {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }

        current = current->next;
    }

    return false;
}

// Displays all reservations or a message if the list is empty.
void ReservationManager::displayReservations() const
{
    if (head == nullptr)
    {
        cout << "No active reservations." << endl;
        return;
    }

    Node* current = head;

    while (current != nullptr)
    {
        current->reservation.display();
        current = current->next;
    }
}

// Finds a reservation by ID and returns its address or nullptr.
Reservation* ReservationManager::searchReservation(int reservationId)
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getReservationId() == reservationId)
        {
            return &(current->reservation);
        }

        current = current->next;
    }

    return nullptr;
}

// Checks whether a resource has a reservation on the given date.
bool ReservationManager::hasConflict(string resourceId, string date) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getResourceId() == resourceId &&
            current->reservation.getReservationDate() == date)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Returns true when the linked list is empty.
bool ReservationManager::isEmpty() const
{
    return head == nullptr;
}

// Counts reservations matching the specified resource ID.
int ReservationManager::countReservationsForResource(string resourceId) const
{
    int count = 0;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getResourceId() == resourceId)
        {
            count++;
        }

        current = current->next;
    }

    return count;
}

// Counts every reservation in the linked list.
int ReservationManager::countReservations() const
{
    int count = 0;
    Node* current = head;

    while (current != nullptr)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Counts reservations belonging to the specified student ID.
int ReservationManager::countReservationsForStudent(int studentId) const
{
    int count = 0;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getStudentId() == studentId)
        {
            count++;
        }

        current = current->next;
    }

    return count;
}

// Displays matching student reservations and returns their count.
int ReservationManager::displayReservationsForStudent(int studentId) const
{
    int count = 0;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getStudentId() == studentId)
        {
            current->reservation.display();
            count++;
        }

        current = current->next;
    }

    return count;
}
