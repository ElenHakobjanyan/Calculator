#include <iostream>

#include "calc.hpp"
#include "input.hpp"
#include "menu.hpp"

int main()
{	
	while (true)
	{
		welcome_screen();
		
		int line = 0;
		int mode = 0;
		line_mode(line, mode);
		
		gotoxy(1, 1);
		system("clear");
		
		switch (line)
		{
			case 0://calc
				open_calc(mode);
				break;
			case 1://info
				print_about();
				if (escape())
				{
					continue;
				}
				break;
			case 2://esc
				return 0;
			default:
				return 0;
		}
	}
	return 0;
}


//"5+sqrt(16)+sin(0)+cos(0)+tg(45)+ln(e)+lg(100)+abs(5)+abs(0-15)"
//Output: 34

//"(4+2)*8-(6/4)+15"
//Output: 61.5