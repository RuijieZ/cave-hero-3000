#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <iostream>
#include <string>

#include "content.h"
#include "cell.h"

class Character: public Content {
  protected:
      std::string race;
      int Hp;
      int Atk;
      int Def;
  public:
     virtual int getAtk();
     virtual int getDef();
     virtual int getHp();
     void attack(Cell *target);
     std::string getRace();
     int calcDamage(int atkFromAttacker);
     void updateHp(int atkFromAttacker); 
     void playerAttack(Cell *target);
     double getGold();
     virtual std::string getType();
     void addHp(int amount);
     virtual ~Character();
};

#endif
