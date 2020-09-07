#include "car.hpp"


#define WEIGHT_TXT "Weight: "
#define NUM_SEAT "Num. of Seats: "
#define NUM_CYCLE "Num. of Cylinders: "
#define ENG_CAP "Engine Capacity: "
#define REVERSE_SENS "Reverse Parking Sensors: "
using namespace std;

Car::Car(string _name, float _weight, int _num_seats, int _num_cylinder, float _engine_capacity, bool _reverse_sensor, int _id):
	Product(_name, _id) {
	weight = _weight;
	num_seats = _num_seats;
	num_cylinder = _num_cylinder;
	engine_capacity = _engine_capacity;
	reverse_sensor = _reverse_sensor;
	type = CAR;
}

string Car::show_detail(){
	string statment = "";
	statment += name;
	statment += "\n";
	statment += WEIGHT_TXT;
	statment += to_string(weight);
	statment += "\n";
	statment += NUM_SEAT;
	statment += to_string(num_seats);
	statment += "\n";
	statment += NUM_CYCLE;
	statment += to_string(num_cylinder);
	statment += "\n";
	statment += ENG_CAP;
	statment += to_string(engine_capacity);
	statment += "\n";
	statment += REVERSE_SENS;
	statment += to_string(reverse_sensor);
	statment += "\n";
	return statment;
}