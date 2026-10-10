
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include <string>

#include "Resource.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "Sorting.h"

using namespace std;

class ReportGenerator
{
public:
    static void displayActiveReservations(
        const vector<Resource>& resources,
        const ReservationManager& manager,
        const vector<WaitingList>& waitingLists);

    static void displayResourceUtilization(
        const vector<Resource>& resources,
        const ReservationManager& manager,
        const vector<WaitingList>& waitingLists);

    static void displayMostRequested(
        const vector<Resource>& resources,
        const ReservationManager& manager,
        const vector<WaitingList>& waitingLists);

    static void displayWaitingListStatistics(
        const vector<Resource>& resources,
        const ReservationManager& manager,
        const vector<WaitingList>& waitingLists);

private:
    static vector<ResourceRecord> buildResourceRecords(
        const vector<Resource>& resources,
        const ReservationManager& manager,
        const vector<WaitingList>& waitingLists);
};

#endif
