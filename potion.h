#ifndef __POTION_H__
#define __POTION_H__
#include <iostream>
#include <string>

#include "content.h"
#include "player.h"
class Cell;

class Potion: public Player{
   protected:
      std::string type;
      Player* next;
   public:
      Potion();
      void addHp(int amount);
      virtual int getHp() = 0;
      virtual int getAtk() = 0;
      virtual int getDef() = 0;
      virtual std::string getType() = 0;
      virtual ~Potion();
};

#endif

