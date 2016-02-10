#include <iostream>
#include <string>

#include "vampire.h"

using namespace std;

Vampire::Vampire(){
   symbol = "V";
   race = "Vampire";
   Hp = 50;
   Atk = 25;
   Def = 25;
}

Vampire::~Vampire() {
}
