#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED

#include "Node.h"

class Compare{
public:
    bool operator() (Node* a, Node* b){
    return a->freq > b->freq;
    }
};



#endif // COMPARE_H_INCLUDED
