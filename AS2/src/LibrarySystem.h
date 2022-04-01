#ifndef LIBRARYSYSTEM_H_INCLUDED
#define LIBRARYSYSTEM_H_INCLUDED

#include <string>
#include <fstream>
#include "Movie.h"
#include "MovieList.h"
#include "User.h"
#include "UserList.h"

using namespace std;

class LibrarySystem {
    public:
    MovieList movieList;
    UserList userList;
    ofstream& output;
    int prev_cmd; // 1-9 for all commands

    LibrarySystem(ofstream& of);
    ~LibrarySystem();

    void addMovie(const int movieId, const string movieTitle, const int year);
    void deleteMovie(const int movieId);

    void addUser(const int userId, const string userName);
    void deleteUser(const int userId);

    void checkoutMovie(const int movieId, const int userId);
    void returnMovie(const int movieId);

    void showAllMovie();
    void showMovie(const int movieId);
    void showUser(const int userId);
};


#endif // LIBRARYSYSTEM_H_INCLUDED
