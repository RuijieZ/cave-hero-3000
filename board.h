#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 
#include "textdisplay.h"
#include "cell.h"
#include "content.h"
#include "player.h"
#include "enemy.h"

class Board {
  //Board();
  Cell theBoard[maxRow][maxCol];                   // The actual n x n grid.
  TextDisplay *td;                  // The text display.
  void clearBoard();
  void init();
   Board();
 public:
 // Board();
  ~Board();
  Cell* getOneCell(int r, int c);
  friend std::ostream &operator<<(std::ostream &out, const Board &g);
  Cell* generateRandomCell(int chamberNum);
  void generateEnemy();
  Cell * generatePlayerCell();
  Cell * generateStairCell();
  Cell * generateEnemyCell();
  Cell *generateTreasureCell();
  Cell *generatePotionCell();
  Cell *findEmptyCellHasEmptyNeighbour();
  static Board* instanceBoard;
  static Board* getInstance();
};

#endif

