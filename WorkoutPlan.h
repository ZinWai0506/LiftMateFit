// WorkoutPlan.h
// This class controls the current workout day and exercises.

#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
#include <vector>

// WorkoutPlan controls which day the user is on
// and which workout/exercises should be shown for that day.
class WorkoutPlan
{
public:
    // This constructor starts the workout at Day 1.
    WorkoutPlan();

    // This returns the workout name for the current day.
    std::string getDayPlan(int days) const;

    // This returns the exercise list for the current day and workout type.
    std::vector<std::string> getExercises(int days, const std::string &type) const;

    // This moves to the next day and loops back after the last day.
    void nextDay(int days);

    // This returns the current workout day number.
    int getCurrentDay() const;

private:
    // This keeps track of which workout day is currently active.
    int currentDay;
};

#endif
