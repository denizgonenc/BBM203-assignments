#include <iostream>
#include <fstream>
#include "Card.h"
#include "Commands.h"

using namespace std;


string printBoard(Card Stock[], Card Waste[], Card Foundation[][13], Card Piles[][19]){
    //returns a string that represents the board

    string s = "\n";
    if (Stock[0].isnull) s += "___";
    else s += "@@@";

    s += " ";

    bool wasteEmpty=true;
    for (int i=23; i>=0; i--){
        if(!Waste[i].isnull) wasteEmpty = false;
    }

    int w=23;
    if (wasteEmpty) w=21;
    else{
        while (Waste[w].isnull) w--;
        w -= (w % 3);
    }

    int term = w + 3;
    for (w; w<term; w++){
        if (Waste[w].isnull) s += "___";
        else s += Waste[w].printCard();
        s += " ";
    }

    s += "        ";

    for (int i=0; i<4; i++){
        if (Foundation[i][0].isnull) s += "___";
        else {
            for (int j=12; j>=0; j--){
                if (!Foundation[i][j].isnull){
                    s += Foundation[i][j].printCard();
                    break;
                }
        }
        }
        s += " ";
    }

    s += "\n\n";
    int Midx=0, e, idx;
    for (e=6; e>=0; e--){
        idx = 18;
        while(Piles[e][idx].isnull) idx--;
        if (idx > Midx) Midx = idx;
    }


    for (int j=0; j<=Midx; j++){
        for (int i=0; i<7; i++){
            s += Piles[i][j].printCard();
            s += "   ";
        }
        s += "\n";
    }
    s += "\n";

    return s;
}

bool checkWin(Card Foundation[][13]){
    //returns true if win conditions are met, false otherwise

    bool win = true;
    for (int i=0; i<4; i++){
        if (Foundation[i][12].isnull){
            win = false;
            break;
        }
    }
    return win;
}

int main(int argc, char* argv[]){

    // initialize the deck
    ifstream input;
    input.open(argv[1]);
    string line;
    Card Deck[52];
    for (int i=0; i<52; i++){
        getline(input, line);
        Card c(line[0], line[1], line[2]);
        Deck[i] = c;
    }
    input.close();

    // initialize the piles
    Card Piles[7][19];
    int cardidx = 51;
    for (int j=0; j<7; j++){
        for (int i=0; i<7; i++){
            if (i >= j) {
                Piles[i][j] = Deck[cardidx];
                cardidx--;
                if (i==j) Piles[i][j].open = true;
            }
        }
    }

    //initialize the stock, waste and foundations
    Card Stock[24];
    copy(Deck, Deck + 24, Stock);
    Card Waste[24];
    Card Foundation[4][13];

    //start reading commands and printing output
    ifstream commands;
    commands.open(argv[2]);
    ofstream output;
    output.open(argv[3]);

    output << printBoard(Stock, Waste, Foundation, Piles);

    while(getline(commands, line)){
        int res = Commands::matchCommand(line, Waste, Piles, Foundation, Stock);
        switch (res){
            case -1:
                output << line << "\n\nInvalid Move!\n\n****************************************\n";
                break;
            case 0:
                output << line << "\n\n****************************************\n\n" << "Game Over!\n";
                output.close();
                commands.close();
                return 0;
                break;
            case 1:
                output << line << "\n\n****************************************\n";
                break;
        }

        output << printBoard(Stock, Waste, Foundation, Piles);
        output.flush();

        //check if win conditions are met
        if (checkWin(Foundation)){
            output << "****************************************\n\n";
            output << "You Win!\n\nGame Over!\n";
            output.close();
            commands.close();
            return 0;
        }
    }

    //close output
    commands.close();
    output.close();
    return 0;
}
