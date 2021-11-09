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
	char typ; //Riktning p� ordern
	int l�ngd; //L�ngd p� ordern
};

int main() {
	instruktion* inst[2] = {nullptr};
	intGrid grid;

	int Instruktioner = 0;
	unsigned int minLength = -1;
	int minX = NAN;
	int minY = NAN;

	int antalM�ten = 0;
	int temp = 0;
	int* m�tenX = nullptr;
	int* m�tenY = nullptr;


	cout << "Hur m�nga m�ten vill du kunna hantera? ";
	cin >> temp;
	m�tenX = new int[temp];
	m�tenY = new int[temp];

	cout << "Hur l�nga �r instruktionerna f�r varje kabel? ";
	cin >> Instruktioner;

	inst[0] = new instruktion[Instruktioner];
	inst[1] = new instruktion[Instruktioner];

	cout << "Instruktionerna f�r den f�rsta:\n";
	for (int i = 0; i < Instruktioner; i++) { //Tar lika m�nga instruktioner som varje best�r av
		cin >> inst[0][i].typ; //Tar bokstaven
		cin >> inst[0][i].l�ngd; //Tar siffran
		getchar(); //Sl�nger 
	}

	for(int z = 1; z < 3; z++){
		int nuvarandeY = 0;
		int nuvarandeX = 0;
		for (int i = 0; i < Instruktioner; i++) {
			cout << i << " ";
			switch (inst[z-1][i].typ)
			{
			case 'U':
				increaseGrid(&grid, nuvarandeX, nuvarandeY - inst[z-1][i].l�ngd);
				for (int j = 0; j < inst[z-1][i].l�ngd; j++) {
					nuvarandeY--;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'D':
				increaseGrid(&grid, nuvarandeX, nuvarandeY + inst[z-1][i].l�ngd);
				for (int j = 0; j < inst[z-1][i].l�ngd; j++) {
					nuvarandeY++;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'L':
				increaseGrid(&grid, nuvarandeX - inst[z-1][i].l�ngd, nuvarandeY);
				for (int j = 0; j < inst[z-1][i].l�ngd; j++) {
					nuvarandeX--;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			case 'R':
				increaseGrid(&grid, nuvarandeX + inst[z-1][i].l�ngd, nuvarandeY);
				for (int j = 0; j < inst[z-1][i].l�ngd; j++) {
					nuvarandeX++;
					*gridValue(&grid, nuvarandeX, nuvarandeY) += z;
				}
				break;
			default:
				cout << "ERROR! FELAKTIG RIKTNINGSINSTRUKTION P� INST " << i;
				break;
			}

		}
		if (z == 1) {
			//cout << "Systemet efter den f�rsta:\n";
			//displayGrid(&grid);

			cout << "\nInstruktionerna f�r den andra:\n";
			for (int i = 0; i < Instruktioner; i++) { //Tar lika m�nga instruktioner som varje best�r av
				inst[1][i].typ = getchar(); //Tar bokstaven
				cin >> inst[1][i].l�ngd; //Tar siffran
				getchar(); //Sl�nger kommatecknet
			}
		}
	}
	
	//cout << "Systemet efter den andra:\n";
	//displayGrid(&grid);

			for (int y = 0; y < grid.maxY; y++)
				for (int x = 0; x < grid.maxX; x++)
				if (grid.grid[x][y] == 3) {//Om det var ett m�te
					m�tenX[antalM�ten] = -(grid.centerX - x);
					m�tenY[antalM�ten] = -(grid.centerY - y);
					antalM�ten++;

					if (manhattanDistance(-(grid.centerX - x), -(grid.centerY - y)) < minLength) {
						cout << ", och det var n�rmare";
						minLength = manhattanDistance(-(grid.centerX - x), -(grid.centerY - y));
						minX = -(grid.centerX - x);
						minY = -(grid.centerY - y);
					}
				}

	cout << "\nDet minimala avst�ndet �r p� [" << minX << "][" << minY << "] och �r " << minLength;

	//Reproducerar att bygga den f�r att finna hur l�ngt den g�r

	minLength = -1;

	for (int m = 0; m < antalM�ten; m++) {
		int l�ngd[2] = { 0 };
		cout <<  m << " ";

		for (int z = 1; z < 3; z++) {
			int nuvarandeY = 0;
			int nuvarandeX = 0;
			bool M�TE = false;
			cout << endl << z - 1 << ": ";
			for (int i = 0; i < Instruktioner and !M�TE; i++) {
				cout << endl << "   " << i << ": ";
				switch (inst[z - 1][i].typ)
				{
				case 'U':
					for (int j = 0; j < inst[z - 1][i].l�ngd; j++) {
						nuvarandeY--;
						l�ngd[z - 1]++;
						if (nuvarandeY == m�tenY[m] and nuvarandeX == m�tenX[m]) {
							M�TE = true;
							break;
						}
					}
					break;
				case 'D':
					for (int j = 0; j < inst[z - 1][i].l�ngd; j++) {
						nuvarandeY++;
						l�ngd[z - 1]++;
						if (nuvarandeY == m�tenY[m] and nuvarandeX == m�tenX[m]) {
							M�TE = true;
							break;
						}
					}
					break;
				case 'L':
					for (int j = 0; j < inst[z - 1][i].l�ngd; j++) {
						nuvarandeX--;
						l�ngd[z - 1]++;
						if (nuvarandeY == m�tenY[m] and nuvarandeX == m�tenX[m]) {
							M�TE = true;
							break;
						}
					}
					break;
				case 'R':
					for (int j = 0; j < inst[z - 1][i].l�ngd; j++) {
						nuvarandeX++;
						l�ngd[z - 1]++;
						if (nuvarandeY == m�tenY[m] and nuvarandeX == m�tenX[m]) {
							M�TE = true;
							break;
						}
					}
					break;
				default:
					cout << "ERROR! FELAKTIG RIKTNINGSINSTRUKTION P� INST " << i;
					break;
				}
			}
		}

		if (l�ngd[0] + l�ngd[1] < minLength) {
			cout << "\nKortare v�g hittad";
			minLength = l�ngd[0] + l�ngd[1];
		}
	}

	cout << "\nDet kortaste totala avst�ndet �r: " << minLength;

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
	specialX = grid->centerX;
	specialY = grid->centerY;

	cout << endl;
	for (int j = 0; j < grid->maxY; j++) {
		for (int i = 0; i < grid->maxX; i++)
			if (i == specialX and j == specialY) //F�r speciell printfunktion
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