//
//  Functions.h
//  CAS
//
//  Created by Andrei Purcarus on 2014-04-04.
//  Copyright (c) 2014 Andrei Purcarus. All rights reserved.
//

//Functions do not self-check for invalid input.

#ifndef FUNCTIONS
#define FUNCTIONS

const long double MAX_ERROR = 0.000000000000001;
const long double E = 2.718281828459045235360287471352662497757247093;
const long double PI = 3.141592653589793238462643383279502884197169399;
const long double DEG_TO_RAD = PI/180;
const int ARCSIN_DIVISIONS = 100; //Divisions for integral of 1/(1-x^2)^(1/2).
const int BASE_ARCTAN_DIVISIONS = 10; //Divisions for integral of 1/(1+x^2) per 1 unit interval.

namespace Andrei
{
	long double abs(const long double& argument);
	long double exp(const long double& argument);
	long double ln(const long double& argument);
	long double pow(const long double& argument, const long double& exponent);
	long double sin(const long double& argument);
	long double cos(const long double& argument);
	long double tan(const long double& argument);
	long double sec(const long double& argument);
	long double csc(const long double& argument);
	long double cot(const long double& argument);
	long double sindeg(const long double& argument);
	long double cosdeg(const long double& argument);
	long double tandeg(const long double& argument);
	long double secdeg(const long double& argument);
	long double cscdeg(const long double& argument);
	long double cotdeg(const long double& argument);
	long double arcsin(const long double& argument);
	long double arccos(const long double& argument);
	long double arctan(const long double& argument);
	long double arcsindeg(const long double& argument);
	long double arccosdeg(const long double& argument);
	long double arctandeg(const long double& argument);
}

#endif