#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node{
public:
    bool isInternal;
    char ch;
    unsigned int freq;
    Node* left;
    Node* right;

    Node(bool isInter, char d, int f);
};


#endif // NODE_H_INCLUDED
