#ifndef __SMALLHORDE_H__
#define __SMALLHORDE_H__
#include <iostream>
#include <string>

#include "content.h"
#include "treasure.h"
#include "player.h"

class SmallHorde: public Treasure{
   public:
    SmallHorde();
    ~SmallHorde();
};

#endif
