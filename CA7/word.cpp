#include "word.hpp"
#include <bits/stdc++.h> 
using namespace std;

#define EMPTY -10

Word::Word(string _name, double _good_prob, double _bad_prob): name(_name){
    if(_good_prob == 0.0)
        good_prob = EMPTY;
    else
        good_prob = log10(_good_prob);
    if(_bad_prob == 0.0)
        bad_prob = EMPTY;
    else
        bad_prob = log10(_bad_prob);
}

bool Word::is_name(string _name){
    return (_name == name);
}