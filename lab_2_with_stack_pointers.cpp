/*the variable names and comments switch betweeen german and english*/

#include <string>
#include <stack>
#include <iostream>
#include <cstdlib>

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

const int size = 40;
double calc_stack[size];      // Globale Variable
double *pos = calc_stack - 1; // points at a position prior to the stack

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
            else if (zahl[i] == '.')
                state = KOMMA;
            else if (zahl[i] == 'e' || zahl[i] == 'E')
                state = EXPONENT;
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
            else if (zahl[i] == '+' || zahl[i] == '-')
                state = HVORZEICHEN;
            else
            {
                state = ERROR;
            }
            break;
        case HVORZEICHEN:
            if (zahl[i] >= '0' && zahl[i] <= '9')
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
    if (state == ZAHL || state == HOCHZAHL || state == NACHKOMMAZAHL)
        return true;
    else
        return false;
}
Type CheckInputType(string input)
{
    if ((input.length() == 1) && (input[0] == 'x' || input[0] == 'q'))
        return BEFEHL;
    else if ((input.length() == 1) && (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/'))
        return OPERATOR;
    else if (CheckDoubleNumber(input) == true)
        return OPERAND;
    else
    {
        return FEHLER;
    }
}
bool stack_push(double pushval)
{
    if (pos >= calc_stack + size - 1) // überprüft, ob der Array voll ist (size 4 - 1 = 3 eigentlich, falls größer oder gleich -> voll)
        return false;
    else
    {
        *(++pos) = pushval; // inkrementiert den Pointer und er zeigt jetzt auf das letzte ELement
        return true;
    }
}

bool stack_pop(double *popval)
{
    if (pos < calc_stack) // vergleicht den Anfang mit dem Pointer -> falls pointer kleiner ist, ist das array leer, falls gleihc, hat es genau ein Element
        return false;
    else
    {
        *popval = *pos; // speichert in popval den aktuellen Wert
        pos--;
        return true; // zeigt auf das vorherige Element
    }
}

void stack_print()
{
    for (double *ptr = calc_stack; ptr <= pos; ptr++) //*ptr gibt den Wert des Elements im calc_stack aus, auf den ptr aktuell zeigt
    {
        cout << *ptr << endl; // ohne Sternchen würde die Adresse ausgegeben werden
    }
}

int main()
{
    string Input;
    bool m = true;

    while (m)
    {
        double result;

        cout << "Enter:" << endl;
        cin >> Input;

        Type type = CheckInputType(Input);

        switch (type)
        {
        case OPERAND:
        {
            double in = stod(Input);
            stack_push(in);
        }
        break;

        case OPERATOR:
        {
            double temp1, temp2;
            if (stack_pop(&temp1) && stack_pop(&temp2)) // stack_pop(double *popval)
            {
                switch (Input[0])
                {
                case '+':
                    result = temp1 + temp2;
                    stack_push(result);
                    break;
                case '-':
                    result = temp2 - temp1; // nicht kommutativ
                    stack_push(result);
                    break;
                case '*':
                    result = temp1 * temp2;
                    stack_push(result);
                    break;
                case '/':
                    if (temp1 != 0)
                    {
                        result = temp2 / temp1; // nicht kommutativ
                        stack_push(result);
                    }
                    else
                    {
                        cout << "Division durch 0 ist nicht erlaubt." << endl;
                        stack_push(temp2);
                        stack_push(temp1);
                    }
                    break;
                }
            }
            else
            {
                cout << "Nicht genuegend Operanden im Stack." << endl;
                if (pos == calc_stack-1)
					stack_push(temp1);
            }
        }

        break;
        case FEHLER:
            cout << "Falsche Eingabe" << endl;
            break;
        case BEFEHL:
            return 0;
        }
        stack_print();
    }
}
// Zu 2b: was wäre ein "echter" Stackpointer oder "echte" Pointer Arithmetik? Und wieso brauche ich einen neuen Projekt?
