#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__
#include <iostream>
#include <string>

#include "content.h"
#include "treasure.h"
#include "player.h"

class DragonHorde: public Treasure{
   public:
    DragonHorde();
   ~DragonHorde();
};

#endif
