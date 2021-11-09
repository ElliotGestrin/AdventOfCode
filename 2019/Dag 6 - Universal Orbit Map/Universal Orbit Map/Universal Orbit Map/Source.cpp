#include <iostream>
#include <string>

using namespace::std;

struct orbiter {
	orbiter* directlyOrbits = nullptr;
	int totalOrbits = 0;
	string namn = "";
};

int avståndCOM(orbiter* orbi); //returnar avståndet till COM i orbitaler

int main() {
	int antal = 0;
	int totalaOrbitaler = 0;
	orbiter* solsystemet;
	string* info;

	cout << "Hur många orbitaler finns det? ";
	cin >> antal;

	solsystemet = new orbiter[antal + 1]; //Innehåller alla orbitaler
	info = new string[antal]; //Kommmer innehålla infon för varje orbital, vem den vill va runt och dens namn (inputten)

	for (int i = 0; i < antal; i++) {
		cin >> info[i]; //Tar in orbitalens info
		for (int j = 4; j < 7; j++) //Plockar ut vad orbitalen heter och namnger den
			solsystemet[i].namn += info[i].at(j);
	}

	solsystemet[antal].namn = "COM"; //Skapar COM på den sista platsen

	for (int i = 0; i < antal; i++) {//Ger alla referensen till den de ska orbitera
		string sökes = "";

		for (int j = 0; j < 3; j++) //Plockar ut vad den som du vill orbitera heter
			sökes += info[i].at(j);
		
		for (int j = 0; j < (antal + 1); j++) //Letar upp den som har rätt namn (inkluderar COM)
			if (solsystemet[j].namn == sökes) {
				solsystemet[i].directlyOrbits = &solsystemet[j];//Den pekar till den som den ska peka till
				break; //Slutar leta, har ju sin drömprins
			}
	}
	for (int i = 0; i < antal; i++)
		solsystemet[i].totalOrbits = avståndCOM(&solsystemet[i]); //Ger dem deras avstånd

	for (int i = 0; i < antal; i++)
		cout << "\nOrbiter " << i << " heter: " << solsystemet[i].namn << " och orbiterar: " << solsystemet[i].directlyOrbits->namn << " och har totalt: " << solsystemet[i].totalOrbits << " orbitaler.";
		

	for (int i = 0; i < antal; i++) //Räknar det totala antalet orbitaler
		totalaOrbitaler += solsystemet[i].totalOrbits;
	
	cout << "\n\nTotala antal orbitaler: " << totalaOrbitaler;

	delete[] solsystemet;
	delete[] info;
}

int avståndCOM(orbiter* orbi) {
	if (orbi->namn == "COM")
		return(0);
	else
		return(avståndCOM(orbi->directlyOrbits) + 1);
}
