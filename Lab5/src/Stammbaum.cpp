/*
 * Stammbaum.cpp
 *
 *  Created on: 21.06.2024
 *      Author: Adriana Misic

 * neuKind
 * neuMutter
 * neuVater
 * PrintTree
 * printTree
 * NaviVater
 * NaviMutter
 * NaviUp
 *
 * Destructor
 * saveKnoten
 * loadKnoten
 * savefile
 * loadfile
 */

#include "Stammbaum.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

Stammbaum::Stammbaum() {
	wurzel = nullptr; // Sicherheitsmaßnahme, dass der Baum leer ist und grade keinen akteullen Zeiger hat
	aktuell = nullptr; //stellt sicher, dass der Baum beim erstellen leer ist und der curretn Pointer auf nichts zeigt
}

void Stammbaum::deleteKnoten(Knoten *aktuell) {
	if (aktuell) {
		if (aktuell->vater) {
			deleteKnoten(aktuell->vater);
		}
		if (aktuell->mutter) {
			deleteKnoten(aktuell->mutter);
		}
		delete aktuell;
	}
}

Stammbaum::~Stammbaum() {
	deleteKnoten(wurzel);
}

// Ausgabe
void Stammbaum::printTree(Knoten *node, int elternteil, int tiefe) {

	if (node == nullptr) {
		return;
	} else {

		printTree(node->vater, 0, tiefe + 1);

		if (tiefe >= 1)
			cout << setw((tiefe - 1) * 3) << "";
		if (node == aktuell) {
			cout << ">>>";
		} else {
			cout << "   ";
		}
		if (elternteil == 0) {
			cout << "/--";
		} else if (elternteil == 1) {
			cout << "\\--";
		}

		cout << node->vorname << " " << node->nachname << endl;

		printTree(node->mutter, 1, tiefe + 1);

	}

}

void Stammbaum::printTree() {
	if (wurzel) {
		printTree(wurzel, 8, 0);
	}

}

// Knoten hinzufügen
void Stammbaum::neuKind(string vorname, string nachname) {
	if (wurzel == nullptr) {
		wurzel = new Knoten;
		wurzel->vorname = vorname;
		wurzel->nachname = nachname;
		aktuell = wurzel;
	}
}

void Stammbaum::neuVater(string vorname, string nachname) {
	if (aktuell != nullptr && aktuell->vater == nullptr) {
		aktuell->vater = new Knoten;
		aktuell->vater->vorname = vorname;
		aktuell->vater->nachname = nachname;
		aktuell->vater->davor = aktuell;

	}
}

void Stammbaum::neuMutter(string vorname, string nachname) {
	if (aktuell != nullptr && aktuell->mutter == nullptr) {
		aktuell->mutter = new Knoten;
		aktuell->mutter->vorname = vorname;
		aktuell->mutter->nachname = nachname;
		aktuell->mutter->davor = aktuell;

	}
}

// Navigation
void Stammbaum::NaviUp() {
	if (aktuell->davor) {
		aktuell = aktuell->davor;
	}

}

void Stammbaum::Navi2Vater() {

	if (aktuell != nullptr && aktuell->vater != nullptr) {
		aktuell = aktuell->vater;
	}
}

void Stammbaum::Navi2Mutter() {
	if (aktuell != nullptr && aktuell->mutter != nullptr) {
		aktuell = aktuell->mutter;
	}
}

// Speichern und holen
void Stammbaum::saveKnoten(ofstream &datei, Knoten *node) {
	if (node == nullptr) {
		datei << "NULL" << endl;
	} else {
		datei << node->vorname << ' ' << node->nachname << endl;

		saveKnoten(datei, node->vater);
		saveKnoten(datei, node->mutter);
	}
	return;
}

void Stammbaum::SaveToFile() {
	ofstream datei;
	datei.open("Stammbaum.txt");
	if (datei.is_open()) {
		saveKnoten(datei, wurzel);
		datei.close();
	} else {
		cout << "Datei konnte nicht geöffnet werden." << endl;
	}
}

//was passiert hier:
Stammbaum::Knoten* Stammbaum::loadKnoten(ifstream &datei) {
	string vorname, nachname;

	datei >> vorname;
	if (vorname != "NULL") {
		datei >> nachname;
		Knoten *k = new Knoten;						//baut einen Knoten auf
		k->vorname = vorname;
		k->nachname = nachname;

		k->vater = loadKnoten(datei); //"Bauvorschriften" im Fall von Vater (rekursiv alle Väter)

		k->mutter = loadKnoten(datei); //"Bauvorschriften" im Fall von Mutter (rekursiv alle Mütter)
		return k;
	} else {

		return nullptr;

	}

}

void Stammbaum::LoadFromFile() {
	ifstream datei;
	datei.open("Stammbaum.txt");
	if (datei.is_open()) {
		wurzel = loadKnoten(datei);
		datei.close();
	} else {
		cout << "Datei konnte nicht geöffnet werden." << endl;
	}
}
