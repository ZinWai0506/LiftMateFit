// User.h
// This class stores the user's basic information.

#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    User();

    // This function saves all user values at one time.
    void setData(int newAge,
                 double newHeight,
                 double newWeight,
                 const std::string &newGoal,
                 int newDays,
                 const std::string &newType);

    int age;
    double height;
    double weight;
    std::string goal;
    int days;
    std::string type;
};

#endif
