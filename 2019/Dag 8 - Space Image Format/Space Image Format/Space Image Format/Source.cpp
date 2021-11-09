#include <iostream>

using namespace::std;

int main() {
	struct layer {
		int** inneh�ll;
	};
	layer* lager;
	layer* kopia;
	int lagerNummer = 1;

	int bredd = 0;
	int h�jd = 0;
	int l�ngd = 0;

	cout << "Hur bred �r bilden? ";
	cin >> bredd;

	cout << "\nHur h�g �r bilden? ";
	cin >> h�jd;

	cout << "\nHur l�ng �r datan? ";
	cin >> l�ngd;

	lager = new	layer[lagerNummer];

	for (int j = 0; j < lagerNummer; j++) { //Lagers alla nya lager g�rs s� att de fins
		lager[j].inneh�ll = new int* [h�jd];
		for (int k = 0; k < h�jd; k++)
			lager[j].inneh�ll[k] = new int[bredd];
	}

		
	for (int j = 0; j < h�jd; j++) //Tar in v�rdet
		for (int k = 0; k < bredd; k++)
			lager[lagerNummer].inneh�ll[j][k] = 0;

	cout << "\nLanga image datan:\n";
	for (int i = 0; i < l�ngd; i++) {
		for (int j = 0; j < h�jd; j++) //Tar in v�rdet
			for (int k = 0; k < bredd; k++)
				cin >> lager[lagerNummer].inneh�ll[j][k];
		
		if (i % (bredd * h�jd) == (bredd * h�jd) - 1) {//Om lagret �r fullt
			kopia = new layer[lagerNummer + 1]; //Kopia f�r ytterligare ett lager

			for (int j = 0; j < lagerNummer + 1; j++) { //Lagers alla nya lager g�rs s� att de fins
				kopia[j].inneh�ll = new int* [h�jd];
				for (int k = 0; k < h�jd; k++)
					kopia[j].inneh�ll[k] = new int[bredd];
			}

			for (int j = 0; j < lagerNummer; j++) { //Kopias alla nya lager g�rs s� att de fins
				kopia[j].inneh�ll = new int* [h�jd];
				for (int k = 0; k < h�jd; k++)
					kopia[j].inneh�ll[k] = new int[bredd];
			}

			if (lagerNummer != 0)
				for (int j = 0; j < lagerNummer; j++) //Kopias lager g�rs till kopior av lagers
					for (int k = 0; k < h�jd; k++)
						for (int l = 0; l < bredd; l++)
							kopia[j].inneh�ll[k][l] = lager[j].inneh�ll[k][l];

			for (int j = 0; j < lagerNummer; j++) { //Alla lagers delar f�rst�rs
				for (int k = 0; k < h�jd; k++)
					delete[] lager[j].inneh�ll[k];
				delete[] lager[j].inneh�ll;
			}

			lager = kopia; //Lager tar �ver kopia 

			lagerNummer++; //Lagernummer kommer sluta ett h�gre �n det faktiskt �r, eller snarare samma
		}
	}

	for (int nuvarandeLager = 0; nuvarandeLager < lagerNummer; nuvarandeLager++) {
		cout << nuvarandeLager << ":  ";
		for (int nuvarandeH�jd = 0; nuvarandeH�jd < h�jd; nuvarandeH�jd++) {
			cout << endl;
			for (int nuvarandeBredd = 0; nuvarandeBredd < bredd; nuvarandeBredd++)
				cout << lager[nuvarandeLager].inneh�ll[nuvarandeH�jd][nuvarandeBredd] << " ";
		}
	}

	for (int j = 0; j < lagerNummer; j++) { //Alla lagers delar f�rst�rs
		for (int k = 0; k < h�jd; k++)
			delete[] lager[j].inneh�ll[k];
		delete[] lager[j].inneh�ll;
	}
}