//
//  integrals.cpp
//  CAS
//
//  Created by Andrei Purcarus on 2014-04-04.
//  Copyright (c) 2014 Andrei Purcarus. All rights reserved.
//

#include <string>
#include "Calculator.h"
#include "Functions.h"
#include "Misc.h"
using namespace std;

long double Calculator::integral(const string& function, const long double& lower_limit, const long double& upper_limit)
{
	long double sum = 0;
	long double dx = (upper_limit - lower_limit) / divisions;
	long double x = lower_limit + dx;
	string input, f;
	for (int i = 1; i <= divisions; i++)
	{
		if (error == '0')
		{
			input = ftos(x);
			f = sub(function, input);
			sum += compute(f) * dx;
            x += dx;
		}
		else
		{
			break;
		}
	}
	return sum;
}

long double Calculator::midpoint_integral(const string& function, const long double& lower_limit, const long double& upper_limit)
{
    long double sum = 0;
	long double dx = (upper_limit - lower_limit) / divisions;
	long double x = lower_limit + dx / 2;
	string input, f;
	for (int i = 1; i <= divisions; i++)
	{
		if (error == '0')
		{
			input = ftos(x);
			f = sub(function, input);
			sum += compute(f) * dx;
            x += dx;
		}
		else
		{
			break;
		}
	}
	return sum;
}

long double Calculator::trapezoid_integral(const string& function, const long double& lower_limit, const long double& upper_limit)
{
    long double sum = 0;
	long double dx = (upper_limit - lower_limit) / (divisions);
	long double x = lower_limit;
	string input, f;
	for (int i = 0; i <= (divisions); i++)
	{
		if (error == '0')
		{
			if (i == 0)
			{
				input = ftos(x);
				f = sub(function, input);
				sum += compute(f) * dx;
			}
			else if (i == divisions)
			{
				input = ftos(x);
				f = sub(function, input);
				sum += compute(f) * dx;
			}
			else
			{
				input = ftos(x);
				f = sub(function, input);
				sum += 2 * compute(f) * dx;
			}
			x += dx;
		}
		else
		{
			break;
		}
	}
	return sum / 2;
}

long double Calculator::simpson_integral(const string& function, const long double& lower_limit, const long double& upper_limit)
{
    long double sum = 0;
	int total_divisions = 2*divisions;
	long double dx = (upper_limit - lower_limit) / (total_divisions);
	long double x = lower_limit;
	string input, f;
	for (int i = 0; i <= (total_divisions); i++)
	{
		if (error == '0')
		{
			if (i == 0)
			{
				input = ftos(x);
				f = sub(function, input);
				sum += compute(f) * dx;
			}
			else if (i == total_divisions)
			{
				input = ftos(x);
				f = sub(function, input);
				sum += compute(f) * dx;
			}
			else if (i % 2 == 0)
			{
				input = ftos(x);
				f = sub(function, input);
				sum += 2 * compute(f) * dx;
			}
			else
			{
				input = ftos(x);
				f = sub(function, input);
				sum += 4 * compute(f) * dx;
			}
			x += dx;
		}
		else
		{
			break;
		}
	}
	return sum / 3;
}