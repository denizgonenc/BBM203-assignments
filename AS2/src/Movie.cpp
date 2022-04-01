#include <string>
#include "Movie.h"

Movie::Movie(int ID, std::string title, int year){
    movieId = ID;
    movieTitle = title;
    this -> year = year;
}

Movie::~Movie(){
    next = NULL;
}
