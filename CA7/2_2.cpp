#include <iostream>
#include <vector>

using namespace std;

int find_max(vector <int> line){
	int head = line.back();
	if(line.size() == 1)
		return head;
	line.pop_back();
	if(find_max(line) > head)
		return find_max(line);
	else
		return head;
}

vector <int>  find_max_vector(vector <int> line, int max_number){
	int head = line.back();	
	line.pop_back();
	if(head == max_number){
		return line;
	}
	line = find_max_vector(line, max_number);
	line.push_back(head);
	return line;
}

void print_vector(vector <int> list){
	if(list.size() == 1){
		cout << list.back();
		return;
	}
	int head = list.back();
	list.pop_back();
	print_vector(list);
	cout << ' ' << head;
	list.push_back(head);
}

vector <int> sort_recursive(vector <int> list){
	if(list.size() == 1)
		return list;
	int max_idx = find_max(list);
	list = find_max_vector(list, max_idx);
	list = sort_recursive(list);
	list.push_back(max_idx);
	return list;
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
	vector <int> result = sort_recursive(inputs);
	print_vector(result);
	cout << endl;
	return 0;
}