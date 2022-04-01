#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED
#include "Card.h"
#include <string>
#include <sstream>

using namespace std;

class Commands{

public:

    static int matchCommand(string s, Card Waste[24], Card Piles[7][19], Card Foundation[4][13], Card Stock[24]){
        if (s.substr(0,4).compare("move") == 0){
            if (s.substr(5,13).compare("to foundation") == 0){
                if (s.substr(19,4).compare("pile") == 0){
                    int a = s[24] - 48;
                    return moveToFoundation(a, Waste, Piles, Foundation);
                }
                else if (s.substr(19,5).compare("waste") == 0){
                    return moveToFoundation(-1, Waste, Piles, Foundation);
                }
            }
            else {
                if (s.substr(5, 4).compare("pile") == 0){
                    string muse[5];
                    int museidx = 0;
                    stringstream ss(s);
                    string element;
                    while (getline(ss, element, ' ')){
                        muse[museidx] = element;
                        museidx ++;
                    }
                    int a = stoi(muse[2]), b = stoi(muse[3]), c = stoi(muse[4]), ver=0;

                    return solMove(ver, Waste, Piles, Foundation, a, b, c);
                }
                else if (s.substr(5,5).compare("waste") == 0){
                    int ver=1, a=s[11]-48;
                    return solMove(ver, Waste, Piles, Foundation, a);
                }
                else {
                    int ver=2, a=s[16]-48, b=s[18]-48;
                    return solMove(ver, Waste, Piles, Foundation, a, b);
                }
            }

        }

        else if (s.substr(0,4).compare("open") == 0){
            if (s.length() != 5 && s.substr(5,10) == "from stock"){
                return openFromStock(Stock, Waste);
            }
            else {
                int a = s[5] -48;
                return open(a, Piles);
            }
        }

        else if (s.substr(0,4).compare("exit") == 0){
            return 0;
        }

        return -1;
    }



    static int solMove(int ver, Card Waste[], Card Piles[][19], Card Foundation[][13], int a, int b=0, int c=0){
        switch(ver){
        // pile
        case 0:
            {
                int d=18, s=18;
                while (Piles[a][s].isnull && s > 0) s--; //source
                while (Piles[c][d].isnull && d > 0) d--; //destination

                if(Piles[c][0].isnull && Piles[a][s-b].value != 13){
                    return -1;
                }
                if (Piles[c][0].isnull == true){
                    d = 0;
                    while (b >= 0){
                        Piles[c][d] = Piles[a][s-b];
                        Piles[a][s-b].isnull = true;
                        Piles[c][d].open = true;
                        Piles[c][d].isnull = false;
                        b--;
                        d++;
                    }
                    return 1;
                }
                else {
                    int s1 = Piles[a][s-b].suitIndex();
                    int s2 = Piles[c][d].suitIndex();
                    int v1 = Piles[a][s-b].value;
                    int v2 = Piles[c][d].value;

                    if (((((s1 == 0 || s1 == 1) && (s2 == 2 || s2 == 3)) || ((s1 == 2 || s1 == 3) && (s2 == 0 || s2 == 1))) && (v1 == (v2 - 1)))){
                        while (b >= 0){
                            Piles[c][d+1] = Piles[a][s-b];
                            Piles[a][s-b].isnull = true;
                            Piles[c][d+1].open = true;
                            Piles[c][d+1].isnull = false;
                            b--;
                            d++;
                        }
                        return 1;
                    }
                }
            }
            break;
        // waste
        case 1:
            {
                bool wasteEmpty = true;
                for (int i=23; i>=0; i--){
                    if (!Waste[i].isnull) {
                        wasteEmpty = false;
                        break;
                    }
                }
                if (wasteEmpty) return -1;

                int w = 23;
                while (Waste[w].isnull) w--;

                int d = 18;
                if(Piles[a][0].isnull && Waste[w].value != 13) return -1;
                if (!Piles[a][0].isnull){
                    while(Piles[a][d].isnull) d--;

                    int s1 = Waste[w].suitIndex();
                    int s2 = Piles[a][d].suitIndex();
                    int v1 = Waste[w].value;
                    int v2 = Piles[a][d].value;

                    if ((((s1==0 || s1==1) && (s2==2 || s2==3)) || ((s2==0 || s2==1) && (s1==2 || s1==3))) && v1 == (v2 - 1)){
                        Piles[a][d+1] = Waste[w];
                        Waste[w].isnull = true;

                        if(w % 3 == 0){
                            for (int i=23; i>=0; i--){
                                if(!Waste[i].isnull){
                                    int bef = i, af = i + (3 - (i%3));
                                    Waste[af] = Waste[bef];
                                    Waste[bef].isnull = true;
                                    return 1;
                                    break;
                                }

                            }

                        }

                        return 1;
                    }
                }
                else {
                    Piles[a][0] = Waste[w];
                    Waste[w].isnull = true;

                    if(w % 3 == 0){
                            for (int i=23; i>=0; i--){
                                if(!Waste[i].isnull){
                                    int bef = i, af = i + (3 - (i%3));
                                    Waste[af] = Waste[bef];
                                    Waste[bef].isnull = true;
                                    return 1;
                                    break;
                                }

                            }

                        }

                    return 1;
                }
            }
            break;
        //foundation
        case 2:
            {
                if (Foundation[a][0].isnull) return -1;

                int f=12;
                while (Foundation[a][f].isnull) f--;

                int d=18;
                if(Piles[b][0].isnull && Foundation[a][f].value != 13) return -1;
                if(Piles[b][0].isnull) {
                    d = 0;
                    Piles[b][0] = Foundation[a][f];
                    Foundation[a][f].isnull = true;
                    return 1;
                }
                else {
                    while (Piles[b][d].isnull) d--;
                    int s1=Piles[b][d].suitIndex(), s2=Foundation[a][f].suitIndex(), v1=Foundation[a][f].value, v2=Piles[b][d].value;
                    if ((((s1==0 || s1==1) && (s2==2 || s2==3)) || ((s2==0 || s2==1)  && (s1==2 || s1==3))) && v1 == (v2-1)){
                        Piles[b][d+1] = Foundation[a][f];
                        Foundation[a][f].isnull = true;
                        return 1;
                    }
                }
            }
            break;
        }
        return -1;
    }



    static int openFromStock(Card Stock[24], Card Waste[24]){
        if (Stock[0].isnull){
            int j=0;
            for (int i=23; i>=0; i--){
                if (!Waste[i].isnull){
                    Stock[j] = Waste[i];
                    Waste[i].isnull = true;
                    j++;
                }
            }
            return 1;
        }
        else {
            int w=23;
            bool wasteEmpty=true;
            for (int i=23; i>=0; i--){
                if(!Waste[i].isnull) wasteEmpty = false;
            }

            if (wasteEmpty){
                w=0;
            }
            else {
                while(Waste[w].isnull) w--;
                w = w + (3 - (w%3));
            }

            int s=23;
            while (Stock[s].isnull) s--;

            int take=3;
            if (s < 2) take=s+1;

            for(take; take>0; take--, w++, s--){
                Waste[w] = Stock[s];
                Stock[s].isnull = true;
                Waste[w].open = true;
            }
            return 1;
        }
        return -1;
    }



    static int moveToFoundation(int a, Card Waste[24], Card Piles[7][19], Card Foundation[4][13]){
        Card temp;
        int idx;
        int f;
        int y, x;
        bool foundationEmpty = true;

        if (a == -1){
            for (int i=23; i>=0; i--){
                if (!Waste[i].isnull){
                    temp = Waste[i];
                    idx = temp.suitIndex();

                    for(int p=12; p>=0; p--){
                        if(!Foundation[idx][p].isnull){
                            foundationEmpty = false;
                            f = p;
                            break;
                        }
                    }

                    if (!foundationEmpty && (temp.value != (Foundation[idx][f].value + 1))){
                        return -1;
                    }


                    Waste[i].isnull = true;

                    y = i;

                    int w = i;
                    if(w % 3 == 0){
                            for (int j=23; j>=0; j--){
                                if(!Waste[j].isnull){
                                    int bef = j, af = j + (3 - (j % 3));
                                    Waste[af] = Waste[bef];
                                    Waste[bef].isnull = true;
                                    break;
                                }

                            }

                        }
                    break;
                }
            }
        }
        else{
            int z=18;
            for (z; z>=0; z--){
                if (!Piles[a][z].isnull){
                    temp = Piles[a][z];

                    idx = temp.suitIndex();

                    for(int p=12; p>=0; p--){
                        if(!Foundation[idx][p].isnull){
                            foundationEmpty = false;
                            f = p;
                            break;
                        }
                    }

                    if (!foundationEmpty && temp.value != (Foundation[idx][f].value + 1)){
                        return -1;
                    }

                    Piles[a][z].isnull = true;
                    x = z;
                    break;
                }
            }
        }

        if (foundationEmpty && (temp.value == 1)){
            Foundation[idx][0] = temp;
            Foundation[idx][0].isnull = false;
            Foundation[idx][0].open = true;
            return 1;
        }
        else{
            for (int j=12; j>=0; j--){
                if (!Foundation[idx][j].isnull && Foundation[idx][j].value == (temp.value - 1)){
                    Foundation[idx][j+1] = temp;
                    Foundation[idx][j+1].isnull = false;
                    Foundation[idx][j+1].open = true;
                    return 1;
                }
            }
        }

        if (a == -1){
            if (y >= 0 && y <= 23) Waste[y].isnull = false;
        }
        else{
            if (x >= 0 && x <= 18)Piles[a][x].isnull = false;
        }

        return -1;
    }

    static int open(int pile_num, Card Piles[7][19]){
        for (int i=18; i>=0; i--){
            if (!Piles[pile_num][i].isnull){
                if (!Piles[pile_num][i].open){
                    Piles[pile_num][i].open = true;
                    return 1;
                }
                return -1;
            }
        }
        return -1;
    }
};

#endif // COMMANDS_H_INCLUDED
