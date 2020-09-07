#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"
#include <iostream>
enum Reflex {No, H, V};
using namespace std;


class Bullet: public Entity
{
private:
    TIME startTime;
    Power power;
    double speed;
    int ownerId;
public:
    Bullet(int _x, int _y, int _angle, Power _power, int _id)
    :  Entity(_x, _y), power(_power), ownerId(_id){
        startTime = NOW;
        angle = _angle;
        speed = (power==Shotgun)? 1.5:1;
    }
    int getOwnerId(){return ownerId;}
   void move(bool revert = false){
        px = x;
        int dir = revert? -1:1;
        x += speed * dir * (cos(angle*PI/180) * BULLET_SPEED * TICK_DURATION);
        py = y; 
        y += speed * dir * (sin(angle*PI/180) * BULLET_SPEED * TICK_DURATION);

    }
    void reflex(Reflex r){
        this->move(true);
        if (r == H)
            angle = 360 - angle;
        if (r == V)
            angle = 180 - angle;
        angle %= 360;
    }
    bool active(){
        if (power == Normal)
            return (NOW - startTime).count() < NORMAL_LIFE;
        if (power == Double)
            return (NOW - startTime).count() < DOUBLE_LIFE;
        if (power == Shotgun)
            return (NOW - startTime).count() < SHOTGUN_LIFE;
        
    }

    Power getPower(){return power;}
};




#endif