#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h> 
#include <sstream>
#include <typeinfo>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#define DATA_SET "dataset"
#define LABELS "labels"
#define CLASSIFIER "classifier_"
#define NOT_CLASSIFIER ""
#define CSV_FORMAT ".csv"
#define ACCURACY_STATMENT "Accuracy :"
#define NUMBER_FRACTION 2
#define FIRST "0"
#define CLASSIFIER_LOCATION "./Assets/weight_vectors/"

using namespace std;

typedef vector < vector <float> > float_table;
typedef vector <float> float_vector;
typedef vector <int> int_vector;

float string_to_float(string string_number){
	stringstream number(string_number);
	float int_number = 0;
	number >> int_number;
	return int_number;
}

float max(float_vector number_vector){
	float max_number = number_vector[0];
	for(int i = 0; i < number_vector.size(); i++)
		if(max_number < number_vector[i])
			max_number = number_vector[i];
	return max_number;
}

int arg_max(float_vector scores){
	float max_number = max(scores);
	for(int i = 0; i < scores.size(); i++)
		if(scores[i] == max_number)
			return i;
}

float_vector read_point(ifstream & file, string type){
	float_vector data_point;
	string input;
	if(type == CLASSIFIER){
		getline(file, input, ',');
		data_point.push_back(string_to_float(input));
	}
	if(type == DATA_SET || type == CLASSIFIER){
		getline(file, input, ',');
		data_point.push_back(string_to_float(input));
	}
	getline(file, input, '\n');
	data_point.push_back(string_to_float(input));
	return data_point;
}

float_table read_data_set(string File_loc, string type, string number_package){
	float_table data_table;
	ifstream file(File_loc + '/' + type + number_package + CSV_FORMAT);
	bool is_first = true;
	while(file.good()){
		if(!is_first){
			data_table.push_back(read_point(file, type));
		}
		else{
			read_point(file, type);
			is_first = false;
		}
	}
	file.close();
	return data_table;
}

float calculate_score(float_vector data_point, float_vector weight){
	float score = 0;
	score += data_point[0] * weight[0];
	score += data_point[1] * weight[1];
	score += weight[2];
	return score;
}

float_vector calculte_score_point(float_vector data_point, float_table weights){
	float_vector scores;
	for(int i = 0; i < weights.size(); i++)
		scores.push_back(calculate_score(data_point, weights[i]));
	return scores;
}

float_table calculate_score_table(float_table data_set, float_table weights){
	float_table score;
	for(int i = 0; i < data_set.size(); i++)
		score.push_back(calculte_score_point(data_set[i], weights));
	return score;
}

int_vector predict_label(float_table data_set, float_table weights){
	int_vector predicted_labels;
	float_table score_table = calculate_score_table(data_set, weights);
	for(int i = 0; i < score_table.size(); i++)
		predicted_labels.push_back(arg_max(score_table[i]));
	return predicted_labels;
}

float_table majority_vote_table(int_vector estimated_labels, float_table predictions){
	for(int i = 0; i < estimated_labels.size(); i++)
		predictions[i][estimated_labels[i]] += 1.0;
	return predictions;
}

int_vector majority_vote(float_table majority_vote_table){
	int_vector predict;
	for(int i = 0; i < majority_vote_table.size(); i++)
		predict.push_back(arg_max(majority_vote_table[i]));
	return predict;
}

float calculate_accuracy(int_vector predict, float_table True_label){
	float number_correct = 0.0;
	for(int i = 0; i < predict.size(); i++)
		if((float) predict[i] == True_label[i][0])
			number_correct += 1;
	return ((number_correct / predict.size()) * 100);
}

string cut_begining(string name){
	string shorted_string = "";
	for(int i = 0; i < strlen(CLASSIFIER); i++)
		shorted_string += name[i];
	return shorted_string;
}

int number_file_in_dir (void){
  DIR *dp;
  struct dirent *ep;     
  dp = opendir (CLASSIFIER_LOCATION);
  int number = 0;
  if (dp != NULL){
    while (ep = readdir (dp)){
    	string file_name = (ep -> d_name);
    	if(cut_begining(file_name) != CLASSIFIER)
    		continue;
    	number += 1;
    }
    (void) closedir (dp);
  }
  return number;
}

int_vector predict_flower(string classifier_location, float_table data_set, float_table labels){
	float_table weights = read_data_set(classifier_location, CLASSIFIER, FIRST);
	float_table predictions(data_set.size(), float_vector (weights.size(), 0.0));
	for(int i = 0; i < number_file_in_dir(); i++){
		float_table weights = read_data_set(classifier_location, CLASSIFIER, to_string(i));
		int_vector estimated_labels = predict_label(data_set, weights);
		predictions =  majority_vote_table(estimated_labels, predictions);
	}
	return majority_vote(predictions);
}

int ten_power(int digit){
	int number = 1;
	for(int i = 0; i < digit; i++)
		number *= 10;
	return number;
}

float round_number(float percent, int digit){
	int number = ten_power(digit + 1) * percent;
	percent = (float) number;
	percent /= ten_power(digit + 1);
	return percent;
}

void print_result(int_vector predicted_labels, float_table labels){
	cout << ACCURACY_STATMENT  << setprecision(NUMBER_FRACTION) << fixed << round_number(calculate_accuracy(predicted_labels, labels), NUMBER_FRACTION) << "%" << endl;	
}

int main(int argc, char const *argv[]){
	float_table data_set = read_data_set(argv[1], DATA_SET, NOT_CLASSIFIER);
	float_table labels = read_data_set(argv[1], LABELS, NOT_CLASSIFIER);
	int_vector predicted_labels = predict_flower(argv[2], data_set, labels);
	print_result(predicted_labels, labels);
	return 0;
}