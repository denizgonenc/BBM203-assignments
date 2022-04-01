#include "Package.h"
#include "DLL.h"
#include <cstdlib>
#include <iostream>

typedef struct Node Node;

template <typename T>
DLL<T>::DLL(){
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

template <typename T>
void DLL<T>::add(T& p){
    //if head is null set new item as head (and tail)
    if(head == nullptr){
        head = new Node;
        head->item = p;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
        _size++;
        return;
    }

    Node* temp = new Node;
    temp->item = p;
    temp->next = nullptr;
    temp->prev = tail;
    tail->next = temp;
    tail = temp;
    _size++;
}

template <typename T>
void DLL<T>::del(T& ret, int index){
    if(head == nullptr || tail == nullptr){
        //error
    }

    int i = -1;

    Node* temp = head;

    while(temp->next != nullptr && i != index){
        temp = temp->next;
        i++;
    }

    if(_size != 2){
        (temp->prev)->next = temp->next;
        if(temp->next != nullptr) (temp->next)->prev = temp->prev;
        ret = temp->item;
        free(temp);
    }
    //if deleting tail
    else{
        head->next = nullptr;
        tail = head;
        ret = temp->item;
        free(temp);
    }
    _size--;
}

template <typename T>
int DLL<T>::size(){
    return _size;
}

template class DLL<Package>;
