#include <iostream>
#include <vector>
#include <istream>

#define UNKNOWN_POINT '*'
#define EMPTY_POINT '0'
#define MINE_POINT 'M'
#define NUM_OF_ADDTIONAL_COLUMN 2
#define NUM_OF_ADDTIONAL_ROW 2

using namespace std;

vector < vector <char> > pick_point(vector < vector <char> > , vector < vector <char> > , int , int );

vector <char> get_chars(int count, istream& stream){
	vector <char> line;
	char chr;
	for(int i = 0; i < count; i++){
		cin >> chr;
		line.push_back(chr);
	}
	return line;
}

vector <char> get_table_row(int number_coloum, bool wrap = true){
	vector <char> line = get_chars(number_coloum, cin);
	if(wrap)
	{
		line.insert(line.begin(), EMPTY_POINT);
		line.push_back(EMPTY_POINT);
	}
	return line;

}

vector <char> cast_char(int length, char c){
	vector <char> line(length, c);
	return line;
}

vector < vector <char> > get_table(int number_coloum, int number_row, bool wrap = true){
	vector < vector <char> > table;
	table.push_back(cast_char(number_coloum + NUM_OF_ADDTIONAL_COLUMN, EMPTY_POINT));
	for(int i = 0; i < number_row; i++){
		table.push_back(get_table_row(number_coloum));
	}
	table.push_back(cast_char(number_coloum + NUM_OF_ADDTIONAL_COLUMN, EMPTY_POINT));
	return table;
}

void print_1d_vector(const vector <char>& line){
	for(int i = 0; i < line.size(); i++){
		cout << line[i];
	}
	cout << endl;
}

void print_2d_vector(const vector < vector <char> >& vector_2d){
	for(int i = 0; i < vector_2d.size(); i++)
		print_1d_vector(vector_2d[i]);
}

int count_neighbors_mines(const vector < vector <char> >& table, int x_point, int y_point){
	int sum = 0;
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(table[y_point + i][x_point + j] == MINE_POINT)
				sum += 1;
		}
	}
	return sum;
}

char int_to_char(int integer){
	char c = (48 + integer);
	return c;
}

vector < vector <char> > expand_around(vector < vector <char> > result, vector < vector <char> > table, int x_point, int y_point){
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if((j == 0 && i == 0) || result[y_point + i][x_point + j] != UNKNOWN_POINT)
				continue;
			result = pick_point(result, table, x_point + j, y_point + i);
		}
	}
	return result;
}

vector < vector <char> > pick_point(vector < vector <char> > result, vector < vector <char> > table, int x_point, int y_point){
	if(table[y_point][x_point] == EMPTY_POINT)
		return result;
	int around = count_neighbors_mines(table, x_point, y_point);
	result[y_point][x_point] = int_to_char(around);
	if(around == 0){
		result = expand_around(result, table, x_point, y_point);
	}
	return result;
}

vector < vector <char> > create_empty_table(int number_row, int number_coloum){
	int row = number_row + NUM_OF_ADDTIONAL_ROW;
	int column = number_coloum + NUM_OF_ADDTIONAL_COLUMN;
	vector < vector <char> > empty_lists(row, vector <char>(column, UNKNOWN_POINT));
	return empty_lists;
}

vector <char> uncover_list(vector <char> covered_list){
	vector <char> cleaned;
	for(int i = 1; i < covered_list.size() - 1; i++){
		cleaned.push_back(covered_list[i]);
	}
	return cleaned;
}

vector < vector <char> > uncover_table(vector < vector <char> > covered_table){
	vector < vector <char> > clean;
	for(int i = 1; i < covered_table.size() - 1; i++){
		clean.push_back(uncover_list(covered_table[i]));
	}
	return clean;
}

int main(){
	int number_row, number_coloum, x_point, y_point;
	cin >> number_row >> number_coloum >> x_point >> y_point;
	vector < vector <char> > table = get_table(number_coloum, number_row);
	vector < vector <char> > result_table = pick_point(create_empty_table(number_row, number_coloum),
		table, x_point, y_point);
	print_2d_vector(uncover_table(result_table));
	return 0;
}