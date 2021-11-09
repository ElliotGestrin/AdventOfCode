#include <iostream>

using namespace::std;

struct asteroid {
	int x = 0;
	int y = 0;
	int visibleAsteroids = 0;
};

asteroid createAsteroid(int x, int y);
double asteroidAngle(asteroid dom, asteroid sub);
asteroid* increaseAsteroids(asteroid*, int* activeAsteroids, int* maxAsteroids);


int main() {
	char analyser = NULL;

	asteroid *asteroids;
	asteroids = new asteroid[20];
	int activeAsteroids = 0;
	int maxAsteroids = 20;
	asteroid* best = &asteroids[0];

	int x = 0;
	int y = 0;

	cout << "Langa asteroiderna:\n";
	analyser = getchar();
	while (analyser != '!') {//Samlar in datan
		switch (analyser){
		case '#':
			if (activeAsteroids == maxAsteroids)
				asteroids = increaseAsteroids(asteroids, &activeAsteroids, &maxAsteroids);
			asteroids[activeAsteroids++] = createAsteroid(x, y);
			x++;
			break;
		case '.':
			x++;
			break;
		case '\n':
			x = 0;
			y++;
			break;
		default:
			cout << "ERROR! Felaktigt tecken!";
			break;
		}
		analyser = getchar();
	}

	cout << "\nUppfattat asteroidfält:\n";
	
	int activeX = 0;
	int activeY = 0;
	for (int i = 0; i < activeAsteroids; i++) {
		while (asteroids[i].y != activeY) {
			cout << endl;
			activeY++;
			activeX = 0;
		}
		while (asteroids[i].x > activeX) {
			cout << ".";
			activeX++;
		}
		cout << "#";
		activeX++;
	}

	for (int mainAsteroid = 0; mainAsteroid < activeAsteroids; mainAsteroid++) {//Ger dem antalet asteroider de kan se
		double* angles = new double[activeAsteroids];
		bool matchingAngle = false;

		for (int subAsteroid = 0; subAsteroid < activeAsteroids; subAsteroid++) 
			angles[subAsteroid] = asteroidAngle(asteroids[mainAsteroid], asteroids[subAsteroid]);

		for (int mainAngle = 0; mainAngle < activeAsteroids; mainAngle++) {//För varje vinkel
			if (!isnan(angles[mainAngle])) {//Då den inte är sig själv
				for (int subAngle = mainAngle + 1; subAngle < activeAsteroids; subAngle++)//Kollar den alla efterföljande vinklar
					if (angles[mainAngle] == angles[subAngle]) {//Om samma hittas
						matchingAngle = true;
						break; //Ingen mening med att leta vidare
					}
				if (!matchingAngle) //Om den inte krockade med någon annan
					asteroids[mainAsteroid].visibleAsteroids++;
				matchingAngle = false;
			}
		}

		delete[] angles;
	}

	activeX = 0;
	activeY = 0;
	cout << endl << endl;
	for (int i = 0; i < activeAsteroids; i++) {//Visar alla asteroiderna
		while (asteroids[i].y != activeY) {
			cout << endl;
			activeY++;
			activeX = 0;
		}
		while (asteroids[i].x > activeX) {
			cout << ".";
			if(activeAsteroids > 10)
				cout << ".";
			if (activeAsteroids > 100)
				cout << ".";
			activeX++;
			cout << " ";
		}
		cout << asteroids[i].visibleAsteroids;
		activeX++;
		cout << " ";
	}

	for (int i = 0; i < activeAsteroids; i++)//Hittar den bästa
		if (asteroids[i].visibleAsteroids > best->visibleAsteroids)
			best = &asteroids[i];

	cout << "\n\nDen bästa asteroiden är på position [" << best->x << "][" << best->y << "] med " << best->visibleAsteroids << " synliga astroider\n\n";
}

double asteroidAngle(asteroid dom, asteroid sub) {
	const double pi = 3.14159265358979323846;

	double deltaX = double(sub.x) - double(dom.x);
	double deltaY = double(dom.y)  - double(sub.y);
	double angle = 0;


	if (deltaX != 0) //Hittar vinkeln
		angle = atan(deltaY/deltaX);
	else {
		if (deltaY > 0)
			angle = pi / 2;
		else if (deltaY < 0)
			angle = -(pi / 2);
		else//De är samma asteroid
			angle = NAN;
	}

	if (deltaX < 0) {//Om den ska va i kvadrant 2 eller 3 så adderas det
		angle += pi;
	}
	return(angle);
}


asteroid createAsteroid(int x, int y) {
	asteroid newAsteroid;

	newAsteroid.x = x;
	newAsteroid.y = y;

	return(newAsteroid);
}


asteroid* increaseAsteroids(asteroid* asteroids, int* activeAsteroids, int* maxAsteroids){
	asteroid* temp = new asteroid[*maxAsteroids + 10];
	
	*maxAsteroids += 10;

	for (int i = 0; i < *activeAsteroids; i++)
		temp[i] = asteroids[i];
	
	delete[] asteroids;

	return(temp);
}
