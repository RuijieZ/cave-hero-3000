#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "player.h"
#include "content.h"
#include "enemy.h"
#include "character.h"
#include "potion.h"
#include "dragon.h"

class Game {
    int merchantInitialNum;
    Board *board;
    Player* player;
    Cell* currentCell; // where the player is currently at
    Cell* stairCell;
    std::vector <Cell*> enemyList;
    void moveEnemy(Cell *current); 
    Game();
    public:
       void addEnemy();
       void chooseRace();
       void startGame();
       void printStatus();
       static Game *gameInstance;
       static Game *getInstance();
       void generateEnemy();
       void enemyAction();
       void generateTreasure();
       void updatePlayerGold(int amount);
       void generatePotion();
       void usePotion(Cell *);
       void generateDragon();
       bool ifHostile(Enemy *enemy);
       bool merchantHostileCheck();
       bool dragonHostileCheck(Enemy *);
       void goldStealing();
       void resetBoard();
       void setBoardFromInput();
       void gameOver();
       ~Game();
};

#endif
