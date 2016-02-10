#include <iostream>
#include <string>

#include "textdisplay.h"
#include "board.h"
#include "cell.h"

using namespace std;
/*
class TextDisplay {
      std::string display[25][79];
public:
      void notify(int r, int c, std::string symbol);
      friend std::ostream& operator<< (std::ostream& out, TextDisplay *);
};

*/
void TextDisplay::notify(int r, int c, string symbol) {
      display[r][c] = symbol;
}

ostream& operator<<(ostream& out, TextDisplay *td) {
     for (int i= 0; i < 25; i++) {
        for (int j=0; j < 79; j++) {
           cout << td->display[i][j];
        }
     cout << endl; 
    }
    return out;
}
