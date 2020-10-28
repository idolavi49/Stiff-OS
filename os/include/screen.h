#ifndef  SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"

int cursorX, cursorY;
const uint8 sw, sh, sd;		// we define the screen width, height and depth.
void clearLine(uint8 from , uint8 to); // clear a line.


void updateCursor(); // update the location of the cursor.


void clearScreen(); // clears all the screen lines 



void scrollUp(uint8 lineNumber); // moves up the lines in the screen by $lineNumber lines.


void newLineCheck(); // move up the screen by 1 because there is a new line.


void printch (char c); // print a char



void print (string ch); // print a sentence

  


#endif









