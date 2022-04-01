#include <string>
#include <fstream>
#include <iostream>
#include "Movie.h"
#include "User.h"
#include "LibrarySystem.h"

using namespace std;

LibrarySystem::LibrarySystem(ofstream& of) : output(of), movieList(), userList() {} ;

LibrarySystem::~LibrarySystem(){
}

//code 1
void LibrarySystem::addMovie(const int movieId, const string movieTitle, const int year){
    if(prev_cmd != 1) output << "\n===addMovie() method test===\n";

    if(movieList.findMovie(movieId) || userList.findMovie(movieId)){
        output << "Movie " << movieId << " already exists\n";
    }
    else{
    movieList.addMovie(movieId, movieTitle, year);
    output << "Movie " << movieId << " has been added\n";
    }
};

//code 2
void LibrarySystem::deleteMovie(const int movieId){
    if(prev_cmd != 2) output << "\n===deleteMovie() method test===\n";

    Movie* mv;
    if(movieList.findMovie(movieId)){
        output << "Movie " << movieId << " has not been checked out\n";
        mv = movieList.findMovieObj(movieId);
        movieList.deleteMovie(movieId);
        output << "Movie " << movieId << " has been deleted\n";
    }
    else if (userList.findMovie(movieId)){
        output << "Movie " << movieId << " has been checked out\n";
        User* user = userList.findUserObjByMovie(movieId);
        mv = user->userMovieList.findMovieObj(movieId);
        user->userMovieList.deleteMovie(movieId);
        output << "Movie " << movieId << " has been deleted\n";
    }
    else{
        output << "Movie " << movieId << " does not exist\n";
    }
};

//code 3
void LibrarySystem::addUser(const int userId, const string userName){
    if(prev_cmd != 3) output << "\n===addUser() method test===\n";

    if(userList.findUser(userId)){
        output << "User " << userId << " already exists\n";
        return;
    }

    User* user = new User(userId, userName);
    userList.addUser(userId, userName);
    output << "User " << userId << " has been added\n";
};

//code 4
void LibrarySystem::deleteUser(const int userId){
    if(prev_cmd != 4) output << "\n===deleteUser() method test===\n";

    if(!userList.findUser(userId)){
        output << "User " << userId << " does not exist\n";
    }
    else{
        User* user = userList.findUserObj(userId);
        userList.deleteUser(userId);
        userList.deleteUser(userId);
        output << "User " << userId << " has been deleted\n";
    }
};

//code 5
void LibrarySystem::checkoutMovie(const int movieId, const int userId){
    if(prev_cmd != 5) output << "\n===checkoutMovie() method test===\n";

    if(!movieList.findMovie(movieId) || userList.findMovie(movieId)){
        output << "Movie " << movieId << " does not exist for checkout\n";
        return;
    }

    if(!userList.findUser(userId)){
        output << "User " << userId << " does not exist for checkout\n";
        return;
    }

    Movie* movie = movieList.findMovieObj(movieId);
    User* user = userList.findUserObj(userId);
    user -> userMovieList.addMovie(movie->movieId, movie->movieTitle, movie->year);
    movieList.deleteMovie(movie->movieId);
    output << "Movie " << movieId << " has been checked out by User " << userId << "\n";
};

//code 6
void LibrarySystem::returnMovie(const int movieId){
    if(prev_cmd != 6) output << "\n===returnMovie() method test===\n";

    if(userList.findMovie(movieId)){
        User* user = userList.findUserObjByMovie(movieId);
        Movie* mv = userList.findMovieObj(movieId);
        movieList.addMovie(mv->movieId, mv->movieTitle, mv->year);
        user->userMovieList.deleteMovie(mv->movieId);
        output << "Movie " << movieId << " has been returned\n";
    }
    else if(movieList.findMovie(movieId)){
        output << "Movie " << movieId << " has not been checked out\n";
    }
    else{
        output << "Movie " << movieId << " not exist in the library\n";
    }
};

//code 8
void LibrarySystem::showAllMovie(){
    if(prev_cmd != 8) output << "\n===showAllMovie() method test===\nMovie id - Movie name - Year - Status\n";

    if(movieList.head != NULL){
        Movie* temp = movieList.head;
        do{
            output << temp->movieId << " " << temp->movieTitle << " " << temp->year << " Not checked out\n";
            temp = temp -> next;
        }
        while(temp != movieList.head);
    }

    if(userList.head != NULL){
        User* temp2 = userList.head;
        do{
            if(temp2->userMovieList.head != NULL){
                Movie* temp3 = temp2->userMovieList.head;
                do{
                output << temp3->movieId << " " << temp3->movieTitle << " " << temp3->year << " Checked out by User " << temp2->userId << "\n";
                temp3 = temp3 -> next;
                }
                while(temp3 != temp2->userMovieList.head);
            }
            temp2 = temp2 -> next;
        }
        while(temp2 != userList.head);
    }
};

//code 7
void LibrarySystem::showMovie(const int movieId){
    if(prev_cmd != 7) output << "\n===showMovie() method test===\n";

    if(movieList.findMovie(movieId)){
        Movie* mv = movieList.findMovieObj(movieId);
        output << mv->movieId << " " << mv->movieTitle << " " << mv->year << " Not checked out\n";
    }
    else if(userList.findMovie(movieId)){
        Movie* mv = userList.findMovieObj(movieId);
        User* user = userList.findUserObjByMovie(movieId);
        output << mv->movieId << " " << mv->movieTitle << " " << mv->year << " Checked out by User " << user->userId << "\n";
    }
    else{
        output << "Movie with the id " << movieId << " does not exist\n";
    }
};

//code 9
void LibrarySystem::showUser(const int userId){
    if(prev_cmd != 9) output << "\n===showUser() method test===\n";

    if(!userList.findUser(userId)){
        output << "User" << userId<< "does not exist in the system\n";
        return;
    }

    User* user = userList.findUserObj(userId);
    output << "User id: " << userId << " User name: " << user->userName << "\n";
    output << "User " << userId << " checked out the following Movies:\n";
    if(user->userMovieList.head != NULL){
        output << "Movie id - Movie name - Year\n";
        Movie* temp = user->userMovieList.head;
        do{
            output << temp->movieId << " " << temp->movieTitle << " " << temp->year << "\n";
            temp = temp -> next;
        }
        while(temp != user->userMovieList.head);
    }
};
