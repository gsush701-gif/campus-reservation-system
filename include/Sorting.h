
/*
    Sorting.h
    Defines resource records and sorting functions.
*/

#ifndef SORTING_H
#define SORTING_H

#include <string>
#include <vector>

using namespace std;

// Stores resource information and its reservation counts.
struct ResourceRecord
{
    string resourceId;
    string name;
    string type;
    string status;
    int reservationCount;
    int waitingCount;
};

class Sorting
{
public:
    // Returns a copy sorted by resource name in ascending order.
    static vector<ResourceRecord> sortByName(
        const vector<ResourceRecord>& records);

    // Returns a copy sorted by reservation count in descending order.
    static vector<ResourceRecord> sortByReservationCount(
        const vector<ResourceRecord>& records);

private:
    // Sorts records by name using merge sort.
    static void mergeSortByName(vector<ResourceRecord>& records,
                                int left, int right);

    // Sorts records by reservation count using merge sort.
    static void mergeSortByReservationCount(
        vector<ResourceRecord>& records, int left, int right);

    // Merges two sections in name order.
    static void mergeByName(vector<ResourceRecord>& records,
                            int left, int middle, int right);

    // Merges two sections in reservation count order.
    static void mergeByReservationCount(
        vector<ResourceRecord>& records, int left, int middle, int right);
};

#endif
