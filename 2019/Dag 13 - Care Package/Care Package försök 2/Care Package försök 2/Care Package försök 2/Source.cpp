#include <iostream>

using namespace::std;

struct intGrid {
	int** grid = nullptr;
	int centerX = 0;
	int centerY = 0;
	int maxX = 0;
	int maxY = 0;
};

int* gridValue(intGrid* grid, int targetX, int targetY);
void increaseGrid(intGrid* grid, int trueX, int trueY);
void changeGrid(intGrid* grid, int targetX, int targetY, int value);
void displayGrid(intGrid* grid, void* painter = nullptr);
int howManyGrid(intGrid* grid, int target);

struct extraMinne {
	long long v�rde = 0;
	unsigned long position = 0;
};

struct state {
	long long* lista = nullptr;
	double l�ngd = NAN;
	int i = 0;
	int relativeBase = 0;
	int antalExtraMinnen = 0;
	extraMinne* minnen = nullptr;
	double output1 = NAN;
	double output2 = NAN;
	double output3 = NAN;
	bool trueEnd = false;
};

int* extraheraDelar(int offer);
void t�m();
extraMinne* hittaMinne(extraMinne minnen[], int l�ngd, unsigned long s�kes);
extraMinne* �ndraMinne(extraMinne* minnen, int* l�ngd, int v�rde, unsigned long position);
void IntcodeComputer(state*, int input);


void mainy() {
	intGrid grid;

	int xPosition = 0;
	int yPosition = 0;
	int tileId = 0;

	int antalBlock = 0;

	for (int i = 0; i < 3; i++) {
		cout << "\nX-position: ";
		cin >> xPosition;

		cout << "\nY-position: ";
		cin >> yPosition;

		cout << "\nTile-ID: ";
		cin >> tileId;

		changeGrid(&grid, xPosition, yPosition, tileId);

		cout << endl;
		displayGrid(&grid);
	}

	antalBlock = howManyGrid(&grid, 2);

	cout << "\nTotalt �r det " << antalBlock << " block";
}

int main() {
	long long* referensLista = nullptr;
	int l�ngd = 0;
	state computer;

	intGrid grid;

	int antalBlock = 0;

	cout << "Hur l�ng �r koden? ";
	cin >> l�ngd;

	referensLista = new long long[l�ngd];

	cout << "\nDina order: ";
	for (int i = 0; i < l�ngd; i++) {
		cin >> referensLista[i];
	}

	computer.lista = referensLista;
	computer.l�ngd = l�ngd;

	cout << "\nListan: ";
	for (int i = 0; i < computer.l�ngd; i++)
		cout << computer.lista[i] << ", ";

	t�m(); //Sl�nger allt som finns kvar i inputten
	
	cout << "\nD� k�r vi d�";
	
	while (computer.trueEnd != true) {
		IntcodeComputer(&computer, NAN);
		//cout << "\nState: listan = " << computer.lista << ", i = " << computer.i << ", RB = " << computer.relativeBase << ", aEM = " << computer.antalExtraMinnen
		//	<< ", minnen = " << computer.minnen << ", TE = " << computer.trueEnd;
		if (computer.trueEnd != true) {
			changeGrid(&grid, computer.output1, computer.output2, computer.output3);


			displayGrid(&grid);
			computer.output1 = NAN;
			computer.output2 = NAN;
			computer.output3 = NAN;
		}
	}

	antalBlock = howManyGrid(&grid, 2);
	cout << "\nDet finns totalt: " << antalBlock;
	cout << "\n\nDet va det.";

	if (grid.grid != nullptr) {
		for (int i = 0; i < grid.maxX; i++)
			delete[] grid.grid[i];
		delete[] grid.grid;
	}
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

void IntcodeComputer(state* nuvarande, int input) {
	int i = nuvarande->i;
	int l�ngd = nuvarande->l�ngd;
	int relativeBase = nuvarande->relativeBase;
	long long* lista = nuvarande->lista;
	int antalExtraMinnen = nuvarande->antalExtraMinnen;
	extraMinne* minnen = nuvarande->minnen;

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
			cout << "ERROR! VARF�R TAR DEN INPUT!?";
			*parameterOne = input;
			i += 2;
			break;

		case 4: //Output
			i += 2;
			if (isnan(nuvarande->output1))
				nuvarande->output1 = *parameterOne;
			else if (isnan(nuvarande->output2))
				nuvarande->output2 = *parameterOne;
			else if(isnan(nuvarande->output3)){
				nuvarande->output3 = *parameterOne;

				nuvarande->i = i;//Sparar alla inst�llningar
				nuvarande->relativeBase = relativeBase;
				nuvarande->antalExtraMinnen = antalExtraMinnen;
				nuvarande->minnen = minnen;
				nuvarande->trueEnd = false;

				return;
			}
			else
				cout << "ERROR! Kom du ih�g att nollst�lla alla outputs?";
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

	nuvarande->i = i;//Sparar alla inst�llningar
	nuvarande->relativeBase = relativeBase;
	nuvarande->antalExtraMinnen = antalExtraMinnen;
	nuvarande->minnen = minnen;
	nuvarande->trueEnd = true;

	return;
}



int* gridValue(intGrid* grid, int targetX, int targetY) {//Skickar tillbaka v�rdet med koordinaterna [targetX][targetY]
	int trueX = grid->centerX + targetX;
	int trueY = grid->centerY + targetY;

	if (grid->grid == nullptr)
		increaseGrid(grid, targetX, targetY);

	if (trueX >= grid->maxX or trueY >= grid->maxY or trueX < 0 or trueY < 0)
		increaseGrid(grid, targetX, targetY);

	trueX = grid->centerX + targetX;
	trueY = grid->centerY + targetY;

	return(&grid->grid[trueX][trueY]);
}

void increaseGrid(intGrid* grid, int targetX, int targetY) {
	int trueX = grid->centerX + targetX;
	int trueY = grid->centerY + targetY;
	int xF�rskjutning = 0;
	int yF�rskjutning = 0;

	if (0 <= trueX and trueX < grid->maxX and 0 <= trueY and trueY < grid->maxY) {//Om den redan f�r plats
		return;
	}

	if (0 <= trueX and trueX < grid->maxX)
		trueX = grid->maxX - 1;
	if (0 <= trueY and trueY < grid->maxY)
		trueY = grid->maxY - 1;

	if (trueX < 0) {
		xF�rskjutning = abs(trueX);
		grid->centerX += xF�rskjutning;
		trueX = grid->maxX + xF�rskjutning - 1;
	}
	trueX++;

	if (trueY < 0) {
		yF�rskjutning = abs(trueY);
		grid->centerY += yF�rskjutning;
		trueY = grid->maxY + yF�rskjutning - 1;
	}
	trueY++;


	int** reference = new int* [trueX];
	for (int i = 0; i < trueX; i++) {
		reference[i] = new int[trueY];
		for (int j = 0; j < trueY; j++)
			reference[i][j] = false;
	}

	for (int i = xF�rskjutning; i < grid->maxX + xF�rskjutning; i++) //Kopiar allt
		for (int j = yF�rskjutning; j < grid->maxY + yF�rskjutning; j++)
			reference[i][j] = grid->grid[i - xF�rskjutning][j - yF�rskjutning];

	if (grid->grid != nullptr) {
		for (int i = 0; i < grid->maxX; i++)
			delete[] grid->grid[i];
		delete[] grid->grid;
	}


	grid->grid = reference;
	grid->maxX = trueX;
	grid->maxY = trueY;


}

void displayGrid(intGrid* grid, void* painter) {
	int specialX = grid->maxX;//Dessa �r normalt sett st�rre �n m�jligt
	int specialY = grid->maxY;

	//if (painter != nullptr) {F�r ett s�rskilt objekt
	//	specialX = painter->x + grid->centerX;
	//	specialY = painter->y + grid->centerY;
	//}

	//TA BORT NEDANST�ENDE D� SPECIELL DISPLAY OBJEKT ANV�NDS
	//specialX = grid->centerX;
	//specialY = grid->centerY;

	cout << endl;
	for (int j = 0; j < grid->maxY; j++) {
		for (int i = 0; i < grid->maxX; i++)
			//if (i == specialX and j == specialY) //F�r speciell printfunktion
			//	cout << "?";
			//else
			if (grid->grid[i][j] == 4)
				cout << "o";
			else if (grid->grid[i][j] == 3)
				cout << "_";
			else if (grid->grid[i][j] == 2)
				cout << "#";
			else if (grid->grid[i][j] == 1)
				cout << "|";
			else if (grid->grid[i][j] == 0)
				cout << ".";
			else
				cout << "ERROR! FELAKTIG TEXT!";

		cout << endl;
	}
}

void changeGrid(intGrid* grid, int targetX, int targetY, int value) {
	*gridValue(grid, targetX, targetY) = value;
}

int howManyGrid(intGrid* grid, int target) {
	int antalS�dana = 0;

	for (int y = 0; y < grid->maxY; y++)
		for (int x = 0; x < grid->maxX; x++)
			if (grid->grid[x][y] == target)
				antalS�dana++;

	return(antalS�dana);
}
