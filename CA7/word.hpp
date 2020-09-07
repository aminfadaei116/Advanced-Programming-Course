#ifndef __WORD_H__
#define __WORD_H__

#include <iostream>
#include <vector>




class Word{
public:
    Word(std::string, double, double);
    double get_good_prob() { return good_prob; };
    double get_bad_prob() { return bad_prob; };
    bool is_name(std::string);
protected:
    std::string name;
    double good_prob;
    double bad_prob;
};

#endif