
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "dstack.h"

using namespace std;


enum State
{
    START,
    VORZEICHEN,
    ZAHL,
    KOMMA,
    NACHKOMMAZAHL,
    EXPONENT,
    HOCHZAHL,
    HVORZEICHEN,
    ERROR,
};

enum Type
{
    BEFEHL,
    OPERATOR,
    OPERAND,
    FEHLER,
};

bool CheckDoubleNumber(string zahl)
{
    State state = START;
    bool quit = false;

    unsigned int i = 0;

    while (!quit && (i < zahl.size()))
    {
        switch (state)
        {
        case START:
            if (zahl[i] == '+' || zahl[i] == '-')
                state = VORZEICHEN;
            else if (zahl[i] >= '0' && zahl[i] <= '9')
                state = ZAHL;
            else
            {
                state = ERROR;
            }
            break;

        case VORZEICHEN:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = ZAHL;
            else
            {
                state = ERROR;
            }
            break;

        case ZAHL:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = ZAHL;
            else if (zahl[i] == '.' )
                state = KOMMA;
            else
            {
                state = ERROR;
            }
            break;

        case KOMMA:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = NACHKOMMAZAHL;
            else
            {
                state = ERROR;
            }
            break;

        case NACHKOMMAZAHL:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = NACHKOMMAZAHL;
            else if (zahl[i] == 'e' || zahl[i] == 'E')
                state = EXPONENT;
            else
            {
                state = ERROR;
                ;
            }
            break;

        case EXPONENT:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = HOCHZAHL;
            else if (zahl[i] == '+' || zahl[i] == '-' )
            	state = HVORZEICHEN;
            else
            {
                state = ERROR;
            }
            break;
        case HVORZEICHEN:
            if (zahl[i] == '+' || zahl[i] == '-')
                state = HOCHZAHL;
            else if (zahl[i] >= '0' && zahl[i] <= '9')
                state = HOCHZAHL;
            else
                state = ERROR;
            break;

        case HOCHZAHL:
            if (zahl[i] >= '0' && zahl[i] <= '9')
                state = HOCHZAHL;
            else
            {
                state = ERROR;
            }
            break;

        case ERROR:
            quit = true;
            break;
        }
        i++;
    }
       if(state == ZAHL || state == HOCHZAHL || state == NACHKOMMAZAHL)
       return true;
       else
       return false;
}
Type CheckInputType(string input)
{
    if ((input.length() == 1) && (input[0] == 'x' || input[0] == 'q' || input[0]== 'p'))
        return BEFEHL;
    else if ((input.length() == 1) && (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/'))
        return OPERATOR;
    else if (CheckDoubleNumber(input) == true)
        return OPERAND;
    else {return FEHLER;
    }
}

int main()
{
	    string Input;
	    bool m = true;
	    DStack stack;
	    double popValue = 0.;

	    while (m)
	    {
	        cout << "x, q = Rechnung zu beenden." << endl;
	        cout << "p = Stack ausgeben." << endl;
	        cout << "Eingabefeld:" << endl;
	        cin >> Input;

	        Type type = CheckInputType(Input);

	        switch (type)
	        {
	        case OPERAND:
	            stack.Push(stod(Input));
	            break;
	        case OPERATOR:
	            if (stack.Pop(popValue)) {
	                double temp1 = popValue;
	                if (stack.Pop(popValue)) {
	                    double temp2 = popValue;
	                    switch (Input[0]) {
	                    case '+':
	                        stack.Push(temp1 + temp2);
	                        cout << "Summe: " << stack.PrintValue() << endl;
	                        break;
	                    case '-':
	                        stack.Push(temp2 - temp1);
	                        cout << "Differenz: " << stack.PrintValue() << endl;
	                        break;
	                    case '*':
	                        stack.Push(temp1 * temp2);
	                        cout << "Produkt: " << stack.PrintValue() << endl;
	                        break;
	                    case '/':
	                        if (temp1 != 0) {
	                            stack.Push(temp2 / temp1);
	                            cout << "Quotient: " << stack.PrintValue() << endl;
	                        } else {
	                            cout << "Division durch 0 ist nicht erlaubt." << endl;
	                            stack.Push(temp2);
	                            stack.Push(temp1);
	                        }
	                        break;
	                    }
	                } else {
	                    cout << "Nicht genügend Operanden vorhanden." << endl;
	                    stack.Push(temp1);
	                }
	            }
	            break;
	        case BEFEHL:
	            if (Input == "q" || Input == "x")
	                m = false;
	            else if (Input == "p")
	                stack.SPrintReverse();
	            else
	                cout << "Falsche Eingabe" << endl;
	            break;
	        case FEHLER:
	            cout << "### FEHLER ###" << endl;
	            break;
	        }
	    }

	    return 0;
	}
