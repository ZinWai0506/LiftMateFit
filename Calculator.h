// Calculator.h
// This class calculates calories and protein.

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "User.h"

class Calculator
{
public:
    // This constructor sets default result values before any calculation is done.
    Calculator();

    // This function calculates calories and protein from the user data.
    // It is related to the Meals page and the Generate Plan step.
    void calculate(const User &user);

    // This returns the calorie result for display.
    double getCalories() const;

    // This returns the protein result for display.
    double getProtein() const;

private:
    double calories;
    double protein;
};

#endif
