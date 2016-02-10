#ifndef __NEGATIVEATK_H__
#define __NEGATIVEATK_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class NegativeAtk: public Potion{
   public:
      NegativeAtk(Player* next, std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~NegativeAtk();
};

#endif
