#include "Node.h"

Node::Node(bool isInter, char d, int f){
    isInternal = isInter;
    ch = d;
    freq = f;
}
