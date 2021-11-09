#include <iostream>

using namespace::std;

struct tal {
	int siffra[5] = { 0,0,0,0,0,};
	int v�rde = 0;
};

tal byggTal(int v�rde); //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void �kaTal(tal* offer, int position = 0); //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)
bool enAvVarje(tal* koll);


bool StillGoing(int x) { //Kollar om det �r en 99a och slutar isf
	return(not(x == 99)); //Returnar sant om det inte �r 99, annars falskt
}

int* extraheraDelar(int offer) {//Plockar ut delarna ur instruktionen. int[0] blir typen, int[1] blir f�rsta parametertypen och int[2] den andra (sett fr�n h�ger)
	int* delar = new int[4];

	for (int i = 4; i >= 2; i--) { //Extraherar siffrorna, fr�n st�rst till minst
		delar[i - 1] = int(offer / pow(10, i)); //D� det �r ett int blir bara f�rsta siffran kvar
		offer = offer - int(delar[i - 1]) * pow(10, i); //Tar bort den siffran vi just extraherade
	}
	delar[0] = offer;

	return(delar);
}

void t�m() { //T�mmer inputten 
	char tecken = NULL;
	int bortagnaTecken = 0;

	tecken = getchar();

	while (tecken != '\n' and tecken != EOF) {
		bortagnaTecken++;
		tecken = getchar();
	}

	if (bortagnaTecken != 0) //Om den har tagit bort n�got
		cout << endl << bortagnaTecken << " tecken har tagits bort.";
}

int IntcodeComputer(int lista[], int l�ngd, int input, int phase) {
	int i = 0;
	int inputNummer = 1;

	while (StillGoing(lista[i])) {//Kontrollerar f�rst om det ska va slut, genomf�r sedan de faktiska instruktionerna. Adderar fyra d� det �r f�rskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int* instruction = extraheraDelar(lista[i]); //Tar ut instruktionen och dess argument (Instruktionen)
		int* parameterOne = nullptr;//Arg ett
		int* parameterTwo = nullptr; //Arg tv�
		int* parameterThree = nullptr;//Arg tre


		if (i + 1 < l�ngd)
			switch (instruction[1])//L�get f�r parameterOne
			{
			case 1://Immediate mode
				parameterOne = &lista[i + 1];
				break;
			case 0://Position mode
				parameterOne = &lista[lista[i + 1]];
				break;
			default:
				cout << "Felaktig parameterOne l�ge!";
				break;
			}

		if (i + 2 < l�ngd)
			switch (instruction[2])//L�get f�r parameterTwo
			{
			case 1://Immediate mode
				parameterTwo = &lista[i + 2];
				break;
			case 0://Position mode
				parameterTwo = &lista[lista[i + 2]];
				break;
			default:
				cout << "Felaktig parameterTwo l�ge!";
				break;
			}

		if (i + 3 < l�ngd)
			switch (instruction[3])//L�get f�r parameterThree
			{
			case 1://Immediate mode
				parameterThree = &lista[i + 3];
				break;
			case 0://Position mode
				parameterThree = &lista[lista[i + 3]];
				break;
			default:
				cout << "Felaktig parameterThree l�ge!";
				break;
			}

		switch (instruction[0])//Instruktionen
		{
		case 1: //Addition
			*parameterThree = *parameterTwo + *parameterOne;
			i += 4;
			break;

		case 2: //Multiplikation
			*parameterThree = (*parameterTwo) * (*parameterOne);
			i += 4;
			break;

		case 3: //Input
			i += 2;
			if (inputNummer == 1) {
				*parameterOne = phase;
				inputNummer++;
				break;
			}
			else if (inputNummer == 2) {
				*parameterOne = input;
				inputNummer++;
				break;
			}
			else {
				cout << "VARF�R TAR DEN FLER INPUTS!?";
				break;
			}
		case 4: //Output
			return(*parameterOne);
			i += 2;
			break;

		case 5: //Jump if true
			if (*parameterOne)
				i = *parameterTwo;
			else
				i += 3;
			break;
		case 6: //Jump if false
			if (!*parameterOne)
				i = *parameterTwo;
			else
				i += 3;
			break;
		case 7: //Less than
			if (*parameterOne < *parameterTwo)
				*parameterThree = 1;
			else
				*parameterThree = 0;
			i += 4;
			break;
		case 8: //Equals
			if (*parameterOne == *parameterTwo)
				*parameterThree = 1;
			else
				*parameterThree = 0;
			i += 4;
			break;
		default:
			cout << "!!!ERRORR!!! felaktig order";
			break;
		}
	}

}

int main() {
	int* lista = nullptr;
	int* referensLista = nullptr;
	int l�ngd = 0;

	cout << "Hur l�ng �r koden? ";
	cin >> l�ngd;

	lista = new int[l�ngd];
	referensLista = new int[l�ngd];
	
	cout << "\nDina order: ";
	for (int i = 0; i < l�ngd; i++) {
		cin >> lista[i];
		referensLista[i] = lista[i];
	}

	cout << "\nListan: ";
	for (int i = 0; i < l�ngd; i++)
		cout << lista[i] << ", ";

	t�m(); //Sl�nger allt som finns kvar i inputten

	cout << "\nD� optimerar vi d�";

	int b�staV�rdet = 0;
	int output = 0;
	tal phases;
	phases = byggTal(0);

	while (1) {
		�kaTal(&phases);
		while (!enAvVarje(&phases) and phases.v�rde != 44444)//Om den inte uppfyller kravet s� forts�tter man tills en g�r det
			�kaTal(&phases);
		if (phases.v�rde == 44444)
			break;

		cout << "\nProvar med phase: ";
		visaTal(phases);
		for (int i = 0; i < 5; i++) {
			output = IntcodeComputer(lista, l�ngd, output, phases.siffra[i]);
			for (int i = 0; i < l�ngd; i++)
				lista[i] = referensLista[i];
		}
		cout << "\nSlutresultatet blev: " << output;
		if (output > b�staV�rdet)
			b�staV�rdet = output;
		
		output = 0;
	}

	cout << "\nDet b�sta vi kan l�sa �r nog: " << b�staV�rdet;

	cout << "\n\nD� va det klart";

	delete[] lista;
}

tal byggTal(int v�rde) { //Skapar ett "tal", dess v�rde blir v�rde och dess siffror blir siffrorna i v�rde
	tal bygge;
	bygge.v�rde = v�rde;

	for (int i = 4; i >= 0; i--) { //Extraherar siffrorna, fr�n st�rst till minst
		bygge.siffra[i] = v�rde / pow(10, i); //D� det �r ett int blir bara f�rsta siffran kvar
		v�rde = v�rde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.v�rde << " (";
	for (int i = 4; i >= 0; i--)
		cout << offer.siffra[i] << ", ";
	cout << ")";
}

void �kaTal(tal* offer, int position) { //�kar v�rdet p� ett tal vid den position som anges, default �r 0, f�rsta siffran (funkar d� som ++)
	if (offer->v�rde == 44444)
		cout << "Error! Kan inte �ka mer";
	else {
		while (offer->siffra[position] == 4) {//Om siffran �r en nia
			offer->siffra[position] = 0;//S� s�tts den siffran till noll
			position++; //Och n�sta siffra kollas 
		}
		offer->siffra[position]++; //Den f�rsta siffran som inte �r nio �kas ett steg

		offer->v�rde = 0;
		for (int i = 4; i >= 0; i--) { //Extraherar siffrorna, fr�n st�rst till minst
			offer->v�rde += offer->siffra[i] * pow(10, i); //D� det �r ett int blir bara f�rsta siffran kvar
		}
	}
}

bool enAvVarje(tal* koll) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (koll->siffra[i] == koll->siffra[j] and j != i) //Om n�gra av de tv� �r samma s� return sann
				return(false); //OM de inte �r samma, dvs d� j = i
	return(true);
}