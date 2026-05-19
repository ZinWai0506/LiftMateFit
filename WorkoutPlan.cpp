// WorkoutPlan.cpp
// This file contains the day-by-day workout logic.

#include "WorkoutPlan.h"

WorkoutPlan::WorkoutPlan()
    : currentDay(1)
{
    // The workout cycle always starts from Day 1.
}

std::string WorkoutPlan::getDayPlan(int days) const
{
    // const means this function only reads data.
    // It does not change currentDay.
    if (days == 3)
    {
        return "Full Body";
    }

    if (days == 4)
    {
        if (currentDay == 1 || currentDay == 3)
        {
            return "Upper";
        }

        return "Lower";
    }

    if (days == 5)
    {
        if (currentDay == 1)
        {
            return "Chest";
        }
        if (currentDay == 2)
        {
            return "Back";
        }
        if (currentDay == 3)
        {
            return "Legs";
        }
        if (currentDay == 4)
        {
            return "Shoulders";
        }

        return "Arms";
    }

    return "Full Body";
}

std::vector<std::string> WorkoutPlan::getExercises(int days, const std::string &type) const
{
    // This function returns a vector of strings.
    // A vector is a list that can hold multiple exercise names.
    if (type == "Home")
    {
        if (days == 3)
        {
            return {"Bodyweight Squat", "Push-Up", "Plank"};
        }

        if (days == 4)
        {
            if (currentDay == 1 || currentDay == 3)
            {
                return {"Push-Up", "Pike Push-Up", "Chair Dip"};
            }

            return {"Squat", "Lunge", "Glute Bridge"};
        }

        if (currentDay == 1)
        {
            return {"Wide Push-Up", "Chest Press Band", "Knee Push-Up"};
        }
        if (currentDay == 2)
        {
            return {"Back Extension", "Band Row", "Superman Hold"};
        }
        if (currentDay == 3)
        {
            return {"Squat", "Lunge", "Wall Sit"};
        }
        if (currentDay == 4)
        {
            return {"Pike Push-Up", "Arm Circles", "Band Press"};
        }

        return {"Bicep Curl Band", "Chair Dip", "Hammer Curl Band"};
    }

    if (days == 3)
    {
        return {"Squat", "Bench Press", "Row"};
    }

    if (days == 4)
    {
        if (currentDay == 1 || currentDay == 3)
        {
            return {"Bench Press", "Row", "Shoulder Press"};
        }

        return {"Squat", "Leg Press", "Romanian Deadlift"};
    }

    if (currentDay == 1)
    {
        return {"Bench Press", "Chest Fly", "Push-Up"};
    }
    if (currentDay == 2)
    {
        return {"Lat Pulldown", "Seated Row", "Deadlift"};
    }
    if (currentDay == 3)
    {
        return {"Squat", "Leg Press", "Lunge"};
    }
    if (currentDay == 4)
    {
        return {"Shoulder Press", "Lateral Raise", "Front Raise"};
    }

    return {"Bicep Curl", "Tricep Pushdown", "Hammer Curl"};
}

void WorkoutPlan::nextDay(int days)
{
    // Move to the next workout day.
    currentDay++;

    // If the current day goes past the selected plan,
    // loop back to Day 1 again.
    if (currentDay > days)
    {
        currentDay = 1;
    }
}

int WorkoutPlan::getCurrentDay() const
{
    // Return the current workout day number.
    return currentDay;
}
