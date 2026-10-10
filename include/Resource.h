/*
    Resource.h
    Represents a campus resource that students can reserve.
*/

#ifndef RESOURCE_H

#define RESOURCE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Resource {

private:

    // Unique ID, such as "R101".
    string resourceId;

    // Display name, such as "Study Room 101".
    string resourceName;

    // Category, such as "Study Room".
    string resourceType;

    // True if the resource can currently be reserved.
    bool available;

public:

    // Creates a resource with the given ID, name, type, and availability.
    Resource(string resourceId, string resourceName, string resourceType, bool available);

    // Returns the resource ID.
    string getResourceId() const;

    // Returns the resource name.
    string getResourceName() const;

    // Returns the resource type.
    string getResourceType() const;

    // Returns true if the resource is available.
    bool isAvailable() const;

    // Marks the resource as available or unavailable.
    void setIsAvailable(bool available);

    // Prints the resource's ID, name, type, and status on one line.
    void display() const;
};

// Reads resources from a pipe-delimited file: ID|Name|Type|Status.
vector<Resource> loadResources(string filename);

#endif
