// User.cpp
// This file sets default values for the user.

#include "User.h"

User::User()
    : age(0), height(0.0), weight(0.0), goal("General"), days(3), type("Gym")
{
}

void User::setData(int newAge,
                   double newHeight,
                   double newWeight,
                   const std::string &newGoal,
                   int newDays,
                   const std::string &newType)
{
    age = newAge;
    height = newHeight;
    weight = newWeight;
    goal = newGoal;
    days = newDays;
    type = newType;
}
