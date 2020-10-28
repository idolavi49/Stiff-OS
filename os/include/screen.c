#include "screen.h"
int cursorX = 0 , cursorY = 0;
const uint8 sw = 80 , sh = 25 , sd = 2;		// we define the screen width, height and depth.
void clearLine(uint8 from , uint8 to) // clear a line.
{
		uint16 i = sw * from * sd;
		string vidmem = (string)0xb8000;
		for(i;i<(sw*(to+1)*sd);i++)
		{
				vidmem[i] = 0x0;
		}
}

void updateCursor() // update the location of the cursor.
{
		unsigned temp;
		
		temp = cursorY * sw + cursorX;		// Position = (y * width) + x
		
		outportb(0x3D4, 14);						// CRT Control Register: Select Cursor Location
		outportb(0x3D5, temp >> 8);			// Send the high byte across the bus
		outportb(0x3D4, 15);						// CRT Control Register Select Send Low byte
		outportb(0x3D5, temp);					// Send the Low byte of the cursor location
}

void clearScreen() // clears all the screen lines 
{
		clearLine(0,sh-1);
		cursorX = 0;
		cursorY = 0;
		updateCursor();
}


void scrollUp(uint8 lineNumber) // moves up the lines in the screen by $lineNumber lines.
{
		string vidmem = (string) 0xb8000;
		uint16 i = 0;
		for(i;i<sw*(sh-1)*sd;i++)
		{
				vidmem[i] = vidmem[i+sw*sd*lineNumber]; 
		}
		clearLine(sh-1-lineNumber, sh-1);
		if((cursorY - lineNumber) < 0)
		{
				cursorY = 0;
				cursorX = 0;
		}
		
		else
		{
				cursorY -= lineNumber;
		}
		updateCursor();
}

void newLineCheck() // move up the screen by 1 because there is a new line.
{
		if(cursorY >=sh-1)
		{
				scrollUp(1);
		}
}

void printch(char c) // print a char
{
		string vidmem = (string) 0xb8000;
		switch(c)
		{
			case (0x08): // print a delete char (the above pipline keyboard)
					if(cursorX > 0)
					{ 
						cursorX--; 
						vidmem[(cursorY * sw + cursorX)*sd] = 0x00;
					}
					break;
					
			case (0x09): // print tab
					cursorX = (cursorX + 8) & ~(8 - 1);
					break;
			
			case ('\r'): // back to the start of the line
					cursorX = 0;
					break;
						
			case ('\n'): // get a line down
					cursorX = 0;
					cursorY++;
					break;
						
			default: // default - print the char
					vidmem [((cursorY * sw + cursorX))*sd] = c;
					vidmem [((cursorY * sw + cursorX))*sd+1] = 0x0F; 
					cursorX++;
					break;
		}
		
		if(cursorX >= sw) // if we got to the end of the line get a line down to the beginning
		{
				cursorX = 0;
				cursorY++;
		}
		newLineCheck();
		updateCursor();
}


void print (string ch) // print a sentence
{
	uint16 i = 0;
	uint8 length = strlength(ch) - 1; // Updated (now we store string length on a variable to call the function only once)
	for(i;i<length;i++)
	{
		printch(ch[i]);
	}
}