#ifndef DESTINATION_H_INCLUDED
#define DESTINATION_H_INCLUDED

#include <string>
#include "Package.h"
#include "Truck.h"
#include "Stack.h"
#include "Queue.h"

class Destination{
public:
    std::string name;
    Stack<Package> packages;
    Queue<Truck> trucks;

    Destination(std::string s) : packages(), trucks(){
        name = s;
    }
};

#endif // DESTINATION_H_INCLUDED
