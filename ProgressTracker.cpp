// ProgressTracker.cpp
// This file updates progress values after each workout.

#include "ProgressTracker.h"

#include <QString>

#include <fstream>

ProgressTracker::ProgressTracker()
    : streak(0), totalDays(0)
{
}

void ProgressTracker::loadFromFile(const std::string &fileName)
{
    std::ifstream inputFile(fileName.c_str());

    // If the file is missing, create a simple default one first.
    if (!inputFile.is_open())
    {
        saveToFile(fileName);
        return;
    }

    int loadedStreak = 0;
    int loadedTotalDays = 0;
    std::vector<std::string> loadedHistory;
    std::vector<QDate> loadedDates;
    std::string line;
    std::string currentSection;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (line.front() == '[' && line.back() == ']')
        {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == "Progress")
        {
            std::size_t equalPosition = line.find('=');

            if (equalPosition == std::string::npos)
            {
                continue;
            }

            std::string key = line.substr(0, equalPosition);
            std::string value = line.substr(equalPosition + 1);

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

void ProgressTracker::saveToFile(const std::string &fileName) const
{
    std::ofstream outputFile(fileName.c_str());

    outputFile << "[Progress]\n";
    outputFile << "streak=" << streak << "\n";
    outputFile << "totalDays=" << totalDays << "\n\n";

    outputFile << "[History]\n";

    for (std::size_t i = 0; i < history.size(); ++i)
    {
        outputFile << history[i] << "\n";
    }

    outputFile << "\n[Dates]\n";

    for (std::size_t i = 0; i < completedDates.size(); ++i)
    {
        outputFile << completedDates[i].toString("yyyy-MM-dd").toStdString() << "\n";
    }
}

void ProgressTracker::completeDay(const std::string &dayName, const QDate &date)
{
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
    QDate today = QDate::currentDate();
    int currentYear = 0;
    int currentWeek = today.weekNumber(&currentYear);
    int count = 0;

    for (std::size_t i = 0; i < completedDates.size(); ++i)
    {
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
