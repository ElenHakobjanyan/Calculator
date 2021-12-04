#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>

#include <tuple>

#include "input.hpp"
#include "menu.hpp"

constexpr double PI = 3.14159265359;
constexpr double  e = 2.71828182846;

bool rad = false;
const int SIZE = 15;

std::tuple <std::string, char, int> precedence[SIZE] = {
    {   ".", '.', 5},
    {   "!", '!', 5},
    {"sqrt", 'q', 4},
    { "sin", 's', 4},
    { "cos", 'c', 4},
    {  "tg", 't', 4},
    {  "ln", 'l', 4},
    {  "lg", 'L', 4},
    {   "%", '%', 4},
    { "abs", 'a', 4},
    {   "^", '^', 3},
    {   "*", '*', 2},
    {   "/", '/', 2},
    {   "+", '+', 1},
    {   "-", '-', 1}
};

int compare(char op_2, char op_1) 
{
	int temp = 0;

	for (int i = 0; i < SIZE; ++i)
	{
		if (op_2 == std::get<1>(precedence[i]))
		{
			temp += std::get<2>(precedence[i]);
		}
		if (op_1 == std::get<1>(precedence[i]))
		{
			temp -= std::get<2>(precedence[i]);
		}
	}
	return temp;
}

int print(std::string s)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		std::cout << s[i];
	}
	std::cout << std::endl;

	return 0;
}

template <typename T>
int print(std::stack<T> s)
{
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << std::endl;

	return 0;
}

double operation_op_right(char op, double num)
{
	switch (op)
	{
	case '!':
		for (double i = num - 1; i >= 2; --i)
		{
			num *= i;
		}
		return num;
	case 'q'://sqrt
		return sqrt(num);
	case 's'://sin
		return sin((rad) ? num : num * PI / 180);
	case 'c'://cos
		return cos((rad) ? num : num * PI / 180);
	case 't'://tg

		if (cos((rad) ? num : num * PI / 180) - cos(PI / 2) >= 0.0000000001)
			return sin((rad) ? num : num * PI / 180) / cos((rad) ? num : num * PI / 180);
		std::cout << "**error** dividing by zer0 in tg(x) action\n";
		return INFINITY;
	case 'l'://ln
		return log(num);
	case 'L'://lg
		return log10(num);
	case '%':
		//----------------------------------------------------------------------------------------------------
		break;
	case 'a'://abs
		return abs(num);
	default:
		break;
	}

	return 1;
}

double operation_left_op_right(char op, double num_left, double num_right)
{
	switch (op)
	{
	case '.':
		while (num_right >= 1)
		{
			num_right /= 10;
		}
		return num_left + num_right;
	case '^':
		return pow(num_left, num_right);
	case '*':
		return num_left * num_right;
	case '/':
		if (num_right)
		{
			return num_left / num_right;
		}
		std::cout << "**error** dividing by zer0 in a/b action\n";
		break;
	case '+':
		return num_left + num_right;
	case '-':
		return num_left - num_right;
	default:
		break;
	}

	return 1;
}

void operation(char op_2, std::stack<double>& stk_num)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (op_2 == std::get<1>(precedence[i]))
		{
			if (i >= 1 && i <= 9)//one operand operation
			{
				double num = stk_num.top();
				stk_num.pop();

				stk_num.push(operation_op_right(op_2, num));
			}
			else//two operand operation
			{
				double num_right = stk_num.top();
				stk_num.pop();
				double num_left = stk_num.top();
				stk_num.pop();

				stk_num.push(operation_left_op_right(op_2, num_left, num_right));
			}
			break;
		}
	}
}

double calculate(std::string str)
{
	std::stack<double> stk_num;
	std::stack<char> stk_op;
	
	if (str == "") return 0;
	
	unsigned int i = 0;
	while (i < str.size())//While there are still tokens to be read in,
	{
		switch (str[i])//If the next token is :
		{
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			{
				int temp = 0;
				while (str[i] - '0' >= 0 && str[i] - '0' <= 9)
				{
					temp = temp * 10 + (str[i++] - '0');
				}
				stk_num.push(temp);//A number: push it onto the value stack.
				--i;
				break;
			}
			case 'p'://Number pi
				stk_num.push(PI);
				++i;
				break;
			case 'e'://Number e
				stk_num.push(e);
				break;
			case 'x'://A variable. Gets it's value and push onto the value stack.
				break;
			case '('://A left parenthesis: push it onto the operator stack.
				stk_op.push(str[i]);
				break;
			case ')'://A right parenthesis:
				while (stk_op.top() != '(')//While the thing on top of the operator stack is not a left parenthesis,
				{
					operation(stk_op.top(), stk_num);//Apply the operator to the operands. Push the result onto the value stack.
					stk_op.pop();
				}
				stk_op.pop();//Pop the left parenthesis from the operator stack, and discard it.
				break;
			case 's'://sqrt -- q sin -- s
				switch (str[i+1])
				{
					case 'q':
						stk_op.push('q');
						i += 3;
						break;
					case 'i':
						stk_op.push(str[i]);
						i += 2;
						break;
				}
				break;
			case 'c': case 'a'://cos -- c abs -- a
				stk_op.push(str[i]);
				i += 2;
				break;
			case 't': case 'l'://tg -- t ln -- l lg -- L
				stk_op.push((str[i] == 'l' && str[i + 1] == 'g') ? 'L' : str[i]);
				++i;
				break;
			default://An operator (call it thisOp):
				//While the operator stack is not empty, and the top thing on the operator stack has the same or greater precedence as thisOp,
				while (!stk_op.empty() && stk_op.top() != '(' && compare(str[i], stk_op.top()) <= 0)
				{
					//Apply the operator to the operands, in the correct order. Push the result onto the value stack.
					operation(stk_op.top(), stk_num);
					stk_op.pop();
				}
				stk_op.push(str[i]);//Push thisOp onto the operator stack.
				break;
		}
		++i;
	}

	while (!stk_op.empty())//While the operator stack is not empty,
	{
		//Apply the operator to the operands, in the correct order. Push the result onto the value stack.
		operation(stk_op.top(), stk_num);
		stk_op.pop();
	}

	//At this point the operator stack should be empty, and the value stack should have only one value in it, which is the final result.
	
	return stk_num.top();
}

int print_calc()
{
	system("clear");
	gotoxy(1, 1);
	
	std::cout << "       ╔══════════════════════════════════════════════════════════════════════════════════════════════════╗       \n";
	std::cout << "       ║ INPUT  [                                                                                         ║       \n";
	std::cout << "       ║                                                                                                 ]║       \n";
	std::cout << "       ║ ANSWER [                                                                                         ║       \n";
	std::cout << "       ║                                                                                                 ]║       \n";
	std::cout << "       ╚══════════════════════════════════════════════════════════════════════════════════════════════════╝       \n\n";
	
	print_how_to_use();
	
	/*
	std::cout << "                     ╠═════════╦═════════════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╣                    \n";
	std::cout << "                     ║ ▓   ▓▓▓ ║  ▓▓ ▓▓▓ ▓▓▓ ║  ▓▓▓  ║  ▓▓▓  ║  ▓▓▓  ║     ▓ ║  ▓▓▓▓ ║  ▓▓▓  ║                    \n";
	std::cout << "                     ║ ▓   ▓ ▓ ║ ▓    ▓  ▓ ▓ ║    ▓  ║  ▓ ▓  ║  ▓ ▓  ║    ▓  ║ ▓   ▓ ║ ▓     ║                    \n";
	std::cout << "                     ║ ▓   ▓ ▓ ║  ▓   ▓  ▓ ▓ ║    ▓  ║  ▓▓▓  ║  ▓▓▓  ║   ▓   ║▓    ▓ ║ ▓     ║                    \n";
	std::cout << "                     ║ ▓   ▓ ▓ ║   ▓  ▓  ▓ ▓ ║    ▓  ║  ▓ ▓  ║    ▓  ║  ▓    ║ ▓   ▓ ║ ▓     ║                    \n";
	std::cout << "                     ║ ▓▓▓ ▓ ▓ ║ ▓▓  ▓▓▓ ▓ ▓ ║    ▓  ║  ▓▓▓  ║  ▓▓▓  ║ ▓     ║  ▓▓▓▓ ║  ▓▓▓  ║                    \n";
	std::cout << "                     ╠═════════╬═════════════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣                    \n";
	std::cout << "                     ║ ▓    ▓▓ ║  ▓▓  ▓   ▓▓ ║  ▓ ▓  ║  ▓▓▓  ║  ▓▓▓  ║ ▓ ▓ ▓ ║   ▓   ║   ▓   ║                    \n";
	std::cout << "                     ║ ▓   ▓   ║ ▓   ▓ ▓ ▓   ║  ▓ ▓  ║  ▓    ║  ▓    ║  ▓▓▓  ║  ▓    ║    ▓  ║                    \n";
	std::cout << "                     ║ ▓   ▓ ▓ ║ ▓   ▓ ▓  ▓  ║  ▓▓▓  ║  ▓▓▓  ║  ▓▓▓  ║   ▓   ║  ▓    ║    ▓  ║                    \n";
	std::cout << "                     ║ ▓   ▓ ▓ ║ ▓   ▓ ▓   ▓ ║    ▓  ║    ▓  ║  ▓ ▓  ║  ▓▓▓  ║  ▓    ║    ▓  ║                    \n";
	std::cout << "                     ║ ▓▓▓  ▓▓ ║  ▓▓  ▓  ▓▓  ║    ▓  ║  ▓▓▓  ║  ▓▓▓  ║ ▓ ▓ ▓ ║   ▓   ║   ▓   ║                    \n";
	std::cout << "                     ╠═════════╬═════════════╬═══════╬═══════╬═══════╬═══════╬═══════╬═══════╣                    \n";
	std::cout << "                     ║    ▓    ║ ▓▓▓  ▓  ▓▓▓ ║   ▓   ║  ▓▓▓  ║  ▓▓▓  ║   ▓   ║   ▓   ║      ▓║                    \n";
	std::cout << "                     ║    ▓    ║  ▓  ▓ ▓ ▓ ▓ ║  ▓▓   ║    ▓  ║    ▓  ║   ▓   ║  ▓ ▓  ║     ▓ ║                    \n";
	std::cout << "                     ║    ▓    ║  ▓  ▓▓▓ ▓ ▓ ║   ▓   ║  ▓▓▓  ║   ▓▓  ║ ▓▓▓▓▓ ║       ║▓▓  ▓  ║                    \n";
	std::cout << "                     ║         ║  ▓  ▓ ▓ ▓ ▓ ║   ▓   ║  ▓    ║    ▓  ║   ▓   ║       ║ ▓ ▓   ║                    \n";
	std::cout << "                     ║    ▓    ║  ▓  ▓ ▓ ▓ ▓ ║  ▓▓▓  ║  ▓▓▓  ║  ▓▓▓  ║   ▓   ║       ║  ▓    ║                    \n";
	std::cout << "                     ╠═════════╬═════════════╬═══════╬═══════╬═══════╬═══════╬═══════╩═══════╣                    \n";
	std::cout << "                     ║  ▓   ▓  ║  ▓  ▓▓   ▓▓ ║  ▓▓▓  ║       ║     ▓ ║       ║               ║                    \n";
	std::cout << "                     ║  ▓▓ ▓▓  ║ ▓ ▓ ▓ ▓ ▓   ║  ▓ ▓  ║       ║ ▓  ▓  ║       ║  ▓▓▓▓▓▓▓▓▓▓▓  ║                    \n";
	std::cout << "                     ║  ▓ ▓ ▓  ║ ▓▓▓ ▓▓   ▓  ║  ▓ ▓  ║       ║   ▓   ║ ▓▓▓▓▓ ║               ║                    \n";
	std::cout << "                     ║  ▓   ▓  ║ ▓ ▓ ▓ ▓   ▓ ║  ▓ ▓  ║       ║  ▓  ▓ ║       ║  ▓▓▓▓▓▓▓▓▓▓▓  ║                    \n";
	std::cout << "                     ║  ▓   ▓  ║ ▓ ▓ ▓▓  ▓▓  ║  ▓▓▓  ║   ▓   ║ ▓     ║       ║               ║                    \n";
	std::cout << "                     ╚═════════╩═════════════╩═══════╩═══════╩═══════╩═══════╩═══════════════╝                    \n";
	*/
	
	return 0;
}

int open_calc(std::string& expr, int mode = 0)
{
	while (true)
	{
		system("clear");
		
		switch (mode)
		{
			case 1:
				//break;
			case 2:
				//break;
			default:
				print_calc();
				gotoxy(18, 2);
				getline(std::cin, expr);
				gotoxy(18, 4);
				std::cout  << calculate(expr) << std::endl;
				break;
		}

		cbreak();
		int k = -1;
		while (k == -1)
		{
			k = keypress();
		}
		normal();
		if (k == 27) return 0;
	}
	
}
