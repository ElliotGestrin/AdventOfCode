#include <iostream>

using namespace::std;


struct extraMinne {
	long long v�rde = 0;
	unsigned long position = 0;
};

int* extraheraDelar(int offer);
void t�m();
extraMinne* hittaMinne(extraMinne minnen[], int l�ngd, unsigned long s�kes);
extraMinne* �ndraMinne(extraMinne* minnen, int* l�ngd, int v�rde, unsigned long position);
void IntcodeComputer(long long* lista, int l�ngd);


int main() {
	long long* lista = nullptr;
	int l�ngd = 0;

	cout << "Hur l�ng �r koden? ";
	cin >> l�ngd;

	lista = new long long[l�ngd];

	cout << "\nDina order: ";
	for (int i = 0; i < l�ngd; i++) {
		cin >> lista[i];
	}

	cout << "\nListan: ";
	for (int i = 0; i < l�ngd; i++)
		cout << lista[i] << ", ";

	t�m(); //Sl�nger allt som finns kvar i inputten

	cout << "\nD� k�r vi d�\n\n";

	IntcodeComputer(lista, l�ngd);

	cout << "\n\nD� va det klart";

	delete[] lista;
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

int* extraheraDelar(int offer) {//Plockar ut delarna ur instruktionen. int[0] blir typen, int[1] blir f�rsta parametertypen och int[2] den andra (sett fr�n h�ger)
	int* delar = new int[4];

	for (int i = 4; i >= 2; i--) { //Extraherar siffrorna, fr�n st�rst till minst
		delar[i - 1] = int(offer / pow(10, i)); //D� det �r ett int blir bara f�rsta siffran kvar
		offer = offer - int(delar[i - 1]) * pow(10, i); //Tar bort den siffran vi just extraherade
	}
	delar[0] = offer;

	return(delar);
}

extraMinne* hittaMinne(extraMinne minnen[], int l�ngd, unsigned long s�kes) {//Skickar tillbaka en referens till det s�kta minnet
	if (l�ngd != 0)
		for (int i = 0; i < l�ngd; i++) { //Eller nullptr om det saknas
			if (minnen[i].position == s�kes)
				return(&minnen[i]);
		}
	return(nullptr);
}

extraMinne* �ndraMinne(extraMinne* minnen, int* l�ngd, int v�rde, unsigned long position) {
	extraMinne* m�l = hittaMinne(minnen, *l�ngd, position);

	if (m�l != nullptr) //Dvs positionen finns redan
		m�l->v�rde = v�rde;
	else {//Annars f�r vi skapa ny plats f�r den
		extraMinne* temp = new extraMinne[*l�ngd + 1];

		for (int i = 0; i < *l�ngd; i++) {//G�r temp till en ett st�rre kopia
			temp[i].position = minnen[i].position;
			temp[i].v�rde = minnen[i].v�rde;
		}
		temp[*l�ngd].position = position;//L�gger till det nya
		temp[*l�ngd].v�rde = v�rde;

		delete[] minnen;

		minnen = temp;

		*l�ngd += 1;//Uppdaterar l�ngden med
	}

	return(minnen);
}

void IntcodeComputer(long long* lista, int l�ngd) {
	int i = 0;
	int relativeBase = 0;
	int antalExtraMinnen = 0;
	extraMinne* minnen = nullptr;

	//cout << "\nInput = " << input;

	while (lista[i] != 99) {//Kontrollerar f�rst om det ska va slut, genomf�r sedan de faktiska instruktionerna. Adderar fyra d� det �r f�rskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int* instruction = extraheraDelar(lista[i]); //Tar ut instruktionen och dess argument (Instruktionen)
		long long* parameterOne = nullptr;//Arg ett
		long long* parameterTwo = nullptr; //Arg tv�
		long long* parameterThree = nullptr;//Arg tre
		bool skaAnv�ndaMinnet[3] = { false };//Ifall n�gon av parametrarna ska anv�nda extraminne

		//cout << "\n[" << i << "][" << relativeBase << "]    "; //Visar massvis vid behov av debugging avancerade system
		//for (int j = 0; j < 4; j++)
		//	cout << lista[i + j] << " ";
		//cout << "   [";
		//for (int j = 0; j < antalExtraMinnen; j++)
		//	cout << minnen[j].position << ":" << minnen[j].v�rde << "  ";
		//cout << "]";

		if (i + 1 < l�ngd)
			switch (instruction[1])//L�get f�r parameterOne
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 1] < l�ngd) //Om den finns
					parameterOne = &lista[relativeBase + lista[i + 1]];
				else//Om den ska va i extraminne
					skaAnv�ndaMinnet[0] = true;
				break;
			case 1://Immediate mode
				parameterOne = &lista[i + 1];
				break;
			case 0://Position mode 
				if (lista[i + 1] < l�ngd)//Den �r en del av standard
					parameterOne = &lista[lista[i + 1]];
				else {//Den �r en del av extraminne
					skaAnv�ndaMinnet[0] = true;
				}
				break;
			default:
				cout << "Felaktig parameterOne l�ge!";
				break;
			}

		if (i + 2 < l�ngd)
			switch (instruction[2])//L�get f�r parameterTwo
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 2] < l�ngd) //Om den finns
					parameterTwo = &lista[relativeBase + lista[i + 2]];
				else //Om den ska va i extraminne
					skaAnv�ndaMinnet[1] = true;
				break;
			case 1://Immediate mode
				parameterTwo = &lista[i + 2];
				break;
			case 0://Position mode
				if (lista[i + 2] < l�ngd)//Den �r en del av standard
					parameterTwo = &lista[lista[i + 2]];
				else
					skaAnv�ndaMinnet[1] = true;
				break;
			default:
				cout << "Felaktig parameterTwo l�ge!";
				break;
			}

		if (i + 3 < l�ngd)
			switch (instruction[3])//L�get f�r parameterThree
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 1] < l�ngd) //Om den finns
					parameterThree = &lista[relativeBase + lista[i + 3]];
				else {//Om den ska va i extraminne
					skaAnv�ndaMinnet[2] = true;
				}
				break;
			case 1://Immediate mode
				parameterThree = &lista[i + 3];
				break;
			case 0://Position mode
				if (lista[i + 3] < l�ngd)//Den �r en del av standard
					parameterThree = &lista[lista[i + 3]];
				else {
					skaAnv�ndaMinnet[2] = true;
				}
				break;
			default:
				break;
			}

		//G�r �ndringar i "minne" efter behov! Beh�ver ske samtidigt ty annars byts minnena n�r n�sta g�r detta
		for (int j = 1; j < 4; j++) //Skapar alla nya minnen
			if (skaAnv�ndaMinnet[j - 1]) {
				unsigned long s�ktPosition = lista[i + j];
				if (instruction[j] == 2) // Om den ska va i relative, �r ju i antingen relative eller position
					s�ktPosition += relativeBase;
				if (hittaMinne(minnen, antalExtraMinnen, s�ktPosition) == nullptr)//Om minnet inte redan fanns
					minnen = �ndraMinne(minnen, &antalExtraMinnen, 0, s�ktPosition);
			}
		for (int j = 1; j < 4; j++) {//V�ljer vilken
			long long** aktivParameter = nullptr;
			switch (j) {
			case 1:
				aktivParameter = &parameterOne;
				break;
			case 2:
				aktivParameter = &parameterTwo;
				break;
			case 3:
				aktivParameter = &parameterThree;
				break;
			}

			if (skaAnv�ndaMinnet[j - 1]) {//Ger dem deras st�llen
				unsigned long s�ktPosition = lista[i + j];
				if (instruction[j] == 2) // Om den ska va i relative, �r ju i antingen relative eller position
					s�ktPosition += relativeBase;
				*aktivParameter = &hittaMinne(minnen, antalExtraMinnen, s�ktPosition)->v�rde;
			}
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
			*parameterOne = getchar();;
			i += 2;
			break;

		case 4: //Output
			i += 2;
			cout << char(*parameterOne);
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
		case 9: //Relative base adjust
			relativeBase += *parameterOne;
			i += 2;
			break;
		default:
			cout << "!!!ERRORR!!! felaktig order";
			break;
		}
	}

	return;
}