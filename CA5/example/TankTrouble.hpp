#ifndef TT_H
#define TT_H

#include "../src/rsdl.hpp"
#include "tank.hpp"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define UP_MARGIN -50
#define LEFT_MARGIN -50
#define NO_MOVE 'n'



class TankTrouble {
private:
  Window *win;
  bool quit;
  int width;
  int height;
  vector<string> map;
  string mapFileName;
  TIME lastTimePower;
  int rows, cols, xpos1, xpos2, ypos1, ypos2;
  Tank *tank1, *tank2;
  vector<Bullet *> bullets;
  vector<PowerObject *> powers;
  char input1, input2;
  bool end;
  int winner;
  void draw();
  void readMap();
  void getAndProcessInput();
  void processLastEvent();
  void drawBackground();
  void drawWalls();
  void drawTanks();
  void drawBullets();
  void drawPowers();
  bool checkCollision(Tank * tank);
  Reflex checkCollision(Bullet * bullet);
  void checkActiveBullets();
  void moveBullets();
  void moveTanks();
  void addBullets();
  void checkPowerPickup();
  void addPowers(int n);

public:
  TankTrouble(string _mapFileName, int _width = 640, int _height = 480);
  void run();
};

#endif