#ifndef MOVIELIST_H_INCLUDED
#define MOVIELIST_H_INCLUDED

#include <string>
#include "Movie.h"

class MovieList{
public:
    Movie* head;

    MovieList();
    ~MovieList();

    bool findMovie(int ID);
    Movie* findMovieObj(int ID);
    void addMovie(int ID, std::string title, int year);
    void deleteMovie(int ID);
};

#endif // MOVIELIST_H_INCLUDED
