#ifndef USERLIST_H_INCLUDED
#define USERLIST_H_INCLUDED

#include <string>
#include "Movie.h"
#include "MovieList.h"
#include "User.h"

class UserList{
public:
    User* head;

    UserList();
    ~UserList();

    void addUser(int ID, std::string name);
    void deleteUser(int ID);
    bool findMovie(int movieID);
    bool findUser(int userID);
    Movie* findMovieObj(int ID);
    User* findUserObj(int userID);
    User* findUserObjByMovie(int movieID);
};

#endif // USERLIST_H_INCLUDED
