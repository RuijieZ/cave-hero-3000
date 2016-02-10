#include <iostream>
#include <string>

#include "treasure.h"

using namespace std;

Treasure::Treasure() {
    symbol = "G";
}

void Treasure::attack(Cell *target) {}
int Treasure::calcDamage(int atkFromAttacker){return -1;}
void Treasure::updateHp(int atkFromAttacker) {}
int Treasure::getHp() {return -1;}

double Treasure::getGold() {
   return gold;
}

string Treasure::getType() {
    return "";
}
// do it for all of the rest......
Treasure:: ~Treasure() {
}
