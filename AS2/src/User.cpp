#include <string>
#include "Movie.h"
#include "MovieList.h"
#include "User.h"

User::User(int ID, std::string name) : userMovieList() {
    userId = ID;
    userName = name;
}

User::~User(){
    prev = NULL;
    next = NULL;
}
