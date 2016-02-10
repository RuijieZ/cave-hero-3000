#ifndef __NEGATIVEDEF_H__
#define __NEGATIVEDEF_H__
#include <iostream>
#include <string>
#include "content.h"
#include "potion.h"


class NegativeDef: public Potion{
   public:
      NegativeDef(Player* next, std::string race);
      int getHp();
      int getAtk();
      int getDef();
      std::string getType();
      ~NegativeDef();
};

#endif
