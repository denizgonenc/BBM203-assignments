#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Movie.h"
#include "MovieList.h"
#include "User.h"
#include "UserList.h"
#include "LibrarySystem.h"

using namespace std;

void split(stringstream& ss, vector<string>& out){
    string inter;
    while(getline(ss, inter, '\t')){
        out.push_back(inter);
    }
}

void matchFunction(string line, LibrarySystem& libsys){
    stringstream ss(line);
    vector<string> input;
    split(ss, input);
    string anan = input[0];
    int code;

    if(anan.compare("addMovie") == 0) code=1;
    else if(anan.compare("deleteMovie") == 0) code=2;
    else if(anan.compare("addUser") == 0)code=3;
    else if(anan.compare("deleteUser") == 0) code=4;
    else if(anan.compare("checkoutMovie") == 0) code=5;
    else if(anan.compare("returnMovie") == 0) code=6;
    else if(anan.compare("showMovie") == 0) code=7;
    else if(anan.compare("showAllMovie") == 0) code=8;
    else if(anan.compare("showUser") == 0) code=9;

    switch(code){
    case 1: {
        int movieId = stoi(input[1]), movieYear = stoi(input[3]);
        string movieTitle = input[2];
        libsys.addMovie(movieId, movieTitle, movieYear);
        }
        break;
    case 2: {
        int movieId = stoi(input[1]);
        libsys.deleteMovie(movieId);
        }
        break;
    case 3: {
        int userId = stoi(input[1]);
        string userName = input[2];
        libsys.addUser(userId, userName);
        }
        break;
    case 4: {
        int userId = stoi(input[1]);
        libsys.deleteUser(userId);
        }
        break;
    case 5: {
        int movieId = stoi(input[1]), userId = stoi(input[2]);
        libsys.checkoutMovie(movieId, userId);
        }
        break;
    case 6: {
        int movieId = stoi(input[1]);
        libsys.returnMovie(movieId);
        }
        break;
    case 7: {
        int movieId = stoi(input[1]);
        libsys.showMovie(movieId);
        }
        break;
    case 8: {
        libsys.showAllMovie();
        }
        break;
    case 9: {
        int userId = stoi(input[1]);
        libsys.showUser(userId);
        }
        break;
    }
    libsys.prev_cmd = code;
}

int main(int argc, const char* argv[])
{
    ifstream commands;
    commands.open(argv[1]);

    ofstream output;
    output.open(argv[2]);
    LibrarySystem libsys(output);
    libsys.prev_cmd = 0;
    output << "===Movie Library System===\n";

    for(string line; getline(commands, line);)
    {
        matchFunction(line, libsys);
        output.flush();
    }

    commands.close();
    output.close();
    return 0;
}
