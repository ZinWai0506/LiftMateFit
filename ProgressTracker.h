// ProgressTracker.h
// This class stores workout progress, history, and completed dates.

#ifndef PROGRESSTRACKER_H
#define PROGRESSTRACKER_H

#include <QDate>

#include <string>
#include <vector>

class ProgressTracker
{
public:
    ProgressTracker();

    // These functions save and load progress with a simple text file.
    void loadFromFile(const std::string &fileName);
    void saveToFile(const std::string &fileName) const;

    // This updates the progress when a workout is completed.
    void completeDay(const std::string &dayName, const QDate &date);

    int getStreak() const;
    int getThisWeekCount() const;
    int getTotalDays() const;
    std::vector<std::string> getHistory() const;
    std::vector<QDate> getCompletedDates() const;

    // This resets only the streak so the user can restart the plan.
    void resetStreak();

private:
    int streak;
    int totalDays;
    std::vector<std::string> history;
    std::vector<QDate> completedDates;
};

#endif
