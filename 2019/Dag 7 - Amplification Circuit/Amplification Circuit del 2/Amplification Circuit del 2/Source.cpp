#include <iostream>

using namespace::std;

struct tal {
	int siffra[5] = { 0,0,0,0,0, };
	int värde = 0;
};

tal byggTal(int värde); //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
void visaTal(tal offer); //Visar ett tal, coutar lite bara
void ökaTal(tal* offer, int position = 0); //Ökar värdet på ett tal vid den position som anges, default är 0, första siffran (funkar då som ++)
bool enAvVarje(tal* koll);

struct state {
	int *lista = nullptr;
	int längd = 0;
	int phase = 0;
	int i = 0;
	int inputNummer = 1;
	int output = 0;
	bool trueEnd = false;
};

int* extraheraDelar(int offer);
void töm();
bool IntcodeComputer(state* nuvarande, int input);

int main() {
	int* referensLista = nullptr;
	int längd = 0;

	cout << "Hur lång är koden? ";
	cin >> längd;

	referensLista = new int[längd];

	cout << "\nDina order: ";
	for (int i = 0; i < längd; i++) {
		cin >> referensLista[i];
	}

	cout << "\nListan: ";
	for (int i = 0; i < längd; i++)
		cout << referensLista[i] << ", ";

	töm(); //Slänger allt som finns kvar i inputten

	cout << "\nDå optimerar vi då";

	int bästaVärdet = 0;
	tal phases;
	phases = byggTal(55555);


	while (1) {
		state AMP[5];
		int aktivAMP = 0;

		for (int j = 0; j < 5; j++)
			AMP[j].lista = new int[längd];

		for (int j = 0; j < 5; j++) //Bygger upp varje individuell lista
			for (int i = 0; i < längd; i++) 
				AMP[j].lista[i] = referensLista[i];


		ökaTal(&phases);
		while (!enAvVarje(&phases) and phases.värde != 99999)//Om den inte uppfyller kravet så fortsätter man tills en gör det
			ökaTal(&phases);
		if (phases.värde == 99999)
			break;

		cout << "\nProvar med phase: ";
		visaTal(phases);
		
		for (int i = 0; i < 5; i++) {
			AMP[i].phase = phases.siffra[i];
			AMP[i].längd = längd;
		}

		IntcodeComputer(&AMP[0], 0);

		while (AMP[aktivAMP].trueEnd != true) {//Så länge den nuvarande inte är slut på riktigt
			aktivAMP++;
			aktivAMP = aktivAMP % 5;
			if (aktivAMP == 0)
				IntcodeComputer(&AMP[aktivAMP], AMP[4].output);
			else
				IntcodeComputer(&AMP[aktivAMP], AMP[aktivAMP - 1].output);

			//cout << endl << aktivAMP << ": "; //Visar upp hela listan för den aktiva ampen
			//for (int i = 0; i < längd; i++) {
			//	cout << AMP[aktivAMP].lista[i] << ", ";
			//}
		}


		cout << "\nSlutresultatet blev: " << AMP[4].output;
		if (AMP[4].output > bästaVärdet)
			bästaVärdet = AMP[4].output;

		for (int j = 0; j < 5; j++)
			delete[] AMP[j].lista;
	}

	cout << "\n\nDet bästa vi kan lösa är nog: " << bästaVärdet;

	cout << "\n\nDå va det klart";

	delete[] referensLista;
}

tal byggTal(int värde){ //Skapar ett "tal", dess värde blir värde och dess siffror blir siffrorna i värde
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
		while (offer->siffra[position] == 9) {//Om siffran är en nia
			offer->siffra[position] = 5;//Så sätts den siffran till noll
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

int* extraheraDelar(int offer) {//Plockar ut delarna ur instruktionen. int[0] blir typen, int[1] blir första parametertypen och int[2] den andra (sett från höger)
	int* delar = new int[4];

	for (int i = 4; i >= 2; i--) { //Extraherar siffrorna, från störst till minst
		delar[i - 1] = int(offer / pow(10, i)); //Då det är ett int blir bara första siffran kvar
		offer = offer - int(delar[i - 1]) * pow(10, i); //Tar bort den siffran vi just extraherade
	}
	delar[0] = offer;

	return(delar);
}

bool IntcodeComputer(state* nuvarande, int input) {

	int längd = nuvarande->längd; //Sparar dens konstanta inställningar
	int* lista = nuvarande->lista;
	int phase = nuvarande->phase;
	int i = nuvarande->i;
	int inputNummer = nuvarande->inputNummer;
	


	while (lista[i] != 99) {//Kontrollerar först om det ska va slut, genomför sedan de faktiska instruktionerna. Adderar fyra då det är förskjutningen mellan de olika "kommandona" (kommandot och tre argument)
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
				break;
			}
			else{
				cout << "VARFÖR TAR DEN FLER INPUTS!?";
				break;
			}
		case 4: //Output
			i += 2;
			nuvarande->i = i;
			nuvarande->trueEnd = false;
			nuvarande->output = *parameterOne;
			nuvarande->inputNummer = inputNummer;

			return(false);
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

	nuvarande->trueEnd = true;
	return(true);
}