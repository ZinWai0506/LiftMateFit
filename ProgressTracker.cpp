// ProgressTracker.cpp
// This file updates progress values after each workout.

#include "ProgressTracker.h"

#include <QString>

#include <iostream>
#include <fstream>

ProgressTracker::ProgressTracker()
    : streak(0), totalDays(0)
{
    // Start the progress values at zero.
}

void ProgressTracker::loadFromFile(const std::string &fileName)
{
    // This try/catch block handles file or number-reading errors.
    try
    {
        // This reads saved progress from progress.txt.
        // It loads simple key-value data, history text, and completed dates.
        std::ifstream inputFile(fileName.c_str());

        // If the file is missing, create a simple default one first.
        if (!inputFile.is_open())
        {
            throw "progress.txt could not be opened.";
        }

        int loadedStreak = 0;
        int loadedTotalDays = 0;
        std::vector<std::string> loadedHistory;
        std::vector<QDate> loadedDates;
        std::string line;
        std::string currentSection;

        // Read the file one line at a time.
        while (std::getline(inputFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            if (line.front() == '[' && line.back() == ']')
            {
                // Section titles such as [Progress] or [History]
                // tell the program what kind of data comes next.
                currentSection = line.substr(1, line.size() - 2);
            }
            else if (currentSection == "Progress")
            {
                // Example line: streak=3
                std::size_t equalPosition = line.find('=');

                if (equalPosition == std::string::npos)
                {
                    continue;
                }

                std::string key = line.substr(0, equalPosition);
                std::string value = line.substr(equalPosition + 1);

                // stoi can throw if the file contains bad number text.
                if (key == "streak")
                {
                    loadedStreak = std::stoi(value);
                }
                else if (key == "totalDays")
                {
                    loadedTotalDays = std::stoi(value);
                }
            }
            else if (currentSection == "History")
            {
                loadedHistory.push_back(line);
            }
            else if (currentSection == "Dates")
            {
                // Convert plain text into a QDate object.
                QDate loadedDate = QDate::fromString(QString::fromStdString(line), "yyyy-MM-dd");

                if (loadedDate.isValid())
                {
                    loadedDates.push_back(loadedDate);
                }
            }
        }

        streak = loadedStreak;
        totalDays = loadedTotalDays;
        history = loadedHistory;
        completedDates = loadedDates;
    }
    catch (const std::exception &error)
    {
        std::cerr << "ProgressTracker load error: " << error.what() << std::endl;
        streak = 0;
        totalDays = 0;
        history.clear();
        completedDates.clear();
        saveToFile(fileName);
    }
    catch (const char *error)
    {
        std::cerr << "ProgressTracker load error: " << error << std::endl;
        streak = 0;
        totalDays = 0;
        history.clear();
        completedDates.clear();
        saveToFile(fileName);
    }
}

void ProgressTracker::saveToFile(const std::string &fileName) const
{
    // This try/catch block handles file errors while saving progress.
    try
    {
        // This writes the current progress values back into progress.txt.
        std::ofstream outputFile(fileName.c_str());

        if (!outputFile.is_open())
        {
            throw "progress.txt could not be opened for writing.";
        }

        // Save basic number values first.
        outputFile << "[Progress]\n";
        outputFile << "streak=" << streak << "\n";
        outputFile << "totalDays=" << totalDays << "\n\n";

        outputFile << "[History]\n";

        // Save each completed workout message.
        for (std::size_t i = 0; i < history.size(); ++i)
        {
            outputFile << history[i] << "\n";
        }

        outputFile << "\n[Dates]\n";

        // Save each date in a fixed text format.
        for (std::size_t i = 0; i < completedDates.size(); ++i)
        {
            outputFile << completedDates[i].toString("yyyy-MM-dd").toStdString() << "\n";
        }
    }
    catch (const char *error)
    {
        std::cerr << "ProgressTracker save error: " << error << std::endl;
    }
}

void ProgressTracker::completeDay(const std::string &dayName, const QDate &date)
{
    // This updates all progress values when one workout is completed.
    streak++;
    totalDays++;
    history.push_back(dayName);
    completedDates.push_back(date);
}

int ProgressTracker::getStreak() const
{
    return streak;
}

int ProgressTracker::getThisWeekCount() const
{
    // Count how many completed dates belong to the current calendar week.
    QDate today = QDate::currentDate();
    int currentYear = 0;
    int currentWeek = today.weekNumber(&currentYear);
    int count = 0;

    for (std::size_t i = 0; i < completedDates.size(); ++i)
    {
        // weekNumber gives the calendar week for each saved date.
        int completedYear = 0;
        int completedWeek = completedDates[i].weekNumber(&completedYear);

        if (completedWeek == currentWeek && completedYear == currentYear)
        {
            count++;
        }
    }

    return count;
}

int ProgressTracker::getTotalDays() const
{
    return totalDays;
}

std::vector<std::string> ProgressTracker::getHistory() const
{
    return history;
}

std::vector<QDate> ProgressTracker::getCompletedDates() const
{
    return completedDates;
}

void ProgressTracker::resetStreak()
{
    streak = 0;
}
