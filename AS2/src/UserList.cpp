#include <string>
#include "Movie.h"
#include "MovieList.h"
#include "User.h"
#include "UserList.h"

UserList::UserList(){
    head = NULL;
}

UserList::~UserList(){
    User* curr = head;
    while(curr != NULL){
        User* temp = curr -> next;
        delete curr;
        curr = temp;
    }
    head = NULL;
}

void UserList::addUser(int ID, std::string name){
    User* us = new User(ID, name);

    if(head == NULL){
        head = us;
        head->next = head;
        head->prev = head;
        return;
    }

    User* last = head->prev;
    us -> next = head;
    head -> prev = us;
    last -> next = us;
    us -> prev = last;
}

void UserList::deleteUser(int ID){
    if(head == NULL) return;

    if(head->userId == ID && head->next == head){
        free(head);
        head = NULL;
        return;
    }

    if(head->userId == ID){
        User* curr = head;
        User* last = head -> prev;
        head = head -> next;
        last -> next = head;
        head -> prev = last;
        free(curr);
        return;
    }

    User* curr = head->next;
    while(curr != head && curr->userId != ID){
        curr = curr -> next;
    }

    if(curr->userId == ID){
        User* last = curr->prev;
        User* temp = curr->next;
        last->next = temp;
        temp->prev = last;
        free(curr);
    }
}

bool UserList::findMovie(int ID){
    if(head == NULL) return false;

    User* temp = head;

    do{
        if(temp->userMovieList.findMovie(ID)) return true;
        temp = temp -> next;
    }
    while(temp != head);

    return false;
}

bool UserList::findUser(int ID){
    if(head == NULL) return false;

    User* temp = head;

    do{
        if(temp -> userId == ID) return true;
        temp = temp -> next;
    }
    while(temp != head);

    return false;
}

Movie* UserList::findMovieObj(int ID){
    User* temp = head;

    do{
        if(temp->userMovieList.findMovie(ID)) return temp->userMovieList.findMovieObj(ID);
        temp = temp -> next;
    }
    while(temp != head);
}

User* UserList::findUserObj(int ID){
    User* temp = head;

    do{
        if(temp -> userId == ID) return temp;
        temp = temp -> next;
    }
    while(temp != head);
}

User* UserList::findUserObjByMovie(int ID){
    User* temp = head;

    do{
        if(temp->userMovieList.findMovie(ID)) return temp;
        temp = temp -> next;
    }
    while(temp != head);

}
