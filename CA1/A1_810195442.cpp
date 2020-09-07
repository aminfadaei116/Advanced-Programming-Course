#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h> 
#include <sstream>
#include <typeinfo>

#define Exit 1
#define Sent 1
#define Failed 0
#define function_call "show_msg"
#define File_loc "SampleTestcases/people.txt"
using namespace std;

int string_to_int(string s) {
    stringstream s_str(s);  
    int integer = 0;
    s_str >> integer; 
  	return integer;
}

template <typename Out>
void split_to_int(const string &s, char delim, Out result) {
    stringstream stream_str(s); 
    string item;
    while (getline(stream_str, item, delim)) {
        *(result++) = string_to_int(item);
    }
}

vector <int> split_to_int(const string &s, char delim) {
    vector <int> elems;
    split_to_int(s, delim, back_inserter(elems));
    return elems;
}

vector < vector <int> > read_file(){
	string line;
	stringstream s;
	vector <vector <int> >vec;
	ifstream in_File; 
	in_File.open(File_loc); 
    if (!in_File) {
        cout << "Unable to open file";
        exit(Exit);
    }
    while(getline(in_File, line)){
    	vector <int> x = split_to_int(line, ' ');
    	vec.push_back(x);
    }
    return vec;
}

vector < vector <int> > empty_vec(int size){
	vector < vector <int> > vect;
	for(int i=0; i < size; i++){
		vector <int> sub_vect = {};
		vect.push_back(sub_vect);
	}
	return vect;
}

vector < vector <int> > orgenize(vector < vector <int> > graph){
	vector < vector <int> > vec = empty_vec(graph.size());
	for(int i=0; i < graph.size(); i++){
		for(int j=1; j < graph[i].size(); j++){
			vec[i].push_back(graph[i][j]);
			vec[graph[i][j]].push_back(i);
		}
	}
	return vec;
}

bool check_permission(vector < vector <int> > orgenize, int sender_ID, int receiver_ID){
	if(sender_ID > orgenize.size()-1 || receiver_ID > orgenize.size()-1)
		return Failed;
	for(int i=0; i < orgenize[sender_ID].size(); i++){
		if(orgenize[sender_ID][i] == receiver_ID)
			return Sent;
	}
	return Failed;
}

string remove_index(string text, int index){
	if(index > text.size()){
		return text;
	}
	string temp;
	for(int i=0; i < text.size(); i++){
		if(i != index)
			temp += text[i];
	}
	return temp;
}

void show_state_of_message(int flag){ 
	if(flag == Sent)
		cout << "sent" << endl;
	else
		cout << "failed" << endl;
}

void write_message(string message, int sender_ID, int receiver_ID){	
  	ofstream my_file;
    my_file.open (to_string(receiver_ID) + ".txt", ios_base::app);
  	my_file << sender_ID << " " << message << "\n";
    my_file.close();
}

vector <string> check_end_via_space(vector < string> splited){
	for(int i=splited.size(); i > 2; i--){
		if(splited[i-1][splited[i-1].size()-1] == ' ' || splited[i-1].size() == 0){
			splited.pop_back();
		}
	}
	return splited;
}

vector <string> split_space(string command){
	vector <string> splited;
	string word;
	for(int i=0; i < command.size(); i++){
		if(command[i] == ' ' && word.size()){
			splited.push_back(word);
			word = "";
		}
		else if(command.size()){
			word += command[i];
		}
	}
	splited.push_back(word);
	splited = check_end_via_space(splited);
	return splited;
}

vector <string> implement_commands(vector <string> command, int number_of_commands) {
	vector <string> temp;
	string word;
	for(int i=0; i < number_of_commands; i++)
		temp.push_back(command[i]);
	for(int i=number_of_commands; i < command.size(); i++){
		word = word + command[i] + " "; 
	}
	word = remove_index(word, word.size()-1);
	temp.push_back(word);
	return temp;
}

vector <string> get_command(string command){
	vector <string> temp = split_space(command);
	if(temp[0] == function_call){ 
		return implement_commands(temp, 1);
	}
	else{
		return implement_commands(temp, 2);
	}
}

void show_message(int index){
	ifstream ifile(to_string(index) + ".txt");
	if (ifile) {
		ifstream file(to_string(index) + ".txt");
    	cout << file.rdbuf();
	}
	else
		cout << "failed" << endl;
}

void assign_message(vector <string> command, vector < vector <int> > orgenized_graph){
	int sender_ID = string_to_int(command[0]);
	int receiver_ID = string_to_int(command[1]);
	string message = command[2];
	bool condition = check_permission(orgenized_graph, sender_ID, receiver_ID);
	if(condition == Sent){
		write_message(message, sender_ID, receiver_ID);			
	}
	show_state_of_message(condition);
}

void do_command(vector <string> command, vector < vector <int> > orgenized_graph){
	if(command[0] == function_call){
		show_message(string_to_int(command[1]));
	}
	else{
		assign_message(command, orgenized_graph);
	}
}

void command_processor(vector < vector <int> > orgenized_graph){ 
	vector <string> command;
	string command_line;
	while(getline(cin, command_line)){
		command = get_command(command_line);
		do_command(command, orgenized_graph);
	}
}

int main(){
	vector < vector <int> > orgenized_graph = orgenize(read_file());
	command_processor(orgenized_graph);
	return 0;
}
