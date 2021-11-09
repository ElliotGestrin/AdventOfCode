#include <iostream>

using namespace::std;

struct moon {
	int x = 0;
	int y = 0;
	int z = 0;

	int vx = 0;
	int vy = 0;
	int vz = 0;

	int kineticEnergy = 0;
	int potentialEnergy = 0;
	int totalEnergy = 0;
};

moon buildMoon(void);
void applyGravity(moon* moon1, moon* moon2);
void applyVelocity(moon* moon);
int calculateEnergy(moon* moon);
void displayMoon(moon* moon);

int main() {
	moon* månar = nullptr;
	int antalMånar = 0;

	int simLength = 0;
	int updateFrequency = 0;

	int totalEnergy = 0;

	cout << "Hur många månar finns det?	";
	cin >> antalMånar;
	månar = new moon[antalMånar];

	cout << "\nMånarnas data tack:\n";

	for (int i = 0; i < antalMånar; i++) {
		månar[i] = buildMoon();
		displayMoon(&månar[i]);
		cout << endl;
	}

	cout << "\nHur länge vill du simulera? ";
	cin >> simLength;

	cout << "\nHur ofta vill du ha uppdateringar? ";
	cin >> updateFrequency;

	for (int i = 0; i < simLength; i++) {
		for (int mainMoon = 0; mainMoon < antalMånar; mainMoon++)
			for (int subMoon = mainMoon + 1; subMoon < antalMånar; subMoon++)
				applyGravity(&månar[mainMoon], &månar[subMoon]);

		for (int j = 0; j < antalMånar; j++) {
			applyVelocity(&månar[j]);
			totalEnergy += calculateEnergy(&månar[j]);
		}

		if ((i + 1) % updateFrequency == 0) {
			cout << endl << "Efter " << i + 1 << "steg: ";
			for (int j = 0; j < antalMånar; j++) {
				cout << endl;
				displayMoon(&månar[j]);
			}
			cout << endl << "Totalenergi: " << totalEnergy << endl;
		}

		totalEnergy = 0;
	}

	delete[] månar;
}

moon buildMoon(void) {
	moon måne;
	char analyser = NULL;

	while (analyser != '<')
		cin >> analyser;
	for (int j = 0; j < 3; j++) {
		cin >> analyser; //Första värdet i serien;
		switch (analyser)
		{
		case 'x':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktigt skrift för x";
			cin >> måne.x;
			break;
		case 'y':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktit skrift för y";
			cin >> måne.y;
			break;
		case 'z':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktit skrift för z";
			cin >> måne.z;
			break;
		default:
			cout << "Error! Felaktig dimenstion!";
			break;
		}
		if (j != 2) {
			cin >> analyser;
			if (analyser != ',')
				cout << "Error! Felaktig kommatering!";
		}
	}
	cin >> analyser;
	if (analyser != '>')
		cout << "Error! Tog inte upp all data!";

	return(måne);
}

void applyGravity(moon* moon1, moon* moon2) {
	if (moon1->x > moon2->x) {//x grav
		moon1->vx--;
		moon2->vx++;
	}
	else if (moon1->x < moon2->x) {
		moon1->vx++;
		moon2->vx--;
	}

	if (moon1->y > moon2->y) {//Y grav
		moon1->vy--;
		moon2->vy++;
	}
	else if (moon1->y < moon2->y) {
		moon1->vy++;
		moon2->vy--;
	}

	if (moon1->z > moon2->z) {//Z grav
		moon1->vz--;
		moon2->vz++;
	}
	else if (moon1->z < moon2->z) {
		moon1->vz++;
		moon2->vz--;
	}
}

void applyVelocity(moon* moon) {
	moon->x += moon->vx;
	moon->y += moon->vy;
	moon->z += moon->vz;
}

int calculateEnergy(moon* moon) {
	moon->potentialEnergy = abs(moon->x) + abs(moon->y) + abs(moon->z);
	moon->kineticEnergy = abs(moon->vx) + abs(moon->vy) + abs(moon->vz);

	moon->totalEnergy = moon->kineticEnergy * moon->potentialEnergy;

	return(moon->totalEnergy);
}

void displayMoon(moon* moon) {
	cout << "[" << moon->x << "][" << moon->y << "][" << moon->z << "]";
	cout << "   {" << moon->vx << "}{" << moon->vy << "}{" << moon->vz << "}";
	cout << "   pot: " << moon->potentialEnergy << ", kin: " << moon->kineticEnergy << ", tot: " << moon->totalEnergy;
}
