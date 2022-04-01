#ifndef PACKAGE_H_INCLUDED
#define PACKAGE_H_INCLUDED

#include <string>

class Package{
public:
    std::string name;

    Package(){}

    Package(std::string s){
        name = s;
    }
};


#endif // PACKAGE_H_INCLUDED
