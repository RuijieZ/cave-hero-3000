#ifndef __NORMAL_H__
#define __NORMAL_H__
#include <iostream>
#include <string>

#include "content.h"
#include "treasure.h"
#include "player.h"

class Normal: public Treasure{
   public:
    Normal();
    ~Normal();
};

#endif
