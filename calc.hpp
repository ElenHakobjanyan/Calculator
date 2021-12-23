#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <stack>

//compares precedences of two operators
int compare(char op_2, char op_1);

//one operand operations
double operation_op_right(char op, double num);

//two operand operations
double operation_left_op_right(char op, double num_left, double num_right);

//choses how many operands do operation needs
void operation(char op_2, std::stack<double>& stk_num);

//calculates while parsing the input string
double calculate(const std::string& str, const double& var);

//prints calculator interface and manual
int print_calc();

//chooses the calculator type based on mode
int open_calc(int mode);

#endif //CALCULATOR_HPP