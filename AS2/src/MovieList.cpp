#include "Movie.h"
#include "MovieList.h"
#include <string>

MovieList::MovieList(){
    head = NULL;
}

MovieList::~MovieList(){
    Movie* curr = head;
    while(curr != NULL){
        Movie* temp = curr -> next;
        delete curr;
        curr = temp;
    }
    head = NULL;
}

bool MovieList::findMovie(int ID){
    //if head is null
    if(head == NULL) return false; //not found

    Movie* temp = head;
    do{
        if(temp->movieId == ID) return true; //found
        temp = temp->next;
    }
    while(temp != head);

    return false; //not found
}

Movie* MovieList::findMovieObj(int ID){
    Movie* temp = head;
    do{
        if(temp->movieId == ID) return temp;
        temp = temp->next;
    }
    while(temp != head);
}


void MovieList::addMovie(int ID, std::string title, int year){
    Movie* mv = new Movie(ID, title, year);

    if(head == NULL){
        head = mv;
        head -> next = head;
    }
    else {
        Movie* temp = head;
        while(temp -> next != head){
            temp = temp -> next;
        }

        temp -> next = mv;
        mv -> next = head;
    }
}

void MovieList::deleteMovie(int ID){
    if (head == NULL) return;

    if(head->movieId == ID && head->next == head){
        free(head);
        head = NULL;
        return;
    }

    if(head->movieId == ID){
        Movie* curr=head;
        Movie* prev;
        do{
            prev = curr;
            curr = curr -> next;
        }
        while(curr != head);

        prev -> next = head -> next;
        free(head);
        head = prev -> next;
        return;
    }

    Movie* prev=head;
    while(prev->next != head && prev->next->movieId != ID){
        prev = prev -> next;
    }

    if(prev->next->movieId == ID){
        Movie* temp = prev -> next;
        prev -> next = temp -> next;
        free(temp);
    }
}
