#include <iostream>

using namespace::std;

int main() {
	struct lager {
		int nollor = 0;
		int ettor = 0;
		int tvåor = 0;
	};
	lager* bild = nullptr;


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

	cout << "\nHur lång är datan? ";
	cin >> längd;

	if (längd % (bredd * höjd) != 0)
		cout << "\nTänkte du rätt nu? Datan fyller inte alla lager, lite kommer slängas";
		
	antalPerLager = bredd * höjd;
	antalLager = längd / antalPerLager;

	bild = new lager[antalLager];
	
	cout << "\nLanga datan då: ";

	for(int i = 0; i < antalLager; i++)
		for (int j = 0; j < antalPerLager; j++) {
			cin >> analys;

			switch (analys)
			{
			case 2:
				bild[i].tvåor++;
				break;
			case 1:
				bild[i].ettor++;
				break;
			case 0:
				bild[i].nollor++;
				break;
			default:
				cout << "Error! Felaktigt tecken! " << analys;
				break;
			}
		}

	for (int i = 0; i < antalLager; i++)
		if (bild[i].nollor < bild[nollMaster].nollor)
			nollMaster = i;

	cout << "\n\nDen med fest nollor är lager " << nollMaster << " och den har " << bild[nollMaster].nollor << "st";
	cout << "\nDen har " << bild[nollMaster].ettor << " ettor och " << bild[nollMaster].tvåor << "tvåor";
	cout << "\nProdukten blir därmed: " << bild[nollMaster].ettor * bild[nollMaster].tvåor;

	delete[] bild;
}