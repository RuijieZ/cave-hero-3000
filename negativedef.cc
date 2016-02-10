#include <iostream>
#include <string>
#include "negativedef.h"

using namespace std;

NegativeDef::NegativeDef(Player *next, string race){
    type = "WD";
    this->next = next;
    this->race = race;
    if (next != NULL) {this->gold = next->getGold();}
}

int NegativeDef::getHp() {
    return next->getHp();
}

int NegativeDef::getDef() {
    int def = next->getDef();
    if (race == "Elf") {
       return def + 5;
    }
    if (def <= 5) {
       return 0;
    }
    return def - 5;
}

int NegativeDef::getAtk() {
    return next->getAtk();
}

string NegativeDef::getType() {
    return type;
}

NegativeDef::~NegativeDef() {
    delete next;
}
