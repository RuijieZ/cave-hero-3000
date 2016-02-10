#ifndef __MONSTER_H__
#define __MONSTER_H__
#include <iostream>
#include <string>

#include "character.h"

class Enemy: public Character {
   public:
      Enemy();
      virtual ~Enemy();
};

#endif
