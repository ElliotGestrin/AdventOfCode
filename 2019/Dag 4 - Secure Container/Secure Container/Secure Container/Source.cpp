#include <iostream>

using namespace std;

struct tal {
	int siffra[6] = {0,0,0,0,0,0};
	int v�rde = 0;
};

//Basala funktioner
tal byggTal(int v�rde); //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void �kaTal(tal *offer, int position = 0); //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)

//Kravfunktioner
bool v�xande(tal kontroll); //Kollar om varje siffra �r >= den f�reg�ende
bool tv�Lika(tal kontroll); //Kollar om minst tv� siffror bredvid varandra �r lika 
bool tv�LikaMenInteEnTrippel(tal kontroll); //Kollar om minst tv� siffror bredvid varandra �r lika, men inte fler


int main() {
	int undreGr�ns;
	int �vreGr�ns;
	int lyckadeKoder = 0;
	int f�rLitenPosition = 4; //Fyra ty den st�rsta inte kan j�mf�ras upp�t (och st�rsta �r fem dummer)
	int n�staTal = 0;

	tal koden;

	cout << "Vad �r den undre gr�nsen?";
	cin >> undreGr�ns;
	
	cout << "\nVad �r den �vre gr�nsen?";
	cin >> �vreGr�ns;

	koden = byggTal(undreGr�ns);

	while (koden.v�rde <= �vreGr�ns) { //Kollar alla koder till�tna

		if (v�xande(koden) and tv�LikaMenInteEnTrippel(koden))//Om den klarar alla krav (v�xande �r egentligen en formalitet)
			lyckadeKoder++;

		�kaTal(&koden);

		if (!v�xande(koden)) { //Om den inte �r v�xande, dvs den har f�r sm� tal, s� ska vi �ka upp den
			while (koden.siffra[f�rLitenPosition] >= koden.siffra[f�rLitenPosition + 1]) //S� l�nge som det �r okej
				f�rLitenPosition--; //R�kna ner och hitta felet, avsluter n�r den har hittats
			for (int i = 5; i > f�rLitenPosition; i--)
				n�staTal += koden.siffra[i] * pow(10, i); //Alla de siffror som va ok ska beh�llas
			for (int i = f�rLitenPosition; i >= 0; i--)
				n�staTal += koden.siffra[f�rLitenPosition + 1] * pow(10, i); //Alla siffror efter den st�rsta ers�tts med den som va f�r stor
				// allt annat kommer �nd� va f�r sm�, det blir minsta till�ttna

			koden = byggTal(n�staTal); //Vi s�tter koden till n�sta v�rde som faktiskt �r ok
			n�staTal = 0;
			f�rLitenPosition = 4; //Fem ty den st�rsta inte kan j�mf�ras upp�t
		}
	}

	cout << "\nDet finns: " << lyckadeKoder << "st ok koder mellan " << undreGr�ns << " och " << �vreGr�ns;
}

tal byggTal(int v�rde) { //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
	tal bygge;
	bygge.v�rde = v�rde;
	
	for (int i = 5; i >= 0; i--){ //Extraherar siffrorna, fr�n st�rst till minst
		bygge.siffra[i] = v�rde / pow(10,i); //D� det �r ett int blir bara f�rsta siffran kvar
		v�rde = v�rde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.v�rde; //<< " (";
	//for (int i = 5; i >= 0; i--)
	//	cout << offer.siffra[i] << ", ";
	//cout << ")";
}

void �kaTal(tal *offer, int position) { //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)
	if (offer->v�rde == 999999)
		cout << "Error! Kan inte �ka mer";

	offer->v�rde += pow(10, position); //�kar v�rdet korrekt (d� position �r 0 �kar den med 1)

	while(offer->siffra[position] == 9) {//Om siffran �r en nia
		offer->siffra[position] = 0;//S� s�tts den siffran till noll
		position++; //Och n�sta siffra kollas 
	}
	offer->siffra[position]++; //Den f�rsta siffran som inte �r nio �kas ett steg
}

bool v�xande(tal kontroll) { //Kollar om varje siffra �r >= den f�reg�ende
	for (int i = 4; i >= 0; i--)
		if (kontroll.siffra[i] < kontroll.siffra[i + 1])//Om en siffra �r mindre �n den f�reg�ende
			return(false);
	return(true);
}

bool tv�Lika(tal kontroll) { //Kollar om minst tv� siffror bredvid varandra �r lika
	for (int i = 5; i >= 0; i--)
		if (kontroll.siffra[i] == kontroll.siffra[i + 1])//Om en siffra �r likadan som den f�reg�ende
			return(true);
	return(false);
}

bool tv�LikaMenInteEnTrippel(tal kontroll) { //Kollar om minst tv� siffror bredvid varandra �r lika, men inte fler
	for (int i = 4; i >= 0; i--)
		if (kontroll.siffra[i] == kontroll.siffra[i + 1])//Om en siffra �r likadan som den f�reg�ende
		{
			if (i == 0)
			{
				if (kontroll.siffra[i] != kontroll.siffra[i + 2]) //Kolla tv� upp ocks�
				return(true);
			}
			if (i == 4)
			{

				if (kontroll.siffra[i] != kontroll.siffra[i - 1]) //Kolla ett ner ocks�
					return(true);
			}
			if(i != 4 and i != 0)
			{
				if (kontroll.siffra[i] != kontroll.siffra[i - 1] and kontroll.siffra[i] != kontroll.siffra[i + 2]) //Kolla ett steg ner och tv� upp ocks�
					return(true);
			}

		}

	return(false);
}