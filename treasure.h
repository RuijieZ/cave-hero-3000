#ifndef __TREASURE_H__
#define __TREASURE_H__
#include <iostream>
#include <string>

#include "content.h"
class Player;

class Treasure: public Content{
   protected:
      //std::string symbol;
      double gold;
   public:
     Treasure();
     void attack(Cell *target) ;
     int calcDamage(int atkFromAttacker);
     void updateHp(int atkFromAttacker) ;
     int getHp();
     double getGold();
     std::string getType();
     virtual ~Treasure();
};

#endif
