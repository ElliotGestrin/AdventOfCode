// Spacer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace::std;

int main()
{
	char skräp = '0';
	int längd = 0;

	long long* lista = new long long [10000];

	for (int i = 0; i < 17585; i++) {
		if (i % 2 == 0) {
			cin >> lista[i / 2];
			längd++;
		}
		else
			cin >> skräp;
	}
	cout << endl << endl << endl;
	for (int i = 0; i < längd; i++)
		cout << lista[i] << " ";

	delete[] lista;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
