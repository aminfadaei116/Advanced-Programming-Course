#include "model.hpp"
#include "word.hpp"
#include <fstream>
#include "exeption.hpp"
#include "functions.hpp"

#define TRAIN_DATA_ADDRESS "train.csv"
#define TEST_DATA_ADDRESS "test.csv"
#define PRIOR_GOOD "class probabilities"
#define RECALL "Recall: "
#define PRECISION "Precision: "
#define ACCURACY "Accuracy: "

using namespace std;
Model::Model(): prior(0.5) {
}

void Model::Train(){
    string prior_str;
    ifstream my_file, The_file;
    The_file.open(PRIOR_GOOD);
	if(!The_file) {
		throw new NOT_FOUND();
	}
    getline(The_file, prior_str);
    prior = stod(prior_str);
    The_file.close();
	my_file.open(TRAIN_DATA_ADDRESS);
	if(!my_file) {
		throw new NOT_FOUND();
	}
	get_header(my_file);
    string input;
	while(getline(my_file, input)){
        words.push_back(make_word(input));
	}
	my_file.close();
}

Word* Model::make_word(string input){
    stringstream str(input);
    string name, good_prob, bad_prob;
    getline(str, name, ',');
    getline(str, good_prob, ',');
    getline(str, bad_prob, '\n');    
    return (new Word(name, stod(good_prob), stod(bad_prob)));
}

string Model::show_result(){
    return Test();
}

string Model::Test(){
    string input;
    ifstream my_file;
	my_file.open(TEST_DATA_ADDRESS);
	if(!my_file) {
		throw new NOT_FOUND();
	}
	get_header(my_file);
    vector <int> Predicted_labels;
    vector <int> True_label;
	while(getline(my_file, input)){
        stringstream str(input);
        string label;
        getline(str, input, ',');
        getline(str, label, '\n');
        string_vector comment = remove_dup_word(input);
        Predicted_labels.push_back(predict(comment));
        True_label.push_back(stoi(label));
	}
	my_file.close();
    return calculate_parameters(Predicted_labels, True_label);
}

string Model::calculate_parameters(vector <int> _predeicted_label, vector <int> _true_label){
    string statment = "";
    statment += RECALL;
    statment += (to_string(recall(_predeicted_label, _true_label)) +  "\n");
    statment += PRECISION;
    statment += (to_string(precision(_predeicted_label, _true_label)) + "\n");
    statment += ACCURACY;
    statment += (to_string(accuracy(_predeicted_label, _true_label)) + "\n");
    return statment;
}

double Model::recall(vector <int> _predeicted_label, vector <int> _true_label){
    double count_det = 0;
    double count_all = 0;
    for(int i = 0; i < _true_label.size(); i++){
        if(_true_label[i] == 0){
            count_all += 1;
            if(_true_label[i] == _predeicted_label[i])
                count_det += 1;
        }
    }
    return (count_det / count_all) * 100;
}

double Model::precision(vector <int> _predeicted_label, vector <int> _true_label){
    double count_det = 0;
    double count_all = 0;
    for(int i = 0; i < _true_label.size(); i++){
        if(_predeicted_label[i] == 0){
            count_all += 1;
            if(_true_label[i] == _predeicted_label[i])
                count_det += 1;
        }
    }
    return (count_det / count_all) * 100;
}

double Model::accuracy(vector <int> _predeicted_label, vector <int> _true_label){
    double count = 0;
    for(int i = 0; i < _true_label.size(); i++){
        if(_true_label[i] == _predeicted_label[i])
            count = count + 1;
    }
    return (count / double(_true_label.size())) * 100;
}

int Model::predict(string_vector _comment){
    double good = good_probability_comment(_comment) + log10(prior);
    double bad = bad_probability_comment(_comment) + log10(1 - prior);
    if(good > bad)
        return 0;
    if(bad > good)
        return 1;
    return -1;
}

double Model::good_probability_comment(string_vector _comment){
    double sum = 0;
    for(int i = 0; i < _comment.size(); i++){
        sum += good_probability(_comment[i]);
    }
    return sum;
}

double Model::bad_probability_comment(string_vector _comment){
    double sum = 0;
    for(int i = 0; i < _comment.size(); i++){
        sum += bad_probability(_comment[i]);
    }
    return sum;
}

double Model::good_probability(string _comment_word){
    for(int i = 0; i < words.size(); i++){
        if(words[i]->is_name(_comment_word))
            return words[i]->get_good_prob();
    }
    return 0.0;
}

double Model::bad_probability(string _comment_word){
    for(int i = 0; i < words.size(); i++){
        if(words[i]->is_name(_comment_word))
            return words[i]->get_bad_prob();
    }
    return 0.0;
}