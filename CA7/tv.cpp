#include "tv.hpp"

#define SCREEN_SIZE_TXT "Screen Size: "
#define SCREEN_TYPE_TXT "Screen Type: "
#define RESOUTION_TXT "Resolution: "
#define THREE_D_TXT "3D: "
#define HDR_TXT "HDR: "

Tv::Tv(std::string _name, float _screen_size, std::string _screen_type, std::string _resolution, bool _is_3d, bool _is_HDR, int _id):
	Product(_name, _id) {	
	screen_size = _screen_size;
	screen_type = _screen_type;
	resolution = _resolution;
	is_3d = _is_3d;
	is_HDR = _is_HDR;
	type = TV;
}

std::string Tv::show_detail(){
	std::string statment = "";
	statment += name;
	statment += "\n";
	statment += SCREEN_SIZE_TXT;
	statment += to_string(screen_size);
	statment += "\n";
	statment += SCREEN_TYPE_TXT;
	statment += screen_type;
	statment += "\n";
	statment += RESOUTION_TXT;
	statment += resolution;
	statment += "\n";
	statment += THREE_D_TXT;
	statment += to_string(is_3d);
	statment += "\n";
	statment += HDR_TXT;
	statment += to_string(is_HDR);
	statment += "\n";
	return statment;
}