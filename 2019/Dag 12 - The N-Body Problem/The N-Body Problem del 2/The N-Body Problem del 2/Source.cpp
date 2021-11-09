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
	moon m�nar[4];
};

moon buildMoon(void);
void applyGravity(moon* moon1, moon* moon2);
void applyVelocity(moon* moon);
int calculateEnergy(moon* moon);
void displayMoon(moon* moon);

bool stateCheck(state* comparator, state* states, long long numberOfStates);

int main() {
	moon* m�nar = nullptr;
	int antalM�nar = 0;

	state* states = nullptr;
	state* kopia = nullptr;
	unsigned long long numberOfStates = 0;
	unsigned long long steps = 0;

	numberOfStates += -1;
	cout << numberOfStates << endl;
	numberOfStates = 0;

	cout << "Hur m�nga m�nar finns det?	";
	cin >> antalM�nar;
	m�nar = new moon[antalM�nar];

	cout << "\nM�narnas data tack:\n";

	for (int i = 0; i < antalM�nar; i++) {
		m�nar[i] = buildMoon();
		displayMoon(&m�nar[i]);
		cout << endl;
	}

	kopia = new state[numberOfStates + 2];

	for (int i = 0; i < numberOfStates; i++)//Kopierar nuvarande
		kopia[i] = states[i];

	if (states != nullptr)
		delete[] states;

	states = kopia;

	for (int i = 0; i < 4; i++) {//Den nytillagda g�rs till en kopia
		states[numberOfStates].m�nar[i] = m�nar[i];
		displayMoon(&states[numberOfStates].m�nar[i]);
	}

	numberOfStates++;

	while(!stateCheck(&states[1], states, numberOfStates)) {
		if (steps % 10000000 == 0)
			cout << endl << steps;

		for (int mainMoon = 0; mainMoon < antalM�nar; mainMoon++)
			for (int subMoon = mainMoon + 1; subMoon < antalM�nar; subMoon++)
				applyGravity(&m�nar[mainMoon], &m�nar[subMoon]);

		for (int j = 0; j < antalM�nar; j++) {
			applyVelocity(&m�nar[j]);
			calculateEnergy(&m�nar[j]);
		}

		//kopia = new state[numberOfStates + 1];

		//for (int i = 0; i < numberOfStates; i++)//Kopierar nuvarande
		//	kopia[i] = states[i];

		//if(states != nullptr)
		//	delete[] states;

		//states = kopia;

		for (int i = 0; i < 4; i++)//Den nytillagda g�rs till en kopia
			states[1].m�nar[i] = m�nar[i];

		numberOfStates++;
		steps++;
	}

	cout << "\nDen upprepade �r:\n";
	for (int i = 0; i < 4; i++) {
		displayMoon(&m�nar[i]);
		cout << endl;
	}
	cout << "\nDetta efter " << steps << " steg";

	delete[] m�nar;
}

moon buildMoon(void) {
	moon m�ne;
	char analyser = NULL;

	while (analyser != '<')
		cin >> analyser;
	for (int j = 0; j < 3; j++) {
		cin >> analyser; //F�rsta v�rdet i serien;
		switch (analyser)
		{
		case 'x':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktigt skrift f�r x";
			cin >> m�ne.x;
			break;
		case 'y':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktit skrift f�r y";
			cin >> m�ne.y;
			break;
		case 'z':
			cin >> analyser;
			if (analyser != '=')
				cout << "Error! Felaktit skrift f�r z";
			cin >> m�ne.z;
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

	return(m�ne);
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

	if (states == nullptr or comparator == nullptr or numberOfStates == 1) //Om det inte �r n�got att j�mf�ra
		return(false);

	for (int currentState = 0; currentState < 1; currentState++) {//Genomf�r flera test, alla m�ste klaras f�r att vara identiska
		for (int currentMoon = 0; currentMoon < 4; currentMoon++)//Kollar om energin �r densamma
			if (comparator->m�nar[currentMoon].totalEnergy != states[currentState].m�nar[currentMoon].totalEnergy) {
				hasFailed = true;
				break;
			}

		if (!hasFailed)//Kollar om allas positioner �r de samma
			for (int currentMoon = 0; currentMoon < 4; currentMoon++)
				if ((comparator->m�nar[currentMoon].x != states[currentState].m�nar[currentMoon].x) or (comparator->m�nar[currentMoon].y != states[currentState].m�nar[currentMoon].y) or (comparator->m�nar[currentMoon].z != states[currentState].m�nar[currentMoon].z)) {
					hasFailed = true;
					break;
				}

		if (!hasFailed)//Kollar om allas hastighet �r samma
			for (int currentMoon = 0; currentMoon < 4; currentMoon++)
				if ((comparator->m�nar[currentMoon].vx != states[currentState].m�nar[currentMoon].vx) or (comparator->m�nar[currentMoon].vy != states[currentState].m�nar[currentMoon].vy) or (comparator->m�nar[currentMoon].vz != states[currentState].m�nar[currentMoon].vz)) {
					hasFailed = true;
					break;
				}

		if (!hasFailed) {//Om den klarar alla testen �r de samma
			cout << "\nUpprepning funnen! " << numberOfStates - 1 << " = " << currentState;
			return(true);
		}

	}
	return(false);//Om den n�dde hit, klarade inget fulltest, s� �r den fel
}