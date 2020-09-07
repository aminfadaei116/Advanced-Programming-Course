#ifndef ENTITY_H
#define ENTITY_H

#include <chrono>
#include <math.h> 
#include <string>

#define TANK_LENGTH (10 * 4)
#define WALL_LENGTH (30 * 4)
#define BULLET_LENGTH (2 * 4)
#define TIME_STEP 3e8 
#define SHIELD_LIFE (6 * TIME_STEP)
#define NORMAL_LIFE (10 * TIME_STEP)
#define SHOTGUN_LIFE (1.5 * TIME_STEP)
#define DOUBLE_LIFE (5 * TIME_STEP)

using namespace std;

#define PI 3.14159265
#define TANK_SPEED 1
#define BULLET_SPEED 0.7
#define TICK_DURATION 10
#define TIME chrono::high_resolution_clock::time_point
#define NOW chrono::high_resolution_clock::now()

enum Power {Shield, Shotgun, Double, Normal};

class Entity
{
protected:
    double x, y, px, py;
    int angle ;
public:
    Entity(int _x, int _y)
    : x(_x), y(_y), px(_x), py(_y){};
    int getX(){return int(x);}
    int getY(){return int(y);}
    int getPX(){return int(px);}
    int getPY(){return int(py);}
    int getAngle(){return angle;}
};
class PowerObject: public Entity
{
private:
    Power power;
    int x, y;
public:
    PowerObject(int _x, int _y, Power _power)
    : Entity(_x, _y), power(_power){}
    Power getPower(){return power;}
    string getFileName(){
    if (power == Shotgun)
        return "example/assets/Shotgun-Pickup.png";
    if (power == Shield)
        return "example/assets/Shield-Pickup.png";
    if (power == Double)
        return "example/assets/DoubleBarrel-Pickup.png";    
    }
};


#endif