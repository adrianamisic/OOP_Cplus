/*This document uses englisch and german terms for variables*/

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
double calc_stack[size];
int position = -1; // initialise, but not with 0!

bool CheckDoubleNumber(string zahl)
{
    State state = START;
    bool quit = false;

    unsigned int i = 0;

    // Finite - State - Machine
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
    if (position >= size - 1) // falls voll
        return false;
    else
    {
        calc_stack[++position] = pushval;
        return true;
    }
}
bool stack_pop(double *popval)
{
    if (position < 0) // falls leer
        return false;
    else
    {
        *popval = calc_stack[position];
        position--;
        return true;
    }
}
void stack_print()
{
    for (int i = 0; i <= position; i++)
    {
        cout << calc_stack[i] << endl;
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
                if (position == -1)
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
