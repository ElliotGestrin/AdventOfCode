#include <iostream>
#include <string>

using namespace::std;

struct orbiter {
	orbiter* directlyOrbits = nullptr;
	int totalOrbits = 0;
	string namn = "";
};

int avst�ndCOM(orbiter* orbi); //returnar avst�ndet till COM i orbitaler

int main() {
	int antal = 0;
	int totalaOrbitaler = 0;
	orbiter* solsystemet;
	string* info;

	cout << "Hur m�nga orbitaler finns det? ";
	cin >> antal;

	solsystemet = new orbiter[antal + 1]; //Inneh�ller alla orbitaler
	info = new string[antal]; //Kommmer inneh�lla infon f�r varje orbital, vem den vill va runt och dens namn (inputten)

	for (int i = 0; i < antal; i++) {
		cin >> info[i]; //Tar in orbitalens info
		for (int j = 4; j < 7; j++) //Plockar ut vad orbitalen heter och namnger den
			solsystemet[i].namn += info[i].at(j);
	}

	solsystemet[antal].namn = "COM"; //Skapar COM p� den sista platsen

	for (int i = 0; i < antal; i++) {//Ger alla referensen till den de ska orbitera
		string s�kes = "";

		for (int j = 0; j < 3; j++) //Plockar ut vad den som du vill orbitera heter
			s�kes += info[i].at(j);
		
		for (int j = 0; j < (antal + 1); j++) //Letar upp den som har r�tt namn (inkluderar COM)
			if (solsystemet[j].namn == s�kes) {
				solsystemet[i].directlyOrbits = &solsystemet[j];//Den pekar till den som den ska peka till
				break; //Slutar leta, har ju sin dr�mprins
			}
	}
	for (int i = 0; i < antal; i++)
		solsystemet[i].totalOrbits = avst�ndCOM(&solsystemet[i]); //Ger dem deras avst�nd

	for (int i = 0; i < antal; i++)
		cout << "\nOrbiter " << i << " heter: " << solsystemet[i].namn << " och orbiterar: " << solsystemet[i].directlyOrbits->namn << " och har totalt: " << solsystemet[i].totalOrbits << " orbitaler.";
		

	for (int i = 0; i < antal; i++) //R�knar det totala antalet orbitaler
		totalaOrbitaler += solsystemet[i].totalOrbits;
	
	cout << "\n\nTotala antal orbitaler: " << totalaOrbitaler;

	delete[] solsystemet;
	delete[] info;
}

int avst�ndCOM(orbiter* orbi) {
	if (orbi->namn == "COM")
		return(0);
	else
		return(avst�ndCOM(orbi->directlyOrbits) + 1);
}
