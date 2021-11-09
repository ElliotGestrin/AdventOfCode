#include <iostream>

using namespace::std;

bool StillGoing(int x) { //Kollar om det är en 99a och slutar isf
	return(not(x == 99)); //Returnar sant om det inte är 99, annars falskt
}

void IntcodeComputer(int lista[]){
	for (int i = 0; StillGoing(lista[i]); i += 4) {//Kontrollerar först om det ska va slut, genomför sedan de faktiska instruktionerna. Adderar fyra då det är förskjutningen mellan de olika "kommandona" (kommandot och tre argument)
		int första = lista[i]; //Tar ut instruktionen och dess argument (Instruktionen)
		int andra = lista[i+1]; //Arg ett
		int tredje = lista[i+2]; //Arg två
		int fjärde = lista[i+3]; //Arg tre

		switch (första)
		{
		case 1:
			lista[fjärde] = lista[tredje] + lista[andra];
			break;

		case 2:
			lista[fjärde] = lista[tredje] * lista[andra];
			break;

		default:
			cout << "!!!ERRORR!!! felaktig order";
			break;
		}
	}

}

int main() {
	int längd = 0;
	char skräp = '0';

	int lista[130] = { 0 };
	int referenslista[130];


	while (cin >> lista[längd]) { //Plockar in in-datan
		cin >> skräp; //Slänger alla komma-tecken
		längd += 1; //Kollar längden
	}

	for (int i = 0; i < längd; i++) //Bygger referenslistan, behlvs för att återställa listan sen
		referenslista[i] = lista[i];

	int noun = 0;
	int	verb = 0; //De två olika invariablerna

	for (; noun < 100; noun++) {//Brute-forcar en lösning på vilka två inputs [1,2] som ger ett visst mål
		for (; verb < 100; verb++) { 
			lista[1] = noun;
			lista[2] = verb;

			cout << "\n\nNoun = " << noun << ": " << lista[1] << ", Verb = " << verb << ": " << lista[2];

			IntcodeComputer(lista);

			cout << " lista[0] = " << lista[0];
			if (lista[0] == 5482655)//19690720) //Målsiffran som sökes
				break;

			else for (int i = 0; i < längd; i++) //Nollställer listan
				lista[i] = referenslista[i];
		}

		if (lista[0] == 5482655)//19690720) //Målsiffran som sökes
			break;
		else
			verb = 0;
	}

	cout << "\n\nNoun = " << noun << ", Verb = "<< verb << " (Ger: "<< lista[0] << ")" ;
}