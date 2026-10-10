
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include <string>

#include "Resource.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "Sorting.h"

// Generates reports without changing the original resource order.
class ReportGenerator
{
public:
    // Displays active reservations and their total count.
    static void displayActiveReservations(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists
    );

    // Displays each resource's status and reservation statistics.
    static void displayResourceUtilization(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists
    );

    // Displays up to five resources that have reservations.
    static void displayMostRequested(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists
    );

    // Displays waiting-list counts for resources and overall statistics.
    static void displayWaitingListStatistics(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists
    );

    // Displays a sorted copy of the resource report records.
    // Choice 1 sorts by name; choice 2 sorts by reservation count.
    static void displaySortedResources(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists,
        int sortChoice
    );

private:
    // Builds report records using the original resource positions.
    static std::vector<ResourceRecord> buildResourceRecords(
        const std::vector<Resource>& resources,
        const ReservationManager& manager,
        const std::vector<WaitingList>& waitingLists
    );
};

#endif
