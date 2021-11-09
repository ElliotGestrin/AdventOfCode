#include <iostream>
using namespace::std;

const int talL�ngd = 4;

struct tal {
	int siffra[talL�ngd] = {0};
	int v�rde = 0;
};


tal byggTal(int v�rde); //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void �kaTal(tal* offer, int position = 0); //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)
bool enAvVarje(tal* koll);
bool sjunkande(tal* koll);

int main() {
	tal kombo;
	kombo = byggTal(10000000);
	string translator[8] = { "dark matter", "astrolabe", "prime number", "weather machine", "coin", "whirled peas", "fixed point", "antenna" };
	

	while (kombo.v�rde <= 7654) {
		while (!enAvVarje(&kombo) or !sjunkande(&kombo)) {
			�kaTal(&kombo);
		}
		visaTal(kombo);
		cout << endl;

		for (int i = 0; i < talL�ngd; i++)
				cout << "take " << translator[kombo.siffra[i]]<< endl;

		cout << "south" << endl;

		for (int i = 0; i < talL�ngd; i++)
				cout << "drop " << translator[kombo.siffra[i]]<< endl;

		�kaTal(&kombo);

		cout << endl << endl;
	}
}

tal byggTal(int v�rde) { //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
	tal bygge;
	bygge.v�rde = v�rde;

	for (int i = talL�ngd; i >= 0; i--) { //Extraherar siffrorna, fr�n st�rst till minst
		bygge.siffra[i] = v�rde / pow(10, i); //D� det �r ett int blir bara f�rsta siffran kvar
		v�rde = v�rde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.v�rde << " (";
	for (int i = talL�ngd - 1; i >= 0; i--)
		cout << offer.siffra[i] << ", ";
	cout << ")";
}

void �kaTal(tal* offer, int position) { //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)
	if (offer->v�rde == 99999)
		cout << "Error! Kan inte �ka mer";
	else {
		while (offer->siffra[position] == 7) {//Om siffran �r en nia
			offer->siffra[position] = 0;//S� s�tts den siffran till noll
			position++; //Och n�sta siffra kollas 
		}
		offer->siffra[position]++; //Den f�rsta siffran som inte �r nio �kas ett steg

		offer->v�rde = 0;
		for (int i = talL�ngd - 1; i >= 0; i--) { //Extraherar siffrorna, fr�n st�rst till minst
			offer->v�rde += offer->siffra[i] * pow(10, i); //D� det �r ett int blir bara f�rsta siffran kvar
		}
	}
}

bool enAvVarje(tal* koll) {
	for (int i = 0; i < talL�ngd; i++)
		for (int j = 0; j < talL�ngd; j++)
			if (koll->siffra[i] == koll->siffra[j] and j != i) //Om n�gra av de tv� �r samma s� return sann
				return(false); //OM de inte �r samma, dvs d� j = i
	return(true);
}

bool sjunkande(tal* koll) {
	for (int i = talL�ngd - 1; i > 0; i--)
		if (koll->siffra[i] < koll->siffra[i - 1]) { //Om en siffra �r mindre �n den som kommer efter
			return(false);
		}
	return(true);
}