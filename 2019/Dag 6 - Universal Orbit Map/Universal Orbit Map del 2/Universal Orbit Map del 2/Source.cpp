#include <iostream>
#include <string>

using namespace::std;

struct orbiter {
	orbiter* directlyOrbits = nullptr;
	int totalOrbits = 0;
	string namn = "";
};

int avst�ndOrbiter(orbiter* orbi, orbiter* m�l); //Returnar avst�ndet mellan tv� orbitaler
orbiter* orbitalNummer(orbiter* orbi, int n); //Skickar tillbaka referens till den orbiter som �r n steg bakom denna

int main() {
	int antal = 0;
	int YOUavst�nd = 0;
	int SANavst�nd = 0;

	orbiter* solsystemet;
	string* info;
	orbiter* COM = nullptr;
	orbiter* YOU = nullptr;
	orbiter* SAN = nullptr;
	orbiter* M�TE = nullptr;

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
	COM = &solsystemet[antal];

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
		cout << "\nOrbiter " << i << " heter: " << solsystemet[i].namn << " och orbiterar: " << solsystemet[i].directlyOrbits->namn;

	for (int i = 0; YOU == nullptr or SAN == nullptr;i++){
		if (solsystemet[i].namn == "YOU")
			YOU = &solsystemet[i];
		if(solsystemet[i].namn == "SAN")
			SAN = &solsystemet[i];
	}
	
	cout << "\n\nYOU orbiterar: " << YOU->directlyOrbits->namn;
	cout << "\nSAN orbiterar: " << SAN->directlyOrbits->namn;


	for(int i = 0; M�TE == nullptr; i++) //Hittar platsen d�r de m�ts. Kollar steg f�r steg om den h�r finns
		for (int j = 0; M�TE == nullptr and orbitalNummer(SAN, j) != COM; j++)  //N�gonstans i den andra
			if (orbitalNummer(YOU, i) == orbitalNummer(SAN, j)) //Slutar n�r den hittat den, ty d� �r inte m�te nullptr
				M�TE = orbitalNummer(YOU, i);
	
	cout << "\n\nDeras m�te �r vid: " << M�TE->namn;
	
	YOUavst�nd = avst�ndOrbiter(YOU->directlyOrbits, M�TE);
	cout << "\nYou �r: " << YOUavst�nd << " hopp bort";

	SANavst�nd = avst�ndOrbiter(SAN->directlyOrbits, M�TE);
	cout << "\nSAN �r: " << SANavst�nd << " hopp bort";

	cout << "\n\nTotalt �r det: " << YOUavst�nd + SANavst�nd << " hopp som beh�ver g�ras";

	delete[] solsystemet;
	delete[] info;
}

int avst�ndOrbiter(orbiter* orbi, orbiter*m�l){ //Returnar avst�ndet mellan tv� orbitaler
	if (orbi->namn == m�l->namn)
		return(0);
	else
		return(avst�ndOrbiter(orbi->directlyOrbits, m�l) + 1);
}

orbiter* orbitalNummer(orbiter* orbi, int n) { //Skickar tillbaka referens till den orbiter som �r n steg bakom denna
	if (n == 0)
		return(orbi);
	else if (orbi->namn == "COM")
		return(orbi);
	else
		return(orbitalNummer(orbi->directlyOrbits, (n - 1)));
}
