#include "Queue.h"
#include "Truck.h"
#include <cstdlib>
#include <iostream>

typedef struct QueueNode QueueNode;

template<typename T>
Queue<T>::Queue(){
    _headNode = nullptr;
    _lastNode = nullptr;
    _size = 0;
}

template<typename T>
Queue<T>::~Queue(){
    //TBI
}

template<typename T>
bool Queue<T>::isEmpty()const{
    if(_headNode == nullptr) return true;
    return false;
}

template<typename T>
int Queue<T>::size()const{
    return _size;
}

template<typename T>
void Queue<T>::enqueue(const T& newItem){
    //if head is null, set new item as head
    if(_headNode == nullptr){
        _headNode = new QueueNode;
        _headNode->item = newItem;
        _headNode->next = nullptr;
        _lastNode = _headNode;
        _size++;
        return;
    }

    QueueNode* temp = new QueueNode;
    temp->item = newItem;
    _lastNode->next = temp;
    _lastNode = temp;
    _size++;
}

template<typename T>
void Queue<T>::dequeue(){
    //if head is null?
    QueueNode* temp = _headNode;
    _headNode = _headNode->next;
    free(temp);
    _size--;
}

template<typename T>
void Queue<T>::getFront(T& queueTop)const{
    //if head is null?
    queueTop = _headNode->item;
}

template<typename T>
void Queue<T>::getItem(T& ret, int index)const{
    //if head is null?

    QueueNode* temp = _headNode;
    while(index>0 && temp->next != nullptr){
        temp = temp->next;
        index--;
    }
    ret = temp->item;
}

template class Queue<Truck>;
