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
void changeGrid(intGrid* grid, int targetX, int targetY, bool value);
void displayGrid(intGrid*, void* painter = nullptr);

int manhattanDistance(int x1, int y1, int x2 = 0, int y2 = 0);

struct instruktion {
	char typ; //Riktning på ordern
	int längd; //Längd på ordern
};

int main() {
	instruktion* inst[2] = {nullptr};
	intGrid grid;

	int Instruktioner = 0;
	unsigned int minLength = -1;
	int minX = NAN;
	int minY = NAN;

	int antalMöten = 0;
	int temp = 0;
	int* mötenX = nullptr;
	int* mötenY = nullptr;


	cout << "Hur många möten vill du kunna hantera? ";
	cin >> temp;
	mötenX = new int[temp];
	mötenY = new int[temp];

	cout << "Hur långa är instruktionerna för varje kabel? ";
	cin >> Instruktioner;

	inst[0] = new instruktion[Instruktioner];
	inst[1] = new instruktion[Instruktioner];

	cout << "Instruktionerna för den första:\n";
	for (int i = 0; i < Instruktioner; i++) { //Tar lika många instruktioner som varje består av
		cin >> inst[0][i].typ; //Tar bokstaven
		cin >> inst[0][i].längd; //Tar siffran
		getchar(); //Slänger 
	}

	for(int z = 1; z < 3; z++){
		int nuvarandeY = 0;
		int nuvarandeX = 0;
		for (int i = 0; i < Instruktioner; i++) {
			cout << i << " ";
			switch (inst[z-1][i].typ)
			{
			case 'U':
				increaseGrid(&grid, nuvarandeX, nuvarandeY - inst[z-1][i].längd);
				for (int j = 0; j < inst[z-1][i].längd; j++) {
					nuvarandeY--;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'D':
				increaseGrid(&grid, nuvarandeX, nuvarandeY + inst[z-1][i].längd);
				for (int j = 0; j < inst[z-1][i].längd; j++) {
					nuvarandeY++;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'L':
				increaseGrid(&grid, nuvarandeX - inst[z-1][i].längd, nuvarandeY);
				for (int j = 0; j < inst[z-1][i].längd; j++) {
					nuvarandeX--;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'R':
				increaseGrid(&grid, nuvarandeX + inst[z-1][i].längd, nuvarandeY);
				for (int j = 0; j < inst[z-1][i].längd; j++) {
					nuvarandeX++;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			default:
				cout << "ERROR! FELAKTIG RIKTNINGSINSTRUKTION PÅ INST " << i;
				break;
			}

		}
		if (z == 1) {
			//cout << "Systemet efter den första:\n";
			//displayGrid(&grid);

			cout << "\nInstruktionerna för den andra:\n";
			for (int i = 0; i < Instruktioner; i++) { //Tar lika många instruktioner som varje består av
				inst[1][i].typ = getchar(); //Tar bokstaven
				cin >> inst[1][i].längd; //Tar siffran
				getchar(); //Slänger kommatecknet
			}
		}
	}
	
	//cout << "Systemet efter den andra:\n";
	//displayGrid(&grid);

			for (int y = 0; y < grid.maxY; y++)
				for (int x = 0; x < grid.maxX; x++)
				if (grid.grid[x][y] == 3) {//Om det var ett möte
					mötenX[antalMöten] = -(grid.centerX - x);
					mötenY[antalMöten] = -(grid.centerY - y);
					antalMöten++;

					if (manhattanDistance(-(grid.centerX - x), -(grid.centerY - y)) < minLength) {
						cout << ", och det var närmare";
						minLength = manhattanDistance(-(grid.centerX - x), -(grid.centerY - y));
						minX = -(grid.centerX - x);
						minY = -(grid.centerY - y);
					}
				}

	cout << "\nDet minimala avståndet är på [" << minX << "][" << minY << "] och är " << minLength;

	//Reproducerar att bygga den för att finna hur långt den går

	minLength = -1;

	for (int m = 0; m < antalMöten; m++) {
		int längd[2] = { 0 };
		cout <<  m << " ";

		for (int z = 1; z < 3; z++) {
			int nuvarandeY = 0;
			int nuvarandeX = 0;
			bool MÖTE = false;
			cout << endl << z - 1 << ": ";
			for (int i = 0; i < Instruktioner and !MÖTE; i++) {
				cout << endl << "   " << i << ": ";
				switch (inst[z - 1][i].typ)
				{
				case 'U':
					for (int j = 0; j < inst[z - 1][i].längd; j++) {
						nuvarandeY--;
						längd[z - 1]++;
						if (nuvarandeY == mötenY[m] and nuvarandeX == mötenX[m]) {
							MÖTE = true;
							break;
						}
					}
					break;
				case 'D':
					for (int j = 0; j < inst[z - 1][i].längd; j++) {
						nuvarandeY++;
						längd[z - 1]++;
						if (nuvarandeY == mötenY[m] and nuvarandeX == mötenX[m]) {
							MÖTE = true;
							break;
						}
					}
					break;
				case 'L':
					for (int j = 0; j < inst[z - 1][i].längd; j++) {
						nuvarandeX--;
						längd[z - 1]++;
						if (nuvarandeY == mötenY[m] and nuvarandeX == mötenX[m]) {
							MÖTE = true;
							break;
						}
					}
					break;
				case 'R':
					for (int j = 0; j < inst[z - 1][i].längd; j++) {
						nuvarandeX++;
						längd[z - 1]++;
						if (nuvarandeY == mötenY[m] and nuvarandeX == mötenX[m]) {
							MÖTE = true;
							break;
						}
					}
					break;
				default:
					cout << "ERROR! FELAKTIG RIKTNINGSINSTRUKTION PÅ INST " << i;
					break;
				}
			}
		}

		if (längd[0] + längd[1] < minLength) {
			cout << "\nKortare väg hittad";
			minLength = längd[0] + längd[1];
		}
	}

	cout << "\nDet kortaste totala avståndet är: " << minLength;

	delete[] inst[0];
	delete[] inst[1];
	if (grid.grid != nullptr) {
		for (int i = 0; i < grid.maxX; i++)
			delete[] grid.grid[i];
		delete[] grid.grid;
	}
}

int manhattanDistance(int x1, int y1, int x2, int y2) {
	return(abs(x1 - x2) + abs(y1 - y2));
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
	specialX = grid->centerX;
	specialY = grid->centerY;

	cout << endl;
	for (int j = 0; j < grid->maxY; j++) {
		for (int i = 0; i < grid->maxX; i++)
			if (i == specialX and j == specialY) //För speciell printfunktion
				cout << "o";
			else
				if (grid->grid[i][j] == 3)
					cout << "#";
				else if (grid->grid[i][j] == 2)
					cout << "+";
				else if (grid->grid[i][j] == 1)
					cout << "%";
			else
				cout << ".";
		cout << endl;
	}
}

void changeGrid(intGrid* grid, int targetX, int targetY, bool value) {
	*gridValue(grid, targetX, targetY) = value;
}