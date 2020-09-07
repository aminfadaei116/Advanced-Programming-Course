#include "tank.hpp"


string Tank::getFileName()
{
  switch (in_queue_powers[0])
  {
  case Normal:
    if (id == 1)
      return "example/assets/Tank1-Normal.png";
    if (id == 2)
      return "example/assets/Tank2-Normal.png";
    break;
  
  case Shield:
    if (id == 1)
      return "example/assets/Tank1-Shield.png";
    if (id == 2)
      return "example/assets/Tank2-Shield.png";
    break;
  
  case Shotgun:
    if (id == 1)
      return "example/assets/Tank1-Shotgun.png";
    if (id == 2)
      return "example/assets/Tank2-Shotgun.png";
    break;
  
  case Double:
    if (id == 1)
      return "example/assets/Tank1-DoubleBarrel.png";
    if (id == 2)
      return "example/assets/Tank2-DoubleBarrel.png";
    break;
  }
}


void Tank::move(Move m){
  if (m!=4)
    switch (m)
    {
    case Up:
        px = x;
        x += (cos(angle*PI/180) * TANK_SPEED );
        py = y;
        y += (sin(angle*PI/180) * TANK_SPEED );
        break;
    case Down:
        px = x;
        x -= (cos(angle*PI/180) * TANK_SPEED );
        py = y;
        y -= (sin(angle*PI/180) * TANK_SPEED );
        break;
    case Right:
        angle += 3;
        break;
    case Left:
        angle -= 3;
        break;
    default:
      break;
    }
}

void Tank::checkShield(){
  if (shieldActive && (in_queue_powers[0] == Shield) && ((NOW - shieldStartTime).count() > SHIELD_LIFE)){
    shieldActive = false;
    in_queue_powers.pop_front();
  }
  if (!shieldActive && in_queue_powers[0] == Shield)
    {
      shieldStartTime = NOW;
      shieldActive = true;
    }
}

void Tank::addPower(Power power){
  int count = (power == Shield)?1 : (power == Double)?5: 3;
  for (int i=0; i<count; i++)
    in_queue_powers.insert(in_queue_powers.end()-1, power);
}


bool Tank::hit(){
  if (in_queue_powers[0] != Shield)
      return true;
  in_queue_powers.pop_front();
  return false;
}



vector <Bullet *> Tank::fire(){

  vector <Bullet *> bullets;
  if ((in_queue_powers[0] == Normal || in_queue_powers[0] == Shield) && shots > 0){
    bullets.push_back(new Bullet(x, y, angle, Normal, id));
    shots--;
  }
  if (in_queue_powers[0] == Double){
    int xMargin = sin(angle*PI/180) * TANK_LENGTH / 10;
    int yMargin = cos(angle*PI/180) * TANK_LENGTH / 10;
    bullets.push_back(new Bullet(x + xMargin, y + yMargin, angle, Double, id));
    bullets.push_back(new Bullet(x - xMargin, y - yMargin, angle, Double, id));
    in_queue_powers.pop_front();
  }
  if (in_queue_powers[0] == Shotgun){
    in_queue_powers.pop_front();
    for (int i=0; i<5; i++){
      bullets.push_back(new Bullet(x, y, angle + 10*i - 20, Shotgun, id));
    }
  }
  return bullets;
}