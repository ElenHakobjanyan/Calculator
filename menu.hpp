#ifndef MENU_HPP
#define MENU_HPP

//prints manual
int print_how_to_use();

//print colorfull text
void color_cout(std::string text, int text_color);

//changes choosen line and mode in main menu
int line_mode(int& line, int& mode);

//prints name of the app and main menu
int welcome_screen();

//prints the about section
int print_about();

#endif //MENU_HPP
