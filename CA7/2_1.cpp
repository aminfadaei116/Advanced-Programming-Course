#include <iostream>
#include <vector>
#include <istream>

using namespace std;

vector <int> push_front(vector <int> line, int element){
	if(line.size() == 0){
		line.push_back(element);
		return line;
	}
	int temp = line.back();
	line.pop_back();
	line = push_front(line, element);
	line.push_back(temp);
	return line;
}


vector <int> reverse(vector <int> vec){
	if(vec.size() == 1)
		return vec;

	int temp = vec.back();
	vec.pop_back();
	vec = push_front(reverse(vec), temp);
	return vec;
}

void print_vector( vector <int> list){
	if(list.size() == 1){
		cout << list.back();
		return;
	}
	int temp = list.back();
	list.pop_back();
	print_vector(list);
	cout << ' ' << temp;
	list.push_back(temp);
}

void get_inputs(istream& stream, vector <int>& inputs){
	int number;
	if(stream >> number){
		inputs.push_back(number);
		get_inputs(stream, inputs);
	}
	return;
}

int main(){
	vector <int> inputs(0);
	get_inputs(cin, inputs );
	vector <int> result = reverse(inputs);
	print_vector(result);
	cout << endl;
	return 0;
}