#ifndef __POSITIVEHP_H__
#define __POSITIVEHP_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class PositiveHp: public Potion{
   public:
      PositiveHp(Player *next, std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~PositiveHp();
};

#endif
