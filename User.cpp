// User.cpp
// This file sets default values for the user.

#include "User.h"

using namespace std;

User::User()
    : Profile(), goal("General"), days(3), type("Gym")
{
    // This constructor uses an initializer list.
    // It gives starting values to the inherited body data and user-specific data.
}

void User::setData(int newAge,
                   double newHeight,
                   double newWeight,
                   const string &newGoal,
                   int newDays,
                   const string &newType)
{
    // Copy each value into the object.
    // After this, the User object keeps the entered data.
    // These three values are stored in the Profile base class.
    setBodyData(newAge, newHeight, newWeight);
    goal = newGoal;
    days = newDays;
    type = newType;
}
