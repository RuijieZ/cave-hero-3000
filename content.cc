#include <iostream>
#include <string>
#include "content.h"

using namespace std;

string Content::getSymbol() {
    return symbol;
}

Content::~Content() {
}

void Content::attack(Cell *target) {}
int Content::calcDamage(int atkFromAttacker) {return -1;}
void Content::updateHp(int atkFromAttacker) {}
int Content::getHp() {return -1;}

