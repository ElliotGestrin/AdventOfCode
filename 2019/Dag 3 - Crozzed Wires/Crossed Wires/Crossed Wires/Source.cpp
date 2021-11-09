#include <iostream>

using namespace::std;

const int Instruktioner = 301; //Antalet intstruktioner för en kabel


struct punkt {
	int x = 0;
	int y = 0;
};

struct kabel {
	punkt* väg = nullptr; //En lista med alla koor-dinater den passerar
	int nuvarandeLängd = 0; //Antalet element
	int maxLängd = 50; //Antalet element som får plats
};

struct instruktion {
	char typ; //Riktning på ordern
	int längd; //Längd på ordern
};

kabel byggKabel(instruktion inst[]);

kabel hittaMöten(kabel a, kabel b);

int beräknaAvstånd(punkt a, punkt b);

int jämför(punkt p1, punkt p2);

kabel sortera(kabel offer);


int main(){
	instruktion* inst = new instruktion[Instruktioner];

	kabel kabel1;
	kabel kabel2;
	kabel möten;

	int minLängd = INFINITY;
	int nuvarandeLängd = 0;

	punkt startpunkt;
	punkt mötespunkt;

	cout << "Vad är den förstas instruktioner?";

	for (int i = 0; i < Instruktioner; i++) { //Tar lika många instruktioner som varje består av
		inst[i].typ = getchar(); //Tar bokstaven
		cin >> inst[i].längd; //Tar siffran
		getchar(); //Slänger kommatecknet
	}

	cout << "\nBygger den första.";

	kabel1 = byggKabel(inst);

	cout << "\nVad är den andras instruktioner?";

	for (int i = 0; i < Instruktioner; i++) {
		inst[i].typ = getchar();
		cin >> inst[i].längd;
		getchar(); //Slänger kommatecknet
	}
	
	cout << "\nBygger den andra.";

	kabel2 = byggKabel(inst);

	cout << "\nKabel1[0] = [" << kabel1.väg[0].x << "][" << kabel1.väg[0].y << "], kabel2[0] = [" << kabel2.väg[0].x << "][" << kabel2.väg[0].y << "]";

	cout << "\nOrdnar båda två.";

	kabel1 = sortera(kabel1);

	for (int i = 0; i < kabel1.nuvarandeLängd; i++) {

	}

	cout << "Klar med första";

	kabel2 = sortera(kabel2);

	cout << "\nKabel1[0] = [" << kabel1.väg[0].x << "][" << kabel1.väg[0].y << "], kabel2[0] = [" << kabel2.väg[0].x << "][" << kabel2.väg[0].y << "]";

	cout << "\n\nLetar upp var de matchar";

	möten=hittaMöten(kabel1, kabel2);

	cout << "\n\nBeräknar vilken som är den minsta längden\n\n";

	for (int x = 0; x < möten.nuvarandeLängd; x++) {
				nuvarandeLängd = beräknaAvstånd(möten.väg[x], startpunkt);

				if (nuvarandeLängd < minLängd and nuvarandeLängd != 0)
				{
					cout << "\nNytt min hittat: ";

					minLängd = nuvarandeLängd;
					cout << minLängd << endl;
				}
	}
	cout << "\n\n Det närmaste mötet var på avståndet: " << minLängd;



	delete[] kabel1.väg;
	delete[] kabel2.väg;
	delete[] möten.väg;
	delete[] inst;
}


kabel byggKabel(instruktion inst[Instruktioner]){
	kabel bygge;
	bygge.väg = new punkt[50];
	punkt* nytt;

	for (int i = 0; i < Instruktioner; i++) {
		if (bygge.nuvarandeLängd = bygge.maxLängd) {//Kopierar över till en ny array om det blir fullt
			nytt = new punkt[bygge.maxLängd + 50];
				for (int j = 0; j < bygge.nuvarandeLängd; j++){
						nytt[j].x = bygge.väg[j].x;
						nytt[j].y = bygge.väg[j].y;
			}
				delete[] bygge.väg;
				bygge.väg = nytt;
				bygge.maxLängd += 50;
		}

		switch (inst[i].typ) {
		case 'U':
			for (int j = 1; j <= inst[i].längd; j++) {
				bygge.väg[bygge.nuvarandeLängd].x = bygge.väg[bygge.nuvarandeLängd - 1].x; //Behåller x-värdet
				bygge.väg[bygge.nuvarandeLängd].y = bygge.väg[bygge.nuvarandeLängd - 1].y + 1; //Ökar y-värdet
			}
			bygge.nuvarandeLängd++;
			break;
		case 'D':
			for (int j = 1; j <= inst[i].längd; j++) {
				bygge.väg[bygge.nuvarandeLängd].x = bygge.väg[bygge.nuvarandeLängd - 1].x; //Behåller x-värdet
				bygge.väg[bygge.nuvarandeLängd].y = bygge.väg[bygge.nuvarandeLängd - 1].y - 1; //Minskar y-värdet
			}
			bygge.nuvarandeLängd++;
			break;
		case 'R':
			for (int j = 1; j <= inst[i].längd; j++) {
				bygge.väg[bygge.nuvarandeLängd].x = bygge.väg[bygge.nuvarandeLängd - 1].x +1; //Ökar x-värdet
				bygge.väg[bygge.nuvarandeLängd].y = bygge.väg[bygge.nuvarandeLängd - 1].y; //Behåller y-värdet
			}
			bygge.nuvarandeLängd++;
			break;
		case 'L':
			for (int j = 1; j <= inst[i].längd; j++) {
				bygge.väg[bygge.nuvarandeLängd].x = bygge.väg[bygge.nuvarandeLängd - 1].x - 1; //Minskar x-värdet
				bygge.väg[bygge.nuvarandeLängd].y = bygge.väg[bygge.nuvarandeLängd - 1].y; //Behåller y-värdet
			}
			bygge.nuvarandeLängd++;
			break;
		}
	}

	return(bygge);
}

kabel hittaMöten(kabel a, kabel b) {//MÅSTE vara sorterade
	kabel möten;
	möten.väg = new punkt[50];
	punkt* nytt;
	
	int positionA = 0;
	int positionB = 0;

	cout << "\nSöker möten\n";

	//Bygger på att de kommer i storleksordning i båda, så att om a.väg[x] < b.väg[y] så är alla a.väg[k] < b.väg då k<x, 
	//därav att detta fungerar, bara öka den som är mindre.
	while (positionA < a.nuvarandeLängd and positionB< b.nuvarandeLängd){//Forsätter tills alla värden i en av kablarna kollats
		switch (jämför(a.väg[positionA], b.väg[positionB])) {
		case -1: //Om a:s är mindre än b:s
			positionA++; //Då ökar a tills dess att den närmar sig
			break;
		case 0: //Om de är lika, dvs de har möte
			if (möten.nuvarandeLängd = möten.maxLängd) {//Ökar arrayens storlek när den blir full
				nytt = new punkt[möten.maxLängd + 50];
				for (int j = 0; j < möten.nuvarandeLängd; j++) {//Skapar en kopia av mötes väg, som har 50 tomma platser i slutet
					nytt[j].x = möten.väg[j].x;
					nytt[j].y = möten.väg[j].y;
				}
				delete[] möten.väg; //Tar bort mötes väg
				möten.väg = nytt; //Ger den dess längre kopia istället
				möten.maxLängd += 50;
			}//Förlänger vid behov möten
			
			cout << " [" << positionA << "][" << positionB << "] ";

			möten.väg[möten.nuvarandeLängd].x = a.väg[positionA].x; //Godtyckligt vilken som används, 
			möten.väg[möten.nuvarandeLängd].y = a.väg[positionA].y; //de är trots allt lika
			positionA++;
			break;
		case 1: //Om b är mindre
			positionB++; //b ökar för att ändra sig
			break;
		}
	}
	return(möten);
}

int beräknaAvstånd(punkt a, punkt b) {
	int x = abs(a.x - b.x);
	int y = abs(a.y - b.y);

	return(x + y);
}

int jämför(punkt p1, punkt p2) //Skickar en 1a om den första är större, -1a om 2a, och 0 om lika
{ //Prioriterar X först och sen Y
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
	sorterad.väg = new punkt[osorterad.nuvarandeLängd];
	sorterad.maxLängd = osorterad.nuvarandeLängd;
	sorterad.nuvarandeLängd = osorterad.nuvarandeLängd;

	int antalMindre = 0; //Antalet vektorer som är mindre, dessa ska va till vänster om den som jämförs
	int lika = 0;

	for (int i = 0; i < osorterad.nuvarandeLängd; i++) {
		for (int j = 0; j < osorterad.nuvarandeLängd; j++) {
			switch (jämför(osorterad.väg[i], osorterad.väg[j])) {
			case -1:  //Om den som jämförs är mindre sker inget
				break;
			case 0: //Om de är lika läggs en lika till
				lika++;
				break;
			case 1: //Om den är större så ökar antalMindre
				antalMindre++;
				break;
			}
		}
		for (int j = 0; j < lika; j++) {//Den sätter lika många som antalet lika (skrivs över varje gång en nya av de lika kommer)
			sorterad.väg[antalMindre + j].x = osorterad.väg[i].x; //Platsen värdet ska ligga på är samma som antalet den slagit
			sorterad.väg[antalMindre + j].y = osorterad.väg[i].y; //Ty första platsen är noll, sen ett värde per lika. Tänk på't.
		}

		antalMindre = 0;
		lika = 0;
	}
	return(sorterad);
}