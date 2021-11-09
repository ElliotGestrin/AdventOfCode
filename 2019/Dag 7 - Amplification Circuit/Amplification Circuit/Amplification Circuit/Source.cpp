#include <iostream>

using namespace::std;

struct tal {
	int siffra[5] = { 0,0,0,0,0,};
	int värde = 0;
};

tal byggTal(int värde); //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void ökaTal(tal* offer, int position = 0); //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
bool enAvVarje(tal* koll);


bool StillGoing(int x) { //Kollar om det är en 99a och slutar isf
	return(not(x == 99)); //Returnar sant om det inte är 99, annars falskt
}

int* extraheraDelar(int offer) {//Plockar ut delarna ur instruktionen. int[0] blir typen, int[1] blir första parametertypen och int[2] den andra (sett från höger)
	int* delar = new int[4];

	for (int i = 4; i >= 2; i--) { //Extraherar siffrorna, från störst till minst
		delar[i - 1] = int(offer / pow(10, i)); //Då det är ett int blir bara första siffran kvar
		offer = offer - int(delar[i - 1]) * pow(10, i); //Tar bort den siffran vi just extraherade
	}
	delar[0] = offer;

	return(delar);
}

void töm() { //Tömmer inputten 
	char tecken = NULL;
	int bortagnaTecken = 0;

	tecken = getchar();

	while (tecken != '\n' and tecken != EOF) {
		bortagnaTecken++;
		tecken = getchar();
	}

	if (bortagnaTecken != 0) //Om den har tagit bort något
		cout << endl << bortagnaTecken << " tecken har tagits bort.";
}

int IntcodeComputer(int lista[], int längd, int input, int phase) {
	int i = 0;
	int inputNummer = 1;

	while (StillGoing(lista[i])) {//Kontrollerar först om det ska va slut, genomför sedan de faktiska instruktionerna. Adderar fyra då det är förskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int* instruction = extraheraDelar(lista[i]); //Tar ut instruktionen och dess argument (Instruktionen)
		int* parameterOne = nullptr;//Arg ett
		int* parameterTwo = nullptr; //Arg två
		int* parameterThree = nullptr;//Arg tre


		if (i + 1 < längd)
			switch (instruction[1])//Läget för parameterOne
			{
			case 1://Immediate mode
				parameterOne = &lista[i + 1];
				break;
			case 0://Position mode
				parameterOne = &lista[lista[i + 1]];
				break;
			default:
				cout << "Felaktig parameterOne läge!";
				break;
			}

		if (i + 2 < längd)
			switch (instruction[2])//Läget för parameterTwo
			{
			case 1://Immediate mode
				parameterTwo = &lista[i + 2];
				break;
			case 0://Position mode
				parameterTwo = &lista[lista[i + 2]];
				break;
			default:
				cout << "Felaktig parameterTwo läge!";
				break;
			}

		if (i + 3 < längd)
			switch (instruction[3])//Läget för parameterThree
			{
			case 1://Immediate mode
				parameterThree = &lista[i + 3];
				break;
			case 0://Position mode
				parameterThree = &lista[lista[i + 3]];
				break;
			default:
				cout << "Felaktig parameterThree läge!";
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
				cout << "VARFÖR TAR DEN FLER INPUTS!?";
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
	int längd = 0;

	cout << "Hur lång är koden? ";
	cin >> längd;

	lista = new int[längd];
	referensLista = new int[längd];
	
	cout << "\nDina order: ";
	for (int i = 0; i < längd; i++) {
		cin >> lista[i];
		referensLista[i] = lista[i];
	}

	cout << "\nListan: ";
	for (int i = 0; i < längd; i++)
		cout << lista[i] << ", ";

	töm(); //Slänger allt som finns kvar i inputten

	cout << "\nDå optimerar vi då";

	int bästaVärdet = 0;
	int output = 0;
	tal phases;
	phases = byggTal(0);

	while (1) {
		ökaTal(&phases);
		while (!enAvVarje(&phases) and phases.värde != 44444)//Om den inte uppfyller kravet så fortsätter man tills en gör det
			ökaTal(&phases);
		if (phases.värde == 44444)
			break;

		cout << "\nProvar med phase: ";
		visaTal(phases);
		for (int i = 0; i < 5; i++) {
			output = IntcodeComputer(lista, längd, output, phases.siffra[i]);
			for (int i = 0; i < längd; i++)
				lista[i] = referensLista[i];
		}
		cout << "\nSlutresultatet blev: " << output;
		if (output > bästaVärdet)
			bästaVärdet = output;
		
		output = 0;
	}

	cout << "\nDet bästa vi kan lösa är nog: " << bästaVärdet;

	cout << "\n\nDå va det klart";

	delete[] lista;
}

tal byggTal(int värde) { //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
	tal bygge;
	bygge.värde = värde;

	for (int i = 4; i >= 0; i--) { //Extraherar siffrorna, från störst till minst
		bygge.siffra[i] = värde / pow(10, i); //Då det är ett int blir bara första siffran kvar
		värde = värde - bygge.siffra[i] * pow(10, i); //Tar bort den siffran vi just extraherade
	}

	return(bygge);
}

void visaTal(tal offer) { //Visar ett tal, coutar lite bara
	cout << offer.värde << " (";
	for (int i = 4; i >= 0; i--)
		cout << offer.siffra[i] << ", ";
	cout << ")";
}

void ökaTal(tal* offer, int position) { //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
	if (offer->värde == 44444)
		cout << "Error! Kan inte öka mer";
	else {
		while (offer->siffra[position] == 4) {//Om siffran är en nia
			offer->siffra[position] = 0;//Så sätts den siffran till noll
			position++; //Och nästa siffra kollas 
		}
		offer->siffra[position]++; //Den första siffran som inte är nio ökas ett steg

		offer->värde = 0;
		for (int i = 4; i >= 0; i--) { //Extraherar siffrorna, från störst till minst
			offer->värde += offer->siffra[i] * pow(10, i); //Då det är ett int blir bara första siffran kvar
		}
	}
}

bool enAvVarje(tal* koll) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (koll->siffra[i] == koll->siffra[j] and j != i) //Om några av de två är samma så return sann
				return(false); //OM de inte är samma, dvs då j = i
	return(true);
}