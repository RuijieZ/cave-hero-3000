#include <iostream>
#include <string>
#include "negativeatk.h"

using namespace std;

NegativeAtk::NegativeAtk(Player* next, string race){
   type = "WA";
   this->next = next;
   this->race = race;
   if (next != NULL) {this->gold = next->getGold();}
}

int NegativeAtk::getHp() {
    return next->getHp();
}

int NegativeAtk::getDef() {
    return next->getDef();
}

int NegativeAtk::getAtk() {
    int atk = next->getAtk();
    if (race == "Elf" ) {
       cout << "works" <<endl;
       return atk + 5;
    }
    if (atk <= 5) {
       return 0;
    }
    return next->getAtk() - 5;
}

string NegativeAtk::getType() {
    return type;
}

NegativeAtk::~NegativeAtk() {
     delete next;
}
