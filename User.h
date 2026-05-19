// User.h
// This class stores the user's basic information.

#ifndef USER_H
#define USER_H

#include "Profile.h"

#include <string>

using namespace std;

// User uses inheritance here.
// It gets age, height, and weight from the Profile base class.
class User : public Profile
{
public:
    // This constructor sets default values when a User object is first created.
    User();

    // This function saves all user values at one time.
    // It is related to the input page and the Generate Plan button.
    void setData(int newAge,
                 double newHeight,
                 double newWeight,
                 const string &newGoal,
                 int newDays,
                 const string &newType);

    string goal;
    int days;
    string type;
};

#endif
