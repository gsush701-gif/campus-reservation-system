#ifndef RESOURCE_H

#define RESOURCE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Resource {

private:

    string resourceId;

    string resourceName;

    string resourceType;

    bool available;

public:

    Resource(string resourceId, string resourceName, string resourceType, bool available);

    string getResourceId() const;

    string getResourceName() const;

    string getResourceType() const;

    bool isAvailable() const;

    void setIsAvailable(bool available);

    void display() const;
};

vector<Resource> loadResources(string filename);

#endif