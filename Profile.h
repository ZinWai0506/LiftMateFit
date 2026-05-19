// Profile.h
// This base class stores the body information shared by a fitness user.

#ifndef PROFILE_H
#define PROFILE_H

// This class is used for inheritance.
// User will inherit age, height, and weight from here.
class Profile
{
public:
    // Start body values at zero.
    Profile()
        : age(0), height(0.0), weight(0.0)
    {
    }

    // This helper function updates the inherited body data.
    void setBodyData(int newAge, double newHeight, double newWeight)
    {
        age = newAge;
        height = newHeight;
        weight = newWeight;
    }

    int age;
    double height;
    double weight;
};

#endif
