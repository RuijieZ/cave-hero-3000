#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "cell.h"
#include "textdisplay.h"
#include "board.h"
#include "game.h"

using namespace std;

extern string action;
extern int Gold;
//extern bool dragonHasDead;

Cell::Cell() {
    cellSymbol = " ";
    numNeighbours = 0;
    content = NULL;
    hasPlayer = false;
    hasEnemy = false;
}

int Cell::getR() {
    return r;
}

int Cell::getC() {
    return c;
}

void Cell::notifyDisplay() {
    td->notify(r, c, cellSymbol);
}

void Cell::addNeighbour(Cell *neighbour) {
    neighbours[numNeighbours] = neighbour;
    numNeighbours++;
}

void Cell::setDisplay(TextDisplay *td) {
    this->td = td;
}

void Cell::notifyAttact(Cell* neighbour, int damage) {
   // wating to be implemented when player class is done;
}

void Cell::setCoords(int row, int col) {
     r = row;
     c = col;
}

string Cell::getSymbol() {
   return cellSymbol;
}

void Cell::setSymbol(string symbol) {
   cellSymbol = symbol;
   notifyDisplay();
}

void Cell::addContent(Content * content) {
    this->content = content;
    if (content != NULL) {
      td->notify(r,c,content->getSymbol());
    }
    else {
      td->notify(r,c,cellSymbol);
    }
}

void Cell::moveContent(Cell* destination) {
    if(this->content == NULL) {
       cout << "out of scope" << endl;
       return;
    }
    if(seePotion(this)) {action = action + "PC sees unknown potion.";}
    if(destination->getContent() != NULL ) {
      if(destination->getContent()->getSymbol() == "G") {
          Gold = destination->getContent()->getGold();
          bool dragonHasDead = checkIfDragonHasDead(destination);
          if (!dragonHasDead && Gold == 6) {
               action = action + "DragonHorde cannot be picked up unless the Dragon has been slained!";
               moveFail = true;
               return;
          }
          delete destination->getContent();
          destination->addContent(this->content);
          destination->setHasPlayer(true);
          this->content = NULL;
          this->hasPlayer = false;
          this->notifyDisplay();
          stringstream ss;
          ss << Gold;
          string tempGold;
          ss >> tempGold;
          action = "PC got " + tempGold + " gold! ";
          return;
      }
      action = "Spot occupied, please try another move." ;
      moveFail = true;
    }
    else if(destination->cellSymbol == " " || destination->cellSymbol == "|" || destination->cellSymbol == "-" || destination->cellSymbol == "\\") {
      action = "invalid move, please try another move." ;
      moveFail = true;
    }
    else {
      destination->addContent(this->content);
      destination->setHasPlayer(true);
      this->content = NULL;
      this->hasPlayer = false;
      this->notifyDisplay();
    }
}

Content* Cell:: getContent() {
     return content;
}

Cell:: ~Cell() {
     delete content;
}

void Cell::setHasPlayer(bool ifHasPlayer) {
     hasPlayer = ifHasPlayer;
}



void Cell::setHasEnemy(bool ifHasEnemy) {
     hasEnemy = ifHasEnemy;
}

bool Cell::getHasPlayer() {
     return hasPlayer;
}

bool Cell::getHasEnemy() {
     return hasEnemy;
}

Cell *Cell::findPlayerCell() {                       // used for enemy to chekc if the player near them, if yes, return the address of the cell where the player is at, else, return NULL.
    for(int i=0; i< maxNeighbours; i++) { 
        if(neighbours[i]->content == NULL) {
            continue;
        }
        else if(neighbours[i]->getHasPlayer()) {
            return neighbours[i];
        }
        else {
             continue;
        }
    }
    return NULL;
}

Cell * Cell::getNeighbour(int pos) {
    return neighbours[pos];
}


void Cell::moveEnemy(Cell* destination) {
    if(this->content == NULL) {
       cout << "out of scope" << endl;
       return;
    }
    else {
      destination->addContent(this->content);
      destination->setHasEnemy(true);
      this->content = NULL;
      this->hasEnemy = false;
      this->notifyDisplay();
    }
}

bool Cell::checkIfDragonHasDead(Cell* current) {
    for(int i=0; i < 8; i++) {
       if (current->getNeighbour(i)->getContent() != NULL) {
          if ( current->getNeighbour(i)->getContent()->getSymbol() == "D") {
              return false;
          }
       }
    } // end of for loop
    return true;
}

bool Cell::seePotion(Cell *current) {
    for(int i=0; i < 8; i++) {
      if(current->getNeighbour(i)->getContent() != NULL) {
         if (current->getNeighbour(i)->getContent()->getSymbol() == "P") {
             return true;
         }
      }
    }
    return false;
}
