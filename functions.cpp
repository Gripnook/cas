//
//  functions.cpp
//  CAS
//
//  Created by Andrei Purcarus on 2014-04-04.
//  Copyright (c) 2014 Andrei Purcarus. All rights reserved.
//

#include "Functions.h"

namespace Andrei
{
	long double abs(const long double& argument)
	{
		if (argument >= 0)
		{
			return argument;
		}
		else
		{
			return -argument;
		}
	}

	long double exp(const long double& argument)
	{
        long double arg = argument;
        char neg = 'N';
        if (argument < 0)
        {
            arg = -argument;
            neg = 'Y';
        }
        
		long double term = 1;
		long double answer = 1;
		long double error = 1;
		int i = 1;

		do
		{
			error = answer;
			term *= arg/i;
			answer += term;
			i++;
		} while (abs(answer - error) >= MAX_ERROR);
        
        if (neg == 'N')
        {
            return answer;
        }
        else
        {
            return 1/answer;
        }
	}

	long double ln(const long double& argument)
	{
		long double temp = argument;
		int count = 0;
		while (temp > 1)
		{
			temp /= E;
			count++;
		}
		while (temp < 1/E)
		{
			temp *= E;
			count--;
		}

		long double y = temp - 1;

		long double answer = y, term = y, error = y;
		int i = 2;

		do 
		{
			error = answer;
			term *= -y;
			answer += term/i;
			i++;
		} while (abs(answer - error) >= MAX_ERROR);
		
		return (answer + count);
	}

	long double pow(const long double& argument, const long double& exponent)
	{
		if (exponent == 0)
		{
			return 1;
		}
		else
		{
			if (argument > 0)
			{
				return exp(exponent*ln(argument));
			}
			else if (argument == 0 && exponent > 0)
			{
				return 0;
			}
			else
			{
				if (exponent - static_cast<int>(exponent) == 0)
				{
                    if (static_cast<int>(exponent) % 2 == 0)
                    {
                        return exp(exponent*ln(abs(argument)));
                    }
                    else
                    {
                        return -exp(exponent*ln(abs(argument)));
                    }
				}
			}
		}
        return 0;
	}

	long double sin(const long double& argument)
	{
		long double temp = argument;
		while (temp > PI)
		{
			temp -= 2*PI;
		}
		while (temp <= -PI)
		{
			temp += 2*PI;
		}
		
		long double y = temp*temp;
		long double term = temp, error = temp, answer = temp;
		int i = 2;

		do
		{
			error = answer;
			term *= -y/(i*(i+1));
			answer += term;
			i += 2;
		} while (abs(answer - error) >= MAX_ERROR);
		
		return answer;
	}

	long double cos(const long double& argument)
	{
		long double temp = argument;
		while (temp > PI)
		{
			temp -= 2*PI;
		}
		while (temp <= -PI)
		{
			temp += 2*PI;
		}
		
		long double y = temp*temp;
		long double term = 1, error = 1, answer = 1;
		int i = 1;

		do
		{
			error = answer;
			term *= -y/(i*(i+1));
			answer += term;
			i += 2;
		} while (abs(answer - error) >= MAX_ERROR);
		
		return answer;
	}

	long double tan(const long double& argument)
	{
        return sin(argument)/cos(argument);
	}

	long double sec(const long double& argument)
	{
        return 1/cos(argument);
	}

	long double csc(const long double& argument)
	{
        return 1/sin(argument);
	}

	long double cot(const long double& argument)
	{
        return cos(argument)/sin(argument);
	}

	long double sindeg(const long double& argument)
	{
		return sin(DEG_TO_RAD * argument);
	}

	long double cosdeg(const long double& argument)
	{
		return cos(DEG_TO_RAD * argument);
	}

	long double tandeg(const long double& argument)
	{
		return tan(DEG_TO_RAD * argument);
	}

	long double secdeg(const long double& argument)
	{
		return sec(DEG_TO_RAD * argument);
	}
	long double cscdeg(const long double& argument)
	{
		return csc(DEG_TO_RAD * argument);
	}

	long double cotdeg(const long double& argument)
	{
		return cot(DEG_TO_RAD * argument);
	}

	long double arcsin(const long double& argument)
	{
		if (argument == 0)
		{
			return 0;
		}
		if (argument == 1)
		{
			return PI/2;
		}
		if (argument == -1)
		{
			return -PI/2;
		}
		long double answer = 0;
		int divisions = 2*ARCSIN_DIVISIONS;
		long double dx = (argument) / (divisions);
		long double x = 0;
		for (int i = 0; i <= (divisions); i++)
		{
			if (i == 0)
			{
				answer += (1 / (Andrei::pow(1 - x*x, 0.5))) * dx / 3;
			}
			else if (i == divisions)
			{
				answer += (1 / (Andrei::pow(1 - x*x, 0.5))) * dx / 3;
			}
				else if (i % 2 == 0)
			{
				answer += (2 / (Andrei::pow(1 - x*x, 0.5))) * dx / 3;
			}
			else
			{
				answer += (4 / (Andrei::pow(1 - x*x, 0.5))) * dx / 3;
			}
			x += dx;
		}
		return answer;
	}

	long double arccos(const long double& argument)
	{
		return PI/2 - arcsin(argument);
	}

	long double arctan(const long double& argument)
	{
		if (argument == 0)
		{
			return 0;
		}
		long double answer = 0;
		int divisions = 2*(static_cast<int>(Andrei::abs(argument)) + 1)*BASE_ARCTAN_DIVISIONS;
		long double dx = (argument) / (divisions);
		long double x = 0;
		for (int i = 0; i <= (divisions); i++)
		{
			if (i == 0)
			{
				answer += (1 / (1 + x*x)) * dx / 3;
			}
			else if (i == divisions)
			{
				answer += (1 / (1 + x*x)) * dx / 3;
			}
				else if (i % 2 == 0)
			{
				answer += (2 / (1 + x*x)) * dx / 3;
			}
			else
			{
				answer += (4 / (1 + x*x)) * dx / 3;
			}
			x += dx;
		}
		return answer;
	}

	long double arcsindeg(const long double& argument)
	{
		return arcsin(argument) / DEG_TO_RAD;
	}

	long double arccosdeg(const long double& argument)
	{
		return arccos(argument) / DEG_TO_RAD;
	}

	long double arctandeg(const long double& argument)
	{
		return arctan(argument) / DEG_TO_RAD;
	}
}