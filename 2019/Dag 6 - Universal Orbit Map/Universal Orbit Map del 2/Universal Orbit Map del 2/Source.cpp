#include <iostream>
#include <string>

using namespace::std;

struct orbiter {
	orbiter* directlyOrbits = nullptr;
	int totalOrbits = 0;
	string namn = "";
};

int avståndOrbiter(orbiter* orbi, orbiter* mål); //Returnar avståndet mellan två orbitaler
orbiter* orbitalNummer(orbiter* orbi, int n); //Skickar tillbaka referens till den orbiter som är n steg bakom denna

int main() {
	int antal = 0;
	int YOUavstånd = 0;
	int SANavstånd = 0;

	orbiter* solsystemet;
	string* info;
	orbiter* COM = nullptr;
	orbiter* YOU = nullptr;
	orbiter* SAN = nullptr;
	orbiter* MÖTE = nullptr;

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
	COM = &solsystemet[antal];

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
		cout << "\nOrbiter " << i << " heter: " << solsystemet[i].namn << " och orbiterar: " << solsystemet[i].directlyOrbits->namn;

	for (int i = 0; YOU == nullptr or SAN == nullptr;i++){
		if (solsystemet[i].namn == "YOU")
			YOU = &solsystemet[i];
		if(solsystemet[i].namn == "SAN")
			SAN = &solsystemet[i];
	}
	
	cout << "\n\nYOU orbiterar: " << YOU->directlyOrbits->namn;
	cout << "\nSAN orbiterar: " << SAN->directlyOrbits->namn;


	for(int i = 0; MÖTE == nullptr; i++) //Hittar platsen där de möts. Kollar steg för steg om den här finns
		for (int j = 0; MÖTE == nullptr and orbitalNummer(SAN, j) != COM; j++)  //Någonstans i den andra
			if (orbitalNummer(YOU, i) == orbitalNummer(SAN, j)) //Slutar när den hittat den, ty då är inte möte nullptr
				MÖTE = orbitalNummer(YOU, i);
	
	cout << "\n\nDeras möte är vid: " << MÖTE->namn;
	
	YOUavstånd = avståndOrbiter(YOU->directlyOrbits, MÖTE);
	cout << "\nYou är: " << YOUavstånd << " hopp bort";

	SANavstånd = avståndOrbiter(SAN->directlyOrbits, MÖTE);
	cout << "\nSAN är: " << SANavstånd << " hopp bort";

	cout << "\n\nTotalt är det: " << YOUavstånd + SANavstånd << " hopp som behöver göras";

	delete[] solsystemet;
	delete[] info;
}

int avståndOrbiter(orbiter* orbi, orbiter*mål){ //Returnar avståndet mellan två orbitaler
	if (orbi->namn == mål->namn)
		return(0);
	else
		return(avståndOrbiter(orbi->directlyOrbits, mål) + 1);
}

orbiter* orbitalNummer(orbiter* orbi, int n) { //Skickar tillbaka referens till den orbiter som är n steg bakom denna
	if (n == 0)
		return(orbi);
	else if (orbi->namn == "COM")
		return(orbi);
	else
		return(orbitalNummer(orbi->directlyOrbits, (n - 1)));
}
