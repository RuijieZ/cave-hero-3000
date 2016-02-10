
#include <iostream>
#include <string>
#include "positiveatk.h"

using namespace std;

PositiveAtk::PositiveAtk(Player * next, string race){
    type = "BA";
    this->next = next;
    this->race = race;
    if (next != NULL) {this->gold = next->getGold();}
}

int PositiveAtk::getHp() {
    return next->getHp();
}

int PositiveAtk::getDef() {
    return next->getDef();
}

int PositiveAtk::getAtk() {
    return next->getAtk() + 5;
}

string PositiveAtk::getType() {
    return type;
}

PositiveAtk::~PositiveAtk() {
    delete next;
}
