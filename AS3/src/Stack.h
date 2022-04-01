#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Package.h"
#include <cstdlib>
#include <iostream>

template <typename T>
class Stack {
	public:
	Stack(){
        _head = nullptr;
        _size = 0;
	}
	~Stack(){}

	bool isEmpty() const{
        if(_head == nullptr) return true;
        return false;
	}

	int size() const{
        return _size;
	}

	//Push: Place item on top of the stack
	void push(const T& newItem){
        //if head is null
        if(_head == nullptr){
            _head = new ListNode;
            _head->item = newItem;
            _head->next = nullptr;
            _size++;
            return;
        }

        struct ListNode* temp = new ListNode;
        temp->item = newItem;
        temp->next = _head;
        _head = temp;
        _size++;
	}

	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const{
	    //if head is null?
        stackTop = _head->item;
	}

	//Pop: Remove item from the top of the stack
	void pop(){
        //if head is null?

        struct ListNode* temp = _head;
        _head = _head->next;
        free(temp);
        _size--;
	}

	void getItem(T& ret, int index)const{
        //if head is null?

        ListNode* temp = _head;
        while(index>0 && temp->next != nullptr){
            temp = temp->next;
            index--;
        }
        ret = temp->item;
	}

private:
    struct ListNode{
        T item;
        ListNode* next;
    };
	ListNode* _head;
	int _size;

};

#endif // STACK_H_INCLUDED

