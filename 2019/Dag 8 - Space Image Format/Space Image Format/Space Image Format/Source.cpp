#include <iostream>

using namespace::std;

int main() {
	struct layer {
		int** innehåll;
	};
	layer* lager;
	layer* kopia;
	int lagerNummer = 1;

	int bredd = 0;
	int höjd = 0;
	int längd = 0;

	cout << "Hur bred är bilden? ";
	cin >> bredd;

	cout << "\nHur hög är bilden? ";
	cin >> höjd;

	cout << "\nHur lång är datan? ";
	cin >> längd;

	lager = new	layer[lagerNummer];

	for (int j = 0; j < lagerNummer; j++) { //Lagers alla nya lager görs så att de fins
		lager[j].innehåll = new int* [höjd];
		for (int k = 0; k < höjd; k++)
			lager[j].innehåll[k] = new int[bredd];
	}

		
	for (int j = 0; j < höjd; j++) //Tar in värdet
		for (int k = 0; k < bredd; k++)
			lager[lagerNummer].innehåll[j][k] = 0;

	cout << "\nLanga image datan:\n";
	for (int i = 0; i < längd; i++) {
		for (int j = 0; j < höjd; j++) //Tar in värdet
			for (int k = 0; k < bredd; k++)
				cin >> lager[lagerNummer].innehåll[j][k];
		
		if (i % (bredd * höjd) == (bredd * höjd) - 1) {//Om lagret är fullt
			kopia = new layer[lagerNummer + 1]; //Kopia får ytterligare ett lager

			for (int j = 0; j < lagerNummer + 1; j++) { //Lagers alla nya lager görs så att de fins
				kopia[j].innehåll = new int* [höjd];
				for (int k = 0; k < höjd; k++)
					kopia[j].innehåll[k] = new int[bredd];
			}

			for (int j = 0; j < lagerNummer; j++) { //Kopias alla nya lager görs så att de fins
				kopia[j].innehåll = new int* [höjd];
				for (int k = 0; k < höjd; k++)
					kopia[j].innehåll[k] = new int[bredd];
			}

			if (lagerNummer != 0)
				for (int j = 0; j < lagerNummer; j++) //Kopias lager görs till kopior av lagers
					for (int k = 0; k < höjd; k++)
						for (int l = 0; l < bredd; l++)
							kopia[j].innehåll[k][l] = lager[j].innehåll[k][l];

			for (int j = 0; j < lagerNummer; j++) { //Alla lagers delar förstörs
				for (int k = 0; k < höjd; k++)
					delete[] lager[j].innehåll[k];
				delete[] lager[j].innehåll;
			}

			lager = kopia; //Lager tar över kopia 

			lagerNummer++; //Lagernummer kommer sluta ett högre än det faktiskt är, eller snarare samma
		}
	}

	for (int nuvarandeLager = 0; nuvarandeLager < lagerNummer; nuvarandeLager++) {
		cout << nuvarandeLager << ":  ";
		for (int nuvarandeHöjd = 0; nuvarandeHöjd < höjd; nuvarandeHöjd++) {
			cout << endl;
			for (int nuvarandeBredd = 0; nuvarandeBredd < bredd; nuvarandeBredd++)
				cout << lager[nuvarandeLager].innehåll[nuvarandeHöjd][nuvarandeBredd] << " ";
		}
	}

	for (int j = 0; j < lagerNummer; j++) { //Alla lagers delar förstörs
		for (int k = 0; k < höjd; k++)
			delete[] lager[j].innehåll[k];
		delete[] lager[j].innehåll;
	}
}