#ifndef __SKILL_H__
#define __STILL_H__
#include <iostream>
#include <string>

class Cell;
class Player;
class Skill :public Content {
  protected:
     std::string symbol;
  public:
     std::string getSymbol();
     virtual std::string getType() = 0;
     virtual void attack(Cell *target) ;
     virtual int calcDamage(int atkFromAttacker);
     virtual void updateHp(int atkFromAttacker) ;
     virtual int getHp();
     virtual int getGold() = 0;
     ~Content();
};

#endif
