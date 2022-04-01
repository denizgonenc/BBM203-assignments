#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include <string>
#include "Package.h"

class Truck: public Package{
public:
    double power;

    Truck(){};

    Truck(std::string s, double p) : Package(s){
        power = p;
    }
};

#endif // TRUCK_H_INCLUDED
