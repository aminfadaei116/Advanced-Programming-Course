#include "mobile.hpp"

#define WEIGHT_TXT "Weight: "
#define CPU_FREQ_TXT "CPU Frequency: "
#define BUILT_MEM_TXT "Built-in Memory: "
#define RAM_TXT "RAM: "
#define DISP_SIZE_TXT "Display Size: "
#define CAMERA_RES_TXT "Camera Resolution: "
#define OS_TXT "Operating System: "
using namespace std;

Mobile::Mobile(string _name, float _weight, float _frequency, int _memory, int _RAM, float _disp_size, float _disp_resolution, string _OS, int _id): 
	Product(_name, _id) {
	weight = _weight;
	frequency = _frequency;
	memory = _memory;
	RAM = _RAM;
	disp_size = _disp_size;
	disp_resolution = _disp_resolution;
	OS = _OS;
	type = MOBILE;
}

string Mobile::show_detail(){
	string statment ="";
	statment += name;
	statment += "\n";
	statment += WEIGHT_TXT;
	statment += "\n";
	statment += CPU_FREQ_TXT;
	statment += "\n";
	statment += BUILT_MEM_TXT;
	statment += to_string(memory);
	statment += "\n";
	statment += RAM_TXT;
	statment += to_string(RAM);
	statment += "\n";
	statment += DISP_SIZE_TXT;
	statment += to_string(disp_size);
	statment += "\n";
	statment += CAMERA_RES_TXT;
	statment += to_string(disp_resolution);
	statment += "\n";
	statment += OS_TXT;
	statment += OS;
	statment += "\n";
	return statment;
}