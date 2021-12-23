#ifndef MENU_HPP
#define MENU_HPP

//prints manual
int print_how_to_use();

//print colorfull text
void color_cout(std::string text, int text_color);

//main menu
int print_menu(int Line, int mode_i);

//changes choosen line and mode in main menu
int line_mode(int& line, int& mode);

//CALCULATOR
int print_name();

//prints name of the app and main menu
int welcome_screen();

//in about section prints the manual
int print_about();

#endif //MENU_HPP
