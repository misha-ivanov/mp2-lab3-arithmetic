// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once

#include <string>
#include <vector>
#include "stack.h"

struct Lexem{
	double numb; // number
	char var = '0'; // variable
	char op = '0'; // operator
	bool IsNumb = false;
	int rank = -1; // priority of any element
};

class Arithmetic {
	std::vector<Lexem> data;
	std::vector<Lexem> postfix;
public:
	void Convert(std::string s); // string -> vector<Lexem>
	void CreatePostfix(); // convert expression to Reverse Polish Notation
	double Calculate(); // count the result using RPN
	int GetLengthFromData(); // percieving of Length on pos position
	Lexem GetLexemFromPostfix(int pos); // percieving of Lexem on pos position
	int GetLengthFromPostfix(); // percieving of Length on pos position
};