#Coding style rules

##Intro

The coding style is similar to [Qt coding style](https://wiki.qt.io/Qt_Coding_Style), so the Qt classes used in the code will respect the coding style.

## General
### Indentation
Use 4 spaces (no tabs) for indentation.

### Line size
Lines must not be longer than 100 characters, if necessary line breaks are required. 
Commas go at the end of wrapped lines; operators start at the beginning of the new lines.

```c++
int sumOfVeryLongExpressions = computeLongExpressions(veryLongExpression 
                                                    + veryVeryLongExpression 
                                                    + extremelyLongExpression 
                                                    + unusuallyLongExpression);

if ( (sumOfVeryLongExpressions >= anotherSumOfExpressions)
    && (sumOfVeryLongExpressions <= minimalThresholdForExpressions)
{
    
}
```

## Naming and variable declaration

### Variable naming
Variables must be declared each on a separate line. 

The name of the variable, function and methods must start with a lower case letter, and follow the [Camel case](https://en.wikipedia.org/wiki/Camel_case) style.
The name of a class must start with and upper case letter and follow the [Camel case](https://en.wikipedia.org/wiki/Camel_case) style.

The names should not be abbreviations, with some exceptions for very standard abbreviations like app.
_Example:_
```c++
int score = 0;
int totalScore = 100;
HumanPlayer firstPlayer;
firstPlayer.setScore(totalScore);
```

Constants must be names in all-caps words separated by underscores.
_Example:_
```c++
int MAX_OBJECTS = 1000;
```

### Members, getters and setters
The name of a class members must start with "m_". A getter of m_variable must have the form variable() and the setter setVariable().

_Example:_
````c++
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
    Complex();

    int real() const; //!< Getter of m_real
    void setReal(int real); //!< Setter of m_real

    int imaginary() const; //!< Getter of m_imaginary
    void setImaginary(int imaginary); //!< Setter of m_imaginary

private:
    int m_real;     //!< Real part of the complex
    int m_imaginary;//!< Imaginary part of the complex

};

#endif // COMPLEX_H
```