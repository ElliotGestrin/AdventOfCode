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
	long long värde = 0;
	unsigned long position = 0;
};

struct state {
	long long* lista = nullptr;
	double längd = NAN;
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
void töm();
extraMinne* hittaMinne(extraMinne minnen[], int längd, unsigned long sökes);
extraMinne* ändraMinne(extraMinne* minnen, int* längd, int värde, unsigned long position);
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

	cout << "\nTotalt är det " << antalBlock << " block";
}

int main() {
	long long* referensLista = nullptr;
	int längd = 0;
	state computer;

	intGrid grid;

	int antalBlock = 0;

	cout << "Hur lång är koden? ";
	cin >> längd;

	referensLista = new long long[längd];

	cout << "\nDina order: ";
	for (int i = 0; i < längd; i++) {
		cin >> referensLista[i];
	}

	computer.lista = referensLista;
	computer.längd = längd;

	cout << "\nListan: ";
	for (int i = 0; i < computer.längd; i++)
		cout << computer.lista[i] << ", ";

	töm(); //Slänger allt som finns kvar i inputten
	
	cout << "\nDå kör vi då";
	
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

extraMinne* hittaMinne(extraMinne minnen[], int längd, unsigned long sökes) {//Skickar tillbaka en referens till det sökta minnet
	if (längd != 0)
		for (int i = 0; i < längd; i++) { //Eller nullptr om det saknas
			if (minnen[i].position == sökes)
				return(&minnen[i]);
		}
	return(nullptr);
}

extraMinne* ändraMinne(extraMinne* minnen, int* längd, int värde, unsigned long position) {
	extraMinne* mål = hittaMinne(minnen, *längd, position);

	if (mål != nullptr) //Dvs positionen finns redan
		mål->värde = värde;
	else {//Annars får vi skapa ny plats för den
		extraMinne* temp = new extraMinne[*längd + 1];

		for (int i = 0; i < *längd; i++) {//Gör temp till en ett större kopia
			temp[i].position = minnen[i].position;
			temp[i].värde = minnen[i].värde;
		}
		temp[*längd].position = position;//Lägger till det nya
		temp[*längd].värde = värde;

		delete[] minnen;

		minnen = temp;

		*längd += 1;//Uppdaterar längden med
	}

	return(minnen);
}

void IntcodeComputer(state* nuvarande, int input) {
	int i = nuvarande->i;
	int längd = nuvarande->längd;
	int relativeBase = nuvarande->relativeBase;
	long long* lista = nuvarande->lista;
	int antalExtraMinnen = nuvarande->antalExtraMinnen;
	extraMinne* minnen = nuvarande->minnen;

	//cout << "\nInput = " << input;

	while (lista[i] != 99) {//Kontrollerar först om det ska va slut, genomför sedan de faktiska instruktionerna. Adderar fyra då det är förskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int* instruction = extraheraDelar(lista[i]); //Tar ut instruktionen och dess argument (Instruktionen)
		long long* parameterOne = nullptr;//Arg ett
		long long* parameterTwo = nullptr; //Arg två
		long long* parameterThree = nullptr;//Arg tre
		bool skaAnvändaMinnet[3] = { false };//Ifall någon av parametrarna ska använda extraminne

		//cout << "\n[" << i << "][" << relativeBase << "]    "; //Visar massvis vid behov av debugging avancerade system
		//for (int j = 0; j < 4; j++)
		//	cout << lista[i + j] << " ";
		//cout << "   [";
		//for (int j = 0; j < antalExtraMinnen; j++)
		//	cout << minnen[j].position << ":" << minnen[j].värde << "  ";
		//cout << "]";

		if (i + 1 < längd)
			switch (instruction[1])//Läget för parameterOne
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 1] < längd) //Om den finns
					parameterOne = &lista[relativeBase + lista[i + 1]];
				else//Om den ska va i extraminne
					skaAnvändaMinnet[0] = true;
				break;
			case 1://Immediate mode
				parameterOne = &lista[i + 1];
				break;
			case 0://Position mode 
				if (lista[i + 1] < längd)//Den är en del av standard
					parameterOne = &lista[lista[i + 1]];
				else {//Den är en del av extraminne
					skaAnvändaMinnet[0] = true;
				}
				break;
			default:
				cout << "Felaktig parameterOne läge!";
				break;
			}

		if (i + 2 < längd)
			switch (instruction[2])//Läget för parameterTwo
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 2] < längd) //Om den finns
					parameterTwo = &lista[relativeBase + lista[i + 2]];
				else //Om den ska va i extraminne
					skaAnvändaMinnet[1] = true;
				break;
			case 1://Immediate mode
				parameterTwo = &lista[i + 2];
				break;
			case 0://Position mode
				if (lista[i + 2] < längd)//Den är en del av standard
					parameterTwo = &lista[lista[i + 2]];
				else
					skaAnvändaMinnet[1] = true;
				break;
			default:
				cout << "Felaktig parameterTwo läge!";
				break;
			}

		if (i + 3 < längd)
			switch (instruction[3])//Läget för parameterThree
			{
			case 2://Relative mode
				if (relativeBase + lista[i + 1] < längd) //Om den finns
					parameterThree = &lista[relativeBase + lista[i + 3]];
				else {//Om den ska va i extraminne
					skaAnvändaMinnet[2] = true;
				}
				break;
			case 1://Immediate mode
				parameterThree = &lista[i + 3];
				break;
			case 0://Position mode
				if (lista[i + 3] < längd)//Den är en del av standard
					parameterThree = &lista[lista[i + 3]];
				else {
					skaAnvändaMinnet[2] = true;
				}
				break;
			default:
				break;
			}

		//Gör ändringar i "minne" efter behov! Behöver ske samtidigt ty annars byts minnena när nästa gör detta
		for (int j = 1; j < 4; j++) //Skapar alla nya minnen
			if (skaAnvändaMinnet[j - 1]) {
				unsigned long söktPosition = lista[i + j];
				if (instruction[j] == 2) // Om den ska va i relative, är ju i antingen relative eller position
					söktPosition += relativeBase;
				if (hittaMinne(minnen, antalExtraMinnen, söktPosition) == nullptr)//Om minnet inte redan fanns
					minnen = ändraMinne(minnen, &antalExtraMinnen, 0, söktPosition);
			}
		for (int j = 1; j < 4; j++) {//Väljer vilken
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

			if (skaAnvändaMinnet[j - 1]) {//Ger dem deras ställen
				unsigned long söktPosition = lista[i + j];
				if (instruction[j] == 2) // Om den ska va i relative, är ju i antingen relative eller position
					söktPosition += relativeBase;
				*aktivParameter = &hittaMinne(minnen, antalExtraMinnen, söktPosition)->värde;
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
			cout << "ERROR! VARFÖR TAR DEN INPUT!?";
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

				nuvarande->i = i;//Sparar alla inställningar
				nuvarande->relativeBase = relativeBase;
				nuvarande->antalExtraMinnen = antalExtraMinnen;
				nuvarande->minnen = minnen;
				nuvarande->trueEnd = false;

				return;
			}
			else
				cout << "ERROR! Kom du ihåg att nollställa alla outputs?";
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

	nuvarande->i = i;//Sparar alla inställningar
	nuvarande->relativeBase = relativeBase;
	nuvarande->antalExtraMinnen = antalExtraMinnen;
	nuvarande->minnen = minnen;
	nuvarande->trueEnd = true;

	return;
}



int* gridValue(intGrid* grid, int targetX, int targetY) {//Skickar tillbaka värdet med koordinaterna [targetX][targetY]
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
	int xFörskjutning = 0;
	int yFörskjutning = 0;

	if (0 <= trueX and trueX < grid->maxX and 0 <= trueY and trueY < grid->maxY) {//Om den redan får plats
		return;
	}

	if (0 <= trueX and trueX < grid->maxX)
		trueX = grid->maxX - 1;
	if (0 <= trueY and trueY < grid->maxY)
		trueY = grid->maxY - 1;

	if (trueX < 0) {
		xFörskjutning = abs(trueX);
		grid->centerX += xFörskjutning;
		trueX = grid->maxX + xFörskjutning - 1;
	}
	trueX++;

	if (trueY < 0) {
		yFörskjutning = abs(trueY);
		grid->centerY += yFörskjutning;
		trueY = grid->maxY + yFörskjutning - 1;
	}
	trueY++;


	int** reference = new int* [trueX];
	for (int i = 0; i < trueX; i++) {
		reference[i] = new int[trueY];
		for (int j = 0; j < trueY; j++)
			reference[i][j] = false;
	}

	for (int i = xFörskjutning; i < grid->maxX + xFörskjutning; i++) //Kopiar allt
		for (int j = yFörskjutning; j < grid->maxY + yFörskjutning; j++)
			reference[i][j] = grid->grid[i - xFörskjutning][j - yFörskjutning];

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
	int specialX = grid->maxX;//Dessa är normalt sett större än möjligt
	int specialY = grid->maxY;

	//if (painter != nullptr) {För ett särskilt objekt
	//	specialX = painter->x + grid->centerX;
	//	specialY = painter->y + grid->centerY;
	//}

	//TA BORT NEDANSTÅENDE DÅ SPECIELL DISPLAY OBJEKT ANVÄNDS
	//specialX = grid->centerX;
	//specialY = grid->centerY;

	cout << endl;
	for (int j = 0; j < grid->maxY; j++) {
		for (int i = 0; i < grid->maxX; i++)
			//if (i == specialX and j == specialY) //För speciell printfunktion
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
	int antalSådana = 0;

	for (int y = 0; y < grid->maxY; y++)
		for (int x = 0; x < grid->maxX; x++)
			if (grid->grid[x][y] == target)
				antalSådana++;

	return(antalSådana);
}
