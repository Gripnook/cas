# Computer Algebra System
A command line computer algebra system developed as a CEGEP Comprehensive Assessment project in 2014.

## Usage

The program can be compiled by using the `make` utility. Note that this requires the `readline` library to be installed. The compiled executable will then be located in the build/ directory under the name `cas`.

## Features

Predefined functions:

```
+, -, *, /, ^ : Arithmetic operators.
abs(x)        : Absolute value function.
sqrt(x)       : Square root function.
ln(x)         : Natural logarithm function.

sin(x), cos(x), tan(x), sec(x), csc(x), cot(x) : Trig functions.
arcsin(x), arccos(x), arctan(x)                : Inverse trig functions.
```

Special characters:

```
e   : 2.71828
pi  : 3.14159
ans : Previous answer.
mem : Value stored in memory.
```

Special operations:

```
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
```
