#ifndef __POSITIVEDEF_H__
#define __POSITIVEDEF_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class PositiveDef: public Potion{
   public:
      PositiveDef(Player* next,std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~PositiveDef();
};

#endif
