//#include "calculator.hpp"
#include "calc.hpp"
#include "menu.hpp"

double calculate(std::string );

bool escape();

bool key_pressed();

int welcome_screen();

int line_mode(int& , int& );

int open_calc(std::string& , int );

int main()
{
	std::string expression = "";
	
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
				if (open_calc(expression, mode) == 27) break;
			case 1://info
				std::cout << "info\n";
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