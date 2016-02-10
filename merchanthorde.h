#ifndef __MERCHANTHOARD_H__
#define __MERCHANTHOARD_H__
#include <iostream>
#include <string>

#include "content.h"
#include "treasure.h"
#include "player.h"

class MerchantHorde: public Treasure{
   public:
    MerchantHorde();
    ~MerchantHorde();
};

#endif
