#include "Node.h"
#include <utility>
#include <vector>
#include "Tree.h"
#include <string>
#include <cstring>
#include <queue>
#include <assert.h>
#include "Compare.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

Tree::Tree(string s, ofstream& outpath) : out(outpath){
    input = s;

    //calculate the frequencies
    char str[s.length()];
    strcpy(str, s.c_str());
    int i, freq[256] = {0};
    for (i = 0; str[i] != '\0'; i++){
        freq[tolower(str[i])]++;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> q;
    for(i = 0; i < 256; i++){
        if (freq[i] != 0){
            pair<int, string> p;
            p.first = freq[i];
            p.second = char(i);
            q.push(p);
        }
    }

    //initializing single nodes from priority queue q
    priority_queue<Node*, vector<Node*>, Compare> nodeq;
    while(!q.empty()){
        assert(q.top().second.size() == 1);
        char ch = q.top().second[0];
        Node* temp = new Node(false, ch, q.top().first);
        temp->left = temp->right = nullptr;
        nodeq.push(temp);
        q.pop();
    }

    Node* prev;
    int counter = 1;
    while(nodeq.size() > 1){
        Node* top = nodeq.top();

        if (counter % 2 == 0){
            Node* temp = new Node(true, ' ', prev->freq + top->freq);
            temp -> left = prev;
            temp -> right = top;
            nodeq.pop();
            nodeq.push(temp);
        }
        else{
            prev = top;
            nodeq.pop();
        }

        counter++;
    }

    root = new Node(true, ' ', prev->freq + nodeq.top()->freq);
    root -> left = prev;
    root -> right = nodeq.top();

}

void Tree::convert(Node* node, string s){
    if (node->left != nullptr){
        convert(node->left, s + "0");
    }
    if(node->right != nullptr){
        convert(node->right, s + "1");
    }

    if(node->isInternal != true){
        characters.push_back(node->ch);
        huffmans.push_back(s);
    }
}

void Tree::encode(){
    convert(root, "");
    result = "";

    for(int i = 0; i < input.length(); i++){
        auto it = find(characters.begin(), characters.end(), tolower(input[i]));
        if (it != characters.end()){
            int index = it - characters.begin();
            result += huffmans[index];
        }
        else{
            cout << "char not in vector" << endl;
        }
    }

    cout << result << endl;
}

string Tree::decode(string h, vector<char> chars, vector<string> huff){
    string res = "";
    string s = "";
    for (int i = 0; i < h.length(); i++){
        s += h[i];
        auto it = find(huff.begin(), huff.end(), s);
        if (it != huff.end()){
            int index = it - huff.begin();
            res += chars[index];
            s = "";
        }
    }
    return res;
}

string multiplyString(int a, bool check){
    string res = "";
    if(a == 0) return res;
    if(a == 1) return "\t";
    while(a > 0){
        if (check){
            res += "\t";
            if (a != 1) res += "|";
        }
        else{
            res += "\t";
        }
        a--;
    }
    return res;
}

//node = root, rec = 0 and check = false in initial function
void Tree::listTree(Node* node, int rec, bool check, int checkrec){
    out << multiplyString(rec, check) << "+- ";
    if(node->isInternal){
        out << "IN" << endl;
    }
    else{
        out << node->ch << endl;
    }

    if(node->left != nullptr){
        if(node->right != nullptr){
            listTree(node->left, rec+1, true, rec);
            if (checkrec == rec){
                check = false;
                checkrec = -1;
            }
        }
        else listTree(node->left, rec+1, false, -1);
    }

    if(node->right != nullptr){
        listTree(node->right, rec+1, check, checkrec);
    }
}

string Tree::returnEncoding(char ch){
    auto it = find(characters.begin(), characters.end(), tolower(ch));
    if (it != characters.end()){
        int index = it - characters.begin();
        return huffmans[index];
    }
    else {
        cout << "character not in tree" << endl;
    }
}
