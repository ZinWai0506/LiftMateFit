// Calculator.h
// This class calculates calories and protein.

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "User.h"

class Calculator
{
public:
    Calculator();

    // This function calculates calories and protein from the user data.
    void calculate(const User &user);

    double getCalories() const;
    double getProtein() const;

private:
    double calories;
    double protein;
};

#endif
