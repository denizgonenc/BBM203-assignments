#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "Node.h"
#include <queue>
#include <utility>
#include <vector>
#include <string>
#include <fstream>


class Tree{
public:
    Node* root;
    std::vector<char> characters;
    std::vector<std::string> huffmans;
    std::string input;
    std::string result;
    std::ofstream& out;

    Tree(std::string s, std::ofstream& outpath);
    void convert(Node* node, std::string s);
    void encode();
    static std::string decode(std::string h, std::vector<char> chars, std::vector<std::string> huff);
    void listTree(Node* node, int rec, bool check, int checkrec);
    std::string returnEncoding(char ch);
};


#endif // TREE_H_INCLUDED
