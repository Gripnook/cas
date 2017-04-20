#include <string>
#include "Calculator.h"
#include "Functions.h"
#include "Misc.h"
using namespace std;

long double Calculator::root(const string& function, const long double& guess)
{
    string deriv = derive(function);
    string iteration = "(x)-(" + function + ")/(" + deriv + ")";
    long double result = guess, temp;
    int i = 0;
    do
    {
        i++;
        temp = result;
        result = compute(sub(iteration, ftos(result)));
    } while (error == '0' && i < MAX_ITERATIONS_ROOT && Andrei::abs(result - temp) > MAX_ERROR_ROOT);
    if (i == MAX_ITERATIONS_ROOT)
    {
        error = 'M';
    }
    return result;
}
