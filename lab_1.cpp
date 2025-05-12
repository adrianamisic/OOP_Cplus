#include <iostream>
using namespace std;

void myswap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubblesort(int b[], int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m - i; j++) {
            if (b[j] > b[j + 1])		//Aufsteigend
                myswap(b[j], b[j + 1]);
        }
    }
}

int main() {

	//Eingabe
	const int n=12;
	int a[n]; // Arraygröße und Array initialisiert
	cout << "Gebe 12 Integerzahlen an:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> a[i]; //Array befüllen
    }

    //Sortierung
    bubblesort(a,n);

	//Ausgabe
    cout << "Sortierte Zahlen:" << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }


    return 0;
}
