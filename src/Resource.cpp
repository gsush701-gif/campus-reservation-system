#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>

Resource::Resource(string resourceId, string resourceName, string resourceType, bool available) {

    this->resourceId=resourceId;
    this->resourceName=resourceName;
    this->resourceType=resourceType;
    this->available=available;

}

string Resource::getResourceId() const {

    return resourceId;

}

string Resource::getResourceName() const {

    return resourceName;

}

string Resource::getResourceType() const {

    return resourceType;

}

bool Resource::isAvailable() const {

    return available;

}

void Resource::setIsAvailable(bool available) {

    this->available = available;

}

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

vector<Resource> loadResources(string filename) {

    vector<Resource> Resources;

    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return Resources;
    }

    string line;

    while (getline(inFile, line)) {

        stringstream ss(line);

        string ResourceId, ResourceName, category, statusAvailable;

        getline(ss, ResourceId, '|');
        getline(ss, ResourceName, '|');
        getline(ss, category, '|');
        getline(ss, statusAvailable, '|');

        bool isActive = (statusAvailable == "Available");

        Resource p(ResourceId, ResourceName, category, isActive);

        Resources.push_back(p);
    }

    inFile.close();

    return Resources;
}