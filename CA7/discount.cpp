#include "discount.hpp"

using namespace std;

Discount::Discount(float _percent, string _code): percent(_percent), discount_code(_code), submited(0) {}

string Discount::get_code(){
	return discount_code;
}

void Discount::submit_discount(){
	submited = 1;
}
