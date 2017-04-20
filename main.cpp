#include <iostream>
#include <string>
#include "readline/readline.h"
#include "Calculator.h"
#include "Functions.h"
#include "Misc.h"
using namespace std;

void error_check(Calculator& calc);
//Returns type of error to console.

void evaluate(const string& inputstr, Calculator& calc);

void derivative(const string& inputstr, Calculator& calc);

void integral(const string& inputstr, Calculator& calc);

void roots(const string& inputstr, Calculator& calc);

void help();

int main()
{
    Calculator CAS;
    string input;
    char end = '0';
    cout << "Author: Andrei Purcarus.\n"
        << "Enter line of input to be evaluated.\n"
        << "For a list of accepted inputs, enter help.\n"
        << "Current mode: radians.\n\n";
    do
    {
        CAS.reset_error(); //Resets error to 0 after each iteration.
        input = readline("> ");
        input = remove_space(input);
        if (input.empty())
        {
            //Does nothing.
        }
        else if (lower(input.substr(0, 4)) == "quit" || lower(input.substr(0, 4)) == "exit")
        {
            end = '1'; //Ends program.
        }
        else if (lower(input.substr(0, 4)) == "help")
        {
            help();
        }
        else if (lower(input.substr(0, 4)) == "mode")
        {
            string new_mode = lower(input.substr(4, 3));
            if (new_mode == "rad" || new_mode == "deg")
            {
                CAS.set_mode(new_mode);
                if (new_mode == "rad")
                {
                    cout << "Mode set to radians.\n\n";
                }
                else
                {
                    cout << "Mode set to degrees.\n\n";
                }
            }
            else
            {
                cout << "Invalid mode\n\n";
            }
        }
        else if (lower(input.substr(0, 5)) == "store")
        {
            CAS.set_memory(CAS.get_answer());
            cout << "Last answer stored in memory.\n\n";
        }
        else if (lower(input.substr(0, 12)) == "setdivisions")
        {
            int new_divisions = stoi(input.substr(12, input.length() - 12));
            if (new_divisions > 0)
            {
                CAS.set_divisions(new_divisions);
                cout << "Number of divisions set to " << new_divisions << ".\n\n";
            }
            else
            {
                cout << "Invalid number of divisions.\n\n";
            }
        }
        else if (input.length() > 6 && lower(input.substr(0, 6)) == "derive")
        {
            derivative(input, CAS);
        }
        else if (input.length() > 9 && lower(input.substr(0, 9)) == "integrate")
        {
            integral(input, CAS);
        }
        else if (input.length() > 8 && lower(input.substr(0, 8)) == "findroot")
        {
            roots(input, CAS);
        }
        else
        {
            evaluate(input, CAS);
        }
    } while (end == '0');
    return 0;
}

void error_check(Calculator& calc)
{
    switch(calc.get_error())
    {
        case '0':
            cout << "No errors detected.\n\n";
            break;
        case '1':
            cout << "Error. Division by 0.\n\n";
            break;
        case '2':
            cout << "Error. Tangent undefined.\n\n";
            break;
        case '3':
            cout << "Error. Secant undefined.\n\n";
            break;
        case '4':
            cout << "Error. Cosecant undefined.\n\n";
            break;
        case '5':
            cout << "Error. Cotangent undefined.\n\n";
            break;
        case '6':
            cout << "Error. Ln undefined.\n\n";
            break;
        case '7':
            cout << "Error. Cannot take negative number to non-integral power.\n\n";
            break;
        case '8':
            cout << "Error. Function undefined.\n\n";
            break;
        case '9':
            cout << "Error. Missing argument.\n\n";
            break;
        case 'A':
            cout << "Error. Arcsin undefined.\n\n";
            break;
        case 'B':
            cout << "Error. Arcsin undefined.\n\n";
            break;
        case 'C':
            cout << "Error. Invalid mode input.\n\n";
            break;
        case 'M':
            cout << "Error. Max iterations exceeded.\n\n";
            break;
        default:
            ;
    }
    return;
}

void evaluate(const string& inputstr, Calculator& calc)
{
    long double result = calc.compute(inputstr);
    if (calc.get_error() == '0')
    {
        cout << result << endl << endl;
        calc.set_answer(result);
    }
    else
    {
        error_check(calc);
    }
    return;
}

void derivative(const string& inputstr, Calculator& calc)
{
    long at_location = inputstr.find("at");
    if (at_location >= 0)
    {
        string function = inputstr.substr(6, at_location - 6);
        string value = inputstr.substr(at_location + 2, inputstr.length() - at_location - 2);
        string deriv = calc.derive(function);
        if (calc.get_error() == '0')
        {
            long double test = calc.compute(sub("x", value));
            if (calc.get_error() != '0')
            {
                cout << "Error. Invalid value at which the derivative is evaluated.\n\n";
                calc.reset_error();
            }
            else
            {
                long double domain_check = calc.compute(sub(function, value));
                if (calc.get_error() == '0')
                {
                    long double result = calc.compute(sub(deriv, value));
                    if (calc.get_error() == '0')
                    {
                        cout << result << endl << endl;
                        calc.set_answer(result);
                    }
                }
            }
        }
        if (calc.get_error() != '0')
        {
            error_check(calc);
        }
    }
    else
    {
        string function = inputstr.substr(6, inputstr.length() - 6);
        string result = calc.derive(function);
        if (calc.get_error() == '0')
        {
            cout << result << endl << endl;
        }
        else
        {
            error_check(calc);
        }
    }
    return;
}

void integral(const string& inputstr, Calculator& calc)
{
    long double result;
    long index1 = inputstr.find("from");
    long index2 = inputstr.find("to");
    if (index1 >= 0 && index2 >= 0)
    {
        long double lower_limit = calc.compute((inputstr.substr(index1 + 4, index2 - index1 - 4)));
        if (calc.get_error() == '0')
        {
            long double upper_limit = calc.compute((inputstr.substr(index2 + 2, inputstr.length() - index2 - 2)));
            if (calc.get_error() == '0')
            {
                if (upper_limit == lower_limit)
                {
                    cout << 0 << endl << endl;
                }
                else
                {
                    string function = inputstr.substr(9, index1 - 9);
                    result = calc.simpson_integral(function, lower_limit, upper_limit);
                    if (calc.get_error() == '0')
                    {
                        if (Andrei::abs(upper_limit - lower_limit) > calc.get_divisions() / 5)
                        {
                            cout << "Questionable accuracy. Consider increasing divisions.\n";
                        }
                        cout << result << endl << endl;
                        calc.set_answer(result);
                    }
                }
            }
        }
        if (calc.get_error() != '0')
        {
            error_check(calc);
        }
    }
    else
    {
        cout << "Invalid input.\n\n";
    }
    return;
}

void roots(const string& inputstr, Calculator& calc)
{
    long double result, guess;
    cout << "Initial guess for value of root? ";
    cin >> guess;
    result = calc.root(inputstr.substr(8, inputstr.length() - 8), guess);
    if (calc.get_error() == '0')
    {
        cout << result << endl << endl;
        calc.set_answer(result);
    }
    else
    {
        error_check(calc);
    }
    return;
}

void help()
{
    cout << "Predefined functions:\n"
    << "+, -, *, / : Arithmetic operators.\n"
    << "abs()      : Absolute value function.\n"
    << "()^()      : Power function.\n"
    << "sqrt()     : Square root function.\n"
    << "ln()       : Natural logarithm function.\n"
    << endl
    << "sin(), cos(), tan(), sec(), csc(), cot() : Trig functions.\n"
    << "arcsin(), arccos(), arctan()         : Inverse trig functions.\n"
    << endl
    << "Special characters:\n"
    << "e   : 2.71828\n"
    << "pi  : 3.14159\n"
    << "ans : previous answer\n"
    << "mem : value stored in memory\n"
    << endl
    << "Special operations:\n"
    << "quit     : Ends program.\n"
    << "help     : Brings up help.\n"
    << "mode rad : Sets mode to radians.\n"
    << "mode deg : Sets mode to degrees.\n"
    << "store    : Stores previous answer in memory.\n"
    << "       One answer can be stored at a time.\n"
    << endl
    << "derive *f(x)*            : Returns symbolic derivative of f(x).\n"
    << "derive *f(x)* at *value* : Returns derivative of f(x) at value.\n"
    << endl
    << "integrate *f(x)* from \n"
    << "*lower bound* to *higher bound* : Returns integral of f(x) from \n"
    << "                  lower bound to higher bound.\n"
    << "set divisions *integer*         : Sets the number of divisions \n"
    << "                  for integral approximation to \n"
    << "                  value of integer.\n"
    << endl
    << "find root *f(x)* : Finds root of the equation f(x) = 0.\n\n";
    return;
}
