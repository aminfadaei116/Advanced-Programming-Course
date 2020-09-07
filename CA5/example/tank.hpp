#ifndef TANK_H
#define TANK_H


#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include "bullet.hpp"

using namespace std;
#define TIME chrono::high_resolution_clock::time_point

#define UP1 'w'
#define DOWN1 's'
#define LEFT1 'a'
#define RIGHT1 'd'
#define FIRE1 'q'


#define UP2 'i'
#define DOWN2 'k'
#define LEFT2 'j'
#define RIGHT2 'l'
#define FIRE2 'u'

enum Move {Up, Down, Left, Right, NoMove};


class Tank:public Entity
{
private:
    deque <Power> in_queue_powers;
    TIME endOfPower;
    int shots;
    int id;
    TIME shieldStartTime;
    bool shieldActive;
    
    
public:
    Tank(int _x, int _y, int _id)
    :  Entity(_x, _y), id(_id) {
        in_queue_powers.push_back(Normal);
        shots = 5;
        angle = 90;
        shieldActive = false;
    }
    string getFileName();
    vector <Bullet *> fire();
    void move(Move m);
    bool hit();
    void increaseShots(){shots++;}
    void checkShield();
    void addPower(Power power);
};


#endif