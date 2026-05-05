// MealPlan.cpp
// This file contains meal suggestions and simple text file loading.

#include "MealPlan.h"

#include <fstream>

MealPlan::MealPlan()
{
    // These are the default meal plans used if the text file does not exist yet.
    mealPlans["Weight Loss"] = {"Chicken", "Vegetables", "Oats"};
    mealPlans["Muscle Gain"] = {"Eggs", "Chicken", "Rice", "Yogurt", "Shake"};
    mealPlans["General"] = {"Balanced meals", "Fruit", "Water"};
}

void MealPlan::loadFromFile(const std::string &fileName)
{
    std::ifstream inputFile(fileName.c_str());

    // If the file is missing, write the default data first.
    if (!inputFile.is_open())
    {
        saveToFile(fileName);
        return;
    }

    std::map<std::string, std::vector<std::string>> loadedPlans;
    std::string line;
    std::string currentGoal;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (line.front() == '[' && line.back() == ']')
        {
            currentGoal = line.substr(1, line.size() - 2);
            loadedPlans[currentGoal] = std::vector<std::string>();
        }
        else if (!currentGoal.empty())
        {
            loadedPlans[currentGoal].push_back(line);
        }
    }

    if (!loadedPlans.empty())
    {
        mealPlans = loadedPlans;
    }
}

void MealPlan::saveToFile(const std::string &fileName) const
{
    std::ofstream outputFile(fileName.c_str());

    for (std::map<std::string, std::vector<std::string>>::const_iterator it = mealPlans.begin();
         it != mealPlans.end();
         ++it)
    {
        outputFile << "[" << it->first << "]\n";

        for (std::size_t i = 0; i < it->second.size(); ++i)
        {
            outputFile << it->second[i] << "\n";
        }

        outputFile << "\n";
    }
}

std::string MealPlan::getMeal(const std::string &goal) const
{
    std::map<std::string, std::vector<std::string>>::const_iterator it = mealPlans.find(goal);

    if (it == mealPlans.end())
    {
        return "No meal plan found.";
    }

    std::string result;

    for (std::size_t i = 0; i < it->second.size(); ++i)
    {
        result += it->second[i];

        if (i + 1 < it->second.size())
        {
            result += "\n";
        }
    }

    return result;
}
