#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <ctime>
#include <cstdlib>

#include "character.h"
#include "cell.h"
#include "normal.h"
#include "merchanthorde.h"
using namespace std;

extern string action;
//extern bool dragonHasDead;

void Seed() {
  srand(time(0));
}

int missAttack;  // determine whether the attack has missed
string empty = "";

void Character::playerAttack(Cell *target) {
     if (target->getHasEnemy() == false) {
         action = action + " there is no enemy there! Please try again.";
     }
     else {
         if (this->getRace() == "Orc" && target->getContent()->getSymbol() == "N") {
              action = empty+ "causes double damage on goblin!"+ action + " PC ";
              target->getContent()->updateHp(2 * this->getAtk());
         }
         else {
              target->getContent()->updateHp(this->getAtk());
         }
         int tempHP = target->getContent()->getHp();
         stringstream ss;
         ss << tempHP;
         string tempHp;
         ss >> tempHp;
         if (tempHP <= 0) {
              tempHp = "0";
         }
         action = empty + "PC" + " " + action +  " to " + target->getContent()->getSymbol() + " (" + tempHp + " HP).";
         string tempSymbol = target->getContent()->getSymbol();
         if (target->getContent()->getHp() <= 0) {
             delete target->getContent();
             Content *tempGold = new Normal;
             Content *tempGold2 = new MerchantHorde;
           if (tempSymbol == "M") {
                target->addContent(tempGold2);
                delete tempGold;
           }
           else if(tempSymbol == "D") {
                delete tempGold;
                delete tempGold2;
                target->addContent(NULL);
           }
           else {
                target->addContent(tempGold);
                delete tempGold2;
           }
           target->setHasEnemy(false);
         }
     }
}

void Character::attack(Cell *target) {
    missAttack = (rand() % 2);
    if( missAttack == 0) {
       action = action + " "+ this->race + " ";
       target->getContent()->updateHp(Atk);
       if (this->getSymbol() == "V") {
           double healthStolen = ceil(this->getAtk() *0.2);
           stringstream ss;
           string temp;
           ss << healthStolen;
           ss >> temp;
           action = action + " Vampire stolen " + temp + "points of Hp.";
           this->addHp(healthStolen);
       }
    }
    else {
       action = action + " " + this->race + " tries to attack, but missed...";
   }
}

int Character::calcDamage(int atkFromAttacker) {
    double doubleDamage = atkFromAttacker * (100 / (100 + this->getDef() * 1.0));
    int intDamage = ceil(doubleDamage);
    return intDamage;
}

void Character::updateHp(int atkFromAttacker) {
     Hp -= calcDamage(atkFromAttacker);
     stringstream ss;
     ss << calcDamage(atkFromAttacker);
     string damage;
     ss >> damage;
     action = action + "deals " + damage + " points of damage" ;
}

std::string Character:: getRace() {
    return race;
}

int Character::getAtk() {
    return Atk;
}

int Character::getDef() {
    return Def;
}

int Character::getHp() {
   if (Hp > 0) {
     return Hp;
   }
   else {
     return 0;
   }
}

double Character::getGold() {
    return -1.0;
}

string Character::getType() {
   return "";
}

void Character::addHp(int amount) {
     this->Hp += amount;
}

Character::~Character() {
}
