#include <iostream>
#include "bullet.hpp"

using namespace std;

Bullet::Bullet(float _init_x, float _init_y){
	float location_x = _init_x;
	float location_y = _init_y;
	life_duration_left = 10;
}
