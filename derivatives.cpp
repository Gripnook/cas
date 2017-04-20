#include <string>
#include <sstream>
#include "Calculator.h"
#include "Functions.h"
#include "Misc.h"
using namespace std;

string Calculator::derive(const string& inputstr)
{
    string input = inputstr;
    string result;
    if (error != '0')
    {
        result = "1";
    }
    else if (is_brackets(input))
    {
        error = '9'; //Missing argument.
        result = "1";
    }
    else if (check_sum(input))
    {
        result = derive_sum(input);
    }
    else if (check_diff(input))
    {
        result = derive_diff(input);
    }
    else if (check_prod(input))
    {
        result = derive_prod(input);
    }
    else if (check_div(input))
    {
        result = derive_div(input);
    }
    else if (check_pow(input))
    {
        result = derive_pow(input);
    }
    else if (check_other(input))
    {
        result = derive_other(input);
    }
    else
    {
        result = derive_simple(input);
    }
    return remove_space(result);
}

string Calculator::derive_sum(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    string sum;
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
                sum = "1";
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                input1 = destroy_end_brackets(input1);
                input2 = destroy_end_brackets(input2);
                string deriv1 = destroy_end_brackets(derive(input1));
                string deriv2 = destroy_end_brackets(derive(input2));
                if (deriv1 == "0" && deriv2 == "0")
                {
                    sum = "0";
                }
                else if (deriv1 == "0")
                {
                    sum = deriv2;
                }
                else if (deriv2 == "0")
                {
                    sum = deriv1;
                }
                else
                {
                    sum = "(" + deriv1 + ") + (" + deriv2 + ")";
                }
            }
            break;
        }
    }
    return sum;
}

string Calculator::derive_diff(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    string diff;
    if (input.at(0) == '-')
    {
        if (input.length() == 1)
        {
            error = '9'; //Missing argument;
            diff = "1";
        }
        else
        {
            input = destroy_end_brackets(minus_to_plus(input.substr(1, input.length() - 1)));
            string deriv = destroy_end_brackets(derive(input));
            if (deriv == "0")
            {
                diff = "0";
            }
            else
            {
                diff = "-(" + deriv + ")";
            }
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
                    diff = "1";
                }
                else
                {
                    string input1 = input.substr(0, i), input2 = minus_to_plus(input.substr(i + 1, input.length() - i - 1));
                    input1 = destroy_end_brackets(input1);
                    input2 = destroy_end_brackets(input2);
                    string deriv1 = destroy_end_brackets(derive(input1));
                    string deriv2 = destroy_end_brackets(derive(input2));
                    if (deriv1 == "0" && deriv2 == "0")
                    {
                        diff = "0";
                    }
                    else if (deriv1 == "0")
                    {
                        diff = "-(" + deriv2 + ")";
                    }
                    else if (deriv2 == "0")
                    {
                        diff = deriv1;
                    }
                    else
                    {
                        diff = "(" + deriv1 + ") - (" + deriv2 + ")";
                    }
                }
                break;
            }
        }
    }
    return diff;
}

string Calculator::derive_prod(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    string prod;
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
                prod = "1";
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                input1 = destroy_end_brackets(input1);
                input2 = destroy_end_brackets(input2);
                string derv1 = destroy_end_brackets(derive(input1));
                string derv2 = destroy_end_brackets(derive(input2));
                if (derv1 == "0" && derv2 == "0")
                {
                    prod = "0";
                }
                else if (derv1 == "0" && input1 == "1")
                {
                    prod = derv2;
                }
                else if (derv1 == "0" && derv2 == "1")
                {
                    prod = input1;
                }
                else if (derv1 == "0")
                {
                    prod = input1 + "*(" + derv2 + ")";
                }
                else if (derv2 == "0" && input2 == "1")
                {
                    prod = derv1;
                }
                else if (derv2 == "0" && derv1 == "1")
                {
                    prod = input2;
                }
                else if (derv2 == "0")
                {
                    prod = input2 + "*(" + derv1 + ")";
                }
                else if (derv1 == "1" && derv2 == "1")
                {
                    prod = "(" + input1 + ") + (" + input2 + ")";
                }
                else if (derv1 == "1")
                {
                    prod = "(" + input1 + ")*(" + derv2 + ") + (" + input2 + ")";
                }
                else if (derv2 == "1")
                {
                    prod = "(" + input1 + ") + (" + input2 + ")*(" + derv1 + ")";
                }
                else
                {
                    prod = "(" + derv1 + ")*(" + input2 + ") + (" + derv2 + ")*(" + input1 + ")";
                }
            }
            break;
        }
    }
    return prod;
}

string Calculator::derive_div(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    string div;
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
                div = "1";
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                input1 = destroy_end_brackets(input1);
                input2 = destroy_end_brackets(input2);
                string derv1 = destroy_end_brackets(derive(input1));
                string derv2 = destroy_end_brackets(derive(input2));
                if (input2 == "0")
                {
                    error = '1'; //Invalid division by 0.
                    div = "1";
                }
                else if (derv1 == "0" && derv2 == "0")
                {
                    div = "0";
                }
                else if (derv1 == "0" && input1 == "1" && derv2 == "1")
                {
                    div = "-1/(" + input2 + ")^2";
                }
                else if (derv1 == "0" && input1 == "1")
                {
                    div = "-(" + derv2 + ")/(" + input2 + ")^2";
                }
                else if (derv1 == "0" && derv2 == "1")
                {
                    div = "-(" + input1 + ")/(" + input2 + ")^2";
                }
                else if (derv1 == "0")
                {
                    div = "-(" + input1 + ")*(" + derv2 + ")/(" + input2 + ")^2";
                }
                else if (derv2 == "0" && input2 == "1")
                {
                    div = derv1;
                }
                else if (derv2 == "0" && derv1 == "1")
                {
                    div = "1/(" + input2 + ")";
                }
                else if (derv2 == "0")
                {
                    div = "(" + derv1 + ")/(" + input2 + ")";
                }
                else if (derv1 == "1" && derv2 == "1")
                {
                    div = "(" + input2 + " - (" + input1 + "))/(" + input2 + ")^2";
                }
                else if (derv1 == "1")
                {
                    div = "(" + input2 + " - (" + derv2 + ")*(" + input1 + "))/(" + input2 + ")^2";
                }
                else if (derv2 == "1")
                {
                    div = "(" + derv1 + "*(" + input2 + ") - (" + input1 + "))/(" + input2 + ")^2";
                }
                else
                {
                    div = "(" + derv1 + "*(" + input2 + ") - (" + derv2 + ")*(" + input1 + "))/(" + input2 + ")^2";
                }
            }
            break;
        }
    }
    return div;
}

string Calculator::derive_pow(const string& inputstr)
{
    string input = inputstr;
    int bracket_count = 0;
    input = destroy_end_brackets(input);
    string power;
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
                power = "1";
            }
            else
            {
                string input1 = input.substr(0, i), input2 = input.substr(i + 1, input.length() - i - 1);
                input1 = destroy_end_brackets(input1);
                input2 = destroy_end_brackets(input2);
                string derv1 = destroy_end_brackets(derive(input1));
                string derv2 = destroy_end_brackets(derive(input2));
                if (input2 == "0" || input1 == "0")
                {
                    power = "0";
                }
                else if (derv1 == "0" && derv2 == "0")
                {
                    power = "0";
                }
                else if (derv1 == "0" && input1 == "1")
                {
                    power = "0";
                }
                else if (derv1 == "0" && lower(input1) == "e" && derv2 == "1")
                {
                    power = input1 + "^(" + input2 +  ")";
                }
                else if (derv1 == "0" && lower(input1) == "e")
                {
                    power = input1 + "^(" + input2 +  ")*(" + derv2 + ")";
                }
                else if (derv1 == "0" && derv2 == "1")
                {
                    power = input1 + "^(" + input2 +  ")*ln(" + input1 + ")";
                }
                else if (derv1 == "0")
                {
                    power = input1 + "^(" + input2 +  ")*(" + derv2 + ")*ln(" + input1 + ")";
                }
                else if (derv2 == "0" && input2 == "1")
                {
                    power = derv1;
                }
                else if (derv2 == "0" && derv1 == "1" && decrementbyone(input2) == "1")
                {
                    power = "(" + input2 + ")*" + "(" + input1 + ")";
                }
                else if (derv2 == "0" && derv1 == "1")
                {
                    power = "(" + input2 + ")*" + "(" + input1 + ")^(" + decrementbyone(input2) + ")" ;
                }
                else if (derv2 == "0" && decrementbyone(input2) == "1")
                {
                    power = "(" + input2 + ")*" + "(" + input1 + ")*(" + derv1 + ")" ;
                }
                else if (derv2 == "0")
                {
                    power = "(" + input2 + ")*" + "(" + input1 + ")^(" + decrementbyone(input2) + ")*(" + derv1 + ")" ;
                }
                else if (derv1 == "1" && derv2 == "1")
                {
                    power = "(" + input1 + "^(" + input2 +  "))*(ln(" + input1 + ")" + " + (" + input2 + ")/(" + input1 + "))";
                }
                else if (derv1 == "1")
                {
                    power = "(" + input1 + "^(" + input2 +  "))*(" + derv2 + "*ln(" + input1 + ")" + " + (" + input2 + ")/(" + input1 + "))";
                }
                else if (derv2 == "1")
                {
                    power = "(" + input1 + "^(" + input2 +  "))*(ln(" + input1 + ")" + " + (" + derv1 + "*" + input2 + ")/(" + input1 + "))";
                }
                else
                {
                    power = "(" + input1 + "^(" + input2 +  "))*(" + derv2 + "*ln(" + input1 + ")" + " + (" + derv1 + "*" + input2 + ")/(" + input1 + "))";
                }               
            }
            break;
        }
    }
    return power;
}

string Calculator::derive_other(const string& inputstr)
{
    string input = inputstr;
    string result;
    input = destroy_end_brackets(input);
    if (lower(input.substr(0, 3)) == "sin")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "cos(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
            else
            {
                result = "cos(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "cos")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "-sin(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
            else
            {
                result = "-sin(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "tan")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "(sec(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + "))^2";
            }
            else
            {
                result = "(sec(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + "))^2*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "sec")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "sec(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*tan(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
            else
            {
                result = "sec(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*tan(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "csc")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "-csc(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*cot(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
            else
            {
                result = "-csc(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*cot(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "cot")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "-(csc(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + "))^2";
            }
            else
            {
                result = "-(csc(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + "))^2*(" + destroy_end_brackets(deriv) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 2)) == "ln")
    {
        if (input.length() - 2 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(2, input.length() - 2))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "1/(" + destroy_end_brackets(input.substr(2, input.length() - 2)) + ")";
            }
            else
            {
                result = "(" + destroy_end_brackets(deriv) + ")/(" + destroy_end_brackets(input.substr(2, input.length() - 2)) + ")";
            }
        }
    }
    else if (lower(input.substr(0, 6)) == "arcsin")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(6, input.length() - 6))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "1/(1-(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)^(0.5)";
            }
            else
            {
                result = "(" + deriv + ")/(1-(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)^(0.5)";
            }
        }
    }
    else if (lower(input.substr(0, 6)) == "arccos")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(6, input.length() - 6))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "-1/(1-(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)^(0.5)";
            }
            else
            {
                result = "-(" + deriv + ")/(1-(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)^(0.5)";
            }
        }
    }
    else if (lower(input.substr(0, 6)) == "arctan")
    {
        if (input.length() - 6 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(6, input.length() - 6))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "1/(1+(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)";
            }
            else
            {
                result = "(" + deriv + ")/(1+(" + destroy_end_brackets(input.substr(6, input.length() - 6)) + ")^2)";
            }
        }
    }
    else if (lower(input.substr(0, 4)) == "sqrt")
    {
        if (input.length() - 4 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(4, input.length() - 4))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "1/(2*sqrt(" + destroy_end_brackets(input.substr(4, input.length() - 4)) + "))";
            }
            else
            {
                result = "(" + deriv + ")/(2*sqrt(" + destroy_end_brackets(input.substr(4, input.length() - 4)) + "))";
            }
        }
    }
    else if (lower(input.substr(0, 3)) == "abs")
    {
        if (input.length() - 3 <= 0)
        {
            error = '9'; //Missing argument.
            result = "1";
        }
        else
        {
            string deriv = destroy_end_brackets(derive(destroy_end_brackets(input.substr(3, input.length() - 3))));
            if (deriv == "0")
            {
                result = "0";
            }
            else if (deriv == "1")
            {
                result = "(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")/abs(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
            else
            {
                result = "(" + deriv + ")*(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")/abs(" + destroy_end_brackets(input.substr(3, input.length() - 3)) + ")";
            }
        }
    }
    return result;
}

string Calculator::derive_simple(const string& inputstr)
{
    string input = inputstr;
    input = destroy_end_brackets(input);
    if (lower(input) == "e")
    {
        return "0";
    }
    else if (lower(input) == "pi")
    {
        return "0";
    }
    else if (lower(input) == "ans")
    {
        return "0";
    }
    else if (lower(input) == "mem")
    {
        return "0";
    }
    else if (numerical(input))
    {
        return "0";
    }
    else if (lower(input) == "x")
    {
        return "1";
    }
    else
    {
        error = '8'; //Undefined functions.
        return "1";
    }
}

string Calculator::decrementbyone(const string& inputstr)
{
    string result;
    long double temp = compute(inputstr) - 1;
    stringstream ss (stringstream::in | stringstream::out);
        
    ss << temp;
        
    result = ss.str();
    return result;
}
