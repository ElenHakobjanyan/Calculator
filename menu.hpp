#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "input.hpp"

#include <unistd.h>

constexpr int max_lines = 3;

//print colorfull text
void color_cout(std::string text, int text_color = 8)// gunavor tpelu functia
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

int print_menu(int Line = 0, int mode_i = 0)
{
	std::string mode = "";
	
	switch (mode_i)
	{
		case 1:
			mode = "equation calculator";
			break;
		case 2:
			mode = " other  calculator ";
			break;
		default:
			mode = " simple calculator ";
			break;
	}
	
	gotoxy(1, 9);
	
	color_cout("                                                         .\n", 0);
	color_cout("                                             mode: <" + mode + ">\n", (Line == 0)? 3 : 0);
	color_cout("                                                      -about-\n", (Line == 1)? 3 : 0);
	color_cout("                                                       -out-\n", (Line == 2)? 3 : 0);
	color_cout("                                                         .\n", 0);
	
	return 5;
}

int line_mode(int& line, int& mode)
{	
	while (true)
	{
		cbreak();
		int key = keypress();
		
		switch (key)
		{
			case 119://up
				line = (line + max_lines - 1)% max_lines;
				print_menu(line, mode);
				break;
			case 115://down
				line = (line + max_lines + 1)% max_lines;
				print_menu(line, mode);
				break;
			case 97://left
				mode = (mode + max_lines - 1)% max_lines;
				print_menu(line, mode);
				break;
			case 100://right
				mode = (mode + max_lines + 1)% max_lines;
				print_menu(line, mode);
				break;
			case 10://enter
				return(line);
			case 27://esc
				return 2;
			default:
				break;
		}
	}
	normal();
	return 0;
}
//up 119
//down 115
//left 97
//right 100

int print_name()
{
	color_cout("                                                                                                                  \n", 4);
	color_cout("  ::::::::      :::     :::         ::::::::  :::    ::: :::            :::     :::::::::::  ::::::::  :::::::::  \n", 4);
	color_cout(" :+:    :+:   :+: :+:   :+:        :+:    :+: :+:    :+: :+:          :+: :+:       :+:     :+:    :+: :+:    :+: \n", 4);
	color_cout(" +:+         +:+   +:+  +:+        +:+        +:+    +:+ +:+         +:+   +:+      +:+     +:+    +:+ +:+    +:+ \n", 4);
	color_cout(" +#+        +#++:++#++: +#+        +#+        +#+    +:+ +#+        +#++:++#++:     +#+     +#+    +:+ +#++:++#:  \n", 4);
	color_cout(" +#+        +#+     +#+ +#+        +#+        +#+    +#+ +#+        +#+     +#+     +#+     +#+    +#+ +#+    +#+ \n", 4);
	color_cout(" #+#    #+# #+#     #+# #+#        #+#    #+# #+#    #+# #+#        #+#     #+#     #+#     #+#    #+# #+#    #+# \n", 4);
	color_cout("  ########  ###     ### ##########  ########   ########  ########## ###     ###     ###      ########  ###    ### \n\n", 4);
	
	return 8;
}

int welcome_screen()
{
	system("clear");
	int k = print_name();
	gotoxy(1, k + 1);
	print_menu(0);

	return 0;
}

#endif //MENU_HPP
