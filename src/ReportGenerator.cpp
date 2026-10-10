
#include "ReportGenerator.h"

#include <iostream>
#include <iomanip>

using namespace std;

// Builds report records without reordering the original resources.
// Waiting-list counts use the corresponding resource's original index.
vector<ResourceRecord> ReportGenerator::buildResourceRecords(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records;

    for (size_t i = 0; i < resources.size(); i++)
    {
        ResourceRecord record;

        record.resourceId = resources[i].getResourceId();
        record.name = resources[i].getResourceName();
        record.type = resources[i].getResourceType();
        record.status = resources[i].isAvailable()
                            ? "Available"
                            : "Unavailable";

        record.reservationCount =
            manager.countReservationsForResource(record.resourceId);

        if (i < waitingLists.size())
        {
            record.waitingCount =
                static_cast<int>(waitingLists[i].size());
        }
        else
        {
            record.waitingCount = 0;
        }

        records.push_back(record);
    }

    return records;
}

// Displays the active reservation list and its total count.
void ReportGenerator::displayActiveReservations(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    (void)resources;
    (void)waitingLists;

    cout << "\n===== Active Reservations =====" << endl;
    manager.displayReservations();

    cout << "\nTotal active reservations: "
         << manager.countReservations() << endl;
}

// Displays reservation and waiting-list counts for every resource.
void ReportGenerator::displayResourceUtilization(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    cout << "\n===== Resource Utilization =====" << endl;

    cout << left
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(22) << "Type"
         << setw(14) << "Status"
         << setw(15) << "Reservations"
         << setw(12) << "Waiting"
         << endl;

    cout << string(100, '-') << endl;

    for (const ResourceRecord& record : records)
    {
        cout << left
             << setw(12) << record.resourceId
             << setw(25) << record.name
             << setw(22) << record.type
             << setw(14) << record.status
             << setw(15) << record.reservationCount
             << setw(12) << record.waitingCount
             << endl;
    }

    cout << "\nTotal resources: " << resources.size() << endl;

    cout << "Total active reservations: "
         << manager.countReservations() << endl;
}

// Displays the five most requested resources, excluding zero counts.
void ReportGenerator::displayMostRequested(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    // Sorting returns a copy, preserving the original resource order.
    vector<ResourceRecord> sortedRecords =
        Sorting::sortByReservationCount(records);

    cout << "\n===== Most Requested Resources =====" << endl;

    if (sortedRecords.empty() ||
        sortedRecords[0].reservationCount == 0)
    {
        cout << "No reservations yet." << endl;
        return;
    }

    cout << left
         << setw(8)  << "Rank"
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(22) << "Type"
         << setw(14) << "Status"
         << setw(15) << "Reservations"
         << setw(12) << "Waiting"
         << endl;

    cout << string(108, '-') << endl;

    int rank = 1;

    for (const ResourceRecord& record : sortedRecords)
    {
        // Stop when no reservations remain or the top five are shown.
        if (record.reservationCount == 0 || rank > 5)
        {
            break;
        }

        cout << left
             << setw(8)  << rank
             << setw(12) << record.resourceId
             << setw(25) << record.name
             << setw(22) << record.type
             << setw(14) << record.status
             << setw(15) << record.reservationCount
             << setw(12) << record.waitingCount
             << endl;

        rank++;
    }
}

// Displays waiting-list counts and summary statistics.
void ReportGenerator::displayWaitingListStatistics(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    (void)manager;

    cout << "\n===== Waiting-List Statistics =====" << endl;

    cout << left
         << setw(12) << "ID"
         << setw(25) << "Resource"
         << setw(15) << "Waiting"
         << endl;

    cout << string(52, '-') << endl;

    int totalWaiting = 0;
    int resourcesWithWaiting = 0;

    for (size_t i = 0; i < resources.size(); i++)
    {
        int waitingCount = 0;

        if (i < waitingLists.size())
        {
            waitingCount =
                static_cast<int>(waitingLists[i].size());
        }

        totalWaiting += waitingCount;

        if (waitingCount > 0)
        {
            resourcesWithWaiting++;
        }

        cout << left
             << setw(12) << resources[i].getResourceId()
             << setw(25) << resources[i].getResourceName()
             << setw(15) << waitingCount
             << endl;
    }

    cout << "\nTotal students waiting: " << totalWaiting << endl;

    cout << "Resources with waiting students: "
         << resourcesWithWaiting << endl;
}

// Displays a sorted copy of the resource records.
void ReportGenerator::displaySortedResources(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists,
    int sortChoice)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    vector<ResourceRecord> sortedRecords;

    // Select the sorting method requested by the user.
    if (sortChoice == 1)
    {
        sortedRecords = Sorting::sortByName(records);

        cout << "\n===== Resources Sorted by Name =====" << endl;
    }
    else if (sortChoice == 2)
    {
        sortedRecords = Sorting::sortByReservationCount(records);

        cout << "\n===== Resources Sorted by Reservation Count ====="
             << endl;
    }
    else
    {
        cout << "Invalid sorting choice." << endl;
        return;
    }

    cout << left
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(22) << "Type"
         << setw(14) << "Status"
         << setw(15) << "Reservations"
         << setw(12) << "Waiting"
         << endl;

    cout << string(100, '-') << endl;

    for (const ResourceRecord& record : sortedRecords)
    {
        cout << left
             << setw(12) << record.resourceId
             << setw(25) << record.name
             << setw(22) << record.type
             << setw(14) << record.status
             << setw(15) << record.reservationCount
             << setw(12) << record.waitingCount
             << endl;
    }
}
