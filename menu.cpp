#include <iostream>
#include <unistd.h>

#include "input.hpp"
#include "menu.hpp"

constexpr int max_lines = 3;

constexpr int UP_key = 119;
constexpr int DOWN_key = 115;
constexpr int LEFT_key = 97;
constexpr int RIGHT_key = 100;
constexpr int ENTER_key = 10;
constexpr int ESC_key = 27;

//manual
int print_how_to_use()
{

	color_cout("                      Write down the statment without mistakes, without spaces.              \n", 4);
	color_cout("                      Factorial      -- n!                                                   \n", 4);
	color_cout("                      Square root    -- sqrt(n)                                              \n", 4);
	color_cout("                      Sinus          -- sin(n)                                               \n", 4);
	color_cout("                      Cosinus        -- cos(n)                                               \n", 4);
	color_cout("                      Tangens        -- tg(n)                                                \n", 4);
	color_cout("                      Log_e(n)       -- ln(n)                                                \n", 4);
	color_cout("                      Log_10(n)      -- lg(n)                                                \n", 4);
	color_cout("                      Percent        -- %                                                    \n", 4);
	color_cout("                      Absolute       -- abs(n)                                               \n", 4);
	color_cout("                      Power          -- x^n                                                  \n", 4);
	color_cout("                      Multiply       -- x*n                                                  \n", 4);
	color_cout("                      Divide         -- x/n                                                  \n", 4);
	color_cout("                      Plus           -- x+n                                                  \n", 4);
	color_cout("                      Minus          -- x-n                                                  \n", 4);
	
	return 0;
}

//print colorfull text
void color_cout(std::string text, int text_color = 8)
{
	switch(text_color)
	{ 
		case  1: std::cout << "\x1b[90;1m" << text << "\x1b[0m"; break; // gray
		case  2: std::cout << "\x1b[34;1m" << text << "\x1b[0m"; break; // blue
		case  3: std::cout << "\x1b[32;1m" << text << "\x1b[0m"; break; // green
		case  4: std::cout << "\x1b[36;1m" << text << "\x1b[0m"; break; // cyan
		case  5: std::cout << "\x1b[31;1m" << text << "\x1b[0m"; break; // red
		case  6: std::cout << "\x1b[95;1m" << text << "\x1b[0m"; break; // pink
		case  7: std::cout << "\x1b[33;1m" << text << "\x1b[0m"; break; // yellow
		default: std::cout << "\x1b[97;1m" << text << "\x1b[0m";
	}
}

//main menu
int print_menu(int Line = 0, int mode_i = 0)
{
	std::string mode = "";
	
	switch (mode_i)
	{
		case 1:
			mode = " VARIABLE  calculator";
			break;
		case 2:
			mode = "INEQUALITY calculator";
			break;
		default:
			mode = "  SIMPLE   calculator";
			break;
	}
	
	gotoxy(1, 9);
	
	color_cout("                                                         .\n", 1);
	color_cout("                                             mode:", 1); color_cout(" <" + mode + ">\n", (Line == 0)? 4 : 0);
	color_cout("                                                      -about-\n", (Line == 1)? 4 : 0);
	color_cout("                                                       -out-\n", (Line == 2)? 5 : 0);
	color_cout("                                                         .\n", 1);
	
	return 5;
}

//moves up and down and changes the modes
int line_mode(int& line, int& mode)
{
	while (true)
	{
		cbreak();
		int key = keypress();
		
		switch (key)
		{
			case UP_key:
				line = (line + max_lines - 1)% max_lines;
				print_menu(line, mode);
				break;
			case DOWN_key:
				line = (line + max_lines + 1)% max_lines;
				print_menu(line, mode);
				break;
			case LEFT_key:
				if (line == 0)
				{
					mode = (mode + max_lines - 1)% max_lines;
					print_menu(line, mode);
				}
				break;
			case RIGHT_key:
				if (line == 0)
				{
					mode = (mode + max_lines + 1)% max_lines;
					print_menu(line, mode);
				}
				break;
			case ENTER_key:
				normal();
				return line;
			case ESC_key:
				normal();
				return line = 2;
			default:
				break;
		}
	}
	normal();
	return 2;
}

//CALCULATOR
int print_name()
{
	color_cout("                                                                                                                  \n", 4);
	color_cout("  ????????????????????????      ?????????     ?????????         ????????????????????????  ?????????    ????????? ?????????            ?????????     ?????????????????????????????????  ????????????????????????  ???????????????????????????  \n", 4);
	color_cout(" ?????????    ?????????   ????????? ?????????   ?????????        ?????????    ????????? ?????????    ????????? ?????????          ????????? ?????????       ?????????     ?????????    ????????? ?????????    ????????? \n", 4);
	color_cout(" ?????????         ?????????   ?????????  ?????????        ?????????        ?????????    ????????? ?????????         ?????????   ?????????      ?????????     ?????????    ????????? ?????????    ????????? \n", 4);
	color_cout(" ?????????        ????????????????????????????????? ?????????        ?????????        ?????????    ????????? ?????????        ?????????????????????????????????     ?????????     ?????????    ????????? ???????????????????????????  \n", 4);
	color_cout(" ?????????        ?????????     ????????? ?????????        ?????????        ?????????    ????????? ?????????        ?????????     ?????????     ?????????     ?????????    ????????? ?????????    ????????? \n", 4);
	color_cout(" ?????????    ????????? ?????????     ????????? ?????????        ?????????    ????????? ?????????    ????????? ?????????        ?????????     ?????????     ?????????     ?????????    ????????? ?????????    ????????? \n", 4);
	color_cout("  ????????????????????????  ?????????     ????????? ??????????????????????????????  ????????????????????????   ????????????????????????  ?????????????????????????????? ?????????     ?????????     ?????????      ????????????????????????  ?????????    ????????? \n\n", 4);
	
	return 8;
}

//prints name and main menu
int welcome_screen()
{
	system("clear");
	int k = print_name();
	gotoxy(1, k + 1);
	print_menu(0);

	return 0;
}

//in about section prints the manual
int print_about()
{
color_cout("                                                                                                                                        \n", 4);
color_cout("                    ?????????    ?????????  ????????????????????????  ?????????       ?????????    ?????????????????????????????????  ????????????????????????     ?????????    ?????????  ????????????????????????  ?????????????????????????????? \n", 4);
color_cout("                    ?????????    ????????? ?????????    ????????? ?????????       ?????????        ?????????     ?????????    ?????????    ?????????    ????????? ?????????    ????????? ?????????        \n", 4);
color_cout("                    ?????????    ????????? ?????????    ????????? ?????????       ?????????        ?????????     ?????????    ?????????    ?????????    ????????? ?????????        ?????????        \n", 4);
color_cout("                    ?????????????????????????????? ?????????    ????????? ?????????  ?????????  ?????????        ?????????     ?????????    ?????????    ?????????    ????????? ?????????????????????????????? ????????????????????????   \n", 4);
color_cout("                    ?????????    ????????? ?????????    ????????? ????????? ??????????????? ?????????        ?????????     ?????????    ?????????    ?????????    ?????????        ????????? ?????????        \n", 4);
color_cout("                    ?????????    ????????? ?????????    ?????????  ??????????????? ???????????????         ?????????     ?????????    ?????????    ?????????    ????????? ?????????    ????????? ?????????        \n", 4);
color_cout("                    ?????????    ?????????  ????????????????????????    ?????????   ?????????          ?????????      ????????????????????????      ????????????????????????   ????????????????????????  ?????????????????????????????? \n", 4);
color_cout("                                                                                                                                        \n", 4);

	gotoxy(1,10);
	print_how_to_use();

	return 0;
}