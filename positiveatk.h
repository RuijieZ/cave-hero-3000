#ifndef __POSITIVEATK_H__
#define __POSITIVEATK_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class PositiveAtk: public Potion{
   public:
      PositiveAtk(Player* next,std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~PositiveAtk();
};

#endif
