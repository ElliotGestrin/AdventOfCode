#include <iostream>

using namespace std;

struct tal {
	int siffra[6] = {0,0,0,0,0,0};
	int värde = 0;
};

//Basala funktioner
tal byggTal(int värde); //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void ökaTal(tal *offer, int position = 0); //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)

//Kravfunktioner
bool växande(tal kontroll); //Kollar om varje siffra är >= den föregående
bool tvåLika(tal kontroll); //Kollar om minst två siffror bredvid varandra är lika 
bool tvåLikaMenInteEnTrippel(tal kontroll); //Kollar om minst två siffror bredvid varandra är lika, men inte fler


int main() {
	int undreGräns;
	int övreGräns;
	int lyckadeKoder = 0;
	int förLitenPosition = 4; //Fyra ty den största inte kan jämföras uppåt (och största är fem dummer)
	int nästaTal = 0;

	tal koden;

	cout << "Vad är den undre gränsen?";
	cin >> undreGräns;
	
	cout << "\nVad är den övre gränsen?";
	cin >> övreGräns;

	koden = byggTal(undreGräns);

	while (koden.värde <= övreGräns) { //Kollar alla koder tillåtna

		if (växande(koden) and tvåLikaMenInteEnTrippel(koden))//Om den klarar alla krav (växande är egentligen en formalitet)
			lyckadeKoder++;

		ökaTal(&koden);

		if (!växande(koden)) { //Om den inte är växande, dvs den har för små tal, så ska vi öka upp den
			while (koden.siffra[förLitenPosition] >= koden.siffra[förLitenPosition + 1]) //Så länge som det är okej
				förLitenPosition--; //Räkna ner och hitta felet, avsluter när den har hittats
			for (int i = 5; i > förLitenPosition; i--)
				nästaTal += koden.siffra[i] * pow(10, i); //Alla de siffror som va ok ska behållas
			for (int i = förLitenPosition; i >= 0; i--)
				nästaTal += koden.siffra[förLitenPosition + 1] * pow(10, i); //Alla siffror efter den största ersätts med den som va för stor
				// allt annat kommer ändå va för små, det blir minsta tillåttna

			koden = byggTal(nästaTal); //Vi sätter koden till nästa värde som faktiskt är ok
			nästaTal = 0;
			förLitenPosition = 4; //Fem ty den största inte kan jämföras uppåt
		}
	}

	cout << "\nDet finns: " << lyckadeKoder << "st ok koder mellan " << undreGräns << " och " << övreGräns;
}

tal byggTal(int värde) { //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
	tal bygge;
	bygge.värde = värde;
	
	for (int i = 5; i >= 0; i--){ //Extraherar siffrorna, från störst till minst
		bygge.siffra[i] = värde / pow(10,i); //Då det är ett int blir bara första siffran kvar
		värde = värde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.värde; //<< " (";
	//for (int i = 5; i >= 0; i--)
	//	cout << offer.siffra[i] << ", ";
	//cout << ")";
}

void ökaTal(tal *offer, int position) { //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
	if (offer->värde == 999999)
		cout << "Error! Kan inte öka mer";

	offer->värde += pow(10, position); //Ökar värdet korrekt (då position är 0 ökar den med 1)

	while(offer->siffra[position] == 9) {//Om siffran är en nia
		offer->siffra[position] = 0;//Så sätts den siffran till noll
		position++; //Och nästa siffra kollas 
	}
	offer->siffra[position]++; //Den första siffran som inte är nio ökas ett steg
}

bool växande(tal kontroll) { //Kollar om varje siffra är >= den föregående
	for (int i = 4; i >= 0; i--)
		if (kontroll.siffra[i] < kontroll.siffra[i + 1])//Om en siffra är mindre än den föregående
			return(false);
	return(true);
}

bool tvåLika(tal kontroll) { //Kollar om minst två siffror bredvid varandra är lika
	for (int i = 5; i >= 0; i--)
		if (kontroll.siffra[i] == kontroll.siffra[i + 1])//Om en siffra är likadan som den föregående
			return(true);
	return(false);
}

bool tvåLikaMenInteEnTrippel(tal kontroll) { //Kollar om minst två siffror bredvid varandra är lika, men inte fler
	for (int i = 4; i >= 0; i--)
		if (kontroll.siffra[i] == kontroll.siffra[i + 1])//Om en siffra är likadan som den föregående
		{
			if (i == 0)
			{
				if (kontroll.siffra[i] != kontroll.siffra[i + 2]) //Kolla två upp också
				return(true);
			}
			if (i == 4)
			{

				if (kontroll.siffra[i] != kontroll.siffra[i - 1]) //Kolla ett ner också
					return(true);
			}
			if(i != 4 and i != 0)
			{
				if (kontroll.siffra[i] != kontroll.siffra[i - 1] and kontroll.siffra[i] != kontroll.siffra[i + 2]) //Kolla ett steg ner och två upp också
					return(true);
			}

		}

	return(false);
}