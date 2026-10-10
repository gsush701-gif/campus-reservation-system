
/*
    Sorting.cpp
    Implements stable merge sorting for resource records.
*/

#include "Sorting.h"

// Returns a sorted copy of the records by name.
vector<ResourceRecord> Sorting::sortByName(
    const vector<ResourceRecord>& records)
{
    vector<ResourceRecord> sortedRecords = records;

    if (sortedRecords.size() > 1)
    {
        mergeSortByName(sortedRecords, 0,
                        static_cast<int>(sortedRecords.size()) - 1);
    }

    return sortedRecords;
}

// Returns a sorted copy by reservation count, highest first.
vector<ResourceRecord> Sorting::sortByReservationCount(
    const vector<ResourceRecord>& records)
{
    vector<ResourceRecord> sortedRecords = records;

    if (sortedRecords.size() > 1)
    {
        mergeSortByReservationCount(
            sortedRecords, 0,
            static_cast<int>(sortedRecords.size()) - 1);
    }

    return sortedRecords;
}

// Divides the records into smaller sections for name sorting.
void Sorting::mergeSortByName(vector<ResourceRecord>& records,
                              int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortByName(records, left, middle);
    mergeSortByName(records, middle + 1, right);
    mergeByName(records, left, middle, right);
}

// Divides the records into smaller sections for count sorting.
void Sorting::mergeSortByReservationCount(
    vector<ResourceRecord>& records, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortByReservationCount(records, left, middle);
    mergeSortByReservationCount(records, middle + 1, right);

    mergeByReservationCount(records, left, middle, right);
}

// Merges two sections by name, preserving the order of equal names.
void Sorting::mergeByName(vector<ResourceRecord>& records,
                          int left, int middle, int right)
{
    vector<ResourceRecord> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right)
    {
        if (records[i].name <= records[j].name)
        {
            temp.push_back(records[i]);
            i++;
        }
        else
        {
            temp.push_back(records[j]);
            j++;
        }
    }

    while (i <= middle)
    {
        temp.push_back(records[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(records[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++)
    {
        records[left + k] = temp[k];
    }
}

// Merges two sections by reservation count, preserving ties.
void Sorting::mergeByReservationCount(
    vector<ResourceRecord>& records, int left, int middle, int right)
{
    vector<ResourceRecord> temp;

    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right)
    {
        if (records[i].reservationCount >= records[j].reservationCount)
        {
            temp.push_back(records[i]);
            i++;
        }
        else
        {
            temp.push_back(records[j]);
            j++;
        }
    }

    while (i <= middle)
    {
        temp.push_back(records[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(records[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++)
    {
        records[left + k] = temp[k];
    }
}
