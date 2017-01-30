# Computer Algebra System
CEGEP Comprehensive Assessment project (2014)

Predefined functions:
+, -, *, / : Arithmetic operators.
abs()      : Absolute value function.
()^()      : Power function.
sqrt()     : Square root function.
ln()       : Natural logarithm function.

sin(), cos(), tan(), sec(), csc(), cot() : Trig functions.
arcsin(), arccos(), arctan() 		 : Inverse trig functions.

Special characters:
e   : 2.71828
pi  : 3.14159
ans : previous answer
mem : value stored in memory


Special operations:
end      : Ends program.
help     : Brings up help.
mode rad : Sets mode to radians.
mode deg : Sets mode to degrees.
store    : Stores previous answer in memory.
	   One answer can be stored at a time.

derive *f(x)*            : Returns symbolic derivative of f(x).
derive *f(x)* at *value* : Returns derivative of f(x) at value.

integrate *f(x)* from 
*lower bound* to *higher bound* : Returns integral of f(x) from 
				  lower bound to higher bound.
set divisions *integer*         : Sets the number of divisions 
				  for integral approximation to 
				  value of integer.

find root *f(x)* : Finds root of the equation f(x) = 0.
