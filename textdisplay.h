#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <string>

const int maxRow = 25;
const int maxCol = 79;

class TextDisplay {
      std::string display[maxRow][maxCol];
public:
      void notify(int r, int c, std::string symbol);
      friend std::ostream& operator<< (std::ostream& out, TextDisplay *);
};

#endif
