#ifndef CARGODELIVERY_H_INCLUDED
#define CARGODELIVERY_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include "Package.h"
#include "Truck.h"
#include "Stack.h"
#include "Queue.h"
#include "Destination.h"

using namespace std;

class CargoDelivery{
public:
    vector<Destination> destinations;

    CargoDelivery(ifstream& dests, ifstream& packages, ifstream& trucks, ifstream& m, ofstream& r);

    int destinationIndex(string s);
    void printPart(ofstream& r, Package& rp, Truck& rt, int idx);
};

#endif // CARGODELIVERY_H_INCLUDED
