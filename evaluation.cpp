#include <string>
#include "Calculator.h"
#include "Functions.h"
#include "Misc.h"
using namespace std;

long double Calculator::compute(const string& inputstr)
{
    string input = inputstr;
    long double result;
    if (error != '0')
    {
        result = 1;
    }
    else if (is_brackets(input))
    {
        error = '9'; //Missing argument.
        result = 1;
    }
    else if (check_sum(input))
    {
        result = compute_sum(input);
    }
    else if (check_diff(input))
    {
        result = compute_diff(input);
    }
    else if (check_prod(input))
    {
        result = compute_prod(input);
    }
    else if (check_div(input))
    {
        result = compute_div(input);
    }
    else if (check_pow(input))
    {
        result = compute_pow(input);
    }
    else if (check_other(input))
    {
        result = compute_other(input);
    }
    else
    {
        result = numeric(input);
    }
    return result;
}

bool Calculator::check_sum(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    if (numerical(input))
    {
        return false;
    }
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '+')
        {
            return true;
        }
    }
    return false;
}

long double Calculator::compute_sum(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    long double sum = 0;
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '+')
        {
            if (i == 0 || i == input.length() - 1)
            {
                error = '9'; //Missing argument;
                sum = 1;
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                sum = compute(input1) + compute(input2);
            }
            break;
        }
    }
    return sum;
}

bool Calculator::check_diff(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    if (numerical(input))
    {
        return false;
    }
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '-')
        {
            return true;
        }
    }
    return false;
}

long double Calculator::compute_diff(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    long double diff = 0;
    if (input.at(0) == '-')
    {
        if (input.length() == 1)
        {
            error = '9'; //Missing argument;
            diff = 1;
        }
        else
        {
            input = minus_to_plus(input.substr(1, input.length() - 1));
            diff = -1 * compute(input);
        }
    }
    else
    {
        for (unsigned long i = 0; i < input.length(); i++)
        {
            if (input.at(i) == '(')
            {
                bracket_count++;
            }
            if (input.at(i) == ')')
            {
                bracket_count--;
            }
            if (bracket_count == 0 && input.at(i) == '-')
            {
                if (i == 0 || i == input.length() - 1)
                {
                    error = '9'; //Missing argument;
                    diff = 1;
                }
                else
                {
                    string input1 = input.substr(0, i), input2 = minus_to_plus(input.substr(i + 1, input.length() - i - 1));
                    diff = compute(input1) - compute(input2);
                }
                break;
            }
        }
    }
    return diff;
}

bool Calculator::check_prod(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '*')
        {
            return true;
        }
    }
    return false;
}

long double Calculator::compute_prod(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    long double prod = 0;
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '*')
        {
            if (i == 0 || i == input.length() - 1)
            {
                error = '9'; //Missing argument;
                prod = 1;
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                prod = compute(input1) * compute(input2);
            }
            break;
        }
    }
    return prod;
}

bool Calculator::check_div(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '/')
        {
            return true;
        }
    }
    return false;
}

long double Calculator::compute_div(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    long double div = 1;
    for (long i = static_cast<long>(input.length() - 1); i >= 0; i--)
    {
        if (input.at(i) == ')')
        {
            bracket_count++;
        }
        if (input.at(i) == '(')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '/')
        {
            if (i == 0 || i == input.length() - 1)
            {
                error = '9'; //Missing argument;
                div = 1;
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                long double denom = compute(input2);
                if (denom == 0)
                {
                    error = '1'; //Division by 0.
                    div = 1;
                }
                else
                {
                    div = compute(input1) / denom;
                }
            }
            break;
        }
    }
    return div;
}

bool Calculator::check_pow(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (input.at(i) == '(')
        {
            bracket_count++;
        }
        if (input.at(i) == ')')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '^')
        {
            return true;
        }
    }
    return false;
}

long double Calculator::compute_pow(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    long double power = 0;
    for (long i = static_cast<long>(input.length() - 1); i >= 0; i--)
    {
        if (input.at(i) == ')')
        {
            bracket_count++;
        }
        if (input.at(i) == '(')
        {
            bracket_count--;
        }
        if (bracket_count == 0 && input.at(i) == '^')
        {
            if (i == 0 || i == input.length() - 1)
            {
                error = '9'; //Missing argument;
                power = 1;
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                long double argument = compute(input1);
                long double exponent = compute(input2);
                if (argument == 0 && exponent < 0)
                {
                    error = '1'; //Division by 0.
                    power = 1;
                }
                else if (exponent - static_cast<int>(exponent) != 0 && argument < 0)
                {
                    error = '7'; //Negative number to non-integer power.
                    power = 1;
                }
                else
                {
                    power = Andrei::pow(argument, exponent);
                }
            }
            break;
        }
    }
    return power;
}

bool Calculator::check_other(const string& inputstr)
{
    string input = inputstr;
    input = destroy_end_brackets(input);
    if (lower(input.substr(0, 3)) == "sin")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "cos")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "tan")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "sec")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "csc")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "cot")
    {
        return true;
    }
    else if (lower(input.substr(0, 2)) == "ln")
    {
        return true;
    }
    else if (lower(input.substr(0, 3)) == "abs")
    {
        return true;
    }
    else if (lower(input.substr(0, 6)) == "arcsin")
    {
        return true;
    }
    else if (lower(input.substr(0, 6)) == "arccos")
    {
        return true;
    }
    else if (lower(input.substr(0, 6)) == "arctan")
    {
        return true;
    }
    else if (lower(input.substr(0, 4)) == "sqrt")
    {
        return true;
    }
    else
    {
        return false;
    }
}

long double Calculator::compute_other(const string& inputstr)
{
    string input = inputstr;
    long double result = 0;
    input = destroy_end_brackets(input);
    if (lower(input.substr(0, 3)) == "sin")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (lower(mode) == "rad")
            {
                result = Andrei::sin(compute(input.substr(3, input.length() - 3)));
            }
            else
            {
                result = Andrei::sindeg(compute(input.substr(3, input.length() - 3)));
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "cos")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (lower(mode) == "rad")
            {
                result = Andrei::cos(compute(input.substr(3, input.length() - 3)));
            }
            else
            {
                result = Andrei::cosdeg(compute(input.substr(3, input.length() - 3)));
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "tan")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (Andrei::cos(compute(input.substr(3, input.length() - 3))) == 0)
            {
                error = '2'; //Tangent undefined.
                result = 1;
            }
            else
            {
                if (lower(mode) == "rad")
                {
                    result = Andrei::tan(compute(input.substr(3, input.length() - 3)));
                }
                else
                {
                    result = Andrei::tandeg(compute(input.substr(3, input.length() - 3)));
                }
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "sec")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (Andrei::cos(compute(input.substr(3, input.length() - 3))) == 0)
            {
                error = '3'; //Secant undefined.
                result = 1;
            }
            else
            {
                if (lower(mode) == "rad")
                {
                    result = Andrei::sec(compute(input.substr(3, input.length() - 3)));
                }
                else
                {
                    result = Andrei::secdeg(compute(input.substr(3, input.length() - 3)));
                }
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "csc")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (Andrei::sin(compute(input.substr(3, input.length() - 3))) == 0)
            {
                error = '4'; //Cosecant undefined.
                result = 1;
            }
            else
            {
                if (lower(mode) == "rad")
                {
                    result = Andrei::csc(compute(input.substr(3, input.length() - 3)));
                }
                else
                {
                    result = Andrei::cscdeg(compute(input.substr(3, input.length() - 3)));
                }
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "cot")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (Andrei::sin(compute(input.substr(3, input.length() - 3))) == 0)
            {
                error = '5'; //Cotangent undefined.
                result = 1;
            }
            else
            {
                if (lower(mode) == "rad")
                {
                    result = Andrei::cot(compute(input.substr(3, input.length() - 3)));
                }
                else
                {
                    result = Andrei::cotdeg(compute(input.substr(3, input.length() - 3)));
                }
            }
        }
    }
    else if (lower(input.substr(0, 2)) == "ln")
    {
        if (input.length() - 2 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            if (compute(input.substr(2, input.length() - 2)) <= 0)
            {
                error = '6'; //Ln undefined.
                result = 1;
            }
            else
            {
                result = Andrei::ln(compute(input.substr(2, input.length() - 2)));
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "abs")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            result = Andrei::abs(compute(input.substr(3, input.length() - 3)));
        }
    }
    else if (lower(input.substr(0, 6)) == "arcsin")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            long double arg = compute(input.substr(6, input.length() - 6));
            if (arg > 1 || arg < -1)
            {
                error = 'A'; //Arcsin undefined.
                result = 1;
            }
            else if (lower(mode) == "rad")
            {
                result = Andrei::arcsin(arg);
            }
            else
            {
                result = Andrei::arcsindeg(arg);
            }
        }
    }
    else if (lower(input.substr(0, 6)) == "arccos")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            long double arg = compute(input.substr(6, input.length() - 6));
            if (arg > 1 || arg < -1)
            {
                error = 'B'; //Arccos undefined.
                result = 1;
            }
            else if (lower(mode) == "rad")
            {
                result = Andrei::arccos(arg);
            }
            else
            {
                result = Andrei::arccosdeg(arg);
            }
        }
    }
    else if (lower(input.substr(0, 6)) == "arctan")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            long double arg = compute(input.substr(6, input.length() - 6));
            if (lower(mode) == "rad")
            {
                result = Andrei::arctan(arg);
            }
            else
            {
                result = Andrei::arctandeg(arg);
            }
        }
    }
    else if (lower(input.substr(0, 4)) == "sqrt")
    {
        if (input.length() - 4 <= 0)
        {
            error = '9'; //Missing argument.
            result = 1;
        }
        else
        {
            long double arg = compute(input.substr(4, input.length() - 4));
            if (arg < 0)
            {
                error = '7'; //Negative number to non-integer power.
                result = 1;
            }
            else
            {
                result = Andrei::pow(arg, 0.5);
            }
        }
    }
    return result;
}

long double Calculator::numeric(const string& inputstr)
{
    string input = inputstr;
    input = destroy_end_brackets(input);
    if (lower(input) == "ans")
    {
        return answer;
    }
    else if (lower(input) == "mem")
    {
        return memory;
    }
    else if (lower(input) == "e")
    {
        return E;
    }
    else if (lower(input) == "pi")
    {
        return PI;
    }
    else if (numerical(input))
    {
        return stof(input);
    }
    else
    {
        error = '8'; //Undefined functions.
        return 1;
    }
}
