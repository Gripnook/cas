#include <string>
using namespace std;

#ifndef MISC
#define MISC

string remove_space(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: All spaces removed from input string.

string lower(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: All alphanumerical characters converted to lowercase.

string destroy_end_brackets(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: Existing end brackets that contain the entire input expression deleted.

string minus_to_plus(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: All '-' characters outside brackets converted to '+'.

bool numerical(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: Returns true if all characters are numerical or '.', false otherwise.

bool is_num(const char& character);
//Precondition: Character has been obtained.
//Postcondition: Returns true if character is numerical or '.' or 'e' or '+' or '-', false otherwise.

bool is_actualnum(const char& character);
//Precondition: Character has been obtained.
//Postcondition: Returns true if character is numerical or '.', false otherwise.

bool is_brackets(const string& inputstr);
//Precondition: Input string has been obtained.
//Postcondition: Returns true if entire expression consists of '(' or ')', false otherwise.

string ftos(const long double& num);
//Precondition: num is of type double.
//Postcondition: num has been converted to a string.

string sub(const string& last_input, const string& x);
//Precondition: last_input and x defined.
//Postcondition: Replaces all x's in last_input with the string x.

#endif
