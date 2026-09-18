#include <iostream>
#include <vector>
#include <stdexcept>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "CancellationHistory.h"
#include "WaitingList.h"

using namespace std;

int main() {

    vector<Resource> resources = loadResources("data/resources.txt");

    ReservationManager reservationManager;

    CancellationHistory cancellationHistory;

    vector<WaitingList> waitingLists(resources.size());

    int nextReservationId = 301;

    int choice;

    do {

        cout << "\n--------Resource Reservation System-----------" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input. Please enter a number." << endl;

            continue;
        }

        if (choice < 1 || choice > 6) {

            cout << "Invalid choice. Please enter a number from 1 to 6." << endl;

            continue;
        }

        switch (choice) {

        case 1:

            for (int i = 0; i < resources.size(); i++) {

                resources[i].display();

            }

            break;

        case 2:
        {
            int studentId;
            string studentName;
            string resourceId;
            string reservationDate;

            cin.ignore();

            cout << "Enter Student ID: ";
            cin >> studentId;

            if (cin.fail()) {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid Student ID." << endl;

                break;
            }

            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, studentName);

            cout << "Enter Resource ID: ";
            cin >> resourceId;

            int resourceIndex = -1;

            for (int i = 0; i < resources.size(); i++) {

                if (resources[i].getResourceId() == resourceId) {

                    resourceIndex = i;

                    break;
                }
            }

            if (resourceIndex == -1) {

                cout << "Invalid Resource ID." << endl;

                break;
            }

            cout << "Enter Reservation Date (MM/DD/YYYY): ";
            cin >> reservationDate;

            if (!reservationManager.hasConflict(resourceId, reservationDate)) {

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
            else {

                waitingLists[resourceIndex].enqueue(studentId, studentName);

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

            if (cin.fail()) {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Invalid Reservation ID." << endl;

                break;
            }

            Reservation* found =
                reservationManager.searchReservation(reservationId);

            if (found == nullptr) {

                cout << "Reservation not found." << endl;

                break;
            }

            string resourceId = found->getResourceId();
            string reservationDate = found->getReservationDate();

            cancellationHistory.pushCancellation(*found);

            reservationManager.removeReservation(reservationId);

            cout << "Reservation cancelled successfully." << endl;

            int resourceIndex = -1;

            for (int i = 0; i < resources.size(); i++) {

                if (resources[i].getResourceId() == resourceId) {

                    resourceIndex = i;

                    break;
                }
            }

            if (resourceIndex == -1) {

                cout << "Resource not found." << endl;

                break;
            }

            if (!waitingLists[resourceIndex].isEmpty()) {

                pair<int, string> nextStudent =
                    waitingLists[resourceIndex].dequeue();

                Reservation newReservation(
                    nextReservationId,
                    nextStudent.first,
                    nextStudent.second,
                    resourceId,
                    reservationDate
                );

                reservationManager.addReservation(newReservation);

                cout << "Waiting student automatically assigned." << endl;
                cout << "New Reservation ID: "
                     << nextReservationId << endl;

                nextReservationId++;

            }
            else {

                cout << "No students are waiting for this resource."
                     << endl;
            }

            break;
        }

        case 4:

            cout << "\n===== Waiting Lists =====" << endl;

            for (int i = 0; i < resources.size(); i++) {

                cout << "\nResource ID: "
                     << resources[i].getResourceId() << endl;

                cout << "Resource Name: "
                     << resources[i].getResourceName() << endl;

                waitingLists[i].display();

            }

            break;

        case 5:
        {
            try {

                Reservation restoredReservation =
                    cancellationHistory.popCancellation();

                reservationManager.addReservation(restoredReservation);

                cout << "Cancellation undone successfully." << endl;

            }
            catch (runtime_error& e) {

                cout << "Unable to undo cancellation: "
                     << e.what() << endl;

            }

            break;
        }

        case 6:

            cout << "Exiting program..." << endl;

            break;
        }

    } while (choice != 6);

    return 0;
}
