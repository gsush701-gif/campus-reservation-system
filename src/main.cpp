#include "Resource.h"

int main() {
    vector<Resource> parts=loadResources("data/resources.txt");

    for (int i=0;i<parts.size();i++) {
        parts[i].display();
    }

    return 0;
}