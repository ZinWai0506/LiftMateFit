// MealPlan.h
// This class returns meal suggestions and can load them from a text file.

#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <map>
#include <string>
#include <vector>

// MealPlan stores meal suggestions for each goal
// and can also read or write them from a text file.
class MealPlan
{
public:
    // This constructor fills the object with default meal data.
    MealPlan();

    // These functions use a simple text file for meal plan data.
    void loadFromFile(const std::string &fileName);
    void saveToFile(const std::string &fileName) const;

    // This returns the meal text for one selected goal.
    std::string getMeal(const std::string &goal) const;

private:
    // The map connects a goal name such as "Muscle Gain"
    // to a list of meal items.
    std::map<std::string, std::vector<std::string>> mealPlans;
};

#endif
