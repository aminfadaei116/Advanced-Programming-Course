#ifndef __TV_H__
#define __TV_H__

#include <iostream>
#include <vector>
#include "product.hpp"


class Tv: public Product{
public:
	Tv(std::string name, float screen_size, std::string screen_type, std::string resolution, bool is_3d, bool is_HDR, int _id);
	std::string show_detail();
	float get_screen_size() { return screen_size; };
	std::string get_screen_type() { return screen_type; };
	std::string get_resolution() { return resolution; };
	bool Is_tv_3D() { return is_3d; };
	bool Is_tv_HDR() { return is_HDR; };
protected:
	float screen_size;
	std::string screen_type;
	std::string resolution;
	bool is_3d;
	bool is_HDR;
};

#endif