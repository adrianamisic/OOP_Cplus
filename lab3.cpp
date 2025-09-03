/*
     Wähle:
     b  am Anfang einfügen
     e  am Ende einfügen
     s  bubblesort
     i  auf die Richtige Stelle einfügen
     x  Beende
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

struct List
{
    int Element;
    List *next;
};

List *anchor = nullptr;
bool ListSorted = true;

void InsertatBeginning(int x)
{
    List *neu = new List;
    neu->next = anchor;
    neu->Element = x;
    anchor = neu;
    ListSorted = false;
}
void InsertatEnd(int x)
{
    List *neu = new List;
    neu->next = nullptr;
    neu->Element = x;

    if (!anchor)
    {
        anchor = neu;
    }
    else
    {
        List *temp = anchor;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = neu;
    }
    ListSorted = false;
}
void InsertSorted(int x) // wo ist das nächstgrößere Element -> davor einbinden
{
    List *neu = new List;
    neu->Element = x;
    if (!anchor || anchor->Element >= x)
    {
        neu->next = anchor;
        anchor = neu;
    }
    else
    {
        List *aktuell = anchor;
        while (aktuell->next && aktuell->next->Element < x)
        {
            aktuell = aktuell->next;
        }
        neu->next = aktuell->next;
        aktuell->next = neu;
    }

}
void PrintList_Forward()
{   List *aktuell = anchor;
    while(aktuell)
    {
        cout << aktuell->Element <<endl;
        aktuell = aktuell->next;
    }
}
void Bubblesort()
{
    bool swapped;       //ist automatisch true
    List *aktuell;

    do //do-while(swapped):bis !swapped
    {
        swapped = false;                                 
        aktuell = anchor;

        while (aktuell->next)
        {
            if (aktuell->Element > aktuell->next->Element)
            {
                // Tausche die Dateninhalte
                int temp = aktuell->Element;
                aktuell->Element = aktuell->next->Element;
                aktuell->next->Element = temp;
                swapped = true; //signalisiert, dass der Tausch stattgefunden hat
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

        List *temp;

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
             while(anchor)      // soll die ganze Liste löschen vom Anchor aus und solange Anker nicht gleich Nullptr ist.
            {
                temp = anchor;                  //anchor -> Element1 -> Element2 -> Element3 -> nullptr
                anchor = anchor -> next;        //anchor -> Element2 -> Element3 -> nullptr
                delete temp;                    //anchor -> Element3 -> nullptr
            break;                              //anchor -> Element3 -> nullptr         
        default:                                //anchor -> nullptr
            cout << "FEHLER" << endl;
            PrintList_Forward();
            break;
        }
    }
           
    
    }
        return 0;
    }