/*
 * Stammbaum.h
 *
 *  Created on: 21.06.2024
 *      Author: tesla
 */

#ifndef STAMMBAUM_H_
#define STAMMBAUM_H_
#include <iostream>
using namespace std;
//Sobald ich den Struct unter private stehen habe, erkennt er die Funktion loadKnoten nicht.


class Stammbaum {
private:
	struct Knoten{
					string vorname;
					string nachname;
					Knoten *vater = nullptr;  //Knoten
					Knoten *mutter = nullptr;
					Knoten* davor = nullptr;
				};
	//Attribut
	Knoten *wurzel=nullptr;
	Knoten *aktuell=nullptr;
	int tiefe=0;
	//Methoden
	void printTree(Knoten *node, int elternteil, int tiefe);
	void saveKnoten(ofstream& dateiname, Knoten *node);
	Knoten* loadKnoten(ifstream& dateiname);
	void deleteKnoten(Knoten* node);
public:
	//Constructor und Destructor
	Stammbaum();
	virtual ~Stammbaum();
	//Ausgabe
	void printTree();
	//Knoten hinzufügen
	void neuKind(string vorname, string nachname);
	void neuVater(string vorname, string nachname);
	void neuMutter(string vorname, string nachname);
	//File Handeling
	void SaveToFile();
	void LoadFromFile();
	// Navigation
	void NaviUp();
	void Navi2Vater();
	void Navi2Mutter();

};

#endif /* STAMMBAUM_H_ */


