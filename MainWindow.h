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

// These are forward declarations.
// They tell C++ that these Qt classes exist,
// so the header does not need to include every Qt header here.
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

// MainWindow is the main controller for the whole app.
// It creates the screens, connects button actions, and updates what the user sees.
class MainWindow : public QWidget
{
public:
    // This constructor starts the window and loads saved file data.
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

    // These widgets belong to the first stacked page and the dashboard page.
    // The * means these are pointers.
    // In Qt, widgets are often created with new and stored with pointers.
    QStackedWidget *mainStack;
    QWidget *inputPage;
    QWidget *dashboardPage;

    // These widgets collect the user input.
    // Each pointer will later point to a real widget object created in MainWindow.cpp.
    QLineEdit *ageEdit;
    QLineEdit *heightEdit;
    QLineEdit *weightEdit;
    QComboBox *goalComboBox;
    QComboBox *daysComboBox;
    QComboBox *typeComboBox;
    QPushButton *generateButton;

    // These buttons are the left sidebar menu on the dashboard.
    QPushButton *plansButton;
    QPushButton *mealsButton;
    QPushButton *historyButton;
    QPushButton *exercisesButton;

    // This stacked widget changes the right-side page when the sidebar is clicked.
    QStackedWidget *contentStack;

    // These labels show the dashboard title and quick stats.
    QLabel *dashboardTitleLabel;
    QLabel *goalMessageLabel;
    QLabel *streakStatLabel;
    QLabel *totalCompletedStatLabel;
    QLabel *thisWeekStatLabel;

    // These widgets belong to the Plans page.
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

    // These widgets belong to the Meals page.
    QLabel *caloriesLabel;
    QLabel *proteinLabel;
    QTextEdit *mealsTextEdit;

    // These widgets belong to the History page.
    QLabel *streakLabel;
    QLabel *totalWorkoutsLabel;
    QTextEdit *historyTextEdit;

    // These widgets belong to the Exercises page.
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

    // These objects connect the window to the other classes in the project.
    User currentUser;
    Calculator calculator;
    WorkoutPlan workoutPlan;
    MealPlan mealPlan;
    ProgressTracker progressTracker;

    // These containers help store temporary UI and exercise data.
    // vector stores a list that can grow in size.
    // map stores data using a key and a value.
    std::vector<QCheckBox *> exerciseCheckBoxes;
    std::vector<QPushButton *> muscleGroupButtons;
    std::vector<std::string> completionMessages;
    std::map<std::string, std::vector<std::string>> exercises;
    QString currentSmartMessage;
    QString selectedMuscleGroup;
    bool planReady;
};

#endif
