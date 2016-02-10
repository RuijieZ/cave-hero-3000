#include <iostream>
#include <string>
#include "negativehp.h"

using namespace std;

NegativeHp::NegativeHp(Player *next, string race){
      type = "PH";
      this->next = next;
      this->race = race;
      if (next != NULL) { this->gold = next->getGold();}
}

int NegativeHp::getHp() {
    int Hp = next->getHp();
    if (Hp == 0) { return 0;}
    if (race == "Elf" && Hp >= 130 && Hp <= 140) {
       return 140;
    }
    if (race == "Elf" && Hp < 130) {
      return Hp + 10;
    }
   if (Hp  <= 10 ) { return 0;}
    return Hp - 10;
}

int NegativeHp::getDef() {
    return next->getDef();
}

int NegativeHp::getAtk() {
    return next->getAtk();
}

string NegativeHp::getType() {
    return type;
}

NegativeHp::~NegativeHp() {
  delete next;
}
