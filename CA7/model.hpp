#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include <vector>
#include "functions.hpp"
class Word;




class Model{
public:
    Model();
    void Train();
    Word* make_word(std::string);
    std::string show_result();
    std::string Test();
    int predict(string_vector);
    double good_probability_comment(string_vector);
    double bad_probability_comment(string_vector);
    double good_probability(std::string);
    double bad_probability(std::string);
    std::string calculate_parameters(vector <int>, vector <int>);
    double recall(vector <int>, vector <int>);
    double precision(vector <int>, vector <int>);
    double accuracy(vector <int>, vector <int>);
protected:
    std::vector <Word*> words;
    double prior;
};

#endif