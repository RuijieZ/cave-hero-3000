#ifndef __CONTENT_H__
#define __CONTENT_H__
#include <iostream>
#include <string>

class Cell;
class Player;
class Content {
  protected:
     std::string symbol;
  public:
     std::string getSymbol();
     virtual std::string getType() = 0;
     virtual void attack(Cell *target) ;
     virtual int calcDamage(int atkFromAttacker);
     virtual void updateHp(int atkFromAttacker) ;
     virtual int getHp();
     virtual double getGold() = 0;
     virtual ~Content();
};

#endif
