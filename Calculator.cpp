// Calculator.cpp
// This file contains the simple fitness calculations.

#include "Calculator.h"

Calculator::Calculator()
    : calories(0.0), protein(0.0)
{
}

void Calculator::calculate(const User &user)
{
    // The app does not ask for gender, so this example uses one simple
    // version of the Mifflin-St Jeor formula to keep the project beginner-friendly.
    double baseCalories = (10.0 * user.weight) + (6.25 * user.height) - (5.0 * user.age) + 5.0;

    if (user.goal == "Weight Loss")
    {
        baseCalories -= 500.0;
    }
    else if (user.goal == "Muscle Gain")
    {
        baseCalories += 300.0;
    }

    calories = baseCalories;
    protein = 0.8 * user.weight;
}

double Calculator::getCalories() const
{
    return calories;
}

double Calculator::getProtein() const
{
    return protein;
}
