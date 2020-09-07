#include <iostream>
using namespace std;
int convertBase6ToBase10(string six_base_number){
	int number = six_base_number[six_base_number.size() - 1] - 48;
	if(six_base_number.size() == 1)
		return number;
	six_base_number.pop_back();
	return 6 * convertBase6ToBase10(six_base_number)  + number;
}
int main(){
	string six_base_number;
	while(cin >> six_base_number)
		cout << convertBase6ToBase10(six_base_number) << endl;
	return 0;
}