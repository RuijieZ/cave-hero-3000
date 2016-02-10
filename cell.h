#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <string>
#include "textdisplay.h"
#include "content.h"
//#include "player.h"
#include "character.h"

class Player;

const int maxNeighbours = 8;
extern bool moveFail;
class Cell {
      std::string cellSymbol;
      Content * content;
      Cell *neighbours[maxNeighbours];   //pointers to neighbors
      int r, c;                   //co-ordinates of the cell
      TextDisplay * td;        //pointer to the text display
      int numNeighbours;
      bool hasPlayer;
      bool hasEnemy;
public:
      Cell();
      int getR();
      int getC();
      void setSymbol(std::string symbol);
      std::string getSymbol();
      void notifyDisplay();
      void addNeighbour(Cell *neighbour);
      void setDisplay(TextDisplay *td);
      void notifyAttact(Cell* neighbour, int damage);
      void setCoords(int row, int col);
      void addContent(Content * content);
      void moveContent(Cell* destination);
      Content* getContent();
      bool getHasPlayer();
      bool getHasEnemy();
      void setHasPlayer(bool ifHasPlayer);
      void setHasEnemy(bool ifHasEnemy);
      Cell *getNeighbour(int pos);
      void moveEnemy(Cell* destination);
      Cell* findPlayerCell();
      bool checkIfDragonHasDead(Cell* current);
      bool seePotion(Cell *current);
      ~Cell();
};

#endif


