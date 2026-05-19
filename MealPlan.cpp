// MealPlan.cpp
// This file contains meal suggestions and simple text file loading.

#include "MealPlan.h"

#include <iostream>
#include <fstream>

MealPlan::MealPlan()
{
    // These are the default meal plans used if the text file does not exist yet.
    // The map key is the goal name.
    // The value is a vector that stores meal items for that goal.
    mealPlans["Weight Loss"] = {"Chicken", "Vegetables", "Oats"};
    mealPlans["Muscle Gain"] = {"Eggs", "Chicken", "Rice", "Yogurt", "Shake"};
    mealPlans["General"] = {"Balanced meals", "Fruit", "Water"};
}

void MealPlan::loadFromFile(const std::string &fileName)
{
    // This try/catch block handles file errors while reading meal data.
    try
    {
        // This reads meal data from meal_plans.txt.
        // The file format groups foods under each goal name.
        std::ifstream inputFile(fileName.c_str());

        // If the file is missing, create a default one.
        if (!inputFile.is_open())
        {
            throw "meal_plans.txt could not be opened.";
        }

        std::map<std::string, std::vector<std::string>> loadedPlans;
        std::string line;
        std::string currentGoal;

        // Read the file one line at a time.
        while (std::getline(inputFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            if (line.front() == '[' && line.back() == ']')
            {
                // Lines like [Muscle Gain] mean a new section starts here.
                currentGoal = line.substr(1, line.size() - 2);
                loadedPlans[currentGoal] = std::vector<std::string>();
            }
            else if (!currentGoal.empty())
            {
                // If we are already inside a goal section,
                // store the current line as one meal item.
                loadedPlans[currentGoal].push_back(line);
            }
        }

        // If nothing valid was loaded, keep the default meals.
        if (loadedPlans.empty())
        {
            throw "meal_plans.txt did not contain valid meal sections.";
        }

        mealPlans = loadedPlans;
    }
    catch (const char *error)
    {
        std::cerr << "MealPlan load error: " << error << std::endl;
        // The object already has default meals from the constructor,
        // so save them to a new file when loading fails.
        saveToFile(fileName);
    }
}

void MealPlan::saveToFile(const std::string &fileName) const
{
    // This try/catch block handles file errors while saving meal data.
    try
    {
        // This saves the current meal data into a text file.
        std::ofstream outputFile(fileName.c_str());

        if (!outputFile.is_open())
        {
            throw "meal_plans.txt could not be opened for writing.";
        }

        // const_iterator means we are only reading from the map,
        // not changing it while looping.
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
    catch (const char *error)
    {
        std::cerr << "MealPlan save error: " << error << std::endl;
    }
}

std::string MealPlan::getMeal(const std::string &goal) const
{
    // This looks up the selected goal and joins the food list into one text block.
    std::map<std::string, std::vector<std::string>>::const_iterator it = mealPlans.find(goal);

    if (it == mealPlans.end())
    {
        return "No meal plan found.";
    }

    std::string result;

    // Join each meal item into one string separated by line breaks.
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
