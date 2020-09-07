#include "TankTrouble.hpp"
#include <cstdlib>
#include <time.h>
#include <random>

#define TANK_MARGIN (WALL_LENGTH - TANK_LENGTH)/2

void TankTrouble::addPowers(int n){
  srand(time(NULL));
  for (int i=0; i<n; i++){
    Power power = Power(rand()%3);
    int col = rand()%(cols-2)+1;
    int row = rand()%(rows-2)+1;
    int x = (col)*WALL_LENGTH + WALL_LENGTH/2;
    int y = (row)*WALL_LENGTH + WALL_LENGTH/2;
    if ((x == xpos1 && y == ypos1) || (x == xpos2 && y == ypos2)){
      i--;
      continue;
    }
    powers.push_back(new PowerObject(x, y, power));
  }
  lastTimePower = NOW;
  // xpos1 = ypos1 = -1;
  // ypos2 = xpos2 = -1;
}

TankTrouble::TankTrouble(string _mapFileName, int _width, int _height)
    : width(_width), height(_height), mapFileName(_mapFileName){
  win = new Window(width, height, "Tank Trouble");
  readMap();
  tank1 = new Tank((ypos1)*WALL_LENGTH + WALL_LENGTH/2, (xpos1)*WALL_LENGTH + WALL_LENGTH/2, 1);
  tank2 = new Tank((ypos2)*WALL_LENGTH + WALL_LENGTH/2, (xpos2)*WALL_LENGTH + WALL_LENGTH/2, 2);
  addPowers(3);
  quit = false;
  end = false;
}

void TankTrouble::readMap(){
  ifstream file(mapFileName);
  string line;
  file >> rows >> cols;
  rows += 2;
  cols += 2;
  line = "";
  for (int i=0; i<cols; i++) 
    line += "0";
  map.push_back(line);
  getline(file, line);
  for (int i=0; i<rows-2; i++){
    getline(file, line);
    map.push_back("0" + line + "2");
  }
  line = "0";
  for (int i=0; i<cols-2; i++) 
    line += "1";
  map.push_back(line + "0");
  file >> xpos1 >> ypos1;
  xpos1++;
  ypos1++;
  getline(file, line);
  file >> xpos2 >> ypos2;
  xpos2++;
  ypos2++;
  file.close();
}



void TankTrouble::run() {
  while (!quit) {
    getAndProcessInput();
    draw();
    delay(TICK_DURATION);
      
  }
}

void TankTrouble::drawBackground(){
  win->fill_rect(Rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

void TankTrouble::drawWalls(){
  for (int i=0; i<rows; i++)
  {
    for (int j=0; j<cols; j++)
    {
      if (map[i][j] == '1' || map[i][j] == '3')
        win->draw_line(Point(LEFT_MARGIN + j*WALL_LENGTH, UP_MARGIN + i*WALL_LENGTH), Point(LEFT_MARGIN + (j+1)*WALL_LENGTH, UP_MARGIN + (i)*WALL_LENGTH), BLACK);
      if (map[i][j] == '2' || map[i][j] == '3')
        win->draw_line(Point(LEFT_MARGIN + j*WALL_LENGTH, UP_MARGIN + i*WALL_LENGTH), Point(LEFT_MARGIN + (j)*WALL_LENGTH, UP_MARGIN + (i+1)*WALL_LENGTH), BLACK);
    }
  }
}

void TankTrouble::drawTanks(){
  win->draw_img(tank1->getFileName(), Rectangle(LEFT_MARGIN + tank1->getX() - TANK_LENGTH/2, UP_MARGIN + tank1->getY() - TANK_LENGTH/2, TANK_LENGTH, TANK_LENGTH), NULL_RECT, tank1->getAngle());
  win->draw_img(tank2->getFileName(), Rectangle(LEFT_MARGIN + tank2->getX() - TANK_LENGTH/2, UP_MARGIN + tank2->getY() - TANK_LENGTH/2, TANK_LENGTH, TANK_LENGTH), NULL_RECT, tank2->getAngle());
}
void TankTrouble::drawBullets(){
  for (int i=0; i<bullets.size(); i++){
    win->fill_circle(Point(bullets[i]->getX()+LEFT_MARGIN, bullets[i]->getY()+UP_MARGIN), BULLET_LENGTH/2, BLACK);
  }
}

void TankTrouble::drawPowers(){
  for (int i=0; i<powers.size(); i++)
    win->draw_img(powers[i]->getFileName(), Rectangle(LEFT_MARGIN+powers[i]->getX()-TANK_LENGTH/2, UP_MARGIN+powers[i]->getY()-TANK_LENGTH/2, TANK_LENGTH, TANK_LENGTH), NULL_RECT);


}

void TankTrouble::draw() {
  win->clear();
  drawBackground();
  drawPowers();
  drawWalls();
  drawTanks();
  drawBullets();
  // drawScores();
  if (end)
    win->show_text("PLAYER " + to_string(winner) + " WON!", Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), RED , "example/assets/TankTrouble.ttf", 24);
  win->update_screen();
}

Move keyToMove(char key){
  if (key == UP1 || key == UP2 )
    return Up;
  if (key == DOWN1 || key == DOWN2 )
    return Down;
  if (key == LEFT1 || key == LEFT2 )
    return Left;
  if (key == RIGHT1 || key == RIGHT2 )
    return Right; 
  return NoMove;
     
}

Move revert(Move move){
  if (move == Up )
    return Down;
  if (move == Down)
    return Up; 
  return NoMove;
     
}
double distance(Entity * e1 , Entity * e2){
  return sqrt(pow(e1->getX() - e2->getX(), 2) + pow(e1->getY() - e2->getY(), 2));
}

bool TankTrouble::checkCollision(Tank * tank){
  if (sqrt(pow(tank1->getX() - tank2->getX(), 2) + pow(tank1->getY() - tank2->getY(), 2)) < TANK_LENGTH)
    return true;
  int col, Pcol, row, Prow;
  if (tank->getX() - tank->getPX() > 0)
  {
    col = (tank->getX() + TANK_LENGTH/2 )/WALL_LENGTH;
    Pcol = (tank->getPX() - TANK_LENGTH/2)/WALL_LENGTH;
  }
  else
  {
    col = (tank->getX() - TANK_LENGTH/2)/WALL_LENGTH;
    Pcol = (tank->getPX() + TANK_LENGTH/2)/WALL_LENGTH;
  }
  if (tank->getY() - tank->getPY() > 0)
  {
    row = (tank->getY() + TANK_LENGTH/2)/WALL_LENGTH;
    Prow = (tank->getPY() - TANK_LENGTH/2)/WALL_LENGTH;
  }
  else
  {
    row = (tank->getY() - TANK_LENGTH/2)/WALL_LENGTH;
    Prow = (tank->getPY() + TANK_LENGTH/2)/WALL_LENGTH;
  }
  
  if (Prow == row+1 && (map[Prow][Pcol] == '1' || map[Prow][Pcol] == '3'))
    return true;
  if (Prow == row-1 && (map[row][col] == '1' || map[row][col] == '3'))
    return true;
  if (Pcol == col+1 && (map[Prow][Pcol] == '2' || map[Prow][Pcol] == '3'))
    return true;
  if (Pcol == col-1 && (map[row][col] == '2' || map[row][col] == '3'))
    return true;

  return false;
}

Reflex TankTrouble::checkCollision(Bullet * bullet){
  char input;
  int col, Pcol, row, Prow;
  if (bullet->getOwnerId() == 2 && distance(tank1, bullet) < TANK_LENGTH/2) 
    throw '1';
  if (bullet->getOwnerId() == 1 && distance(tank2, bullet) < TANK_LENGTH/2)
    throw '2';
  if (bullet->getX() - bullet->getPX() > 0)
  {
    col = (bullet->getX() + BULLET_LENGTH/2 )/WALL_LENGTH;
    Pcol = (bullet->getPX() - BULLET_LENGTH/2)/WALL_LENGTH;
  }
  else
  {
    col = (bullet->getX() - BULLET_LENGTH/2)/WALL_LENGTH;
    Pcol = (bullet->getPX() + BULLET_LENGTH/2)/WALL_LENGTH;
  }
  if (bullet->getY() - bullet->getPY() > 0)
  {
    row = (bullet->getY() + BULLET_LENGTH/2)/WALL_LENGTH;
    Prow = (bullet->getPY() - BULLET_LENGTH/2)/WALL_LENGTH;
  }
  else
  {
    row = (bullet->getY() - BULLET_LENGTH/2)/WALL_LENGTH;
    Prow = (bullet->getPY() + BULLET_LENGTH/2)/WALL_LENGTH;
  }

  if (Prow == row+1 && (map[Prow][Pcol] == '1' || map[Prow][Pcol] == '3'))
    return H;
  if (Prow == row-1 && (map[row][col] == '1' || map[row][col] == '3'))
    return H;
  if (Pcol == col+1 && (map[Prow][Pcol] == '2' || map[Prow][Pcol] == '3'))
    return V;
  if (Pcol == col-1 && (map[row][col] == '2' || map[row][col] == '3'))
    return V;

  return No;
}

void TankTrouble::checkPowerPickup(){
  if (powers.size() < 3 && (NOW - lastTimePower).count() > 3e9)
  {
    addPowers(1);
    lastTimePower = NOW;
  }
  for (int i=0; i<powers.size(); i++)
  {
    if (distance(powers[i], tank1) < TANK_LENGTH/2)
    {
      tank1->addPower(powers[i]->getPower());
      powers.erase(powers.begin()+i);
    }
    if (distance(powers[i], tank2) < TANK_LENGTH/2)
    {
      tank2->addPower(powers[i]->getPower());
      powers.erase(powers.begin()+i);
    }
  }
}

void TankTrouble::getAndProcessInput() {
  char pressedKey;
  Event lastEvent;
  while(win->has_pending_event()){
    lastEvent = win->poll_for_event();
    if (lastEvent.get_type() == Event::KEY_PRESS)
    {
      pressedKey = lastEvent.get_pressed_key();
      if (pressedKey == 'z')
        quit = true;
      
      if (pressedKey == UP1 || pressedKey == DOWN1 || pressedKey == LEFT1 || pressedKey == RIGHT1 || pressedKey == FIRE1)
      {
        input1 = pressedKey;
      }
        
      else if (pressedKey == UP2 || pressedKey == DOWN2 || pressedKey == LEFT2 || pressedKey == RIGHT2 || pressedKey == FIRE2)
      {
        input2 = pressedKey;
      }
    }
    if (lastEvent.get_type() == Event::KEY_RELEASE){
      pressedKey = lastEvent.get_pressed_key();
      if (pressedKey == UP1 || pressedKey == DOWN1 || pressedKey == LEFT1 || pressedKey == RIGHT1)
        input1 = NO_MOVE;
      else if (pressedKey == UP2 || pressedKey == DOWN2 || pressedKey == LEFT2 || pressedKey == RIGHT2)
        input2 = NO_MOVE;
    }

  }
  
  if (end)
      return;
  tank1->checkShield();
  tank2->checkShield();
  moveTanks();
  checkPowerPickup();
  addBullets();
  moveBullets();
  checkActiveBullets();
}

void TankTrouble::addBullets(){
  vector <Bullet *> newBullets;
  if (input1 == FIRE1){
    newBullets = tank1->fire();
    input1 = NO_MOVE;
  }
  if (input2 == FIRE2){
    newBullets = tank2->fire();
    input2 = NO_MOVE;
  }
  for (int i=0; i<newBullets.size(); i++)
      bullets.push_back(newBullets[i]);
  
}

void TankTrouble::moveTanks(){
  tank1->move(keyToMove(input1));
  if ( checkCollision(tank1))
    tank1->move(revert(keyToMove(input1)));
  tank2->move(keyToMove(input2));
  if ( checkCollision(tank2))
    tank2->move(revert(keyToMove(input2)));
}


void TankTrouble::moveBullets()
{
  for (int i=0; i<bullets.size(); i++){
    try{
      bullets[i]->move();
      Reflex r = checkCollision(bullets[i]);
      if (r != No)
        bullets[i]->reflex(r);
    }
    catch(char hitTank){
      bullets.erase(bullets.begin() + i);
      i--;
      if (hitTank == '1' && tank1->hit())
      {
        end = true;
        winner = 1;
      }
      if (hitTank == '2' && tank2->hit())
      {
        end = true;
        winner = 2;
      }
    }
  }

}

void TankTrouble::checkActiveBullets()
{
  for (int i=0; i<bullets.size(); i++){
    if (! bullets[i]->active())
    {
      if (bullets[i]->getPower() == Normal && bullets[i]->getOwnerId() == 1)
        tank1->increaseShots();
      else if (bullets[i]->getPower() == Normal && bullets[i]->getOwnerId() == 2)
        tank2->increaseShots();

      delete bullets[i];
      bullets.erase(bullets.begin() + i);
      i--;
    }
  }

}