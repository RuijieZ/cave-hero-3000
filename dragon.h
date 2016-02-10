#ifndef __DRAGON_H__
#define __DRAGON_H__
#include <iostream>
#include <string>

#include "enemy.h"

class Dragon: public Enemy {
      Cell *dragonHorde;
   public:
      void setDragonHorde(Cell *);
      Cell *getDragonHorde();
      Dragon();
      ~Dragon();
};

#endif
