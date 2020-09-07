#ifndef __MOBILE_H__
#define __MOBILE_H__

#include <iostream>
#include <vector>
#include "product.hpp"



class Mobile: public Product{
public:
	Mobile(std::string name, float weight, float frequency, int memory, int RAM, float disp_size, float disp_resolution, std::string OS, int _id);
	std::string show_detail();
	float get_weight() { return weight; };
	float get_frequency() { return frequency; };
	int get_memory() { return memory; };
	int get_RAM() { return RAM; };
	float get_disp_size() { return disp_size; };
	float get_disp_resolution() { return disp_resolution; };
	std::string get_OS() { return OS; };
protected:
	float weight;
	float frequency;
	int memory;
	int RAM;
	float disp_size;
	float disp_resolution;
	std::string OS;
};

#endif