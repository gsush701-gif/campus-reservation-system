
/*
    Searching.cpp
    Implements linear search for resources.
*/

#include "Searching.h"

// Checks each resource in order and returns the index of the first match.
int Searching::searchResourceById(const vector<Resource>& resources,
                                  const string& resourceId)
{
    for (int i = 0; i < static_cast<int>(resources.size()); i++)
    {
        if (resources[i].getResourceId() == resourceId)
        {
            return i;
        }
    }

    return NOT_FOUND;
}
