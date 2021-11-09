#include <iostream>

using namespace::std;

int main() {
	int* bild = nullptr;
	bool** resultat = nullptr;

	int bredd = 0;
	int h�jd = 0;
	int l�ngd = 0;
	int antalPerLager = 0;
	int antalLager = 0;
	int analys = NULL;
	int nollMaster = 0;

	cout << "Hur bred �r bilden? ";
	cin >> bredd;

	cout << "\nHur h�g �r bilden? ";
	cin >> h�jd;

	resultat = new bool* [h�jd];

	for (int i = 0; i < h�jd; i++)
		resultat[i] = new bool[bredd];

	cout << "\nHur l�ng �r datan? ";
	cin >> l�ngd;

	bild = new int[l�ngd];

	if (l�ngd % (bredd * h�jd) != 0)
		cout << "\nT�nkte du r�tt nu? Datan fyller inte alla lager, lite kommer sl�ngas";

	antalPerLager = bredd * h�jd;
	antalLager = l�ngd / antalPerLager;

	cout << "\nL�nga datan: ";

	for (int i = 0; i < l�ngd; i++)
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

	cout << "H�r kommer bilden: \n\n";

	for (int pixel = 0; pixel < antalPerLager; pixel++) {
		if (pixel % bredd == 0)
			cout << endl;

		if (resultat[pixel / bredd][pixel % bredd])
			cout << "*";
		else
			cout << " ";
	}

	for (int i = 0; i < h�jd; i++)
		delete[] resultat[i];

	delete[] resultat;

	delete[] bild;
}