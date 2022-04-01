#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
#include <iostream>


class Card{;

public:
    bool isnull;
    bool open;
    char suit;
    int value;

    //For the new array initialization to work
    Card(){
        isnull = true;
    }

    Card(char c1, int c2, int c3, bool b = false)
    {
        suit = c1;
        c2 -= 48;
        c3 -= 48;
        value = c2 * 10 + c3;
        open = b;
        isnull = false;
    }

    std::string printCard(){
        std::string s;
        if (isnull == true) s = "   ";
        else if (open == true){
            char buffer[3];
            sprintf(buffer, "%c%02d", suit, value);
            s = std::string(&buffer[0], 3);
            return s;
        }
        else s = "@@@";
        return s;
    }

    int suitIndex(){
        int j;
        switch (suit) {
        case 'H':
            j = 0;
            break;
        case 'D':
            j = 1;
            break;
        case 'S':
            j = 2;
            break;
        case 'C':
            j = 3;
            break;
        }
        return j;
    }

};




#endif // CARD_H_INCLUDED
