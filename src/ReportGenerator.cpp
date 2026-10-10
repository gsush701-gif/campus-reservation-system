
#include "ReportGenerator.h"

#include <iostream>
#include <iomanip>

using namespace std;

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

        if (resources[i].isAvailable())
        {
            record.status = "Available";
        }
        else
        {
            record.status = "Unavailable";
        }

        record.reservationCount =
            manager.countReservationsForResource(record.resourceId);

        if (i < waitingLists.size())
        {
            record.waitingCount = waitingLists[i].size();
        }
        else
        {
            record.waitingCount = 0;
        }

        records.push_back(record);
    }

    return records;
}

void ReportGenerator::displayActiveReservations(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    cout << "\n===== Active Reservations =====\n\n";

    manager.displayReservations();

    cout << "\nTotal active reservations: "
         << manager.countReservations() << endl;
}

void ReportGenerator::displayResourceUtilization(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    cout << "\n===== Resource Utilization =====\n\n";

    cout << left
         << setw(10) << "ID"
         << setw(22) << "Name"
         << setw(20) << "Reservations"
         << '\n';

    cout << string(52, '-') << '\n';

    for (const ResourceRecord& record : records)
    {
        cout << left
             << setw(10) << record.resourceId
             << setw(22) << record.name
             << setw(20) << record.reservationCount
             << '\n';
    }

    cout << "\nTotal active reservations: "
         << manager.countReservations() << endl;
}

void ReportGenerator::displayMostRequested(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    vector<ResourceRecord> sortedRecords =
        Sorting::sortByReservationCount(records);

    cout << "\n===== Most Requested Resources =====\n\n";

    if (sortedRecords.empty() ||
        sortedRecords[0].reservationCount == 0)
    {
        cout << "No reservations yet.\n";
        return;
    }

    cout << left
         << setw(10) << "Rank"
         << setw(10) << "ID"
         << setw(22) << "Name"
         << setw(15) << "Reservations"
         << '\n';

    cout << string(57, '-') << '\n';

    int rank = 1;
    int displayed = 0;

    for (const ResourceRecord& record : sortedRecords)
    {
        if (record.reservationCount == 0)
        {
            break;
        }

        cout << left
             << setw(10) << rank
             << setw(10) << record.resourceId
             << setw(22) << record.name
             << setw(15) << record.reservationCount
             << '\n';

        rank++;
        displayed++;

        if (displayed == 5)
        {
            break;
        }
    }
}

void ReportGenerator::displayWaitingListStatistics(
    const vector<Resource>& resources,
    const ReservationManager& manager,
    const vector<WaitingList>& waitingLists)
{
    vector<ResourceRecord> records =
        buildResourceRecords(resources, manager, waitingLists);

    cout << "\n===== Waiting-List Statistics =====\n\n";

    cout << left
         << setw(10) << "ID"
         << setw(22) << "Name"
         << setw(18) << "Waiting"
         << '\n';

    cout << string(50, '-') << '\n';

    int totalWaiting = 0;

    for (const ResourceRecord& record : records)
    {
        cout << left
             << setw(10) << record.resourceId
             << setw(22) << record.name
             << setw(18) << record.waitingCount
             << '\n';

        totalWaiting += record.waitingCount;
    }

    cout << "\nTotal students waiting: "
         << totalWaiting << endl;
}
