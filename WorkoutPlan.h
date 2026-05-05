// WorkoutPlan.h
// This class controls the current workout day and exercises.

#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
#include <vector>

class WorkoutPlan
{
public:
    WorkoutPlan();

    // This returns the workout name for the current day.
    std::string getDayPlan(int days) const;

    // This returns a few simple exercises for the current day.
    std::vector<std::string> getExercises(int days, const std::string &type) const;

    // This moves to the next day and loops back after the last day.
    void nextDay(int days);

    int getCurrentDay() const;

private:
    int currentDay;
};

#endif
