/*
     Wähle:
     b  am Anfang einfügen
     e  am Ende einfügen
     s  bubblesort
     i  auf die Richtige Stelle einfügen
     x  Beende

     anchor <---> Inhalt <---> Inhalt <--->nullptr                  
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;
//---------------------------------------------------------------------------------------------------//

/*                      Was soll der Struct beinhalten:
                ________________
                |______24______|         Inhalt
            <---|___previous___|<---     Zeiger auf das vorherige ELement
            --->|_____next_____|--->     Zeiger aud das nächste Inhalt
*/
struct List
{
    int Inhalt;
    List *previous;
    List *next;
};
//---------------------------------------------------------------------------------------------------//
List *anchor = nullptr;
bool ListSorted = true;      //Global angelegt, da diese in jeder Funktion wiederholt verwendet wird
//---------------------------------------------------------------------------------------------------//
void InsertatBeginning(int x)
{
    List *neu = new List;           //1.)Speicherplatz wird allokiert
    neu->Inhalt = x;                //2.)Inhalt = random Number aus der main Funktion
    neu->next = anchor;             //3.)Pointer werden gebogen
    neu->previous = nullptr;

    /*          ________________
                |______x_______|                Inhalt
     nullptr<---|___previous___|<---            Zeiger auf das vorherige ELement
            --->|_____next_____|---> Element    Zeiger auf das nächste Element
   */

    if (anchor != nullptr)  //wenn die Liste nicht leer ist
    {
        anchor->previous = neu; //das vorherige erste Element zeigt auf das neue Element in der Liste
    }
    anchor = neu;           //Anker wird aktualisiert und iegt jetzt auf das neue Element in der Liste
    ListSorted = false;
    /*
     1.)   x <-> y <-> z
              |    
            anker

     2.)   ('v' ist das neu Element)

     3.)   v <-> x <-> y <-> z
            |      |
           neu    anker


           previous
              |
    4.)   v <-> x <-> y <-> z
            |     
          anker 
    */
} 
//---------------------------------------------------------------------------------------------------//
void InsertatEnd(int x)
{
    List *neu = new List;           //1.)Speicherplatz wird allokiert
    neu->Inhalt = x;                //2.)Inhalt = random Number aus der main Funktion
    neu->next = nullptr;            //3.)Pointer werden gebogen 

    /*                ________________
                      |______x_______|                Inhalt
           Element<---|___previous___|<---            Zeiger auf das vorherige ELement
                  --->|_____next_____|---> nullptr    Zeiger aud das nächste
   */

    if (!anchor)//falls die Liste leer ist
    {
        neu->previous = nullptr;
        anchor = neu;       //Das neue Element ist das erste und letzte Element
    }
    else //falls die Liste gefüllt ist
    {
        List *run = anchor;    //zeigt zuerst auf den Anker
        while (run->next)  //durchläuft die Liste bis zum letzen Element (run->nullptr)
        {
            run = run->next; //da wir den "next"-Zeiger haben, muss nur noch der "Previous"-Zeiger bestimmt werden
        }
        run->next = neu;     
        neu->previous = run;
    }
    ListSorted = false;
}
//---------------------------------------------------------------------------------------------------//
void InsertSorted(int x) // wo ist das nächstgrößere Element -> davor einbinden
{
    List *neu = new List;
    neu->Inhalt = x;

    if (!anchor || anchor->Inhalt >= x) // Fall 1: Es gibt keinen Anker/Liste oder Anker ist größer/gleich dem neuen Element
    {
        neu->previous =nullptr;
        neu->next= anchor; //davor eindinden
        if(anchor)
        anchor=neu;
    }
    else //Fall 2: Es gibt einen Anker und der ist kleiner als das neue Element
    {
        List *run = anchor; //fängt beim Anker an
        while (run->next && run->next->Inhalt < x)
        {
            run = run->next; //läuft, bis es auf das letzte Element stößt, dass kleiner ist.
        }
        neu->next = run->next;
        neu->previous = run;

        if (run->next)
        {
            run->next->previous = neu; //dazwischen einsetzen
        }

        run->next = neu;
    }
}

//---------------------------------------------------------------------------------------------------//
void PrintList_Forward()
{
    List *run = anchor; 
    while (run) //solange der Zeiger nicht NULL ist
    {
        cout << run->Inhalt << endl;
        run = run->next;
    }
}
//---------------------------------------------------------------------------------------------------//
void PrintList_Reverse()
{
    if (!anchor) return; // Liste ist leer

    List *run = anchor;
    while (run->next) run = run->next; // gehe zum letzten Element

    // läuft rückwärts und gib die Elemente aus
    while (run)
    {
        cout << run->Inhalt << endl;
        run = run->previous;
    }
}

//---------------------------------------------------------------------------------------------------//
void Bubblesort()
{
    bool swapped; // ist automatisch true
    List *aktuell;

    do // do-while(swapped):bis !swapped
    {
        swapped = false;
        aktuell = anchor;

        while (aktuell && aktuell->next)
        {
            if (aktuell->Inhalt > aktuell->next->Inhalt)
            {
                // Tausche die Dateninhalte
                int run = aktuell->Inhalt;
                aktuell->Inhalt = aktuell->next->Inhalt;
                aktuell->next->Inhalt = run;
                swapped = true; // signalisiert, dass der Tausch stattgefunden hat
            }
            aktuell = aktuell->next;
        }
    } while (swapped);

    /*void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}*/
}
//---------------------------------------------------------------------------------------------------//
int main()
{

    // bei "srand(time(nullptr));" conversion from 'time_t' {aka 'long long int'} to 'unsigned int' may change value [-Wconversion]
    // CHATgpt:
    srand(static_cast<unsigned int>(time(nullptr)));
    char Eingabe;

    while (true)
    {
        cout << "Befehl:" << endl;
        cin >> Eingabe;
        int komp = 1 + rand() % 9998;

        List *run;

        switch (Eingabe)
        {
        case 'b':
            InsertatBeginning(komp);
            PrintList_Forward();
            break;
        case 'e':
            InsertatEnd(komp);
            PrintList_Forward();
            break;
        case 's':
            Bubblesort();
            PrintList_Forward();
            break;
        case 'i':
            InsertSorted(komp);
            PrintList_Forward();
            break;
        case 'x':
            PrintList_Forward();
            while (anchor)
            {
                run = anchor;
                anchor = anchor->next;
                delete run;
                break;
            default:
                cout << "FEHLER" << endl;
                PrintList_Forward();
                break;
            }
        }
    }
    return 0;
}

/* HANDSKIZZEN VOM ABLAUF       Überprüfen lassen       Fälle
1.)InsertAtBegining         +                           Leer, nicht leer
2.)InsertAtEnd              +                           kein vorheriges Element, voll
3.)Bubblesort               +                           nur ein Element, mehrere Elemente
4.)PrintList_Forward        +                           
5.)PrintList_Reverse        +                           
6.)InsertSorted             +                           bereits sortiert? noch nicht sortiert?nur eine Element - eig egal, oder?!
*/