// реализация пользовательского приложения
#include <iostream>
#include "stack.h"
#include "arithmetic.h"

using namespace std;

int main()
{
	char ans = 0; // responds of user
	int f_var = 0; // check of variable
	int i;
	string S;
	
	cout << "Welcome to the calculator based on reverse polish notation!" << endl;
	while (ans != 'q') {
		cout << "Please, enter your expression: " << endl;
		cin >> S;
		Arithmetic A;
		i = 0;

		while (i != S.size() && f_var != 1){ // check of variable
			if (S[i] >= 'a' && S[i] <= 'z')
				f_var = 1;
			i++;
		}
		
		try {
			A.Convert(S);
			A.CreatePostfix();
			do {
				ans = '0';
				cout << "Answer is " << A.Calculate() << endl;
				if (f_var == 1) {
					cout << "Press" << endl << "'a' to enter another expression" << endl << "'c' to change value of variable(s)" << endl << "'q' to finish the programm" << endl;
					cin >> ans;
				}
				else {
					cout << "Press" << endl << "'a' to enter another expression" << endl << "'q' to finish the programm" << endl;
					cin >> ans;
				}
			} while (ans == 'c' && f_var == 1);
		}
		catch (...) {
			ans = '0';
			while ((ans != 'a') && (ans != 'q')) {
				cout << "Press" << endl << "'a' to alter your expression" << endl << "'q' to finish the programm" << endl;
				cin >> ans;
			}
		}
	}

  return 0;
}
