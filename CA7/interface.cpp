#include "interface.hpp"
#include "functions.hpp"

using namespace std;


Interface::Interface(){
	friday_market = new Market();
}

void Interface::processing(){
	friday_market->just_do_it();
}

