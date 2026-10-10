
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
#include "ReportGenerator.h"
#include "Searching.h"

using namespace std;

int main()
{
    // Load resources and initialize the reservation system.
    vector<Resource> resources = loadResources("data/resources.txt");

    ReservationManager reservationManager;
    CancellationHistory cancellationHistory;

    // Each waiting list corresponds to the resource at the same index.
    vector<WaitingList> waitingLists(resources.size());

    // Assign unique IDs to new reservations.
    int nextReservationId = 301;
    int choice = 0;

    // Continue displaying the main menu until the user exits.
    do
    {
        cout << "\n-------- Resource Reservation System --------" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Reservations" << endl;
        cout << "5. View Waiting Lists" << endl;
        cout << "6. View Cancellation History" << endl;
        cout << "7. Undo Cancellation" << endl;
        cout << "8. Search" << endl;
        cout << "9. Sort Resources" << endl;
        cout << "10. Generate Report" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        // Validate main menu input.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice < 1 || choice > 11)
        {
            cout << "Invalid choice. Enter a number from 1 to 11."
                 << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Display resources in their original order.
            for (const Resource& resource : resources)
            {
                resource.display();
            }

            break;
        }

        case 2:
        {
            // Create a reservation or add the student to a waiting list.
            int studentId;
            string studentName;
            string resourceId;
            string reservationDate;

            cout << "Enter Student ID: ";
            cin >> studentId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid Student ID." << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Student Name: ";
            getline(cin, studentName);

            cout << "Enter Resource ID: ";
            cin >> resourceId;

            // Find the resource and its corresponding waiting list.
            int resourceIndex =
                Searching::searchResourceById(resources, resourceId);

            if (resourceIndex == Searching::NOT_FOUND)
            {
                cout << "Invalid Resource ID." << endl;
                break;
            }

            cout << "Enter Reservation Date (MM/DD/YYYY): ";
            cin >> reservationDate;

            if (!reservationManager.hasConflict(
                    resourceId, reservationDate))
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
                cout << "Reservation ID: "
                     << nextReservationId << endl;

                nextReservationId++;
            }
            else
            {
                waitingLists[resourceIndex].enqueue(
                    studentId,
                    studentName,
                    reservationDate
                );

                cout << "Resource is already reserved for that date."
                     << endl;
                cout << "Student added to the waiting list." << endl;
            }

            break;
        }

        case 3:
        {
            // Cancel a reservation and assign an eligible waiting student.
            int reservationId;

            cout << "Enter Reservation ID: ";
            cin >> reservationId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');

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

            // Save the reservation so cancellation can be undone.
            cancellationHistory.pushCancellation(*found);
            reservationManager.removeReservation(reservationId);

            cout << "Reservation cancelled successfully." << endl;

            int resourceIndex =
                Searching::searchResourceById(resources, resourceId);

            if (resourceIndex == Searching::NOT_FOUND)
            {
                cout << "Resource not found." << endl;
                break;
            }

            WaitingList::WaitingEntry nextStudent;

            // Assign the released slot to a student waiting for that date.
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

                cout << "Waiting student automatically assigned."
                     << endl;
                cout << "New Reservation ID: "
                     << nextReservationId << endl;

                nextReservationId++;
            }
            else
            {
                cout << "No students are waiting for that date."
                     << endl;
            }

            break;
        }

        case 4:
        {
            // Display all active reservations.
            cout << "\n===== Active Reservations =====" << endl;
            reservationManager.displayReservations();
            break;
        }

        case 5:
        {
            // Display each waiting list beside its resource.
            cout << "\n===== Waiting Lists =====" << endl;

            for (size_t i = 0; i < resources.size(); i++)
            {
                cout << "\nResource ID: "
                     << resources[i].getResourceId() << endl;

                cout << "Resource Name: "
                     << resources[i].getResourceName() << endl;

                waitingLists[i].display();
            }

            break;
        }

        case 6:
        {
            // Display the cancellation history.
            cout << "\n===== Cancellation History =====" << endl;
            cancellationHistory.displayHistory();
            break;
        }

        case 7:
        {
            // Restore the latest cancellation if no conflict exists.
            try
            {
                Reservation restoredReservation =
                    cancellationHistory.popCancellation();

                string resourceId =
                    restoredReservation.getResourceId();

                string reservationDate =
                    restoredReservation.getReservationDate();

                if (reservationManager.hasConflict(
                        resourceId, reservationDate))
                {
                    cout << "Cannot undo cancellation. Resource "
                         << resourceId
                         << " is already reserved for "
                         << reservationDate << "." << endl;
                }
                else
                {
                    reservationManager.addReservation(
                        restoredReservation);

                    cout << "Cancellation undone successfully."
                         << endl;
                }
            }
            catch (const runtime_error& error)
            {
                cout << "Unable to undo cancellation: "
                     << error.what() << endl;
            }

            break;
        }

        case 8:
        {
            // Display the search menu until the user returns.
            int searchChoice = 0;

            while (searchChoice != 4)
            {
                cout << "\n===== Search =====" << endl;
                cout << "1. Search by Reservation ID" << endl;
                cout << "2. Search by Student ID" << endl;
                cout << "3. Search by Resource ID" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";

                cin >> searchChoice;

                // Handle nonnumeric input.
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid input. Please enter a number."
                         << endl;
                    continue;
                }

                // Reject choices outside the submenu range.
                if (searchChoice < 1 || searchChoice > 4)
                {
                    cout << "Invalid choice. Enter a number from 1 to 4."
                         << endl;
                    continue;
                }

                switch (searchChoice)
                {
                case 1:
                {
                    // Search for one reservation by its ID.
                    int reservationId;

                    cout << "Enter Reservation ID: ";
                    cin >> reservationId;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(), '\n');

                        cout << "Invalid Reservation ID." << endl;
                        break;
                    }

                    Reservation* found =
                        reservationManager.searchReservation(
                            reservationId);

                    if (found == nullptr)
                    {
                        cout << "Reservation not found." << endl;
                    }
                    else
                    {
                        found->display();
                    }

                    break;
                }

                case 2:
                {
                    // Display all reservations belonging to a student.
                    int studentId;

                    cout << "Enter Student ID: ";
                    cin >> studentId;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(), '\n');

                        cout << "Invalid Student ID." << endl;
                        break;
                    }

                    int foundCount =
                        reservationManager.displayReservationsForStudent(
                            studentId);

                    if (foundCount == 0)
                    {
                        cout << "No reservations found for that student."
                             << endl;
                    }

                    break;
                }

                case 3:
                {
                    // Search for one resource by its ID.
                    string resourceId;

                    cout << "Enter Resource ID: ";
                    cin >> resourceId;

                    int resourceIndex =
                        Searching::searchResourceById(resources, resourceId);

                    if (resourceIndex == Searching::NOT_FOUND)
                    {
                        cout << "Resource not found." << endl;
                    }
                    else
                    {
                        resources[resourceIndex].display();
                    }

                    break;
                }

                case 4:
                {
                    cout << "Returning to main menu..." << endl;
                    break;
                }
                }
            }

            break;
        }

        case 9:
        {
            // Sort report records without changing resource order.
            int sortChoice = 0;

            while (sortChoice != 3)
            {
                cout << "\n===== Sort Resources =====" << endl;
                cout << "1. Sort by Name" << endl;
                cout << "2. Sort by Reservation Count" << endl;
                cout << "3. Back to Main Menu" << endl;
                cout << "Enter your choice: ";

                cin >> sortChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid input. Please enter a number."
                         << endl;
                    continue;
                }

                if (sortChoice < 1 || sortChoice > 3)
                {
                    cout << "Invalid choice. Enter a number from 1 to 3."
                         << endl;
                    continue;
                }

                switch (sortChoice)
                {
                case 1:
                {
                    ReportGenerator::displaySortedResources(
                        resources,
                        reservationManager,
                        waitingLists,
                        1
                    );

                    break;
                }

                case 2:
                {
                    ReportGenerator::displaySortedResources(
                        resources,
                        reservationManager,
                        waitingLists,
                        2
                    );

                    break;
                }

                case 3:
                {
                    cout << "Returning to main menu..." << endl;
                    break;
                }
                }
            }

            break;
        }

        case 10:
        {
            // Let the user select which report to display.
            int reportChoice = 0;

            while (reportChoice != 5)
            {
                cout << "\n===== Generate Report =====" << endl;
                cout << "1. Active Reservations" << endl;
                cout << "2. Resource Utilization" << endl;
                cout << "3. Most Requested Resources" << endl;
                cout << "4. Waiting-List Statistics" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "Enter your choice: ";

                cin >> reportChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid input. Please enter a number."
                         << endl;
                    continue;
                }

                if (reportChoice < 1 || reportChoice > 5)
                {
                    cout << "Invalid choice. Enter a number from 1 to 5."
                         << endl;
                    continue;
                }

                switch (reportChoice)
                {
                case 1:
                {
                    ReportGenerator::displayActiveReservations(
                        resources,
                        reservationManager,
                        waitingLists
                    );

                    break;
                }

                case 2:
                {
                    ReportGenerator::displayResourceUtilization(
                        resources,
                        reservationManager,
                        waitingLists
                    );

                    break;
                }

                case 3:
                {
                    ReportGenerator::displayMostRequested(
                        resources,
                        reservationManager,
                        waitingLists
                    );

                    break;
                }

                case 4:
                {
                    ReportGenerator::displayWaitingListStatistics(
                        resources,
                        reservationManager,
                        waitingLists
                    );

                    break;
                }

                case 5:
                {
                    cout << "Returning to main menu..." << endl;
                    break;
                }
                }
            }

            break;
        }

        case 11:
        {
            // Exit the reservation system.
            cout << "Exiting program..." << endl;
            break;
        }
        }
    }
    while (choice != 11);

    return 0;
}
