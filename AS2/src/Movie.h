#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

#include <string>

class Movie{
public:
    int movieId;
    std::string movieTitle;
    int year;
    Movie* next;

    Movie(int movieId, std::string movieTitle, int year);
    ~Movie();
};

#endif // MOVIE_H_INCLUDED
