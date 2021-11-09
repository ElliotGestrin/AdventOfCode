#include <iostream>

using namespace::std;

int* FFT(int* lista, int l�ngd, int* pattern, int patternL�ngd);

void t�m();//T�mmer input

int main() {
	int l�ngd = 0;
	unsigned int offset = 0;
	int* lista = nullptr;
	int* referensLista = nullptr;

	int numPhases = 0;

	int pattern[4] = { 0, 1, 0, -1 };
	int patternL�ngd = 4;

	cout << "Hur l�ng �r din array? ";
	cin >> l�ngd;
	cout << endl << "L�ngd: " << l�ngd << " " << l�ngd * 10000;

	lista = new int[l�ngd * 10000];
	referensLista = new int[l�ngd];

	t�m();
	cout << "\nVad �r ditt starttal? ";
	for (int i = 0; i < l�ngd; i++)
		referensLista[i] = getchar() - 48;

	cout << endl;
	for (int i = 0; i < l�ngd; i++)
		cout << referensLista[i];

	for (int i = 0; i < l�ngd * 10000; i++)
		lista[i] = referensLista[i % l�ngd];

	cout << "\nHur m�nga phases vill du k�ra? ";
	cin >> numPhases;

	cout << endl << "L�ngd: " << l�ngd << " " << l�ngd * 10000 << endl;

	for (int i = 0; i < numPhases; i++) {
		cout <<  i << " ";
		lista = FFT(lista, l�ngd * 10000, pattern, patternL�ngd);
	}

	cout << endl << "Resultat efter " << numPhases << " phases �r: ";
	
	for (int i = 0; i < 7; i++)
		offset += referensLista[i] * pow(10, (6 - i));
	cout << "(Offset = " << offset << ") ";

	for (int i = offset; i < offset + 8; i++) //Vill bara ha �tta tecken
		cout << lista[i];

	delete[] lista;
	delete[] referensLista;
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

int* FFT(int* lista, int l�ngd, int * pattern, int patternL�ngd) {
	int *output = new int [l�ngd];

	for (int main = 0; main < l�ngd; main++) {
		int v�rde = 0;
		
		for (int i = main; i < l�ngd; i += patternL�ngd * (main + 1))//Genomf�r all addition
			for (int j = 0; j < main + 1 and (i + j) < l�ngd; j++)
				v�rde += lista[i + j];

		for (int i = main + patternL�ngd * (main + 1)/2; i < l�ngd; i += patternL�ngd * (main + 1))//Genomf�r all subtraktion
			for (int j = 0; j < main + 1 and (i + j) < l�ngd; j++)
				v�rde -= lista[i + j];

		v�rde = abs(v�rde);
		v�rde -= int(v�rde / 10) * 10;

		//cout << " = " << v�rde << endl;
		output[main] = v�rde;
	}

	delete[] lista;
	return(output);
}
