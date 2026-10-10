
/*
    Resource.cpp
    Implements the Resource class and loads resources from a file.
*/

#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Creates a resource with the given ID, name, type, and availability.
Resource::Resource(string resourceId, string resourceName, string resourceType, bool available) {
    this->resourceId = resourceId;
    this->resourceName = resourceName;
    this->resourceType = resourceType;
    this->available = available;
}

// Returns the resource ID.
string Resource::getResourceId() const {
    return resourceId;
}

// Returns the resource name.
string Resource::getResourceName() const {
    return resourceName;
}

// Returns the resource type.
string Resource::getResourceType() const {
    return resourceType;
}

// Returns true if the resource is available.
bool Resource::isAvailable() const {
    return available;
}

// Marks the resource as available or unavailable.
void Resource::setIsAvailable(bool available) {
    this->available = available;
}

// Prints the resource's ID, name, type, and status on one line.
void Resource::display() const {
    cout << "ID: " << resourceId
         << " | Name: " << resourceName
         << " | Type: " << resourceType
         << " | Status: ";

    if (available) {
        cout << "Available";
    }
    else {
        cout << "Unavailable";
    }

    cout << endl;
}

// Reads resources from a pipe-delimited file: ID|Name|Type|Status.
// Returns an empty list if the file cannot be opened.
vector<Resource> loadResources(string filename) {
    vector<Resource> Resources;

    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return Resources;
    }

    string line;

    while (getline(inFile, line)) {

        // Strip a trailing carriage return left by Windows line endings.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Skip blank lines.
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string ResourceId, ResourceName, category, statusAvailable;

        // Split the line on '|' into its four fields.
        getline(ss, ResourceId, '|');
        getline(ss, ResourceName, '|');
        getline(ss, category, '|');
        getline(ss, statusAvailable, '|');

        // Any status other than "Available" counts as unavailable.
        bool isActive = (statusAvailable == "Available");

        Resource p(ResourceId, ResourceName, category, isActive);

        Resources.push_back(p);
    }

    inFile.close();

    return Resources;
}
