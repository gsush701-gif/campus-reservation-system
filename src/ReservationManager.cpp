#include "ReservationManager.h"

ReservationManager::Node::Node(const Reservation& reservation)

    : reservation(reservation), next(nullptr)

{

}

ReservationManager::ReservationManager()

{

    head = nullptr;

}

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

bool ReservationManager::isEmpty() const

{

    return head == nullptr;

}
