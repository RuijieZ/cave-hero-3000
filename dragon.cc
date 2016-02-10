#include <iostream>
#include <string>

#include "dragon.h"

using namespace std;

Dragon::Dragon(){
   dragonHorde = NULL;
   symbol = "D";
   race = "Dragon";
   Hp = 150;
   Atk = 20;
   Def = 20;
}

void Dragon::setDragonHorde(Cell *current) {
    dragonHorde = current;
}

Cell *Dragon::getDragonHorde() {
   return dragonHorde;
}

Dragon::~Dragon() {
}

