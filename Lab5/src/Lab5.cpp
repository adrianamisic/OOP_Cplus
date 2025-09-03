//============================================================================
// Name        : Lab5.cpp
// Author      : 
// Version     :
// Description : Hello World in C++, Ansi-style
//============================================================================

//Was fehlt: 1. >> bei aktuellen Knoten, 2. Funktionsaufruf

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Stammbaum.h" // Annahme: Hier befindet sich die Deklaration von Stammbaum und Knoten

using namespace std;

enum Type {
	NAVI, SAVE, ADD, READ, ERROR, ENDE
};

Type CheckInputType(string input) {
	if (input.length() == 1
			&& (input[0] == 'r' || input[0] == 'v' || input[0] == 'm'))
		return ADD;
	else if (input.length() == 1 && (input[0] == 's'))
		return SAVE;
	else if (input.length() == 1 && (input[0] == 'f'))
		return READ;
	else if (input.length() == 1
			&& (input[0] == 'd' || input[0] == 'a' || input[0] == 'w'))
		return NAVI;
	else if (input.length() == 1 && (input[0] == 'q'))
		return ENDE;
	else {
		return ERROR;
	}
}

int main() {
	string Input; // Hier nur ein String benötigt, nicht ein Array von Strings
	string vorN;
	string nachN;
	// Annahme: Deklaration der Klasse Knoten
	Stammbaum stamm;  // Annahme: Deklaration der Klasse Stammbaum

	cout << "---------Stammbaumgenerator---------" << endl;

	while (true) {
		stamm.printTree();
		cout << "\nMenu:\n";
		cout << "r - Erstellen eines Wurzelknotens\n";
		cout << "v - Hinzufügen Vater zu aktuellem Knoten\n";
		cout << "m - Hinzufügen Mutter zu aktuellem Knoten\n";
		cout << "d - Navigation: gehe nach unten zu Vater\n";
		cout << "a - Navigation: gehe nach unten zu Mutter\n";
		cout << "w - Navigation: gehe eine Ebene nach oben zu Nachfahre\n";
		cout << "q - Beenden\n";
		cout << "Befehl:" << endl;
		cin >> Input;

		Type type = CheckInputType(Input);

		switch (type) {
		case ADD:
			if (Input == "r") { // Anchor/Kind hinzufügen
				cout << "Vorname des letzten Familienmitglieds:" << endl;
				cin >> vorN;
				cout << "Nachname des letzten Familienmitglieds:" << endl;
				cin >> nachN;
				stamm.neuKind(vorN, nachN);

				cout << "Nach ADD - Stammbaum ausgegeben" << endl;

			} else if (Input == "m") { // Mutter hinzufügen
				cout << "Vorname der Mutter:" << endl;
				cin >> vorN;
				cout << "Nachname der Mutter:" << endl;
				cin >> nachN;
				stamm.neuMutter(vorN, nachN);

				cout << "Nach ADD - Stammbaum ausgegeben" << endl;

			} else if (Input == "v") { // Vater hinzufügen
				cout << "Vorname des Vaters:" << endl;
				cin >> vorN;
				cout << "Nachname des Vaters:" << endl;
				cin >> nachN;
				stamm.neuVater(vorN, nachN);

				cout << "Nach ADD - Stammbaum ausgegeben" << endl;
			} else {
				cout << "Fehler im Case ADD" << endl;
			}
			break;
		case NAVI:
			if (Input == "d") {
				stamm.Navi2Vater();				//wird nicht ausgeführt bzw. kp

			} else if (Input == "a") {
				stamm.Navi2Mutter();
				stamm.printTree();						//wird nicht ausgeführt
			} else if (Input == "w") {
				stamm.NaviUp();

			} else {
				cout << "Fehler im Case NAVI" << endl;

			}
			break;
		case SAVE:
			stamm.SaveToFile();							//wird nicht ausgeführt

			cout << "Stammbaum wurde gespeichert" << endl;
			break;
		case READ:
			stamm.LoadFromFile();

			cout << "Stammbaum wurde gelesen." << endl;
			break;
		case ENDE:
			return 0;
			break;
		case ERROR:
			cout << "Fehler im Switch-Case / Input Type" << endl;

			break;
		}
	}

	return 0;
}
