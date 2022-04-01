#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>
#include "Movie.h"
#include "MovieList.h"

class Movie;

class User{
public:
    int userId;
    std::string userName;
    User* prev;
    User* next;
    MovieList userMovieList;

    User(int userId, std::string userName);
    ~User();
};


#endif // USER_H_INCLUDED
