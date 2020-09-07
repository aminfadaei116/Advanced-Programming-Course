#include <iostream>
#include "functions.hpp"
#include "interface.hpp"
using namespace std;

int main(){
	Interface* ca_interface = new Interface();
	ca_interface->processing();
	return 0;
}