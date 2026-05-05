// MealPlan.h
// This class returns meal suggestions and can load them from a text file.

#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <map>
#include <string>
#include <vector>

class MealPlan
{
public:
    MealPlan();

    // These functions use a simple text file for meal plan data.
    void loadFromFile(const std::string &fileName);
    void saveToFile(const std::string &fileName) const;

    std::string getMeal(const std::string &goal) const;

private:
    std::map<std::string, std::vector<std::string>> mealPlans;
};

#endif
