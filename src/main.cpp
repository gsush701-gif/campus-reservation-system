
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <limits>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "CancellationHistory.h"
#include "WaitingList.h"

using namespace std;

int main()
{
    vector<Resource> resources = loadResources("data/resources.txt");

    ReservationManager reservationManager;
    CancellationHistory cancellationHistory;
    vector<WaitingList> waitingLists(resources.size());

    int nextReservationId = 301;
    int choice;

    do
    {
        cout << "\n--------Resource Reservation System-----------" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice < 1 || choice > 6)
        {
            cout << "Invalid choice. Please enter a number from 1 to 6."
                 << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            for (int i = 0; i < static_cast<int>(resources.size()); i++)
            {
                resources[i].display();
            }

            break;
        }

        case 2:
        {
            int studentId;
            string studentName;
            string resourceId;
            string reservationDate;

            cout << "Enter Student ID: ";
            cin >> studentId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid Student ID." << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Student Name: ";
            getline(cin, studentName);

            cout << "Enter Resource ID: ";
            cin >> resourceId;

            int resourceIndex = -1;

            for (int i = 0; i < static_cast<int>(resources.size()); i++)
            {
                if (resources[i].getResourceId() == resourceId)
                {
                    resourceIndex = i;
                    break;
                }
            }

            if (resourceIndex == -1)
            {
                cout << "Invalid Resource ID." << endl;
                break;
            }

            cout << "Enter Reservation Date (MM/DD/YYYY): ";
            cin >> reservationDate;

            if (!reservationManager.hasConflict(resourceId, reservationDate))
            {
                Reservation reservation(
                    nextReservationId,
                    studentId,
                    studentName,
                    resourceId,
                    reservationDate
                );

                reservationManager.addReservation(reservation);

                cout << "Reservation created successfully." << endl;
                cout << "Reservation ID: " << nextReservationId << endl;

                nextReservationId++;
            }
            else
            {
                // Store the date so the correct student can be assigned later.
                waitingLists[resourceIndex].enqueue(
                    studentId,
                    studentName,
                    reservationDate
                );

                cout << "Resource is already reserved for this date." << endl;
                cout << "Student has been added to the waiting list." << endl;
            }

            break;
        }

        case 3:
        {
            int reservationId;

            cout << "Enter Reservation ID: ";
            cin >> reservationId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid Reservation ID." << endl;
                break;
            }

            Reservation* found =
                reservationManager.searchReservation(reservationId);

            if (found == nullptr)
            {
                cout << "Reservation not found." << endl;
                break;
            }

            string resourceId = found->getResourceId();
            string reservationDate = found->getReservationDate();

            cancellationHistory.pushCancellation(*found);
            reservationManager.removeReservation(reservationId);

            cout << "Reservation cancelled successfully." << endl;

            int resourceIndex = -1;

            for (int i = 0; i < static_cast<int>(resources.size()); i++)
            {
                if (resources[i].getResourceId() == resourceId)
                {
                    resourceIndex = i;
                    break;
                }
            }

            if (resourceIndex == -1)
            {
                cout << "Resource not found." << endl;
                break;
            }

            // Find the first student waiting for this exact date.
            WaitingList::WaitingEntry nextStudent;

            if (waitingLists[resourceIndex].dequeueForDate(
                    reservationDate, nextStudent))
            {
                Reservation newReservation(
                    nextReservationId,
                    nextStudent.studentId,
                    nextStudent.studentName,
                    resourceId,
                    reservationDate
                );

                reservationManager.addReservation(newReservation);

                cout << "Waiting student automatically assigned." << endl;
                cout << "New Reservation ID: "
                     << nextReservationId << endl;

                nextReservationId++;
            }
            else
            {
                cout << "No one waiting for that date." << endl;
            }

            break;
        }

        case 4:
        {
            cout << "\n===== Waiting Lists =====" << endl;

            for (int i = 0; i < static_cast<int>(resources.size()); i++)
            {
                cout << "\nResource ID: "
                     << resources[i].getResourceId() << endl;

                cout << "Resource Name: "
                     << resources[i].getResourceName() << endl;

                waitingLists[i].display();
            }

            break;
        }

        case 5:
        {
            try
            {
                Reservation restoredReservation =
                    cancellationHistory.popCancellation();

                string resourceId =
                    restoredReservation.getResourceId();

                string reservationDate =
                    restoredReservation.getReservationDate();

                // Refuse restoration if the resource and date are occupied.
                // The refused entry is dropped from cancellation history.
                if (reservationManager.hasConflict(
                        resourceId, reservationDate))
                {
                    cout << "Cannot undo cancellation. The resource "
                         << resourceId
                         << " is already reserved for "
                         << reservationDate << "."
                         << endl;
                }
                else
                {
                    reservationManager.addReservation(
                        restoredReservation
                    );

                    cout << "Cancellation undone successfully."
                         << endl;
                }
            }
            catch (const runtime_error& e)
            {
                cout << "Unable to undo cancellation: "
                     << e.what() << endl;
            }

            break;
        }

        case 6:
        {
            cout << "Exiting program..." << endl;
            break;
        }
        }
    }
    while (choice != 6);

    return 0;
}
