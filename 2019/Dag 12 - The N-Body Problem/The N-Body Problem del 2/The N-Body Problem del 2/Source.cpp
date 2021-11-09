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

struct state {
	moon månar[4];
};

moon buildMoon(void);
void applyGravity(moon* moon1, moon* moon2);
void applyVelocity(moon* moon);
int calculateEnergy(moon* moon);
void displayMoon(moon* moon);

bool stateCheck(state* comparator, state* states, long long numberOfStates);

int main() {
	moon* månar = nullptr;
	int antalMånar = 0;

	state* states = nullptr;
	state* kopia = nullptr;
	unsigned long long numberOfStates = 0;
	unsigned long long steps = 0;

	numberOfStates += -1;
	cout << numberOfStates << endl;
	numberOfStates = 0;

	cout << "Hur många månar finns det?	";
	cin >> antalMånar;
	månar = new moon[antalMånar];

	cout << "\nMånarnas data tack:\n";

	for (int i = 0; i < antalMånar; i++) {
		månar[i] = buildMoon();
		displayMoon(&månar[i]);
		cout << endl;
	}

	kopia = new state[numberOfStates + 2];

	for (int i = 0; i < numberOfStates; i++)//Kopierar nuvarande
		kopia[i] = states[i];

	if (states != nullptr)
		delete[] states;

	states = kopia;

	for (int i = 0; i < 4; i++) {//Den nytillagda görs till en kopia
		states[numberOfStates].månar[i] = månar[i];
		displayMoon(&states[numberOfStates].månar[i]);
	}

	numberOfStates++;

	while(!stateCheck(&states[1], states, numberOfStates)) {
		if (steps % 10000000 == 0)
			cout << endl << steps;

		for (int mainMoon = 0; mainMoon < antalMånar; mainMoon++)
			for (int subMoon = mainMoon + 1; subMoon < antalMånar; subMoon++)
				applyGravity(&månar[mainMoon], &månar[subMoon]);

		for (int j = 0; j < antalMånar; j++) {
			applyVelocity(&månar[j]);
			calculateEnergy(&månar[j]);
		}

		//kopia = new state[numberOfStates + 1];

		//for (int i = 0; i < numberOfStates; i++)//Kopierar nuvarande
		//	kopia[i] = states[i];

		//if(states != nullptr)
		//	delete[] states;

		//states = kopia;

		for (int i = 0; i < 4; i++)//Den nytillagda görs till en kopia
			states[1].månar[i] = månar[i];

		numberOfStates++;
		steps++;
	}

	cout << "\nDen upprepade är:\n";
	for (int i = 0; i < 4; i++) {
		displayMoon(&månar[i]);
		cout << endl;
	}
	cout << "\nDetta efter " << steps << " steg";

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

bool stateCheck(state* comparator, state* states, long long numberOfStates) {
	bool hasFailed = false;

	if (states == nullptr or comparator == nullptr or numberOfStates == 1) //Om det inte är något att jämföra
		return(false);

	for (int currentState = 0; currentState < 1; currentState++) {//Genomför flera test, alla måste klaras för att vara identiska
		for (int currentMoon = 0; currentMoon < 4; currentMoon++)//Kollar om energin är densamma
			if (comparator->månar[currentMoon].totalEnergy != states[currentState].månar[currentMoon].totalEnergy) {
				hasFailed = true;
				break;
			}

		if (!hasFailed)//Kollar om allas positioner är de samma
			for (int currentMoon = 0; currentMoon < 4; currentMoon++)
				if ((comparator->månar[currentMoon].x != states[currentState].månar[currentMoon].x) or (comparator->månar[currentMoon].y != states[currentState].månar[currentMoon].y) or (comparator->månar[currentMoon].z != states[currentState].månar[currentMoon].z)) {
					hasFailed = true;
					break;
				}

		if (!hasFailed)//Kollar om allas hastighet är samma
			for (int currentMoon = 0; currentMoon < 4; currentMoon++)
				if ((comparator->månar[currentMoon].vx != states[currentState].månar[currentMoon].vx) or (comparator->månar[currentMoon].vy != states[currentState].månar[currentMoon].vy) or (comparator->månar[currentMoon].vz != states[currentState].månar[currentMoon].vz)) {
					hasFailed = true;
					break;
				}

		if (!hasFailed) {//Om den klarar alla testen är de samma
			cout << "\nUpprepning funnen! " << numberOfStates - 1 << " = " << currentState;
			return(true);
		}

	}
	return(false);//Om den nådde hit, klarade inget fulltest, så är den fel
}