#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <vector>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void findPossibilities(int floatsLeft, const string& in, int n, std::string& floating, vector<string> posb, std::set<std::string>& final, const std::set<std::string>& dict);
int spacesLeft(string inp, int curr);
void nextLetter(string prefix, int floatsLeft, const string& in, int n, std::string& floating, vector<string> posb, std::set<std::string>& final, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //Find Possibilities
    vector<string> posb;
    std::set<std::string> mySet;
    string floaters = floating;
    int floats = spacesLeft(in, 0);
    findPossibilities(floats, in, 0, floaters, posb, mySet, dict);
    return mySet;
}

// Define any helper functions 
void findPossibilities(int floatsLeft, const string& in, int n, std::string& floating, vector<string> posb, std::set<std::string>& final, const std::set<std::string>& dict){
    /*
    for (int i = 0; i < (int) posb.size(); i++){
        cout << posb[i] << " ";
    }
    cout << endl;
    */
    if (n == (int) in.length()) {
        for (int i = 0; i < (int) posb.size(); i++){
            std::set<std::string>::iterator it;
            it = dict.find(posb[i]);
            if (it != dict.end()){
                final.insert(posb[i]);
            }
        }
    }
    else {
        //Case 1: Space is green
        vector<string> nextPos;
        if (in.substr(n,1).compare("-") != 0){
            if (posb.size() == 0){
                nextPos.push_back(in.substr(n,1));
            }
            else {
                for (int i = 0; i < (int) posb.size(); i++){
                    nextPos.push_back(posb[i] + in.substr(n,1));
                }
            }
            findPossibilities(floatsLeft, in, n+1, floating, nextPos, final, dict);
        }
        //Case 2: Space is not green
        else {
            for (int k = 0; k < (int) posb.size(); k++){
                nextLetter(posb[k], floatsLeft, in, n, floating, posb, final, dict);
            }
            if (posb.size() == 0){
                nextLetter("", floatsLeft, in, n, floating, posb, final, dict);
            }
        }
    }
}

void nextLetter(string prefix, int floatsLeft, const string& in, int n, std::string& floating, vector<string> posb, std::set<std::string>& final, const std::set<std::string>& dict){
    string alph = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < (int) floating.size(); i++){
        vector<string> nextPos;
        string nextStr = prefix + floating.substr(i,1);
        string newfloating = floating.substr(0,i) + floating.substr(i+1);
        nextPos.push_back(nextStr);
        findPossibilities(floatsLeft-1,in, n+1, newfloating, nextPos, final, dict);
    }
    if (floatsLeft <= (int) (in.length() - prefix.length()) || floating.length() == 0){
        vector<string> nextPos;
        for (int j = 0; j < 26; j++){
            string nextStr = prefix + alph.substr(j,1);
            nextPos.push_back(nextStr);
        }
        findPossibilities(floatsLeft, in, n+1, floating, nextPos, final, dict);
    }
}

int spacesLeft(string inp, int curr){
    if (curr >= (int) inp.length()){
        return 0;
    }
    int count = 0;
    if (inp.substr(curr,1).compare("-") == 0){
        count = 1;
    }
    return count + spacesLeft(inp, curr+1);
}