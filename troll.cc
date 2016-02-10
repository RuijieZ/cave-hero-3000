#include <iostream>
#include <string>

#include "troll.h"

using namespace std;

Troll::Troll(){
   symbol = "T";
   race = "Troll";
   Hp = 120;
   Atk = 25;
   Def = 15;
}

void Troll::healthRestore(int amount) {
     if (Hp < 120 - amount) {
       this->Hp += amount;
     }
     else {
       this->Hp = 120;
     }
}

Troll::~Troll() {
}
