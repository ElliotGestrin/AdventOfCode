#include <iostream>

using namespace::std;

bool StillGoing(int x) { //Kollar om det �r en 99a och slutar isf
	return(not(x == 99)); //Returnar sant om det inte �r 99, annars falskt
}

void IntcodeComputer(int lista[]){
	for (int i = 0; StillGoing(lista[i]); i += 4) {//Kontrollerar f�rst om det ska va slut, genomf�r sedan de faktiska instruktionerna. Adderar fyra d� det �r f�rskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int f�rsta = lista[i]; //Tar ut instruktionen och dess argument (Instruktionen)
		int andra = lista[i+1]; //Arg ett
		int tredje = lista[i+2]; //Arg tv�
		int fj�rde = lista[i+3]; //Arg tre

		switch (f�rsta)
		{
		case 1:
			lista[fj�rde] = lista[tredje] + lista[andra];
			break;

		case 2:
			lista[fj�rde] = lista[tredje] * lista[andra];
			break;

		default:
			cout << "!!!ERRORR!!! felaktig order";
			break;
		}
	}

}

int main() {
	int l�ngd = 0;
	char skr�p = '0';

	int lista[130] = { 0 };
	int referenslista[130];


	while (cin >> lista[l�ngd]) { //Plockar in in-datan
		cin >> skr�p; //Sl�nger alla komma-tecken
		l�ngd += 1; //Kollar l�ngden
	}

	for (int i = 0; i < l�ngd; i++) //Bygger referenslistan, behlvs f�r att �terst�lla listan sen
		referenslista[i] = lista[i];

	int noun = 0;
	int	verb = 0; //De tv� olika invariablerna

	for (; noun < 100; noun++) {//Brute-forcar en l�sning p� vilka tv� inputs [1,2] som ger ett visst m�l
		for (; verb < 100; verb++) { 
			lista[1] = noun;
			lista[2] = verb;

			cout << "\n\nNoun = " << noun << ": " << lista[1] << ", Verb = " << verb << ": " << lista[2];

			IntcodeComputer(lista);

			cout << " lista[0] = " << lista[0];
			if (lista[0] == 5482655)//19690720) //M�lsiffran som s�kes
				break;

			else for (int i = 0; i < l�ngd; i++) //Nollst�ller listan
				lista[i] = referenslista[i];
		}

		if (lista[0] == 5482655)//19690720) //M�lsiffran som s�kes
			break;
		else
			verb = 0;
	}

	cout << "\n\nNoun = " << noun << ", Verb = "<< verb << " (Ger: "<< lista[0] << ")" ;
}