#include <iostream>

using namespace::std;

const int Instruktioner = 301; //Antalet intstruktioner f�r en kabel


struct punkt {
	int x = 0;
	int y = 0;
};

struct kabel {
	punkt* v�g = nullptr; //En lista med alla koor-dinater den passerar
	int nuvarandeL�ngd = 0; //Antalet element
	int maxL�ngd = 50; //Antalet element som f�r plats
};

struct instruktion {
	char typ; //Riktning p� ordern
	int l�ngd; //L�ngd p� ordern
};

kabel byggKabel(instruktion inst[]);

kabel hittaM�ten(kabel a, kabel b);

int ber�knaAvst�nd(punkt a, punkt b);

int j�mf�r(punkt p1, punkt p2);

kabel sortera(kabel offer);


int main(){
	instruktion* inst = new instruktion[Instruktioner];

	kabel kabel1;
	kabel kabel2;
	kabel m�ten;

	int minL�ngd = INFINITY;
	int nuvarandeL�ngd = 0;

	punkt startpunkt;
	punkt m�tespunkt;

	cout << "Vad �r den f�rstas instruktioner?";

	for (int i = 0; i < Instruktioner; i++) { //Tar lika m�nga instruktioner som varje best�r av
		inst[i].typ = getchar(); //Tar bokstaven
		cin >> inst[i].l�ngd; //Tar siffran
		getchar(); //Sl�nger kommatecknet
	}

	cout << "\nBygger den f�rsta.";

	kabel1 = byggKabel(inst);

	cout << "\nVad �r den andras instruktioner?";

	for (int i = 0; i < Instruktioner; i++) {
		inst[i].typ = getchar();
		cin >> inst[i].l�ngd;
		getchar(); //Sl�nger kommatecknet
	}
	
	cout << "\nBygger den andra.";

	kabel2 = byggKabel(inst);

	cout << "\nKabel1[0] = [" << kabel1.v�g[0].x << "][" << kabel1.v�g[0].y << "], kabel2[0] = [" << kabel2.v�g[0].x << "][" << kabel2.v�g[0].y << "]";

	cout << "\nOrdnar b�da tv�.";

	kabel1 = sortera(kabel1);

	for (int i = 0; i < kabel1.nuvarandeL�ngd; i++) {

	}

	cout << "Klar med f�rsta";

	kabel2 = sortera(kabel2);

	cout << "\nKabel1[0] = [" << kabel1.v�g[0].x << "][" << kabel1.v�g[0].y << "], kabel2[0] = [" << kabel2.v�g[0].x << "][" << kabel2.v�g[0].y << "]";

	cout << "\n\nLetar upp var de matchar";

	m�ten=hittaM�ten(kabel1, kabel2);

	cout << "\n\nBer�knar vilken som �r den minsta l�ngden\n\n";

	for (int x = 0; x < m�ten.nuvarandeL�ngd; x++) {
				nuvarandeL�ngd = ber�knaAvst�nd(m�ten.v�g[x], startpunkt);

				if (nuvarandeL�ngd < minL�ngd and nuvarandeL�ngd != 0)
				{
					cout << "\nNytt min hittat: ";

					minL�ngd = nuvarandeL�ngd;
					cout << minL�ngd << endl;
				}
	}
	cout << "\n\n Det n�rmaste m�tet var p� avst�ndet: " << minL�ngd;



	delete[] kabel1.v�g;
	delete[] kabel2.v�g;
	delete[] m�ten.v�g;
	delete[] inst;
}


kabel byggKabel(instruktion inst[Instruktioner]){
	kabel bygge;
	bygge.v�g = new punkt[50];
	punkt* nytt;

	for (int i = 0; i < Instruktioner; i++) {
		if (bygge.nuvarandeL�ngd = bygge.maxL�ngd) {//Kopierar �ver till en ny array om det blir fullt
			nytt = new punkt[bygge.maxL�ngd + 50];
				for (int j = 0; j < bygge.nuvarandeL�ngd; j++){
						nytt[j].x = bygge.v�g[j].x;
						nytt[j].y = bygge.v�g[j].y;
			}
				delete[] bygge.v�g;
				bygge.v�g = nytt;
				bygge.maxL�ngd += 50;
		}

		switch (inst[i].typ) {
		case 'U':
			for (int j = 1; j <= inst[i].l�ngd; j++) {
				bygge.v�g[bygge.nuvarandeL�ngd].x = bygge.v�g[bygge.nuvarandeL�ngd - 1].x; //Beh�ller x-v�rdet
				bygge.v�g[bygge.nuvarandeL�ngd].y = bygge.v�g[bygge.nuvarandeL�ngd - 1].y + 1; //�kar y-v�rdet
			}
			bygge.nuvarandeL�ngd++;
			break;
		case 'D':
			for (int j = 1; j <= inst[i].l�ngd; j++) {
				bygge.v�g[bygge.nuvarandeL�ngd].x = bygge.v�g[bygge.nuvarandeL�ngd - 1].x; //Beh�ller x-v�rdet
				bygge.v�g[bygge.nuvarandeL�ngd].y = bygge.v�g[bygge.nuvarandeL�ngd - 1].y - 1; //Minskar y-v�rdet
			}
			bygge.nuvarandeL�ngd++;
			break;
		case 'R':
			for (int j = 1; j <= inst[i].l�ngd; j++) {
				bygge.v�g[bygge.nuvarandeL�ngd].x = bygge.v�g[bygge.nuvarandeL�ngd - 1].x +1; //�kar x-v�rdet
				bygge.v�g[bygge.nuvarandeL�ngd].y = bygge.v�g[bygge.nuvarandeL�ngd - 1].y; //Beh�ller y-v�rdet
			}
			bygge.nuvarandeL�ngd++;
			break;
		case 'L':
			for (int j = 1; j <= inst[i].l�ngd; j++) {
				bygge.v�g[bygge.nuvarandeL�ngd].x = bygge.v�g[bygge.nuvarandeL�ngd - 1].x - 1; //Minskar x-v�rdet
				bygge.v�g[bygge.nuvarandeL�ngd].y = bygge.v�g[bygge.nuvarandeL�ngd - 1].y; //Beh�ller y-v�rdet
			}
			bygge.nuvarandeL�ngd++;
			break;
		}
	}

	return(bygge);
}

kabel hittaM�ten(kabel a, kabel b) {//M�STE vara sorterade
	kabel m�ten;
	m�ten.v�g = new punkt[50];
	punkt* nytt;
	
	int positionA = 0;
	int positionB = 0;

	cout << "\nS�ker m�ten\n";

	//Bygger p� att de kommer i storleksordning i b�da, s� att om a.v�g[x] < b.v�g[y] s� �r alla a.v�g[k] < b.v�g d� k<x, 
	//d�rav att detta fungerar, bara �ka den som �r mindre.
	while (positionA < a.nuvarandeL�ngd and positionB< b.nuvarandeL�ngd){//Fors�tter tills alla v�rden i en av kablarna kollats
		switch (j�mf�r(a.v�g[positionA], b.v�g[positionB])) {
		case -1: //Om a:s �r mindre �n b:s
			positionA++; //D� �kar a tills dess att den n�rmar sig
			break;
		case 0: //Om de �r lika, dvs de har m�te
			if (m�ten.nuvarandeL�ngd = m�ten.maxL�ngd) {//�kar arrayens storlek n�r den blir full
				nytt = new punkt[m�ten.maxL�ngd + 50];
				for (int j = 0; j < m�ten.nuvarandeL�ngd; j++) {//Skapar en kopia av m�tes v�g, som har 50 tomma platser i slutet
					nytt[j].x = m�ten.v�g[j].x;
					nytt[j].y = m�ten.v�g[j].y;
				}
				delete[] m�ten.v�g; //Tar bort m�tes v�g
				m�ten.v�g = nytt; //Ger den dess l�ngre kopia ist�llet
				m�ten.maxL�ngd += 50;
			}//F�rl�nger vid behov m�ten
			
			cout << " [" << positionA << "][" << positionB << "] ";

			m�ten.v�g[m�ten.nuvarandeL�ngd].x = a.v�g[positionA].x; //Godtyckligt vilken som anv�nds, 
			m�ten.v�g[m�ten.nuvarandeL�ngd].y = a.v�g[positionA].y; //de �r trots allt lika
			positionA++;
			break;
		case 1: //Om b �r mindre
			positionB++; //b �kar f�r att �ndra sig
			break;
		}
	}
	return(m�ten);
}

int ber�knaAvst�nd(punkt a, punkt b) {
	int x = abs(a.x - b.x);
	int y = abs(a.y - b.y);

	return(x + y);
}

int j�mf�r(punkt p1, punkt p2) //Skickar en 1a om den f�rsta �r st�rre, -1a om 2a, och 0 om lika
{ //Prioriterar X f�rst och sen Y
	if (p1.x < p2.x)
		return(-1);
	else if (p1.x > p2.x)
		return(1);
	else if (p1.y < p2.y)
		return(-1);
	else if (p1.y > p2.y)
		return(1);
	else
		return(0);
}

kabel sortera(kabel osorterad) {
	kabel sorterad;
	sorterad.v�g = new punkt[osorterad.nuvarandeL�ngd];
	sorterad.maxL�ngd = osorterad.nuvarandeL�ngd;
	sorterad.nuvarandeL�ngd = osorterad.nuvarandeL�ngd;

	int antalMindre = 0; //Antalet vektorer som �r mindre, dessa ska va till v�nster om den som j�mf�rs
	int lika = 0;

	for (int i = 0; i < osorterad.nuvarandeL�ngd; i++) {
		for (int j = 0; j < osorterad.nuvarandeL�ngd; j++) {
			switch (j�mf�r(osorterad.v�g[i], osorterad.v�g[j])) {
			case -1:  //Om den som j�mf�rs �r mindre sker inget
				break;
			case 0: //Om de �r lika l�ggs en lika till
				lika++;
				break;
			case 1: //Om den �r st�rre s� �kar antalMindre
				antalMindre++;
				break;
			}
		}
		for (int j = 0; j < lika; j++) {//Den s�tter lika m�nga som antalet lika (skrivs �ver varje g�ng en nya av de lika kommer)
			sorterad.v�g[antalMindre + j].x = osorterad.v�g[i].x; //Platsen v�rdet ska ligga p� �r samma som antalet den slagit
			sorterad.v�g[antalMindre + j].y = osorterad.v�g[i].y; //Ty f�rsta platsen �r noll, sen ett v�rde per lika. T�nk p�'t.
		}

		antalMindre = 0;
		lika = 0;
	}
	return(sorterad);
}