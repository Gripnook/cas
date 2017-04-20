#include <string>
using namespace std;

#ifndef CALCULATOR
#define CALCULATOR

const int MAX_ITERATIONS_ROOT = 1000;
const long double MAX_ERROR_ROOT = 0.000000000000001;

class Calculator
{
    public:
        Calculator();
        //Initializes the calculator to radian mode, with 10 divisions for integrals.
        
        void set_mode(const string& new_mode);
        //Sets the calculator to new_mode.
        //Accepts "rad" and "deg".

        void set_answer(const long double& value);
        //Sets answer to value.

        long double get_answer();
        //Returns answer.
        
        void set_memory(const long double& value);
        //Sets memory to value.

        void set_fmemory(const string& function);
        //Sets the function memory to function.
        
        void set_divisions(const int& new_divisions);
        //Sets the divisions for integration to new_divisions.
        
        int get_divisions();
        //Returns divisions.

        void reset_error();
        //Resets error to '0';

        char get_error();
        //Returns error;
        //error = '0': No error.
        //error = '1': Division by 0.
        //error = '2': Tangent undefined.
        //error = '3': Secant undefined.
        //error = '4': Cosecant undefined.
        //error = '5': Cotangent undefined.
        //error = '6': Ln undefined.
        //error = '7': Cannot take negative number to non-integral power.
        //error = '8': Undefined function input.
        //error = '9': Missing argument.
        //error = 'A': Arcsin undefined.
        //error = 'B': Arccos undefined.
        //error = 'C': Invalid mode;
        //error = 'M': Max iterations exceeded (root finder).

        long double compute(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Value of input string returned. If errors occured, error type stored in variable error.
        
        string derive(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of input string returned. If errors occured, error type stored in variable error.
        
        long double integral(const string& function, const long double& lower_limit, const long double& upper_limit);
        //Precondition: Function to integrate has been defined.
        //Postcondition: Returns numerical value of integral computed using right rectangles.

        long double midpoint_integral(const string& function, const long double& lower_limit, const long double& upper_limit);
        //Precondition: Function to integrate has been defined.
        //Postcondition: Returns numerical value of integral computed using midpoint rectangles.

        long double trapezoid_integral(const string& function, const long double& lower_limit, const long double& upper_limit);
        //Precondition: Function to integrate has been defined.
        //Postcondition: Returns numerical value of integral computed using trapezoids.

        long double simpson_integral(const string& function, const long double& lower_limit, const long double& upper_limit);
        //Precondition: Function to integrate has been defined.
        //Postcondition: Returns numerical value of integral computed using Simpson's rule.

        long double root(const string& function, const long double& guess);
        //Precondition: function and guess have been defined.
        //Postcondition: Returns approximation of root.

    private:
        string mode;
        char error;
        int divisions;
        long double answer;
        string fanswer;
        long double memory;
        string fmemory;
        
        //Evaluation functions:
        
        bool check_sum(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any '+' outside of brackets, false otherwise.

        long double compute_sum(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of first sum in input.

        bool check_diff(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any '-' outside of brackets, false otherwise.

        long double compute_diff(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of first difference in input.

        bool check_prod(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any '*' outside of brackets, false otherwise.

        long double compute_prod(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of first product in input.

        bool check_div(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any '/' outside of brackets, false otherwise.

        long double compute_div(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of last division in input.

        bool check_pow(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any '^' outside of brackets, false otherwise.

        long double compute_pow(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of last power in input.

        bool check_other(const string& inputstr);
        //Precondition: Input string has been obtained.
        //Postcondition: Returns true if input contains any predefined functions outside of brackets, false otherwise.

        long double compute_other(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of first function in input.

        long double numeric(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Returns value of numeric interpretation of input.
        
        //Derivative functions:
        
        string derive_sum(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of sum returned.

        string derive_diff(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of difference returned.

        string derive_prod(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of product returned.

        string derive_div(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of division returned.

        string derive_pow(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of power returned.

        string derive_other(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of other functions returned.

        string derive_simple(const string& inputstr);
        //Precondition: Input string to be computed has been obtained.
        //Postcondition: Derivative of simple function returned.
        
        string decrementbyone(const string& inputstr);
        //Precondition: Input string is numerical.
        //Postcondition: String value decremented by one.
};

#endif
