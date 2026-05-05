// MainWindow.h
// This class builds the two-page LiftMate interface.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QWidget>

#include "Calculator.h"
#include "MealPlan.h"
#include "ProgressTracker.h"
#include "User.h"
#include "WorkoutPlan.h"

#include <map>
#include <vector>

class QCheckBox;
class QComboBox;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QListWidget;
class QProgressBar;
class QPushButton;
class QStackedWidget;
class QTextEdit;
class QVBoxLayout;

class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    // These helper functions keep the class easier to read.
    void createUi();
    void createInputPage();
    void createDashboardPage();
    QWidget *createPlansPage();
    QWidget *createMealsPage();
    QWidget *createHistoryPage();
    QWidget *createExercisesPage();
    void applyStyle();
    bool readUserInput();
    void generatePlan();
    void completeDay();
    void showPlansPage();
    void showMealsPage();
    void showHistoryPage();
    void showExercisesPage();
    void updateDashboard();
    void updatePlansPage();
    void updateMealsPage();
    void updateHistoryPage();
    void updateExerciseRows();
    void updateExerciseProgress();
    void updateMenuSelection(QPushButton *selectedButton);
    void updateMuscleGroupSelection(QPushButton *selectedButton);
    QString buildHistoryText() const;
    QString goalMessageText() const;
    QString randomCompletionMessage() const;
    void showMealPlan();
    void restartPlan();
    void updateStatsBox();
    void loadMuscleGroup(const QString &muscleGroup);
    void initializeExerciseData();
    void loadExercisesFromFile(const std::string &fileName);
    void saveExercisesToFile(const std::string &fileName) const;

    QStackedWidget *mainStack;
    QWidget *inputPage;
    QWidget *dashboardPage;

    QLineEdit *ageEdit;
    QLineEdit *heightEdit;
    QLineEdit *weightEdit;
    QComboBox *goalComboBox;
    QComboBox *daysComboBox;
    QComboBox *typeComboBox;
    QPushButton *generateButton;

    QPushButton *plansButton;
    QPushButton *mealsButton;
    QPushButton *historyButton;
    QPushButton *exercisesButton;

    QStackedWidget *contentStack;

    QLabel *dashboardTitleLabel;
    QLabel *goalMessageLabel;
    QLabel *streakStatLabel;
    QLabel *totalCompletedStatLabel;
    QLabel *thisWeekStatLabel;

    QLabel *currentDayLabel;
    QLabel *statusBadgeLabel;
    QWidget *exerciseContainer;
    QVBoxLayout *exerciseLayout;
    QLabel *progressLabel;
    QProgressBar *exerciseProgressBar;
    QPushButton *showMealPlanButton;
    QPushButton *restartPlanButton;
    QPushButton *completeDayButton;
    QLabel *smartMessageLabel;

    QLabel *caloriesLabel;
    QLabel *proteinLabel;
    QTextEdit *mealsTextEdit;

    QLabel *streakLabel;
    QLabel *totalWorkoutsLabel;
    QTextEdit *historyTextEdit;

    QLabel *exerciseLibrarySubtitleLabel;
    QPushButton *chestButton;
    QPushButton *backButton;
    QPushButton *shouldersButton;
    QPushButton *legsButton;
    QPushButton *bicepsButton;
    QPushButton *tricepsButton;
    QPushButton *coreButton;
    QPushButton *fullBodyButton;
    QListWidget *muscleExerciseListWidget;

    User currentUser;
    Calculator calculator;
    WorkoutPlan workoutPlan;
    MealPlan mealPlan;
    ProgressTracker progressTracker;

    std::vector<QCheckBox *> exerciseCheckBoxes;
    std::vector<QPushButton *> muscleGroupButtons;
    std::vector<std::string> completionMessages;
    std::map<std::string, std::vector<std::string>> exercises;
    QString currentSmartMessage;
    QString selectedMuscleGroup;
    bool planReady;
};

#endif
