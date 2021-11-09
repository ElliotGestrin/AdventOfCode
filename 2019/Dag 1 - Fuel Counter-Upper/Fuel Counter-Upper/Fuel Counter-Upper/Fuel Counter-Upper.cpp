// Fuel Counter-Upper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace::std;

int main()
{
	int model = 1;
	int requiredFuel = 0;
	int counter = 0;
	int fuelCompensate = 0;

	while(1!=0) {
		cin >> model;
		if (model == 0) //Slutar om en modul v�ger noll, h�nder aldrig utom n�r jag ger det
				break;
		
		requiredFuel += (model / 3) - 2; //M�ngd br�nsle som l�ggs till
		fuelCompensate = (model / 3) - 2; //M�ngden br�nsle som ska kompenseras f�r baserat p� modulen (samma som l�ggs till)

		while (1 != 0) { //Kompenserar f�r allt br�nsle
			fuelCompensate = (fuelCompensate / 3) - 2;
			if (fuelCompensate <= 0) //D� beh�ver man inte kompensera mer
				break;
			requiredFuel += fuelCompensate;
		}

		counter += 1; //R�knar antalet moduler
	}
	cout << endl << "Modulerna och deras br�nsle kr�ver: " << requiredFuel << "kg br�nsle. Det var: " << counter << " moduler." << endl;
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
