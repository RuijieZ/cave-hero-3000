#include <iostream>
#include <string>

#include "player.h"
#include "human.h"
#include "elves.h"
#include "dwarf.h"
#include "orc.h"

using namespace std;
/* 
class Player: public Content {
      std::string symbol;
      std::string race;
      int Hp;
      int Atk;
      int Def;
      // skills will be implemented later
};
*/
extern double goldCollected;
Player::Player() {
    symbol = "@";
    gold = 0;
}

double Player::getGold() {
    return gold;
}

Player* Player::playerInstance = NULL;

Player *Player::getInstance(string race) {
   if (playerInstance == NULL) {
      if (race == "Human") {
         playerInstance = new Human;
      }
      if (race == "Elf") {
         playerInstance = new Elves;
      }
      if (race == "Dwarf") {
         playerInstance = new Dwarf;
      }
      if (race == "Orc") {
         playerInstance = new Orc;
      }
  }
   return playerInstance;
}

void Player::setGold(int gold) {
    this->gold = gold * 1.0;
}
// do it for all of the rest......

void Player::addGold(int amount) {
   if (this->getRace() == "Dwarf") {
        gold += (2.0 * amount);
     if(amount > 0) { goldCollected += (2.0 * amount);}
      }
   else if (this->getRace() == "Orc") {
       gold += amount * 0.5;
      if(amount > 0) { goldCollected += amount * 0.5;}
   }
   else {
       gold += amount;
      if (amount > 0) {goldCollected += amount * 1.0;}
   }
}

void Player::addHp(int amount) {
//     cout << "why not affecting?" << endl;
     this->Hp += amount;
}

void Player::setHp(int hp) {
     this->Hp = hp;
}

Player::~Player() {
}
