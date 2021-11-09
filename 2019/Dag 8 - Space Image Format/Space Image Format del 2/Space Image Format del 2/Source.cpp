#include <iostream>

using namespace::std;

int main() {
	int* bild = nullptr;
	bool** resultat = nullptr;

	int bredd = 0;
	int höjd = 0;
	int längd = 0;
	int antalPerLager = 0;
	int antalLager = 0;
	int analys = NULL;
	int nollMaster = 0;

	cout << "Hur bred är bilden? ";
	cin >> bredd;

	cout << "\nHur hög är bilden? ";
	cin >> höjd;

	resultat = new bool* [höjd];

	for (int i = 0; i < höjd; i++)
		resultat[i] = new bool[bredd];

	cout << "\nHur lång är datan? ";
	cin >> längd;

	bild = new int[längd];

	if (längd % (bredd * höjd) != 0)
		cout << "\nTänkte du rätt nu? Datan fyller inte alla lager, lite kommer slängas";

	antalPerLager = bredd * höjd;
	antalLager = längd / antalPerLager;

	cout << "\nLänga datan: ";

	for (int i = 0; i < längd; i++)
		cin >> bild[i];

	for (int pixel = 0; pixel < antalPerLager; pixel++) {
		for (int lager = 0; lager < antalLager; lager++) {

			if (bild[pixel + antalPerLager * lager] == 1) {
				resultat[pixel / bredd][pixel % bredd] = false;
				break;
			}
			else if (bild[pixel + antalPerLager * lager] == 0) {
				resultat[pixel / bredd][pixel % bredd] = true;
				break;
			}
		}
	}

	cout << "Här kommer bilden: \n\n";

	for (int pixel = 0; pixel < antalPerLager; pixel++) {
		if (pixel % bredd == 0)
			cout << endl;

		if (resultat[pixel / bredd][pixel % bredd])
			cout << "*";
		else
			cout << " ";
	}

	for (int i = 0; i < höjd; i++)
		delete[] resultat[i];

	delete[] resultat;

	delete[] bild;
}