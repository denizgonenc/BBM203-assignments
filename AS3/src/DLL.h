#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#include "Package.h"

template <typename T>
class DLL{
public:
    struct Node{
        T item;
        Node* next;
        Node* prev;
    };
    Node* head;
    DLL();

    void add(T& p);
    int size();
    void del(T& ret,int index);


private:
    int _size;
    Node* tail;
};


#endif // DLL_H_INCLUDED
