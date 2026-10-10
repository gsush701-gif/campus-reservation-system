
/*
    Searching.h
    Defines search functions for resources.
*/

#ifndef SEARCHING_H
#define SEARCHING_H

#include <string>
#include <vector>

#include "Resource.h"

using namespace std;

class Searching
{
public:
    // Returned when no resource matches the search.
    static const int NOT_FOUND = -1;

    // Returns the index of the resource with the given ID, or NOT_FOUND.
    static int searchResourceById(const vector<Resource>& resources,
                                  const string& resourceId);
};

#endif
