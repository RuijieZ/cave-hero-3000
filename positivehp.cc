#include <iostream>
#include <string>
#include "positivehp.h"

using namespace std;

PositiveHp::PositiveHp(Player* next, string race){
    type = "RH";
    this->next = next;
    this->race = race;
    if (next != NULL) {this->gold = next->getGold();}
}

int PositiveHp::getHp() {
    int Hp = next->getHp();
    if (Hp == 0) { return 0;}
    if (race == "Elf" && Hp <= 140 && Hp >= 130) { 
       return 140;
    }
    if (race == "Human" && Hp <= 140 && Hp >= 130) { 
       return 140;
    }
    if (race == "Dwarf" && Hp <= 100 && Hp >= 90) { 
       return 100;
    }
    if (race == "Orc" && Hp >= 170 && Hp <= 180) { 
       return 180;
    }
    return Hp + 10;
}

int PositiveHp::getDef() {
    return next->getDef();
}

int PositiveHp::getAtk() {
    return next->getAtk();
}

string PositiveHp::getType() {
    return type;
}

PositiveHp::~PositiveHp() {
  delete next;
}


