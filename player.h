#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>

#include "character.h"
#include "content.h"

class Player: public Character{
   protected:
      double gold;
      Player();
   public:
      double getGold();
      void setGold(int gold);
      static Player* getInstance(std::string race);
      static Player* playerInstance;
      void addGold(int amount);
      void addHp(int amount);
      void setHp(int hp);
      virtual ~Player();
};

#endif

