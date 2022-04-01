#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Tree.h"
#include <fstream>
#include <algorithm>

using namespace std;


int main(int argc, const char* argv[])
{
    string arg1 = argv[1];
    if(arg1.compare("-i") == 0){
        ifstream inputfile;
        inputfile.open(argv[2]);
        stringstream ss;
        ss << inputfile.rdbuf();
        string str = ss.str();




        string arg2 = argv[3];
        if(arg2.compare("-encode") == 0){
            ofstream treefile;
            treefile.open("treefile.txt");

            Tree tree(str, treefile);
            tree.encode();

            ofstream outputfile;
            outputfile.open("vectors.txt");

            for(auto it : tree.characters){
                outputfile << it;
            }
            outputfile << endl;
            for(auto it : tree.huffmans){
                outputfile << it << " ";
            }
            outputfile << endl;

            string sgf = argv[2];
            ofstream decoded;
            decoded.open("decode_" + sgf);
            decoded << tree.result << endl;

            treefile.close();
            outputfile.close();
            decoded.close();
        }
        if(arg2.compare("-decode") == 0){
            ifstream vectors;
            vectors.open("vectors.txt");
            string line;
            vector<char> characters;
            vector<string> codes;
            int counter = 0;
            while(getline(vectors, line)){
                if (counter == 0){
                    for(int i=0; i < line.length(); i++){
                        characters.push_back(line[i]);
                    }
                }
                else{
                    stringstream ss(line);
                    string inter;
                    while(getline(ss, inter, ' ')){
                        codes.push_back(inter);
                    }
                }
            }

            cout << Tree::decode(str, characters, codes) << endl;
            vectors.close();
        }
        inputfile.close();
    }
    else if(arg1.compare("-s") == 0){
        ifstream vectors;
        vectors.open("vectors.txt");
        string line;
        vector<char> characters;
        vector<string> codes;
        int counter = 0;
        while(getline(vectors, line)){
            if (counter == 0){
                for(int i=0; i < line.length(); i++){
                    characters.push_back(line[i]);
                }
            }
            else{
                stringstream ss(line);
                string inter;
                while(getline(ss, inter, ' ')){
                    codes.push_back(inter);
                }
            }
        }

        string asg = argv[2];
        char ch = asg[0];
        auto it = find(characters.begin(), characters.end(), ch);

        if(it != characters.end()){
            int index = it - characters.begin();
            cout << codes[index] << endl;
        }
        else{
            cout << "character not found" << endl;
        }
        vectors.close();
    }
    else if(arg1.compare("-l") == 0){
        ifstream tf;
        tf.open("treefile.txt");
        string line;
        while(getline(tf, line)){
            cout << line << endl;
        }
        tf.close();
    }

    return 0;
}
