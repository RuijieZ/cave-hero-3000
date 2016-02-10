#include <iostream>
#include <string>
#include <fstream>

#include "cell.h"
#include "board.h"
#include "textdisplay.h"
#include "content.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "human.h"
#include "game.h"


using namespace std;
void cleanUp();
bool moveFail = false;
int floor = 1;
bool ifInputFile = false;
char floor1[25][79];
char floor2[25][79];
char floor3[25][79];
char floor4[25][79];
char floor5[25][79];

int main(int argc, char** argv) {
 if (argc == 1) {
   Game *game = Game::getInstance();
   game->startGame();
   atexit(cleanUp);
 }
 else {
   ifInputFile = true;
   ifstream inputFile(argv[1]);
   for (int i=0; i<25; i++) {
       string line;
       getline(inputFile,line);
       for(int j=0; j < 79; j++) {
          floor1[i][j] = line[j];
       }
   }
   for (int i=0; i<25; i++) {
       string line;
       getline(inputFile,line);
       for(int j=0; j < 79; j++) {
          floor2[i][j] = line[j];
       }
   }
   for (int i=0; i<25; i++) {
       string line;
       getline(inputFile,line);
       for(int j=0; j < 79; j++) {
          floor3[i][j] = line[j];
       }
   }
   for (int i=0; i<25; i++) {
       string line;
       getline(inputFile,line);
       for(int j=0; j < 79; j++) {
          floor4[i][j] = line[j];
       }
   }
   for (int i=0; i<25; i++) {
       string line;
       getline(inputFile,line);
       for(int j=0; j < 79; j++) {
          floor5[i][j] = line[j];
       }
   }
   Game *game = Game::getInstance();
   game->startGame();
   atexit(cleanUp);
 }
}

void cleanUp() {
     delete Game::gameInstance;
//   delete Player::playerInstance;
   delete Board::instanceBoard;
}































/*
   Board *b = Board::getInstance(); 
   Cell* c = b->getOneCell(3,3);
   Player * content = new Human;
   c->addContent(content);
   cout << (*b);
   while (true) {
    cin >>testing;
    moveFail = false;
    if (testing == "stop" || cin.eof()) {
      break;
    }
    else if (testing == "no") {
      c->moveContent(b->getOneCell(c->getR()-1, c->getC()));
      if(!moveFail) {
         c = b->getOneCell(c->getR()-1,c->getC());
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "so") {
      c->moveContent(b->getOneCell(c->getR()+1, c->getC()));
      if(!moveFail) {
         c = b->getOneCell(c->getR()+1,c->getC());
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "ea") {
      c->moveContent(b->getOneCell(c->getR(), c->getC()+1));
      if(!moveFail) {
          c = b->getOneCell(c->getR(),c->getC()+1);
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "we") {
      c->moveContent(b->getOneCell(c->getR(), c->getC()-1));
      if(!moveFail) {
          c = b->getOneCell(c->getR(),c->getC()-1);
      }
      cout << (*b);
    }
    else if (testing == "ne") {
      c->moveContent(b->getOneCell(c->getR()-1, c->getC()+1));
      if(!moveFail) {
         c = b->getOneCell(c->getR()+1,c->getC()+1);
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "nw") {
      c->moveContent(b->getOneCell(c->getR()-1, c->getC()-1));
      if(!moveFail) {
         c = b->getOneCell(c->getR()-1,c->getC()-1);
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "sw") {
      c->moveContent(b->getOneCell(c->getR()+1, c->getC()-1));
      if(!moveFail) {
          c = b->getOneCell(c->getR()+1,c->getC()-1);
      }
      cout << (*b);
      printStatus(content);
    }
    else if (testing == "se") {
      c->moveContent(b->getOneCell(c->getR()+1, c->getC()+1));
      if(!moveFail) {
          c = b->getOneCell(c->getR()+1,c->getC()+1);
      }
      cout << (*b);
      printStatus(content);
    }
    else {
       continue;
   }
 }// end of while loop
}

*/
