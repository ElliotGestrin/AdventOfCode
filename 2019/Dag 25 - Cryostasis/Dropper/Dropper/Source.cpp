#include <iostream>
using namespace::std;

const int talLängd = 4;

struct tal {
	int siffra[talLängd] = {0};
	int värde = 0;
};


tal byggTal(int värde); //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void ökaTal(tal* offer, int position = 0); //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
bool enAvVarje(tal* koll);
bool sjunkande(tal* koll);

int main() {
	tal kombo;
	kombo = byggTal(10000000);
	string translator[8] = { "dark matter", "astrolabe", "prime number", "weather machine", "coin", "whirled peas", "fixed point", "antenna" };
	

	while (kombo.värde <= 7654) {
		while (!enAvVarje(&kombo) or !sjunkande(&kombo)) {
			ökaTal(&kombo);
		}
		visaTal(kombo);
		cout << endl;

		for (int i = 0; i < talLängd; i++)
				cout << "take " << translator[kombo.siffra[i]]<< endl;

		cout << "south" << endl;

		for (int i = 0; i < talLängd; i++)
				cout << "drop " << translator[kombo.siffra[i]]<< endl;

		ökaTal(&kombo);

		cout << endl << endl;
	}
}

tal byggTal(int värde) { //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
	tal bygge;
	bygge.värde = värde;

	for (int i = talLängd; i >= 0; i--) { //Extraherar siffrorna, från störst till minst
		bygge.siffra[i] = värde / pow(10, i); //Då det är ett int blir bara första siffran kvar
		värde = värde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.värde << " (";
	for (int i = talLängd - 1; i >= 0; i--)
		cout << offer.siffra[i] << ", ";
	cout << ")";
}

void ökaTal(tal* offer, int position) { //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
	if (offer->värde == 99999)
		cout << "Error! Kan inte öka mer";
	else {
		while (offer->siffra[position] == 7) {//Om siffran är en nia
			offer->siffra[position] = 0;//Så sätts den siffran till noll
			position++; //Och nästa siffra kollas 
		}
		offer->siffra[position]++; //Den första siffran som inte är nio ökas ett steg

		offer->värde = 0;
		for (int i = talLängd - 1; i >= 0; i--) { //Extraherar siffrorna, från störst till minst
			offer->värde += offer->siffra[i] * pow(10, i); //Då det är ett int blir bara första siffran kvar
		}
	}
}

bool enAvVarje(tal* koll) {
	for (int i = 0; i < talLängd; i++)
		for (int j = 0; j < talLängd; j++)
			if (koll->siffra[i] == koll->siffra[j] and j != i) //Om några av de två är samma så return sann
				return(false); //OM de inte är samma, dvs då j = i
	return(true);
}

bool sjunkande(tal* koll) {
	for (int i = talLängd - 1; i > 0; i--)
		if (koll->siffra[i] < koll->siffra[i - 1]) { //Om en siffra är mindre än den som kommer efter
			return(false);
		}
	return(true);
}