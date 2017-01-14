//
//  misc.cpp
//  CAS
//
//  Created by Andrei Purcarus on 2014-04-04.
//  Copyright (c) 2014 Andrei Purcarus. All rights reserved.
//

#include <string>
#include <sstream>
#include <cctype>
#include "Misc.h"
#include "Calculator.h"
using namespace std;

string remove_space(const string& inputstr)
{
	string result = inputstr;
	for (unsigned long i = 0; i < result.length(); i++)
	{
		if (result.at(i) == ' ')
		{
			result.erase(i, 1);
			i--;
		}
	}
	return result;
}

string lower(const string& inputstr)
{
	string result = inputstr;
	for (unsigned long i = 0; i < result.length(); i++)
	{
		result.at(i) = tolower(inputstr.at(i));
	}
	return result;
}

string destroy_end_brackets(const string& inputstr)
{
	string result = inputstr;
	if (result.empty())
	{
		return result;
	}
	if (result.at(0) != '(' || result.at(result.length() - 1) != ')')
	{
		return result;
	}
	int check = 0;
	for (unsigned long i = 1; i < result.length() - 1; i++)
	{
		if (result.at(i) == '(')
		{
			check++;
		}
		if (result.at(i) == ')')
		{
			check--;
		}
		if (check < 0)
		{
			break;
		}
	}
	if (result.at(0) == '(' && result.at(result.length() - 1) == ')' && check >= 0)
	{
		result = destroy_end_brackets(result.substr(1, result.length() - 2));
	}
	return result;
}

string minus_to_plus(const string& inputstr)
{
	string result = inputstr;
	if (result.length() > 1 && result.at(0) == '(' && result.at(1) != '-')
	{
		result = destroy_end_brackets(result);
	}
	int bracket_count = 0;
	for (unsigned long i = 0; i < result.length(); i++)
	{
		if (result.at(i) == '(')
		{
			bracket_count++;
		}
		if (result.at(i) == ')')
		{
			bracket_count--;
		}
        if ((i < 2) || (result.at(i-1) == 'e' && !is_actualnum(result.at(i-2))) || (result.at(i-1) != 'e'))
        {
            if (bracket_count == 0 && result.at(i) == '-')
            {
                result.erase(i, 1);
                result.insert(i, "+");
                i--;
            }
        }
	}
	return result;
}

bool numerical(const string& inputstr)
{
	if (inputstr.length() == 1 && inputstr.at(0) == '-')
	{
		return false;
	}
    int e_count = 0;
    long e_loc = -1;
    for (unsigned long i = 0; i < inputstr.length(); i++)
    {
        if (tolower(inputstr.at(i)) == 'e')
        {
            e_count++;
            e_loc = i;
        }
    }
    int plus_count = 0;
    long plus_loc = -1;
    for (unsigned long i = 0; i < inputstr.length(); i++)
    {
        if (tolower(inputstr.at(i)) == '+')
        {
            plus_count++;
            plus_loc = i;
        }
    }
    int minus_count = 0;
    for (unsigned long i = 0; i < inputstr.length(); i++)
    {
        if (tolower(inputstr.at(i)) == '-')
        {
            minus_count++;
        }
    }
    int dot_count = 0;
    long dot_loc = -1;
    for (unsigned long i = 0; i < inputstr.length(); i++)
    {
        if (tolower(inputstr.at(i)) == '.')
        {
            dot_count++;
            dot_loc = i;
        }
    }
    for (unsigned long i = 0; i < inputstr.length(); i++)
    {
        if (!is_num(inputstr.at(i)) || (e_count != 1 && e_count != 0) || (e_loc == 0 || e_loc == inputstr.length() - 1) || (plus_count != 0 && plus_count != 1) || (minus_count != 0 && minus_count != 1 && minus_count != 2) || (dot_count != 0 && dot_count != 1) || (plus_count == 1 && e_count == 0) || (plus_count == 1 && e_count == 1 && plus_loc != e_loc + 1) || (dot_count == 1 && e_count == 1 && dot_loc > e_loc) || (minus_count == 1 && e_count == 0 && inputstr.at(0) != '-') || (minus_count == 1 && e_count == 1 && inputstr.at(0) != '-' && inputstr.at(e_loc + 1) != '-') || (minus_count == 2 && e_count == 0) || (minus_count == 2 && e_count == 1 && (inputstr.at(0) != '-' || inputstr.at(e_loc + 1) != '-')))
        {
            return false;
        }
    }
    return true;
}

bool is_num(const char& character)
{
    return (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9' || character == '.' || character == 'e' || character == '-' || character == '+');
}

bool is_actualnum(const char& character)
{
    return (character == '0' || character == '1' || character == '2' || character == '3' || character == '4' || character == '5' || character == '6' || character == '7' || character == '8' || character == '9' || character == '.');
}

bool is_brackets(const string& inputstr)
{
	string input = inputstr;
	for (unsigned long i = 0; i < input.length(); i++)
	{
		if (input.at(i) != '(' && input.at(i) != ')')
		{
			return false;
		}
	}
	return true;
}

string ftos(const long double& num)
{
	stringstream ss (stringstream::in | stringstream::out);

	ss << num;

	return ss.str();
}

string sub(const string& last_input, const string& x)
{
    string result = last_input;
	for (int i = 0; i < static_cast<int>(result.length()); i++)
	{
        if (result.at(i) == 'x')
        {
            result.erase(i, 1);
            string temp = "(" + x + ")";
            result.insert(i, temp);
            i--;
        }
	}
	return result;
}