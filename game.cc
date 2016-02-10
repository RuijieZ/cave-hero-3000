
#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "game.h"
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "dragon.h"
#include "phoenix.h"
#include "merchant.h"
#include "cell.h"
#include "normal.h"
#include "smallhorde.h"
#include "merchanthorde.h"
#include "dragonhorde.h"
#include "positivehp.h"
#include "negativehp.h"
#include "positiveatk.h"
#include "positivedef.h"
#include "negativeatk.h"
#include "negativedef.h"
#include "dragon.h"
using namespace std;

string action = "";
int Gold = 0;
Content* enemyHasMovedList[20];
int dragonCount = 0;
extern int floor;
extern bool ifInputFile;
extern char floor1[25][79];
extern char floor2[25][79];
extern char floor3[25][79];
extern char floor4[25][79];
extern char floor5[25][79];
double goldCollected = 0;
bool merchantHostile = false;
//bool dragonHasDead;

bool hasMoved(Content *enemy);    // helper function check if an enmey has moved
void setToNull() ;                // helper function that set the enmeyHasMovedlist to Null
void addToList(Content * enemy);  // helper function that add an enmey to the list, means it has moved.
void healthRestore(Content* target); // helper function that helps restore health for a particular character

std::map<string, string> raceMap;
void setRaceMap() {
   raceMap["h"] = "Human";
   raceMap["e"] = "Elf";
   raceMap["d"] = "Dwarf";
   raceMap["o"] = "Orc";
}

string stairSymbol = "\\";

Game::Game() {/*
   merchantInitialNum = 0;
//   floor = 1;
   board = Board::getInstance();
   player = NULL;
   currentCell = board->generatePlayerCell();
   stairCell = board->generateStairCell();
   enemyList.reserve(20);*/
   //stairCell->setSymbol(stairSymbol);
}

void Game:: printStatus() {
   srand(time(0));
   cout << (*board);  // print the update of the board
   cout << "Race: " << player->getRace() << " Gold: " << player->getGold() << "                                                    Floor: " << floor << endl;
   cout << "HP: " << player->getHp() << endl;
   cout << "Atk: " << player->getAtk() << endl;
   cout << "Def: " << player->getDef() << endl;
   cout << "Action: " << action << endl;
}

void Game::chooseRace() {
  string race;
  cin >> race;
  setRaceMap();
  if (cin.eof() || race == "q") {
      cout << "Fine! I will exit! " << endl;
      delete Board:: instanceBoard;
      delete Player::playerInstance; 
      delete Game::gameInstance;
      exit(0); 
   }
  if (race == "h" || race == "e" || race == "d" || race == "o") { 
     player = Player::getInstance(raceMap[race]);
/*     currentCell->addContent(player);
     cout << "hello world" << endl;
     currentCell->setHasPlayer(true);
     generatePotion();
     generateTreasure();
     generateDragon();
     generateEnemy();*/
     action = "Player character has spawned. ";
     return ;
  }
  else {
    cout << "invalid choose, please choose again." <<endl;
    return Game::chooseRace();
  }
}

Game* Game::gameInstance = NULL;

Game* Game::getInstance() {
   if (gameInstance == NULL) {
      gameInstance = new Game;
   }
   return gameInstance;
}

void Game:: startGame() {
   merchantInitialNum = 0;
   board = Board::getInstance();
   //player = NULL;
   //currentCell = board->generatePlayerCell();
  // stairCell = board->generateStairCell();
   enemyList.reserve(20);
    cout << (*board);
  if( floor == 1) {
//    cout << (*board);
    cout << "please choose a race" << endl;
    cout << "possible options: human, elf, dwarf, orc" << endl;
    cout << "type h for selecting human, e for elf, d for dwarf and o for orc." << endl;
    chooseRace();
  }
     stringstream ss;
     ss << floor;
     string temp;
     ss >> temp;
     action = action + "PC enters floor " + temp + "."; 
 if (!ifInputFile) {
     currentCell = board->generatePlayerCell();
     currentCell->addContent(player);
     currentCell->setHasPlayer(true);
     stairCell = board->generateStairCell();
     stairCell->setSymbol(stairSymbol);
     generatePotion();
     generateTreasure();
     generateDragon();
     generateEnemy();
 }
 else {
   setBoardFromInput();
 }
  printStatus();
  while(true) {
    setToNull();
    string command;
    cin >> command;
    moveFail = false;
    action = "";
    Gold = 0;
    if (command == "q" || cin.eof()) {
      break;
  //  exit(1);
    }
/*    else if (player->getHp() <= 0) {
      if( player->getRace() == "human") { goldCollected *= 1.5;}
      cout << "Game Over, your final score is " << goldCollected << endl;
      break;
    } */
    else if (command == "r" ) {
      floor = 1;
      resetBoard();
      cout << "Please wait, the game is resetting......" << endl;
      return startGame();
    }
    else if (command == "we" && board->getOneCell(currentCell->getR(), currentCell->getC()-1)->getSymbol() == "\\") {
            int hp = player->getHp();
            int gold = player->getGold();
            string race = player->getRace();
            resetBoard();
            player= Player::getInstance(race);
            player->setHp(hp);
            player->setGold(gold);
            floor++;
            if (floor == 6) {
                double gold;
                if (player->getRace() == "Human") { gold = player->getGold() * 1.5;}
                else { gold = player->getGold();}
                cout << "Game Over, you win. Your final score is " << gold << endl;
                cout << "Would like to restart a new game or quit?" <<endl;
                floor = 1;
            }
            return startGame();
    }
    else if (command == "no") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()-1, currentCell->getC()));
      if(!moveFail) {
         currentCell = board->getOneCell(currentCell->getR()-1,currentCell->getC());
         action = action + "PC goes north.";
         player->addGold(Gold);
      }
      enemyAction();
      goldStealing();
      printStatus();
      gameOver();
    }
    else if (command == "so") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()+1, currentCell->getC()));
      if(!moveFail) {
         currentCell = board->getOneCell(currentCell->getR()+1,currentCell->getC());
         action = action + "PC goes south.";
         player->addGold(Gold);
      }
      enemyAction();
      goldStealing();
      printStatus();
      gameOver();
    }
    else if (command == "ea") {
      currentCell->moveContent(board->getOneCell(currentCell->getR(), currentCell->getC()+1));
      if(!moveFail) {
          currentCell = board->getOneCell(currentCell->getR(),currentCell->getC()+1);
          action = action + "PC goes east.";
          player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }
    else if (command == "we") {
      currentCell->moveContent(board->getOneCell(currentCell->getR(), currentCell->getC()-1));
      if(!moveFail) {
          currentCell = board->getOneCell(currentCell->getR(),currentCell->getC()-1);
          action = action + "PC goes west.";
          player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }
    else if (command == "ne") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()-1, currentCell->getC()+1));
      if(!moveFail) {
         currentCell = board->getOneCell(currentCell->getR()-1,currentCell->getC()+1);
         action = action +  "PC goes north-east.";
         player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }
    else if (command == "nw") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()-1, currentCell->getC()-1));
      if(!moveFail) {
         currentCell = board->getOneCell(currentCell->getR()-1,currentCell->getC()-1);
         action = action + "PC goes north-west.";
         player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }
    else if (command == "sw") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()+1, currentCell->getC()-1));
      if(!moveFail) {
          currentCell = board->getOneCell(currentCell->getR()+1,currentCell->getC()-1);
          action = action + "PC goes south-west.";
          player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }
    else if (command == "se") {
      currentCell->moveContent(board->getOneCell(currentCell->getR()+1, currentCell->getC()+1));
      if(!moveFail) {
          currentCell = board->getOneCell(currentCell->getR()+1,currentCell->getC()+1);
          action = action + "PC goes south-east.";
          player->addGold(Gold);
      }
      goldStealing();
      enemyAction();
      printStatus();
      gameOver();
    }// above are move commands
    else if (command == "ano") {
          player->playerAttack(board->getOneCell(currentCell->getR()-1, currentCell->getC()));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "aso") {
          player->playerAttack(board->getOneCell(currentCell->getR()+1, currentCell->getC()));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "aea") {
          player->playerAttack(board->getOneCell(currentCell->getR(), currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "awe") {
          player->playerAttack(board->getOneCell(currentCell->getR(), currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "anw") {
          player->playerAttack(board->getOneCell(currentCell->getR()-1, currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "ane") {
          player->playerAttack(board->getOneCell(currentCell->getR()-1, currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "ase") {
          player->playerAttack(board->getOneCell(currentCell->getR()+1, currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "asw") {
          player->playerAttack(board->getOneCell(currentCell->getR()+1, currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    // here comes with the using potion commands
    else if (command == "uno") {
          Game::usePotion(board->getOneCell(currentCell->getR()-1, currentCell->getC()));
          goldStealing();
          enemyAction();
          printStatus();
    }
    else if (command == "uso") {
          Game::usePotion(board->getOneCell(currentCell->getR()+1, currentCell->getC()));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "uea") {
          Game::usePotion(board->getOneCell(currentCell->getR(), currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "uwe") {
          Game::usePotion(board->getOneCell(currentCell->getR(), currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "une") {
          Game::usePotion(board->getOneCell(currentCell->getR()-1, currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "unw") {
          Game::usePotion(board->getOneCell(currentCell->getR()-1, currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "use") {
          Game::usePotion(board->getOneCell(currentCell->getR()+1, currentCell->getC()+1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    }
    else if (command == "usw") {
          Game::usePotion(board->getOneCell(currentCell->getR()+1, currentCell->getC()-1));
          goldStealing();
          enemyAction();
          printStatus();
          gameOver();
    } // end of using potion
    else {
       continue;
   }
 }// end of while loop
}

// now we are creating the enemy list wohoo!



int randomEnemy;        // temp int only be used in the following function


void Game::addEnemy() {
    randomEnemy = (rand () % 18) +1;
    Cell* temp = board->generateEnemyCell();
    Content *enemy;
    if (randomEnemy == 1 || randomEnemy == 2 || randomEnemy == 3 || randomEnemy == 4) {
        enemy = new Werewolf;
    }
    else if (randomEnemy == 5 || randomEnemy == 6 || randomEnemy == 7) {
        enemy = new Vampire;
    }
    else if (randomEnemy == 8 || randomEnemy == 9 || randomEnemy == 10 || randomEnemy == 11 || randomEnemy == 12) {
        enemy = new Goblin;
    }
    else if (randomEnemy == 13 || randomEnemy == 14) {
        enemy = new Troll;
    }
    else if (randomEnemy == 15 || randomEnemy == 16) {
        enemy = new Phoenix;
    }
    else {
        enemy = new Merchant;
        merchantInitialNum++;
    }
    temp->setHasEnemy(true);
    temp->addContent(enemy);
    enemyList.push_back(temp);
}

void Game::generateEnemy() {
    int count = 20;
    while(count != 0) {
       addEnemy();
       count--;
       if (count == dragonCount) {
            break;
       }
    }
}

void Game::enemyAction() {
   for(int i = 0; i < 25; i++) {
      for (int j = 0; j<79; j++) {
          Cell *current = board->getOneCell(i,j);
          if (current->getHasEnemy() != true) {
               continue;
          }
          else {
              if (current->getContent()->getSymbol() == "T") {
                   healthRestore(current->getContent());
              }
              if (hasMoved(current->getContent())) {
                  continue;
              }
             Cell* potentialPlayerCell = current->findPlayerCell();
             if (potentialPlayerCell == NULL) {
                addToList(current->getContent());
                moveEnemy(current);
                continue;
             }
             else {
                Enemy *enemy =  dynamic_cast<Enemy *>(current->getContent());
                if (enemy != NULL) {
                   if (ifHostile(enemy)) {
                      current->getContent()->attack(potentialPlayerCell);
                      action = action + ".";
                   }
                   if (!ifHostile(enemy) && enemy->getSymbol() == "M") {
                       addToList(current->getContent());
                       moveEnemy(current);
                       continue;
                   }
                }
                else {
                     cout << "check your casting in enemyAction function!" << endl; // I hope I will not see this line while my program runs.
                }
             }
          }
       }
   }// end of doulbe for loop
}

void Game::moveEnemy(Cell *current) {
     if (current->getContent()->getSymbol() == "D") { return;}
     int randomDirection = (rand() % 8);
     int count = 0;
     while (current->getNeighbour(randomDirection)->getContent() != NULL || current->getNeighbour(randomDirection)->getSymbol() == "|" ||
         current->getNeighbour(randomDirection)->getSymbol() == "-" || current->getNeighbour(randomDirection)->getSymbol() == "+" ||
         current->getNeighbour(randomDirection)->getSymbol() == "\\") {
         randomDirection = (rand() % 8);
         count ++;
         if (count == 100) {
              return;
         }
     }
     current->Cell::moveEnemy(current->getNeighbour(randomDirection));
}

void Game::generateTreasure() {
      int count = 10;
      int randomPile = (rand() % 8) + 1;
      Content *treasure;
    while (count != 0) {
       Cell* temp = board->generateTreasureCell();
       if (randomPile == 1 ||randomPile == 2 ||randomPile == 3 ||randomPile == 4 || randomPile == 5 ) {
           treasure = new Normal;
       }
       else if(randomPile == 6 || randomPile == 7) {
           treasure = new SmallHorde;
       }
       else {
           treasure = new DragonHorde;
           temp = board->findEmptyCellHasEmptyNeighbour();
           dragonCount ++;
       }
       temp->addContent(treasure);
       randomPile = (rand() % 8) + 1;
       count --;
    }
}


void Game::generatePotion() {
      int count = 10;
      int randomPotion = (rand() % 6) + 1;
      Content *potion;
    while (count != 0) {
       Cell* temp = board->generatePotionCell();
       if (randomPotion == 1 ) {
           potion = new PositiveHp(NULL,"");
       }
       else if(randomPotion == 2) {
           potion = new PositiveAtk(NULL,"");
       }
       else if(randomPotion == 3)  {
           potion = new PositiveDef(NULL,"");
       }
       else if(randomPotion == 4)  {
           potion = new NegativeDef(NULL,"");
       }
       else if(randomPotion == 5)  {
           potion = new NegativeHp(NULL,"");
       }
       else {
           potion = new NegativeAtk(NULL,"");
       }
       temp->addContent(potion);
       randomPotion = (rand() % 6) + 1;
       count --;
    }
}

void Game::usePotion(Cell *target) {
     if (target->getContent() == NULL) {
        action = action + "There is no potion there. Please try again.";
     }
     else if (target->getContent()->getSymbol() != "P") {
        action = action + "That is not a potion. Please try again.";
     }
     else {
   //   action = action + "PC uses a potion.";
        string type = target->getContent()->getType();
        if (type == "RH") {
            action = action + "PC uses RH.";
            player = new PositiveHp(player,player->getRace());
        }
        else if(type == "PH") {
            action = action + "PC uses PH.";
            if (player->getRace() == "Elf") {
              action = action + " Elf turns the negative effect to positive.";
            }
            player = new NegativeHp(player, player->getRace());
        }
        else if ( type == "BA") {
            action = action + "PC uses BA.";
            player = new PositiveAtk(player, player->getRace());
        }
        else if ( type == "WA") {
            action = action + "PC uses WA.";
            if(player->getRace() == "Elf") {
                 action = action + " Elf turns the negative effect to positive.";
            }
            player = new NegativeAtk(player, player->getRace());
        }
        else if ( type == "BD") {
            action = action + "PC uses BD.";
            player = new PositiveDef(player, player->getRace());
         }
         else {
            action = action + "PC uses WD.";
            if (player->getRace() == "Elf") {
                action = action + " Elf turns the negative effect to positive.";
            }
            player = new NegativeDef(player, player->getRace());
         }
         delete target->getContent();
         target->addContent(NULL);
     }
}


bool hasMoved(Content *enemy) {
    for (int i = 0; i< 20 ; i++) {
       if(enemy == enemyHasMovedList[i]) {
          return true;
       }
    }
    return false;
}

void setToNull() {
   for (int i = 0; i <20; i++) {
      enemyHasMovedList[i] = NULL;
   }
}

void addToList(Content * enemy) {
    for (int i = 0; i < 20; i++) {
      if (enemyHasMovedList[i] == NULL) {
          enemyHasMovedList[i] = enemy;
          return;
      }
    }
}

void Game::generateDragon() {
  for (int i=0; i<25; i++) {
    for (int j=0; j<79; j++) {
      Cell *current = board->getOneCell(i,j);
      if(current->getContent() == NULL) {
           continue;
      }
      else if (current->getContent()->getSymbol() == "G") {
            if (current->getContent()->getGold() == 6) {
                for (int i= 0; i < 8; i++) {
                    Cell *neighbour = current->getNeighbour(i);
                    if(neighbour->getContent() == NULL && neighbour->getSymbol() != "|" && neighbour->getSymbol() != "-" && neighbour->getSymbol() != "+" && neighbour->getSymbol() != "\\") {
                         Dragon *dragon = new Dragon;
                         dragon->setDragonHorde(current);
                         neighbour->addContent(dragon);
                         neighbour->setHasEnemy(true);
                         break;
                    }
                }
            }
      }
      else {
         continue;
      }
   }
 }
}

bool Game::ifHostile(Enemy *enemy) {
   string symbol = enemy->getSymbol();
   if (enemy->getSymbol() == "M") {
      return merchantHostileCheck();
   }
   else if(enemy->getSymbol() == "D") {
      return dragonHostileCheck(enemy);
   }
   else {
      return true;
   }
}

bool Game::merchantHostileCheck() {
     if (merchantHostile) {
        return true;
     }
     int merchantCount = 0;
     for (int i = 0; i <25; i++) {
       for(int j =0; j< 79; j++) {
         if (board->getOneCell(i,j)->getContent() != NULL) {
             if (board->getOneCell(i,j)->getContent()->getSymbol() == "M") {
                 merchantCount++;
             }
          }
       }
     }
     if (merchantCount != merchantInitialNum) {
        return true;
     }
     for (int i=0; i <25; i++) {
       for (int j=0; j <79; j++) {
          Cell* current = board->getOneCell(i,j);
          if (current->getContent() == NULL) {
               continue;
          }
          else if(current->getContent()->getSymbol() == "M") {
               if(current->getContent()->getHp() != 30) {
                    merchantHostile = true;
                    return true;
               }
               continue;
          }
          else {
               continue;
          }
       }
     }
     return false;
}

bool Game::dragonHostileCheck(Enemy *d) {
    Dragon *dragon = dynamic_cast<Dragon *> (d);
    if (dragon->getHp() < 150) {
        return true;
    }
    for (int i=0; i < 8; i++) {
      if (dragon->getDragonHorde()->getNeighbour(i)->getContent() != NULL) {
        string symbol = dragon->getDragonHorde()->getNeighbour(i)->getContent()->getSymbol();
        if (symbol == "@") {
            return true;
         }
      }
    }
    return false;
}

void Game::goldStealing() {
    for (int i=0; i<8; i++) {
       if (currentCell->getNeighbour(i)->getContent() != NULL) {
            if (currentCell->getNeighbour(i)->getContent()->getSymbol() == "N" && player->getGold() > 0) {
                    player->addGold(-1);
                    action = action + " Goblin steals one gold from pc.";
            }
       }
    }
}

void healthRestore(Content* target) {
   Troll *t = dynamic_cast<Troll *> (target);
   if (t != NULL) {
      if (t->getHp() < 120) {
         t->healthRestore(5);
         int hp = t->getHp();
         stringstream ss;
         ss << hp;
         string hpTemp;
         ss >> hpTemp;
         action = action + " troll has regenarate 5 points of health." + " ("+ hpTemp+ " HP)";
      }
   }
   else {
      cout << "check out the dynamic casting you used in game.cc on function healthRestore()!" << endl;
   }
}

Game::~Game() {
 enemyList.clear();
}

void Game::resetBoard() {
    for (int i=0;i<25; i++) {
      for (int j=0; j<79; j++) {
        if (board->getOneCell(i,j)->getSymbol() == "\\") {
           board->getOneCell(i,j)->setSymbol(".");
        }
        delete board->getOneCell(i,j)->getContent();
        board->getOneCell(i,j)->addContent(NULL);
        currentCell = NULL;
//        delete Player::playerInstance;
        Player::playerInstance = NULL;
        delete Board::instanceBoard;
        Board::instanceBoard = NULL;
        board = Board::getInstance();
        enemyList.clear();
      }
    }
}





void Game::setBoardFromInput() {
     if (floor == 1) {
       for(int i=0; i < 25; i++) {
         for(int j =0; j < 79; j++) {
          Cell* current = board->getOneCell(i,j);
          char content = floor1[i][j]; 
          if (content == '@') {
             current->addContent(player);
             currentCell = current;
             currentCell->setHasPlayer(true);
          }
          else if(content == '0') {
             Content *c = new PositiveHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '1') {
             Content *c = new PositiveAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '2') {
             Content *c = new PositiveDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '3') {
             Content *c = new NegativeHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '4') {
             Content *c = new NegativeAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '5') {
             Content *c = new NegativeDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '6') {
             Content *c = new Normal;
             current->addContent(c);
          }
          else if(content == '7') {
             Content *c = new SmallHorde;
             current->addContent(c);
          }
          else if(content == '8') {
             Content *c = new MerchantHorde;
             current->addContent(c);
          }
          else if(content == '9') {
             Content *c = new DragonHorde;
             current->addContent(c);
          }
// now generate the  enemies and next stair
          else if(content == 'N') {
             Content *c = new Goblin;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'D') {
             Content *c = new Dragon;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'V') {
             Content *c = new Vampire;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'T') {
             Content *c = new Troll;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'W') {
             Content *c = new Werewolf;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'M') {
             Content *c = new Merchant;
             current->addContent(c);
             current->setHasEnemy(true);
             merchantInitialNum++;
          }
          else if(content == 'X') {
             Content *c = new Phoenix;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == '\\') {
             stairCell = current;
             stairCell->setSymbol(stairSymbol);
          }
          else {
             continue;
          }
       }
     }
  }
  if (floor == 2) {
       for(int i=0; i < 25; i++) {
         for(int j =0; j < 79; j++) {
          Cell* current = board->getOneCell(i,j);
          char content = floor2[i][j]; 
          if (content == '@') {
             current->addContent(player);
             currentCell = current;
             currentCell->setHasPlayer(true);
          }
          else if(content == '0') {
             Content *c = new PositiveHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '1') {
             Content *c = new PositiveAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '2') {
             Content *c = new PositiveDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '3') {
             Content *c = new NegativeHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '4') {
             Content *c = new NegativeAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '5') {
             Content *c = new NegativeDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '6') {
             Content *c = new Normal;
             current->addContent(c);
          }
          else if(content == '7') {
             Content *c = new SmallHorde;
             current->addContent(c);
          }
          else if(content == '8') {
             Content *c = new MerchantHorde;
             current->addContent(c);
          }
          else if(content == '9') {
             Content *c = new DragonHorde;
             current->addContent(c);
          }
// now generate the  enemies and next stair
          else if(content == 'N') {
             Content *c = new Goblin;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'D') {
             Content *c = new Dragon;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'V') {
             Content *c = new Vampire;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'T') {
             Content *c = new Troll;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'W') {
             Content *c = new Werewolf;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'M') {
             Content *c = new Merchant;
             current->addContent(c);
             current->setHasEnemy(true);
             merchantInitialNum++;
          }
          else if(content == 'X') {
             Content *c = new Phoenix;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == '\\') {
             stairCell = current;
             stairCell->setSymbol(stairSymbol);
          }
          else {
             continue;
          }
      } //end of inner loop
    }// end of outer loop
  } 
  if (floor == 3) {
       for(int i=0; i < 25; i++) {
         for(int j =0; j < 79; j++) {
          Cell* current = board->getOneCell(i,j);
          char content = floor3[i][j]; 
          if (content == '@') {
             current->addContent(player);
             currentCell = current;
             currentCell->setHasPlayer(true);
          }
          else if(content == '0') {
             Content *c = new PositiveHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '1') {
             Content *c = new PositiveAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '2') {
             Content *c = new PositiveDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '3') {
             Content *c = new NegativeHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '4') {
             Content *c = new NegativeAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '5') {
             Content *c = new NegativeDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '6') {
             Content *c = new Normal;
             current->addContent(c);
          }
          else if(content == '7') {
             Content *c = new SmallHorde;
             current->addContent(c);
          }
          else if(content == '8') {
             Content *c = new MerchantHorde;
             current->addContent(c);
          }
          else if(content == '9') {
             Content *c = new DragonHorde;
             current->addContent(c);
          }
// now generate the  enemies and next stair
          else if(content == 'N') {
             Content *c = new Goblin;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'D') {
             Content *c = new Dragon;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'V') {
             Content *c = new Vampire;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'T') {
             Content *c = new Troll;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'W') {
             Content *c = new Werewolf;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'M') {
             Content *c = new Merchant;
             current->addContent(c);
             current->setHasEnemy(true);
             merchantInitialNum++;
          }
          else if(content == 'X') {
             Content *c = new Phoenix;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == '\\') {
             stairCell = current;
             stairCell->setSymbol(stairSymbol);
          }
          else {
             continue;
          }
      } // end of inner loop
   } // end of outer loop
}
 if (floor == 4) {
       for(int i=0; i < 25; i++) {
         for(int j =0; j < 79; j++) {
          Cell* current = board->getOneCell(i,j);
          char content = floor4[i][j]; 
          if (content == '@') {
             current->addContent(player);
             currentCell = current;
             currentCell->setHasPlayer(true);
          }
          else if(content == '0') {
             Content *c = new PositiveHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '1') {
             Content *c = new PositiveAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '2') {
             Content *c = new PositiveDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '3') {
             Content *c = new NegativeHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '4') {
             Content *c = new NegativeAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '5') {
             Content *c = new NegativeDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '6') {
             Content *c = new Normal;
             current->addContent(c);
          }
          else if(content == '7') {
             Content *c = new SmallHorde;
             current->addContent(c);
          }
          else if(content == '8') {
             Content *c = new MerchantHorde;
             current->addContent(c);
          }
          else if(content == '9') {
             Content *c = new DragonHorde;
             current->addContent(c);
          }
// now generate the  enemies and next stair
          else if(content == 'N') {
             Content *c = new Goblin;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'D') {
             Content *c = new Dragon;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'V') {
             Content *c = new Vampire;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'T') {
             Content *c = new Troll;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'W') {
             Content *c = new Werewolf;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'M') {
             Content *c = new Merchant;
             current->addContent(c);
             current->setHasEnemy(true);
             merchantInitialNum++;
          }
          else if(content == 'X') {
             Content *c = new Phoenix;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == '\\') {
             stairCell = current;
             stairCell->setSymbol(stairSymbol);
          }
          else {
             continue;
          }
      } // end of inner loop
   } // end of outer loop
}
     if (floor == 5) {
       for(int i=0; i < 25; i++) {
         for(int j =0; j < 79; j++) {
          Cell* current = board->getOneCell(i,j);
          char content = floor5[i][j]; 
          if (content == '@') {
             current->addContent(player);
             currentCell = current;
             currentCell->setHasPlayer(true);
          }
          else if(content == '0') {
             Content *c = new PositiveHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '1') {
             Content *c = new PositiveAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '2') {
             Content *c = new PositiveDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '3') {
             Content *c = new NegativeHp(NULL, "");
             current->addContent(c);
          }
          else if(content == '4') {
             Content *c = new NegativeAtk(NULL, "");
             current->addContent(c);
          }
          else if(content == '5') {
             Content *c = new NegativeDef(NULL, "");
             current->addContent(c);
          }
          else if(content == '6') {
             Content *c = new Normal;
             current->addContent(c);
          }
          else if(content == '7') {
             Content *c = new SmallHorde;
             current->addContent(c);
          }
          else if(content == '8') {
             Content *c = new MerchantHorde;
             current->addContent(c);
          }
          else if(content == '9') {
             Content *c = new DragonHorde;
             current->addContent(c);
          }
// now generate the  enemies and next stair
          else if(content == 'N') {
             Content *c = new Goblin;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'D') {
             Content *c = new Dragon;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'V') {
             Content *c = new Vampire;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'T') {
             Content *c = new Troll;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'W') {
             Content *c = new Werewolf;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == 'M') {
             Content *c = new Merchant;
             current->addContent(c);
             current->setHasEnemy(true);
             merchantInitialNum++;
          }
          else if(content == 'X') {
             Content *c = new Phoenix;
             current->addContent(c);
             current->setHasEnemy(true);
          }
          else if(content == '\\') {
             stairCell = current;
             stairCell->setSymbol(stairSymbol);
          }
          else {
             continue;
          }
      } // end of inner loop
   }// end of outer loop
 }
}

void Game::gameOver() {
      if (player->getHp() <= 0) {
      double gold;
      if (player->getRace() == "Human") { gold = player->getGold() * 1.5;}
      else { gold = player->getGold();}
      cout << "Game Over, your final score is " << gold << endl;
      cout << "Please wait, the game is resetting!" << endl;
      floor =1;
      resetBoard();
      return startGame();
    }
}

