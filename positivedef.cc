#include <iostream>
#include <string>
#include "positivedef.h"

using namespace std;

PositiveDef::PositiveDef(Player* next, string race){
    type = "BD";
    this->next = next;
    this->race = race;
    if (next != NULL) {this->gold = next->getGold();}
}

int PositiveDef::getHp() {
    return next->getHp();
}

int PositiveDef::getDef() {
    return next->getDef() + 5;
}

int PositiveDef::getAtk() {
    return next->getAtk();
}

string PositiveDef::getType() {
    return type;
}

PositiveDef::~PositiveDef() {
    delete next;
}
