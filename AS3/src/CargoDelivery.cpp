#include "Package.h"
#include "Truck.h"
#include "Stack.h"
#include "Queue.h"
#include "Destination.h"
#include "CargoDelivery.h"
#include "DLL.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void split(stringstream& ss, vector<string>& out, char token){
    //splits a stringstream accordins to a token and stores it in a string vector
    string inter;
    while(getline(ss, inter, token)){
        out.push_back(inter);
    }
}

int CargoDelivery::destinationIndex(string s){
    //returns the index of a city in the destinations vector
    for(int i=0; i<destinations.size(); i++){
        if(destinations[i].name == s) return i;
    }
    return -1; //error
}

void CargoDelivery::printPart(ofstream& r, Package& rp, Truck& rt, int idx){
    //this is for simplicity
    r << "Packages:" << endl;
    for (int i=0; i<destinations[idx].packages.size(); i++){
        destinations[idx].packages.getItem(rp, i);
        r << rp.name << endl;
    }
    r << "Trucks:" << endl;
        for (int i=0; i<destinations[idx].trucks.size(); i++){
        destinations[idx].trucks.getItem(rt, i);
        r << rt.name << endl;
    }
}

CargoDelivery::CargoDelivery(ifstream& dests, ifstream& packages, ifstream& trucks, ifstream& m, ofstream& r){
    string line;

    //read and store destinations
    while(getline(dests, line)){
        Destination d(line);
        destinations.push_back(d);
    }

    //read and store packages in the destinations
    while(getline(packages, line)){
        stringstream ss(line);
        vector<string> v;
        split(ss, v, ' ');
        int idx = destinationIndex(v[1]);
        Package p = Package(v[0]);
        destinations[idx].packages.push(p);
    }

    //read and store trucks in the destinations
    while(getline(trucks, line)){
        stringstream ss(line);
        vector<string> v;
        split(ss, v, ' ');
        int idx = destinationIndex(v[1]);
        Truck t(v[0], stod(v[2]));
        destinations[idx].trucks.enqueue(t);
    }

    //the missions
    while(getline(m, line)){
        //the doubly linked list will store the moving truck and packages
        DLL<Package> dll = DLL<Package>();
        stringstream mss(line);
        vector<string> mv;
        split(mss, mv, '-');

        //beginning station
        int a_idx = destinationIndex(mv[0]);
        Truck t = Truck();
        destinations[a_idx].trucks.getFront(t);
        dll.add(t);
        destinations[a_idx].trucks.dequeue();

        int flag = stoi(mv[3]);
        while(flag>0){
            Package p = Package();
            destinations[a_idx].packages.getTop(p);
            dll.add(p);
            destinations[a_idx].packages.pop();
            flag--;
        }

        //midway station
        int b_idx = destinationIndex(mv[1]);
        flag = stoi(mv[4]);
        while(flag>0){
            Package p = Package();
            destinations[b_idx].packages.getTop(p);
            dll.add(p);
            destinations[b_idx].packages.pop();
            flag--;
        }

        vector<string> indices;
        stringstream ss(mv[5]);
        split(ss, indices, ',');
        vector<int> indices2;
        for (int i=0; i<indices.size(); i++){
            indices2.push_back(stoi(indices[i]));
        }
        sort(indices2.begin(), indices2.end());

        flag = 0;
        while(flag < indices.size()){
            Package p = Package();
            auto it = find(indices2.begin(), indices2.end(), stoi(indices[flag]));
            int bcd = it - indices2.begin();
            dll.del(p, stoi(indices[flag])-min(flag, bcd));
            destinations[b_idx].packages.push(p);
            flag++;
        }

        //final station
        int c_idx = destinationIndex(mv[2]);
        int abc = dll.size();
        for (int i=1; i<abc; i++){
            Package p = Package();
            dll.del(p, 0);
            destinations[c_idx].packages.push(p);
        }
        destinations[c_idx].trucks.enqueue(t);
    }



    //writing output
    Package rp = Package();
    Truck rt = Truck();

    for (int i=0; i<destinations.size(); i++){
        r << destinations[i].name << endl;
        printPart(r, rp, rt, i);
        r << "-------------" << endl;
    }

}


