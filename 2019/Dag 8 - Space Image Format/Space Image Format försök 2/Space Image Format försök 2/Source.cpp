#include <iostream>

using namespace::std;

int main() {
	struct lager {
		int nollor = 0;
		int ettor = 0;
		int tv�or = 0;
	};
	lager* bild = nullptr;


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

	cout << "\nHur l�ng �r datan? ";
	cin >> l�ngd;

	if (l�ngd % (bredd * h�jd) != 0)
		cout << "\nT�nkte du r�tt nu? Datan fyller inte alla lager, lite kommer sl�ngas";
		
	antalPerLager = bredd * h�jd;
	antalLager = l�ngd / antalPerLager;

	bild = new lager[antalLager];
	
	cout << "\nLanga datan d�: ";

	for(int i = 0; i < antalLager; i++)
		for (int j = 0; j < antalPerLager; j++) {
			cin >> analys;

			switch (analys)
			{
			case 2:
				bild[i].tv�or++;
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

	cout << "\n\nDen med fest nollor �r lager " << nollMaster << " och den har " << bild[nollMaster].nollor << "st";
	cout << "\nDen har " << bild[nollMaster].ettor << " ettor och " << bild[nollMaster].tv�or << "tv�or";
	cout << "\nProdukten blir d�rmed: " << bild[nollMaster].ettor * bild[nollMaster].tv�or;

	delete[] bild;
}