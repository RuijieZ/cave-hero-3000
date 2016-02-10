#ifndef __NEGATIVEHP_H__
#define __NEGATIVEHP_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class NegativeHp: public Potion{
   public:
      NegativeHp(Player* next, std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~NegativeHp();
};

#endif
