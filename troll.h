#ifndef __TROLL_H__
#define __TROLL_H__
#include <iostream>
#include <string>

#include "enemy.h"

class Troll: public Enemy {
   public:
      Troll();
      void healthRestore(int amount);
      ~Troll();
};




#endif
