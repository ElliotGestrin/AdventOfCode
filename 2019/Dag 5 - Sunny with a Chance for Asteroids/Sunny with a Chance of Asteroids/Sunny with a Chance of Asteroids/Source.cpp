#include <iostream>

using namespace::std;

bool StillGoing(int x) { //Kollar om det är en 99a och slutar isf
	return(not(x == 99)); //Returnar sant om det inte är 99, annars falskt
}

int * extraheraDelar(int offer) {//Plockar ut delarna ur instruktionen. int[0] blir typen, int[1] blir första parametertypen och int[2] den andra (sett från höger)
	int * delar = new int [4];

	for (int i = 4; i >= 2; i--) { //Extraherar siffrorna, från störst till minst
		delar[i-1] = int(offer / pow(10, i)); //Då det är ett int blir bara första siffran kvar
		offer = offer - int(delar[i-1]) * pow(10, i); //Tar bort den siffran vi just extraherade
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

void IntcodeComputer(int lista[], int längd) {
	int i = 0;
	while (StillGoing(lista[i])) {//Kontrollerar först om det ska va slut, genomför sedan de faktiska instruktionerna. Adderar fyra då det är förskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int * instruction = extraheraDelar(lista[i]); //Tar ut instruktionen och dess argument (Instruktionen)
		int * parameterOne = nullptr;//Arg ett
		int * parameterTwo = nullptr; //Arg två
		int * parameterThree = nullptr;//Arg tre

		cout << "\n[" << i << "][ " << "]    "; //Visar massvis vid behov av debugging avancerade system
		for (int j = 0; j < 4; j++)
			cout << lista[i + j] << " ";
		cout << "   [";
		cout << "]";

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

		if(i+3 < längd)
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
			cout << "\nInput: ";
			cin >> *parameterOne;
			i += 2;
			töm();
			break;

		case 4: //Output
			cout << "\nOutput: ";
			cout << *parameterOne;
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
	int längd = 0;

	cout << "Hur lång är koden? ";
	cin >> längd;

	lista = new int[längd];

	cout << "\nDina order: ";
	for (int i = 0; i < längd; i++)
		cin >> lista[i];

	cout << "\nListan: ";

	for (int i = 0; i < längd; i++)
		cout << lista[i] << ", ";

	töm(); //Slänger allt som finns kvar i inputten

	cout << "\nDå kör vi datorn då";

	IntcodeComputer(lista, längd);

	cout << "\n\nDå va det klart";

	delete[] lista;
}