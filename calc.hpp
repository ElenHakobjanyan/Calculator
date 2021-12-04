#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

//calculate string input statement and returns double
double calculate(std::string str);

//prints calculator design
int print_calc();

//opens wanted calculator mode
int open_calc(std::string& expr, int mode);

#endif //CALCULATOR_HPP