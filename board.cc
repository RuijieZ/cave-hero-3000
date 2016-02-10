#include <string>
#include <iostream>

#include "cell.h"
#include "board.h"
#include "textdisplay.h"

using namespace std;

int playerChamber;
int stairChamber;

void newSeed() {
  srand(time(0));
}

void generatePlayerChamberNumber() {
    newSeed();
    playerChamber = (rand () % 5) + 1;
}


void generateStairChamberNumber() {   // generate stair chamber # , should only be called after player chamber has been genenareted
    //newSeed();
    stairChamber = (rand () % 5) + 1;
    while (playerChamber == stairChamber) {
       stairChamber = (rand () % 5) + 1;
    }
}



Board:: Board(): td(NULL){
    generatePlayerChamberNumber();
    generateStairChamberNumber();
    init();
}

Board * Board::instanceBoard = NULL;

Board *Board::getInstance() {
    if (instanceBoard == NULL) {
       instanceBoard = new Board;
    }
    return instanceBoard;
}

Board::~Board() {
    delete td;
}

void Board::init() {
    delete td;
    td = new TextDisplay();
    for(int i = 0; i < maxRow; i++) {
        for(int j = 0; j < maxCol; j++) {
           theBoard[i][j].setCoords(i,j);
           theBoard[i][j].setDisplay(td);
           theBoard[i][j].notifyDisplay();                 // set the default symbol to be " "
        }
    }                                                      //initialize the board
    for (int i=1; i < maxCol- 1; i++) {
         theBoard[0][i].setSymbol("-");
         theBoard[24][i].setSymbol("-");
    }                                                      //first and last row
    for (int i=0; i < maxRow; i++) {
         theBoard[i][0].setSymbol("|");
         theBoard[i][78].setSymbol("|");
    }                                                      // left and right col

    //now setting the first room
    for (int i=2; i <= 7; i++) {
         theBoard[i][2].setSymbol("|");
         theBoard[i][29].setSymbol("|");
    }
    for (int i=3; i <= 28; i++) {
         theBoard[2][i].setSymbol("-");
         theBoard[7][i].setSymbol("-");
    }
    for (int i=3; i <=6; i++) {
        for(int j=3; j <=28; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
    // the first room has been set up


   // the  second room  is aobut to be set up 
    for (int i=14; i <= 22; i++) {
         theBoard[i][3].setSymbol("|");
         theBoard[i][25].setSymbol("|");
    }
    for (int i=4; i <=24 ; i++) {
         theBoard[14][i].setSymbol("-");
         theBoard[22][i].setSymbol("-");
    }
    for (int i=15; i <=21; i++) {
        for(int j=4; j <=24; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   // the second room been set up


   // the third room  is aobut to be set up 
    for (int i=9; i <=13; i++) {
         theBoard[i][37].setSymbol("|");
         theBoard[i][50].setSymbol("|");
    }
    for (int i=38; i <=49; i++) {
         theBoard[9][i].setSymbol("-");
         theBoard[13][i].setSymbol("-");
    }
    for (int i=10; i <=12; i++) {
        for(int j=38; j <=49; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   // the third room been set up

   // now come the fourth room on the right down
   for (int i=18; i <=22; i++) {
        theBoard[i][36].setSymbol("|");
   }
   for (int i=15; i <=18; i++) {
        theBoard[i][64].setSymbol("|");
   }
   for (int i=15; i <=22; i++) {
        theBoard[i][76].setSymbol("|");
   }
   for (int i=65; i <=75; i++) {
         theBoard[15][i].setSymbol("-");
   }
   for (int i=37; i <=63; i++) {
         theBoard[18][i].setSymbol("-");
   }
   for (int i=37; i <=75; i++) {
         theBoard[22][i].setSymbol("-");
   }
   for (int i=16; i <=18; i++) {
        for(int j=65; j <=75; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   for (int i=19; i <=21; i++) {
        for(int j=37; j <=75; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   // now the fourth room has been set up

   // now the fifth room will be set up
   for (int i=2; i <=7; i++) {
        theBoard[i][38].setSymbol("|");
   }
   for (int i=2; i <=4; i++) {
        theBoard[i][62].setSymbol("|");
   }
   for (int i=4; i <=5; i++) {
        theBoard[i][70].setSymbol("|");
   }
   for (int i=5; i <=6; i++) {
        theBoard[i][73].setSymbol("|");
   }
   for (int i=6; i <=13; i++) {
        theBoard[i][76].setSymbol("|");
   }
   for (int i=7; i <=13; i++) {
        theBoard[i][60].setSymbol("|");
   }


   for (int i=39; i <=61; i++) {
         theBoard[2][i].setSymbol("-");
   }
   for (int i=63; i <=69; i++) {
         theBoard[4][i].setSymbol("-");
   }
   for (int i=71; i <=72; i++) {
         theBoard[5][i].setSymbol("-");
   }
   for (int i=74; i <=75; i++) {
         theBoard[6][i].setSymbol("-");
   }
   for (int i=39; i <=59; i++) {
         theBoard[7][i].setSymbol("-");
   }
   for (int i=61; i <=75; i++) {
         theBoard[13][i].setSymbol("-");
   }


   for (int i=3; i <=6; i++) {
        for(int j=39; j <=61; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   for (int i=5; i <=7; i++) {
        for(int j=61; j <=69; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
   for (int i=6; i <=7; i++) {
        for(int j=70; j <=72; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }
    theBoard[7][73].setSymbol(".");
    theBoard[7][74].setSymbol(".");
    theBoard[7][75].setSymbol(".");
    for (int i=8; i <=12; i++) {
        for(int j=61; j <=75; j++) {
            theBoard[i][j].setSymbol(".");
        }
    }

// fifth room set up 


//now set up the gate "+"

theBoard[7][13].setSymbol("+");
theBoard[4][29].setSymbol("+");
theBoard[14][13].setSymbol("+");
theBoard[20][25].setSymbol("+");
theBoard[9][43].setSymbol("+");
theBoard[13][43].setSymbol("+");
theBoard[4][38].setSymbol("+");
theBoard[13][69].setSymbol("+");
theBoard[15][69].setSymbol("+");
theBoard[20][36].setSymbol("+");
theBoard[7][43].setSymbol("+");
theBoard[18][43].setSymbol("+");
theBoard[11][60].setSymbol("+");

// not the "+" has been setup

// now setting up "#"

   for (int i=8; i <=13; i++) {
        theBoard[i][13].setSymbol("#");
   }
   for (int i=4; i <=8; i++) {
        theBoard[i][33].setSymbol("#");
   }
   for (int i=8; i <=20; i++) {
        theBoard[i][31].setSymbol("#");
   }
   for (int i=11; i <=16; i++) {
        theBoard[i][54].setSymbol("#");
   }
   for (int i=14; i <=17; i++) {
        theBoard[i][43].setSymbol("#");
   }

   for (int i=30; i <=37; i++) {
        theBoard[4][i].setSymbol("#");
   }
   for (int i=31; i <=43; i++) {
        theBoard[8][i].setSymbol("#");
   }
   for (int i=13; i <=31; i++) {
        theBoard[11][i].setSymbol("#");
   }
   for (int i=54; i <=59; i++) {
        theBoard[11][i].setSymbol("#");
   }
   for (int i=31; i <=54; i++) {
        theBoard[16][i].setSymbol("#");
   }
   for (int i=26; i <=35; i++) {
        theBoard[20][i].setSymbol("#");
   }
   theBoard[14][69].setSymbol("#");




//now te "#" has been set up


// now we will set up all the neighbours


    theBoard[0][0].addNeighbour(&theBoard[0][1]);
    theBoard[0][0].addNeighbour(&theBoard[1][0]);
    theBoard[0][78].addNeighbour(&theBoard[0][77]);
    theBoard[0][78].addNeighbour(&theBoard[1][78]);
    theBoard[24][0].addNeighbour(&theBoard[24][1]);
    theBoard[24][0].addNeighbour(&theBoard[23][0]);
    theBoard[24][78].addNeighbour(&theBoard[24][77]);
    theBoard[24][78].addNeighbour(&theBoard[23][78]);    // setting neighbours for the 4 corners
    for (int i = 1; i < 24; i++) {
       theBoard[i][0].addNeighbour(&theBoard[i-1][0]);
       theBoard[i][0].addNeighbour(&theBoard[i][1]);
       theBoard[i][0].addNeighbour(&theBoard[i+1][0]);
       theBoard[i][78].addNeighbour(&theBoard[i-1][78]);
       theBoard[i][78].addNeighbour(&theBoard[i][77]);
       theBoard[i][78].addNeighbour(&theBoard[i+1][78]);
    }                                                    // left side and  right side
    for (int i = 1; i <78; i++) {
       theBoard[0][i].addNeighbour(&theBoard[0][i-1]);
       theBoard[0][i].addNeighbour(&theBoard[1][i]);
       theBoard[0][i].addNeighbour(&theBoard[0][i+1]);
       theBoard[24][i].addNeighbour(&theBoard[24][i-1]);
       theBoard[24][i].addNeighbour(&theBoard[24][i]);
       theBoard[24][i].addNeighbour(&theBoard[24][i-1]);
    }                                                      // setting neighbours for  the four sides of the board
    for (int i = 1; i < 24; i++) {
       for (int j = 1; j <77; j++) {
            theBoard[i][j].addNeighbour(&theBoard[i][j+1]);
            theBoard[i][j].addNeighbour(&theBoard[i][j-1]);
            theBoard[i][j].addNeighbour(&theBoard[i-1][j]);
            theBoard[i][j].addNeighbour(&theBoard[i+1][j]);
            theBoard[i][j].addNeighbour(&theBoard[i+1][j+1]);
            theBoard[i][j].addNeighbour(&theBoard[i+1][j-1]);
            theBoard[i][j].addNeighbour(&theBoard[i-1][j-1]);
            theBoard[i][j].addNeighbour(&theBoard[i-1][j+1]);
       }
    }
}

Cell* Board::getOneCell(int r, int c) {
     return &theBoard[r][c];
}


ostream& operator<<(ostream &out, const Board &g) {
    out << (g.td);
    return out;
}
/*
void Board:: moveContent(int r1 ,int c1, int r2, int c2) {
   if (theBoard[r1][c1].content == NULL) {
       cout << "out of scope" << endl;
       return;
    }
   if(theBoard[r2][c2] != NULL) {
      cout << "Spot occupied, please try another move" << endl;
      moveFail = true;
    }
    else if(theBoard[r2][c2].contentSymbol == " " || theBoard[r2][c2].contentSymbol == "|" || theBoard[r2][c2].contentSymbol == "-") {
      cout << "invalid move, please try another move" << endl;
      moveFail = true;
    }
    else {
      theBoard[r2][c2].addContent(theBoard[r1][c1].getContent);
       NULL;
      this->notifyDisplay();
    }
}
      
*/

// now we wnat to define chamber 1



Cell *Board::generateRandomCell(int chamberNum) {
    if (chamberNum == 1) {    // top left
      int randomRow = (rand () % 4) + 3;
      int randomCol = (rand () % 26) + 3;
      return &theBoard[randomRow][randomCol];
    }
    else if (chamberNum == 2) {    // bottom left
      int randomRow = (rand () % 7) + 15;
      int randomCol = (rand () % 21) + 4;
      return &theBoard[randomRow][randomCol];
    }
    else if (chamberNum == 3) {  // middle
      int randomRow = (rand () % 3) + 10;
      int randomCol = (rand () % 12) + 38;
      return &theBoard[randomRow][randomCol];
    }
    else if (chamberNum == 4) {   // bottom right
      int randomRow = (rand () % 6) + 16; 
      int randomCol = (rand () % 39) + 37;
      while (randomRow >= 16 && randomRow <= 18 && randomCol >= 37 && randomCol <= 64) {
          randomRow = (rand () % 6) + 16; 
          randomCol = (rand () % 39) + 37;
      }
      return &theBoard[randomRow][randomCol];
    }
    else {         	           // top right
      int randomRow = (rand () % 10) + 3;
      int randomCol = (rand () % 37) + 39;
      while ((randomRow >= 2 && randomRow <= 4 && randomCol >= 62 and randomCol <= 76) || (randomRow >= 4 && randomRow <= 5 && randomCol >= 70 and randomCol <= 74) ||
      (randomRow >= 5 && randomRow <= 6 && randomCol >= 73 and randomCol <= 76) || (randomRow >= 7 && randomRow <= 13 && randomCol >= 38 and randomCol <= 60)) {
          randomRow = (rand () % 10) + 3;
          randomCol = (rand () % 37) + 39;
      }
      return &theBoard[randomRow][randomCol];
    }
}

Cell * Board::generatePlayerCell() {
    return generateRandomCell(playerChamber);
}

Cell *Board::generateStairCell() {
    Cell* temp = generateRandomCell(stairChamber);
    int r = temp->getR();
    int c = temp->getC();
    while ((r>=3 && r <= 6 &&c == 28)|| (r>=15 && r <= 21 &&c == 24)|| (r == 5 &&c == 69)|| (r == 6 && c == 72)||
           (r>=10 && r <= 12 &&c == 49)|| (r>=7 && r <= 12 &&c == 75)|| (r>=16 && r <= 21 &&c == 75) ||(r>=3 && r <= 4 &&c == 61))  {
        temp = generateRandomCell(stairChamber);
        r = temp->getR();
        c = temp->getC();
    }
    return temp;
}

Cell *Board::generateEnemyCell() {
    newSeed();
    int randomChamber = (rand() % 5) + 1;
    Cell* temp = generateRandomCell(randomChamber);
    while (temp->getContent() != NULL || temp->getSymbol() == "\\") {
        randomChamber = (rand() % 5) + 1;
        temp = generateRandomCell(randomChamber);
    }
    return temp;
}

Cell *Board::generateTreasureCell() {
    return generateEnemyCell();
}

Cell *Board::generatePotionCell() {
    return generateEnemyCell();
}

Cell *Board::findEmptyCellHasEmptyNeighbour() {
    Cell *temp = generateEnemyCell();
    bool ifHasEmptyNeighbour = false;
    for (int i = 0; i < 8; i++) {
       Cell* neighbour = temp->getNeighbour(i);
       if ( neighbour->getContent() == NULL && neighbour->getSymbol() != "+" && neighbour->getSymbol() != "-" && neighbour->getSymbol() != "|" && neighbour->getSymbol() != "\\") {
            ifHasEmptyNeighbour = true;
       }
    }
    if (!ifHasEmptyNeighbour) {
       return findEmptyCellHasEmptyNeighbour();
    }
    return temp;
}

