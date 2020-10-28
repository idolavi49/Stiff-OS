#include "include/screen.h"
#include "include/kb.h"
#include "include/string.h"

kmain()
{
	clearScreen();
	print("Welcome to Stiffler's operating system!\nPlease enter a command\n ");

	while (1)
	{
				print("\nStiff> ");
				string ch = readStr();
			    if(strEql(ch,"cmd"))
				{
						print("\nYou are allready in cmd\n");
				}
				
				else if(strEql(ch,"clear"))
				{
						clearScreen();
				}
				
				else
				{
						print("\nBad command!\n");
				}
				
				print("\n"); 
	}
}
