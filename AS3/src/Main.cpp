#include <iostream>
#include <fstream>

#include "CargoDelivery.h"

using namespace std;

int main(int argc, const char* argv[]){
    //file open
    ifstream dests;
    dests.open(argv[1]);
    ifstream packages;
    packages.open(argv[2]);
    ifstream trucks;
    trucks.open(argv[3]);
    ifstream missions;
    missions.open(argv[4]);

    ofstream result;
    result.open(argv[5]);

    //the main driver code is in this class' constructor
    CargoDelivery cd(dests, packages, trucks, missions, result);

    //file close
    dests.close();
    packages.close();
    trucks.close();
    missions.close();
    result.close();
    return 0;
}
