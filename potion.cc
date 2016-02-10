#include <iostream>
#include <string>

#include "potion.h"

using namespace std;


Potion::Potion() {
   symbol = "P";
}

void Potion::addHp(int amount) {
     this->Hp += amount;
}

Potion::~Potion() {
   delete next;
}
