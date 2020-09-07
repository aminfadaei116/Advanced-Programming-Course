#ifndef __DISCOUNT_H__
#define __DISCOUNT_H__

#include <iostream>
#include <vector>
#include <string>


class Discount{
public:
	Discount(float, std::string);
	std::string get_code();
	void submit_discount();
	float get_percent() { return percent; };
protected:
	float percent;
	std::string discount_code;
	bool submited;
};

#endif