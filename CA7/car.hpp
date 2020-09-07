#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
#include <vector>
#include "product.hpp"



class Car: public Product{
public:
	Car(std::string name, float weight, int num_seats, int num_cylinder, float engine_capacity, bool reverse_sensor, int _id);
	std::string show_detail();
	float get_weight() { return weight; };
	int get_num_seats() { return num_seats; };
	int get_num_cylinder() { return num_cylinder; };
	float get_engine_capacity() { return engine_capacity; };
	bool has_reverse_sensor() { return reverse_sensor; };
protected:
	float weight;
	int num_seats;
	int num_cylinder;
	float engine_capacity;
	bool reverse_sensor;
};

#endif