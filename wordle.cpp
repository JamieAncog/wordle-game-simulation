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
void findPossibilities(const string& in, int n, std::string& floating, vector<string> posb, vector<string>& final);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //Find Possibilities
    vector<string> posb;
    vector<string> final;
    string floats = floating;
    findPossibilities(in, 0, floats, posb, final);
    //Test if word and convert to set
    std::set<std::string> mySet;
    for (int i = 0; i < (int) final.size(); i++){
        mySet.insert(final[i]);
    }
    return mySet;
}

// Define any helper functions 
void findPossibilities(const string& in, int n, std::string& floating, vector<string> posb, vector<string>& final){
    if (n == (int) in.length()) {
        for (int i = 0; i < (int) posb.size(); i++){
            final.push_back(posb[i]);
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
            findPossibilities(in, n+1, floating, nextPos, final);
        }
        //Case 2: Space is not green
        else {
            for (int k = 0; k < (int) posb.size(); k++){
                for (int i = 0; i < (int) floating.size(); i++){
                    string nextStr = posb[k] + floating.substr(i,1);
                    string newfloating = floating.substr(0,i) + floating.substr(i+1);
                    nextPos.push_back(nextStr);
                    findPossibilities(in, n+1, newfloating, nextPos, final);
                }
                if (n <= (int) in.length() - 1 - (int) floating.length()){
                    string alph = "abcdefghijklmnopqrstuvwzyz";
                    for (int j = 0; j < 26; j++){
                        string nextStr = posb[k] + alph[j];
                        nextPos.push_back(nextStr);
                    }
                    findPossibilities(in, n+1, floating, nextPos, final);
                }
            }
        }
    }
}