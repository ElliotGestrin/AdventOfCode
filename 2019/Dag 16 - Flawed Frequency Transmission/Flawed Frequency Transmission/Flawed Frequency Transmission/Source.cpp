#include <iostream>

using namespace::std;

int* FFT(int* lista, int längd, int* pattern, int patternLängd);

void töm();//Tömmer input

int main() {
	int längd = 0;
	unsigned int offset = 0;
	int* lista = nullptr;
	int* referensLista = nullptr;

	int numPhases = 0;

	int pattern[4] = { 0, 1, 0, -1 };
	int patternLängd = 4;

	cout << "Hur lång är din array? ";
	cin >> längd;
	cout << endl << "Längd: " << längd << " " << längd * 10000;

	lista = new int[längd * 10000];
	referensLista = new int[längd];

	töm();
	cout << "\nVad är ditt starttal? ";
	for (int i = 0; i < längd; i++)
		referensLista[i] = getchar() - 48;

	cout << endl;
	for (int i = 0; i < längd; i++)
		cout << referensLista[i];

	for (int i = 0; i < längd * 10000; i++)
		lista[i] = referensLista[i % längd];

	cout << "\nHur många phases vill du köra? ";
	cin >> numPhases;

	cout << endl << "Längd: " << längd << " " << längd * 10000 << endl;

	for (int i = 0; i < numPhases; i++) {
		cout <<  i << " ";
		lista = FFT(lista, längd * 10000, pattern, patternLängd);
	}

	cout << endl << "Resultat efter " << numPhases << " phases är: ";
	
	for (int i = 0; i < 7; i++)
		offset += referensLista[i] * pow(10, (6 - i));
	cout << "(Offset = " << offset << ") ";

	for (int i = offset; i < offset + 8; i++) //Vill bara ha åtta tecken
		cout << lista[i];

	delete[] lista;
	delete[] referensLista;
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

int* FFT(int* lista, int längd, int * pattern, int patternLängd) {
	int *output = new int [längd];

	for (int main = 0; main < längd; main++) {
		int värde = 0;
		
		for (int i = main; i < längd; i += patternLängd * (main + 1))//Genomför all addition
			for (int j = 0; j < main + 1 and (i + j) < längd; j++)
				värde += lista[i + j];

		for (int i = main + patternLängd * (main + 1)/2; i < längd; i += patternLängd * (main + 1))//Genomför all subtraktion
			for (int j = 0; j < main + 1 and (i + j) < längd; j++)
				värde -= lista[i + j];

		värde = abs(värde);
		värde -= int(värde / 10) * 10;

		//cout << " = " << värde << endl;
		output[main] = värde;
	}

	delete[] lista;
	return(output);
}
