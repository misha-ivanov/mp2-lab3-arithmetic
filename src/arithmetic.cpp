// реализация функций и классов для вычис1ления арифметических выражений

#include <iostream>
#include <cmath>
#include "arithmetic.h"

void Arithmetic::Convert(std::string s) // string -> vector<Lexem>
{
	int i = 0; // counter of string
	Stack<char> Brackets; // will be used in check of brackets
	Lexem* L;
	while (s[i] != '\0')
	{
		// switch version
		L = new Lexem;
		switch (s[i]) {
		case '+':
			if (i == 0) {
				std::cout << "Sign '+' can't be on the first place!" << std::endl;
				throw "sign_first_error";
			}
			if (s[i + 1] == '\0') {
				std::cout << "Sign '+' can't be on the last place!" << std::endl;
				throw "sign_last_error";
			}
			if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')' || s[i + 1] == '.') {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			L->op = '+';
			L->rank = 2;
			break;

		case '-':
			if (s[i + 1] == '\0') {
				std::cout << "Sign '-' can't be on the last place!" << std::endl;
				throw "sign_last_error";
			}
			if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')' || s[i + 1] == '.') {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			if ((s[i + 1] >= '0' && s[i + 1] <= '9') && (i == 0 || s[i - 1] == '(')) { // check of negative numbers
				L->IsNumb = true;
				i++;
				L->numb = (-1) * double(s[i] - '0');
				int f = 0; // trigger of first '.' and actual number of numbers after '.'
				while ((s[i + 1] != '\0') && ((s[i + 1] >= '0' && s[i + 1] <= '9') || (s[i + 1] == '.' && s[i + 2] != '\0'))) {
					i++;
					if (s[i] >= '0' && s[i] <= '9') {
						if (f == 0)
							L->numb = L->numb * 10 + int(s[i] - '0');
						else {
							f++;
							L->numb = L->numb + int(s[i] - '0') * pow(0.1, f);
						}
					}
					else {
						if (f != 0) {
							std::cout << "Expression is wrong! Number of points more than 1. Look at the symbol #" << i << std::endl;
							throw "more_one_point";
						}
						else {
							if (s[i + 1] == '\0') {
								std::cout << "Point can't be on the last place!" << std::endl;
								throw "point_is_last_point";
							}
							f++;
							i++;
							L->numb = L->numb + 0.1 * int(s[i] - '0');
						}
					}
				}
			}
			else { // if real 'minus'
				L->op = '-';
				L->rank = 2;
			}
			break;

		case '*':
			if (i == 0) {
				std::cout << "Sign '*' can't be on the first place!" << std::endl;
				throw "sign_first_error";
			}
			if (s[i + 1] == '\0') {
				std::cout << "Sign '*' can't be on the last place!" << std::endl;
				throw "sign_last_error";
			}
			if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')' || s[i + 1] == '.') {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			L->op = '*';
			L->rank = 3;
			break;

		case '/':
			if (i == 0) {
				std::cout << "Sign '/' can't be on the first place!" << std::endl;
				throw "sign_first_error";
			}
			if (s[i + 1] == '\0') {
				std::cout << "Sign '/' can't be on the last place!" << std::endl;
				throw "sign_last_error";
			}
			if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')' || s[i + 1] == '.') {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			L->op = '/';
			L->rank = 3;
			break;

		case '(':
			if (s[i + 1] == '\0') {
				std::cout << "Sign '(' can't be on the last place!" << std::endl;
				throw "open_bracket_last_error";
			}
			if (s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == ')' || s[i + 1] == '.') {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			Brackets.push('(');
			L->op = '(';
			L->rank = 0;
			break;

		case ')':
			if (s[i + 1] != '\0' && (s[i + 1] == '(' || s[i + 1] == '.' || (s[i + 1] >= '0' && s[i + 1] <= '9'))) {
				std::cout << "Sign was entered wrong. Look at the symbol #" << i << std::endl;
				throw "signs_near_error";
			}
			if (Brackets.IsEmpty()) {
				std::cout << "Brackets were entered wrong. Look at the symbol #" << i << std::endl;
				throw "close_bracket_stack_error";
			}
			else
				Brackets.pop();
			L->op = ')';
			L->rank = 1;
			break;

		default:
			if (s[i] >= 'a' && s[i] <= 'z') // variable
				L->var = s[i];
			else {
				L->IsNumb = true;
				if (s[i] >= '0' && s[i] <= '9') { // non negative number
					L->numb = double(s[i] - '0');
					int f = 0; // trigger of first '.' and actual number of numbers after '.'
					while ((s[i + 1] != '\0') && ((s[i + 1] >= '0' && s[i + 1] <= '9') || (s[i + 1] == '.' && s[i + 2] != '\0' && s[i+2] >= '0' && s[i+2] <= '9'))) {
						i++;
						if (s[i] >= '0' && s[i] <= '9') {
							if (f == 0)
								L->numb = L->numb * 10 + int(s[i] - '0');
							else {
								f++;
								L->numb = L->numb + int(s[i] - '0') * pow(0.1, f);
							}
						}
						else {
							if (f != 0) {
								std::cout << "Expression is wrong! Number of points more than 1. Look at the symbol #" << i << std::endl;
								throw "more_one_point";
							}
							else {
								if (s[i + 1] == '\0') {
									std::cout << "Point can't be on the last place!" << std::endl;
									throw "point_is_last_point";
								}
								f++;
								i++;
								L->numb = L->numb + 0.1 * int(s[i] - '0');
							}
						}
					}
				}
				else {
					std::cout << "Unacceptable symbol was entered! Look at the symbol #" << i << std::endl;
					throw "unacceptable_symbol";
				}
			}
			break;
		}
		data.push_back(*L);
		i++;
	}

	if (!Brackets.IsEmpty()) { // open brackets check
		std::cout << "Brackets were entered wrong. Open brackets more than close ones" << std::endl;
		throw "open_brackets_error";
	}
}


void Arithmetic::CreatePostfix() // convert expression to Reverse Polish Notation
{
	Stack<Lexem> tmp;
	for (int i = 0; i < data.size(); i++) {
		switch (data[i].op) {
		case '(':
			tmp.push(data[i]);
			break;

		case ')':
			while (tmp.Top().op != '(') {
				postfix.push_back(tmp.Top());
				tmp.pop();
			}
			tmp.pop();
			break;

		default:
			if (data[i].op != '0') {
				while (!tmp.IsEmpty() && tmp.Top().rank >= data[i].rank) {
					postfix.push_back(tmp.Top());
					tmp.pop();
				}
				tmp.push(data[i]);
			}
			else
				postfix.push_back(data[i]);
			break;
		}
	}
	while (!tmp.IsEmpty()) {
		postfix.push_back(tmp.Top());
		tmp.pop();
	}
}

double Arithmetic::Calculate() // count the result using RPN
{
	double t;
	Stack<double> tmp;
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i].IsNumb == true)
			tmp.push(postfix[i].numb);
		else {
			if (postfix[i].var != '0') {
				std::cout << "Enter the value of " << postfix[i].var << ":" << std::endl;
				std::cin >> t;
				tmp.push(t);
			}
			else {
				switch (postfix[i].op) {
				case '+':
					t = tmp.Top();
					tmp.pop();
					t = tmp.Top() + t;
					tmp.pop();
					tmp.push(t);
					break;

				case '-':
					t = tmp.Top();
					tmp.pop();
					t = tmp.Top() - t;
					tmp.pop();
					tmp.push(t);
					break;

				case '*':
					t = tmp.Top();
					tmp.pop();
					t = tmp.Top() * t;
					tmp.pop();
					tmp.push(t);
					break;

				case '/':
					t = tmp.Top();
					if (t == 0) {
						std::cout << "Devision by 0 is unacceptable!" << std::endl;
						throw "devision_by_zero";
					}
					tmp.pop();
					t = tmp.Top() / t;
					tmp.pop();
					tmp.push(t);
					break;

				default:
					break;
				}
			}
		}
	}

	return tmp.Top();
}

int Arithmetic::GetLengthFromData() {
	return data.size();
}

Lexem Arithmetic::GetLexemFromPostfix(int pos){
	return postfix[pos];
}

int Arithmetic::GetLengthFromPostfix() {
	return postfix.size();
}