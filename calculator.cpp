#include <string>
#include "Calculator.h"
#include "Misc.h"
using namespace std;

Calculator::Calculator()
{
    mode = "rad";
    error = '0';
    divisions = 10;
    answer = 0;
    fanswer = " ";
    memory = 0;
    fmemory = " ";
}

void Calculator::set_mode(const string& new_mode)
{
    if (lower(new_mode) == "rad" || lower(new_mode) == "deg")
    {
        mode = lower(new_mode);
    }
    else
    {
        error = 'C';
    }
    return;
}

void Calculator::set_answer(const long double& value)
{
    answer = value;
    return;
}
        
long double Calculator::get_answer()
{
    return answer;
}
void Calculator::set_memory(const long double& value)
{
    memory = value;
    return;
}

void Calculator::set_fmemory(const string& function)
{
    fmemory = function;
    return;
}
        
void Calculator::set_divisions(const int& new_divisions)
{
    divisions = new_divisions;
    return;
}

int Calculator::get_divisions()
{
    return divisions;
}

void Calculator::reset_error()
{
    error = '0';
}

char Calculator::get_error()
{
    return error;
}
