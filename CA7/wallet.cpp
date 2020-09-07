#include "wallet.hpp"

using namespace std;

Wallet::Wallet(): amount_money(0) {
	credits.push_back(0);
}

void Wallet::add_credit(float _credit){
	amount_money += _credit;
	credits.push_back(amount_money);
}

void Wallet::dec_credit(float _credit){
	amount_money -= _credit;
	credits.push_back(amount_money);
}

std::string Wallet::show_credit(int _count){
	string statment = "credit \n";
	int mini;
	if(_count > credits.size())
		mini = credits.size();
	else
		mini= _count;
	if(mini == 0)
		return statment;
	for(int i = mini - 1; i >= 0; i--){
		statment += to_string(credits[i]);
		statment += "\n";
	}
	return statment;
}

float Wallet::get_credit(){
	return amount_money;
}

void Wallet::reduce_credit(float _total_credit){
	amount_money -= _total_credit;
}

void Wallet::inc_credit(float _total_credit){
	amount_money += _total_credit;
}