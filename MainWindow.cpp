// MainWindow.cpp
// This file builds the UI and handles the simple app logic.

#include "MainWindow.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QRandomGenerator>
#include <QStackedWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include <fstream>
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      mainStack(nullptr),
      inputPage(nullptr),
      dashboardPage(nullptr),
      ageEdit(nullptr),
      heightEdit(nullptr),
      weightEdit(nullptr),
      goalComboBox(nullptr),
      daysComboBox(nullptr),
      typeComboBox(nullptr),
      generateButton(nullptr),
      plansButton(nullptr),
      mealsButton(nullptr),
      historyButton(nullptr),
      exercisesButton(nullptr),
      contentStack(nullptr),
      dashboardTitleLabel(nullptr),
      goalMessageLabel(nullptr),
      streakStatLabel(nullptr),
      totalCompletedStatLabel(nullptr),
      thisWeekStatLabel(nullptr),
      currentDayLabel(nullptr),
      statusBadgeLabel(nullptr),
      exerciseContainer(nullptr),
      exerciseLayout(nullptr),
      progressLabel(nullptr),
      exerciseProgressBar(nullptr),
      showMealPlanButton(nullptr),
      restartPlanButton(nullptr),
      completeDayButton(nullptr),
      smartMessageLabel(nullptr),
      caloriesLabel(nullptr),
      proteinLabel(nullptr),
      mealsTextEdit(nullptr),
      streakLabel(nullptr),
      totalWorkoutsLabel(nullptr),
      historyTextEdit(nullptr),
      exerciseLibrarySubtitleLabel(nullptr),
      chestButton(nullptr),
      backButton(nullptr),
      shouldersButton(nullptr),
      legsButton(nullptr),
      bicepsButton(nullptr),
      tricepsButton(nullptr),
      coreButton(nullptr),
      fullBodyButton(nullptr),
      muscleExerciseListWidget(nullptr),
      completionMessages({"Nice work! You're getting stronger 💪",
                          "Awesome job today! Keep moving forward 🌟",
                          "Great session! Your consistency matters 🔥",
                          "Well done! Small steps build big results ✅"}),
      currentSmartMessage("Let's get started today."),
      selectedMuscleGroup("Chest"),
      planReady(false)
{
    initializeExerciseData();
    mealPlan.loadFromFile("meal_plans.txt");
    progressTracker.loadFromFile("progress.txt");
    createUi();
    applyStyle();
}

void MainWindow::createUi()
{
    setWindowTitle("LiftMate - Beginner Fitness Tracker");
    resize(900, 620);

    auto *mainLayout = new QVBoxLayout(this);

    mainStack = new QStackedWidget(this);

    createInputPage();
    createDashboardPage();

    mainStack->addWidget(inputPage);
    mainStack->addWidget(dashboardPage);

    mainLayout->addWidget(mainStack);

    mainStack->setCurrentWidget(inputPage);
}

void MainWindow::createInputPage()
{
    inputPage = new QWidget(this);

    auto *layout = new QVBoxLayout(inputPage);

    auto *titleLabel = new QLabel("LiftMate - Beginner Fitness Tracker", inputPage);
    titleLabel->setObjectName("headerLabel");

    auto *subtitleLabel = new QLabel("Enter your information to build a simple beginner plan.", inputPage);
    subtitleLabel->setWordWrap(true);

    auto *sectionLabel = new QLabel("User Input", inputPage);
    sectionLabel->setObjectName("sectionLabel");

    auto *ageLabel = new QLabel("Age", inputPage);
    auto *heightLabel = new QLabel("Height (cm)", inputPage);
    auto *weightLabel = new QLabel("Weight (kg)", inputPage);
    auto *goalLabel = new QLabel("Goal", inputPage);
    auto *daysLabel = new QLabel("Days", inputPage);
    auto *typeLabel = new QLabel("Type", inputPage);

    ageEdit = new QLineEdit(inputPage);
    heightEdit = new QLineEdit(inputPage);
    weightEdit = new QLineEdit(inputPage);

    goalComboBox = new QComboBox(inputPage);
    goalComboBox->addItems({"Weight Loss", "Muscle Gain", "General"});

    daysComboBox = new QComboBox(inputPage);
    daysComboBox->addItems({"3", "4", "5"});

    typeComboBox = new QComboBox(inputPage);
    typeComboBox->addItems({"Gym", "Home"});

    generateButton = new QPushButton("Generate Plan", inputPage);

    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(sectionLabel);
    layout->addWidget(ageLabel);
    layout->addWidget(ageEdit);
    layout->addWidget(heightLabel);
    layout->addWidget(heightEdit);
    layout->addWidget(weightLabel);
    layout->addWidget(weightEdit);
    layout->addWidget(goalLabel);
    layout->addWidget(goalComboBox);
    layout->addWidget(daysLabel);
    layout->addWidget(daysComboBox);
    layout->addWidget(typeLabel);
    layout->addWidget(typeComboBox);
    layout->addWidget(generateButton);
    layout->addStretch();

    connect(generateButton, &QPushButton::clicked, this, [this]() {
        generatePlan();
    });
}

void MainWindow::createDashboardPage()
{
    dashboardPage = new QWidget(this);

    auto *outerLayout = new QVBoxLayout(dashboardPage);

    dashboardTitleLabel = new QLabel("LiftMate Dashboard", dashboardPage);
    dashboardTitleLabel->setObjectName("headerLabel");
    goalMessageLabel = new QLabel("Stay active today ⚡", dashboardPage);
    goalMessageLabel->setWordWrap(true);

    streakStatLabel = new QLabel(QString::fromUtf8("🔥 Streak: 0"), dashboardPage);
    totalCompletedStatLabel = new QLabel(QString::fromUtf8("✔ Total Completed: 0"), dashboardPage);
    thisWeekStatLabel = new QLabel(QString::fromUtf8("📅 This Week: 0"), dashboardPage);

    auto *headerRow = new QHBoxLayout();
    auto *titleLayout = new QVBoxLayout();
    auto *statsWidget = new QWidget(dashboardPage);
    auto *statsLayout = new QVBoxLayout(statsWidget);

    statsWidget->setObjectName("statsWidget");
    statsLayout->setContentsMargins(12, 12, 12, 12);

    titleLayout->addWidget(dashboardTitleLabel);
    titleLayout->addWidget(goalMessageLabel);

    statsLayout->addWidget(streakStatLabel);
    statsLayout->addWidget(totalCompletedStatLabel);
    statsLayout->addWidget(thisWeekStatLabel);

    headerRow->addLayout(titleLayout, 1);
    headerRow->addWidget(statsWidget);

    auto *bodyLayout = new QHBoxLayout();

    auto *menuWidget = new QWidget(dashboardPage);
    menuWidget->setObjectName("menuWidget");
    menuWidget->setFixedWidth(160);

    auto *menuLayout = new QVBoxLayout(menuWidget);

    plansButton = new QPushButton("Plans", menuWidget);
    mealsButton = new QPushButton("Meals", menuWidget);
    historyButton = new QPushButton("History", menuWidget);
    exercisesButton = new QPushButton("Exercises", menuWidget);

    menuLayout->addWidget(plansButton);
    menuLayout->addWidget(mealsButton);
    menuLayout->addWidget(historyButton);
    menuLayout->addWidget(exercisesButton);
    menuLayout->addStretch();

    contentStack = new QStackedWidget(dashboardPage);
    contentStack->addWidget(createPlansPage());
    contentStack->addWidget(createMealsPage());
    contentStack->addWidget(createHistoryPage());
    contentStack->addWidget(createExercisesPage());

    bodyLayout->addWidget(menuWidget);
    bodyLayout->addWidget(contentStack, 1);

    outerLayout->addLayout(headerRow);
    outerLayout->addLayout(bodyLayout);

    connect(plansButton, &QPushButton::clicked, this, [this]() {
        showPlansPage();
    });

    connect(mealsButton, &QPushButton::clicked, this, [this]() {
        showMealsPage();
    });

    connect(historyButton, &QPushButton::clicked, this, [this]() {
        showHistoryPage();
    });

    connect(exercisesButton, &QPushButton::clicked, this, [this]() {
        showExercisesPage();
    });

    showPlansPage();
}

QWidget *MainWindow::createPlansPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);

    auto *titleLabel = new QLabel("Plans", page);
    titleLabel->setObjectName("sectionLabel");

    statusBadgeLabel = new QLabel("Status: ⏳ In Progress", page);
    currentDayLabel = new QLabel("No plan yet.", page);

    exerciseContainer = new QWidget(page);
    exerciseLayout = new QVBoxLayout(exerciseContainer);
    exerciseLayout->setContentsMargins(0, 0, 0, 0);
    exerciseLayout->setSpacing(10);

    progressLabel = new QLabel("Progress: 0 / 0 completed", page);
    exerciseProgressBar = new QProgressBar(page);
    exerciseProgressBar->setMinimum(0);
    exerciseProgressBar->setMaximum(1);
    exerciseProgressBar->setValue(0);

    showMealPlanButton = new QPushButton("Show Meal Plan", page);
    restartPlanButton = new QPushButton("Restart Plan", page);
    showMealPlanButton->setEnabled(false);
    restartPlanButton->setEnabled(false);

    completeDayButton = new QPushButton("Complete Day", page);
    completeDayButton->setEnabled(false);
    smartMessageLabel = new QLabel("Let's get started today.", page);
    smartMessageLabel->setWordWrap(true);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(showMealPlanButton);
    buttonLayout->addWidget(restartPlanButton);
    buttonLayout->addWidget(completeDayButton);

    layout->addWidget(titleLabel);
    layout->addWidget(statusBadgeLabel);
    layout->addWidget(currentDayLabel);
    layout->addWidget(exerciseContainer);
    layout->addWidget(progressLabel);
    layout->addWidget(exerciseProgressBar);
    layout->addLayout(buttonLayout);
    layout->addWidget(smartMessageLabel);
    layout->addStretch();

    connect(completeDayButton, &QPushButton::clicked, this, [this]() {
        completeDay();
    });

    connect(showMealPlanButton, &QPushButton::clicked, this, [this]() {
        showMealPlan();
    });

    connect(restartPlanButton, &QPushButton::clicked, this, [this]() {
        restartPlan();
    });

    updateExerciseRows();

    return page;
}

QWidget *MainWindow::createMealsPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);

    auto *titleLabel = new QLabel("Meals", page);
    titleLabel->setObjectName("sectionLabel");

    caloriesLabel = new QLabel("Calories: -", page);
    proteinLabel = new QLabel("Protein: -", page);

    mealsTextEdit = new QTextEdit(page);
    mealsTextEdit->setReadOnly(true);

    layout->addWidget(titleLabel);
    layout->addWidget(caloriesLabel);
    layout->addWidget(proteinLabel);
    layout->addWidget(mealsTextEdit);

    return page;
}

QWidget *MainWindow::createHistoryPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);

    auto *titleLabel = new QLabel("History", page);
    titleLabel->setObjectName("sectionLabel");

    streakLabel = new QLabel(QString::fromUtf8("🔥 Streak: 0 days"), page);
    totalWorkoutsLabel = new QLabel("Total workouts: 0", page);

    historyTextEdit = new QTextEdit(page);
    historyTextEdit->setReadOnly(true);

    layout->addWidget(titleLabel);
    layout->addWidget(streakLabel);
    layout->addWidget(totalWorkoutsLabel);
    layout->addWidget(historyTextEdit);

    return page;
}

QWidget *MainWindow::createExercisesPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    layout->setSpacing(10);

    auto *titleLabel = new QLabel("Exercises", page);
    titleLabel->setObjectName("sectionLabel");

    exerciseLibrarySubtitleLabel = new QLabel("Select Muscle Group", page);
    exerciseLibrarySubtitleLabel->setWordWrap(true);

    chestButton = new QPushButton("Chest", page);
    backButton = new QPushButton("Back", page);
    shouldersButton = new QPushButton("Shoulders", page);
    legsButton = new QPushButton("Legs", page);
    bicepsButton = new QPushButton("Biceps", page);
    tricepsButton = new QPushButton("Triceps", page);
    coreButton = new QPushButton("Core / Abs", page);
    fullBodyButton = new QPushButton("Full Body", page);

    muscleGroupButtons = {chestButton, backButton, shouldersButton, legsButton, bicepsButton, tricepsButton, coreButton, fullBodyButton};

    layout->addWidget(titleLabel);
    layout->addWidget(exerciseLibrarySubtitleLabel);

    for (std::size_t i = 0; i < muscleGroupButtons.size(); ++i)
    {
        layout->addWidget(muscleGroupButtons[i]);
    }

    muscleExerciseListWidget = new QListWidget(page);

    layout->addWidget(muscleExerciseListWidget);
    layout->addStretch();

    connect(chestButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Chest");
        updateMuscleGroupSelection(chestButton);
    });

    connect(backButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Back");
        updateMuscleGroupSelection(backButton);
    });

    connect(shouldersButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Shoulders");
        updateMuscleGroupSelection(shouldersButton);
    });

    connect(legsButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Legs");
        updateMuscleGroupSelection(legsButton);
    });

    connect(bicepsButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Biceps");
        updateMuscleGroupSelection(bicepsButton);
    });

    connect(tricepsButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Triceps");
        updateMuscleGroupSelection(tricepsButton);
    });

    connect(coreButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Core / Abs");
        updateMuscleGroupSelection(coreButton);
    });

    connect(fullBodyButton, &QPushButton::clicked, this, [this]() {
        loadMuscleGroup("Full Body");
        updateMuscleGroupSelection(fullBodyButton);
    });

    loadMuscleGroup("Chest");
    updateMuscleGroupSelection(chestButton);

    return page;
}

void MainWindow::applyStyle()
{
    setStyleSheet(
        "QWidget { background-color: #f5f6fa; color: #202020; }"
        "QLineEdit, QComboBox, QTextEdit {"
        "  background-color: white;"
        "  border: 1px solid #cfcfcf;"
        "  border-radius: 4px;"
        "  padding: 6px;"
        "}"
        "QPushButton {"
        "  background-color: #0984e3;"
        "  color: white;"
        "  border: 1px solid #0872c2;"
        "  border-radius: 4px;"
        "  padding: 9px;"
        "}"
        "QPushButton:hover { background-color: #076bb5; }"
        "QProgressBar {"
        "  background-color: white;"
        "  border: 1px solid #cfcfcf;"
        "  border-radius: 4px;"
        "  text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: #74b9ff;"
        "  border-radius: 4px;"
        "}"
        "QListWidget {"
        "  background-color: white;"
        "  border: 1px solid #cfcfcf;"
        "  border-radius: 4px;"
        "  padding: 6px;"
        "}"
        "#headerLabel { font-size: 24px; font-weight: bold; }"
        "#sectionLabel { font-size: 18px; font-weight: bold; }"
        "#menuWidget { background-color: #dcdde1; border-radius: 6px; }"
        "#statsWidget { background-color: white; border: 1px solid #dcdde1; border-radius: 8px; }");
}

bool MainWindow::readUserInput()
{
    bool ageOk = false;
    bool heightOk = false;
    bool weightOk = false;

    int age = ageEdit->text().toInt(&ageOk);
    double height = heightEdit->text().toDouble(&heightOk);
    double weight = weightEdit->text().toDouble(&weightOk);
    int days = daysComboBox->currentText().toInt();

    if (!ageOk || !heightOk || !weightOk || age <= 0 || height <= 0 || weight <= 0)
    {
        ageEdit->setText("");
        return false;
    }

    currentUser.setData(age,
                        height,
                        weight,
                        goalComboBox->currentText().toStdString(),
                        days,
                        typeComboBox->currentText().toStdString());

    return true;
}

void MainWindow::generatePlan()
{
    if (!readUserInput())
    {
        return;
    }

    calculator.calculate(currentUser);
    workoutPlan = WorkoutPlan();
    currentSmartMessage = "Let's get started today.";
    exerciseCheckBoxes.clear();

    planReady = true;

    updateDashboard();
    mainStack->setCurrentWidget(dashboardPage);
    showPlansPage();
}

void MainWindow::completeDay()
{
    if (!planReady)
    {
        return;
    }

    std::string dayName = "Day " + std::to_string(workoutPlan.getCurrentDay()) + " finished";

    progressTracker.completeDay(dayName, QDate::currentDate());
    progressTracker.saveToFile("progress.txt");
    workoutPlan.nextDay(currentUser.days);
    currentSmartMessage = randomCompletionMessage();

    updateDashboard();
}

void MainWindow::showPlansPage()
{
    contentStack->setCurrentIndex(0);
    updateMenuSelection(plansButton);
}

void MainWindow::showMealsPage()
{
    contentStack->setCurrentIndex(1);
    updateMenuSelection(mealsButton);
}

void MainWindow::showHistoryPage()
{
    contentStack->setCurrentIndex(2);
    updateMenuSelection(historyButton);
}

void MainWindow::showExercisesPage()
{
    contentStack->setCurrentIndex(3);
    updateMenuSelection(exercisesButton);
}

void MainWindow::updateDashboard()
{
    updateStatsBox();
    updatePlansPage();
    updateMealsPage();
    updateHistoryPage();
    goalMessageLabel->setText(goalMessageText());
}

void MainWindow::updatePlansPage()
{
    if (!planReady)
    {
        currentDayLabel->setText("No plan yet.");
        completeDayButton->setEnabled(false);
        showMealPlanButton->setEnabled(false);
        restartPlanButton->setEnabled(false);
        smartMessageLabel->setText("Generate a plan to get started.");
        statusBadgeLabel->setText("Status: ⏳ In Progress");
        statusBadgeLabel->setStyleSheet("");
        updateExerciseRows();
        return;
    }

    QString text = "Current workout: Day "
                   + QString::number(workoutPlan.getCurrentDay())
                   + " - "
                   + QString::fromStdString(workoutPlan.getDayPlan(currentUser.days))
                   + " (" + QString::fromStdString(currentUser.type) + ")";

    currentDayLabel->setText(text);
    completeDayButton->setEnabled(true);
    showMealPlanButton->setEnabled(true);
    restartPlanButton->setEnabled(true);
    smartMessageLabel->setText(currentSmartMessage);
    updateExerciseRows();
}

void MainWindow::updateMealsPage()
{
    if (!planReady)
    {
        caloriesLabel->setText("Calories: -");
        proteinLabel->setText("Protein: -");
        mealsTextEdit->setPlainText("No meal plan yet.");
        return;
    }

    caloriesLabel->setText("Calories: " + QString::number(calculator.getCalories(), 'f', 0) + " kcal");
    proteinLabel->setText("Protein: " + QString::number(calculator.getProtein(), 'f', 1) + " g");
    mealsTextEdit->setPlainText(QString::fromStdString(mealPlan.getMeal(currentUser.goal)));
}

void MainWindow::updateHistoryPage()
{
    streakLabel->setText(QString::fromUtf8("🔥 Streak: ")
                         + QString::number(progressTracker.getStreak()) + " days");
    totalWorkoutsLabel->setText("Total workouts: " + QString::number(progressTracker.getTotalDays()));
    historyTextEdit->setPlainText(buildHistoryText());
}

void MainWindow::updateExerciseRows()
{
    exerciseCheckBoxes.clear();

    while (exerciseLayout->count() > 0)
    {
        QLayoutItem *item = exerciseLayout->takeAt(0);

        if (item->widget() != nullptr)
        {
            delete item->widget();
        }

        delete item;
    }

    if (!planReady)
    {
        auto *messageLabel = new QLabel("Generate a plan to see exercises.", exerciseContainer);
        exerciseLayout->addWidget(messageLabel);
        exerciseProgressBar->setMaximum(1);
        exerciseProgressBar->setValue(0);
        progressLabel->setText("Progress: 0 / 0 completed");
        return;
    }

    std::vector<std::string> exercises = workoutPlan.getExercises(currentUser.days, currentUser.type);

    for (std::size_t i = 0; i < exercises.size(); ++i)
    {
        auto *rowWidget = new QWidget(exerciseContainer);
        auto *rowLayout = new QHBoxLayout(rowWidget);
        auto *exerciseLabel = new QLabel(QString::fromStdString(exercises[i]), rowWidget);
        auto *checkBox = new QCheckBox(rowWidget);

        rowLayout->setContentsMargins(0, 0, 0, 0);

        // This keeps the label on the left and the checkbox on the right.
        rowLayout->addWidget(exerciseLabel);
        rowLayout->addStretch();
        rowLayout->addWidget(checkBox);

        exerciseLayout->addWidget(rowWidget);
        exerciseCheckBoxes.push_back(checkBox);

        connect(checkBox, &QCheckBox::toggled, this, [this]() {
            updateExerciseProgress();
        });
    }

    updateExerciseProgress();
}

void MainWindow::updateExerciseProgress()
{
    int totalExercises = static_cast<int>(exerciseCheckBoxes.size());
    int completedExercises = 0;

    for (std::size_t i = 0; i < exerciseCheckBoxes.size(); ++i)
    {
        if (exerciseCheckBoxes[i]->isChecked())
        {
            completedExercises++;
        }
    }

    if (totalExercises == 0)
    {
        exerciseProgressBar->setMaximum(1);
        exerciseProgressBar->setValue(0);
        progressLabel->setText("Progress: 0 / 0 completed");
        statusBadgeLabel->setText("Status: ⏳ In Progress");
        statusBadgeLabel->setStyleSheet("");
        return;
    }

    exerciseProgressBar->setMaximum(totalExercises);
    exerciseProgressBar->setValue(completedExercises);
    progressLabel->setText("Progress: "
                           + QString::number(completedExercises)
                           + " / "
                           + QString::number(totalExercises)
                           + " completed");

    if (completedExercises == totalExercises)
    {
        statusBadgeLabel->setText("Status: ✅ Completed");
        statusBadgeLabel->setStyleSheet("color: #00b894; font-weight: bold;");
    }
    else
    {
        statusBadgeLabel->setText("Status: ⏳ In Progress");
        statusBadgeLabel->setStyleSheet("");
    }
}

void MainWindow::updateMenuSelection(QPushButton *selectedButton)
{
    QString normalStyle =
        "QPushButton {"
        "background-color: #dcdde1;"
        "color: #202020;"
        "border: 1px solid #cccccc;"
        "border-radius: 4px;"
        "padding: 8px;"
        "text-align: left;"
        "}";

    QString selectedStyle =
        "QPushButton {"
        "background-color: #74b9ff;"
        "color: white;"
        "border: 1px solid #5ca7f5;"
        "border-radius: 4px;"
        "padding: 8px;"
        "text-align: left;"
        "font-weight: bold;"
        "}";

    plansButton->setStyleSheet(normalStyle);
    mealsButton->setStyleSheet(normalStyle);
    historyButton->setStyleSheet(normalStyle);
    exercisesButton->setStyleSheet(normalStyle);

    selectedButton->setStyleSheet(selectedStyle);
}

void MainWindow::updateMuscleGroupSelection(QPushButton *selectedButton)
{
    QString normalStyle =
        "QPushButton {"
        "background-color: #dcdde1;"
        "color: #202020;"
        "border: 1px solid #cccccc;"
        "border-radius: 4px;"
        "padding: 8px;"
        "text-align: left;"
        "}";

    QString selectedStyle =
        "QPushButton {"
        "background-color: #74b9ff;"
        "color: white;"
        "border: 1px solid #5ca7f5;"
        "border-radius: 4px;"
        "padding: 8px;"
        "text-align: left;"
        "font-weight: bold;"
        "}";

    for (std::size_t i = 0; i < muscleGroupButtons.size(); ++i)
    {
        muscleGroupButtons[i]->setStyleSheet(normalStyle);
    }

    selectedButton->setStyleSheet(selectedStyle);
}

QString MainWindow::buildHistoryText() const
{
    std::vector<std::string> history = progressTracker.getHistory();

    if (history.empty())
    {
        return "No completed workouts yet.";
    }

    QString text;

    for (std::size_t i = 0; i < history.size(); ++i)
    {
        text += QString::fromStdString(history[i]) + "\n";
    }

    return text.trimmed();
}

QString MainWindow::goalMessageText() const
{
    if (currentUser.goal == "Weight Loss")
    {
        return "Burn calories today 🔥";
    }

    if (currentUser.goal == "Muscle Gain")
    {
        return "Lift stronger today 💪";
    }

    return "Stay active today ⚡";
}

QString MainWindow::randomCompletionMessage() const
{
    if (completionMessages.empty())
    {
        return "Nice work today!";
    }

    int index = QRandomGenerator::global()->bounded(static_cast<int>(completionMessages.size()));
    return QString::fromStdString(completionMessages[index]);
}

void MainWindow::showMealPlan()
{
    if (!planReady)
    {
        return;
    }

    QMessageBox::information(this,
                             "Meal Plan",
                             QString::fromStdString(mealPlan.getMeal(currentUser.goal)));
}

void MainWindow::restartPlan()
{
    if (!planReady)
    {
        return;
    }

    workoutPlan = WorkoutPlan();
    progressTracker.resetStreak();
    progressTracker.saveToFile("progress.txt");
    currentSmartMessage = "Plan restarted. Start strong today.";

    updateDashboard();
    showPlansPage();
}

void MainWindow::updateStatsBox()
{
    streakStatLabel->setText(QString::fromUtf8("🔥 Streak: ")
                             + QString::number(progressTracker.getStreak()));
    totalCompletedStatLabel->setText(QString::fromUtf8("✔ Total Completed: ")
                                     + QString::number(progressTracker.getTotalDays()));
    thisWeekStatLabel->setText(QString::fromUtf8("📅 This Week: ")
                               + QString::number(progressTracker.getThisWeekCount()));
}

void MainWindow::loadMuscleGroup(const QString &muscleGroup)
{
    selectedMuscleGroup = muscleGroup;
    muscleExerciseListWidget->clear();

    std::string groupKey = muscleGroup.toStdString();

    if (exercises.find(groupKey) == exercises.end())
    {
        return;
    }

    const std::vector<std::string> &exerciseList = exercises[groupKey];

    for (std::size_t i = 0; i < exerciseList.size(); ++i)
    {
        muscleExerciseListWidget->addItem(QString::fromStdString(exerciseList[i]));
    }
}

void MainWindow::initializeExerciseData()
{
    // These are the default exercises used if the text file is missing.
    exercises["Chest"] = {"Bench Press", "Incline Bench Press", "Decline Bench Press", "Dumbbell Bench Press", "Incline Dumbbell Press",
                          "Chest Fly (Machine)", "Dumbbell Fly", "Cable Fly", "Pec Deck", "Push-ups",
                          "Incline Push-ups", "Decline Push-ups", "Chest Dips", "Single-arm Cable Fly", "Squeeze Press"};

    exercises["Back"] = {"Lat Pulldown", "Pull-ups", "Chin-ups", "Seated Row", "Barbell Row",
                         "Dumbbell Row", "T-Bar Row", "Cable Row", "Face Pull", "Deadlift",
                         "Straight Arm Pulldown", "Reverse Fly", "Machine Row", "Resistance Band Row", "Inverted Row"};

    exercises["Shoulders"] = {"Shoulder Press", "Dumbbell Shoulder Press", "Barbell Shoulder Press", "Arnold Press", "Lateral Raises",
                              "Front Raises", "Rear Delt Fly", "Cable Lateral Raise", "Upright Row", "Shrugs",
                              "Machine Shoulder Press", "Plate Raises", "Face Pull (rear delt)", "Reverse Pec Deck", "Pike Push-ups"};

    exercises["Legs"] = {"Squat", "Leg Press", "Lunges", "Walking Lunges", "Bulgarian Split Squat",
                         "Step-ups", "Leg Curl", "Leg Extension", "Deadlift", "Romanian Deadlift",
                         "Hip Thrust", "Glute Bridge", "Calf Raises", "Seated Calf Raise", "Wall Sit"};

    exercises["Biceps"] = {"Barbell Curl", "Dumbbell Curl", "Hammer Curl", "Concentration Curl", "Preacher Curl",
                           "Cable Curl", "Incline Dumbbell Curl", "EZ Bar Curl", "Spider Curl", "Reverse Curl",
                           "Cross-body Curl", "Machine Curl", "Resistance Band Curl", "Zottman Curl", "Chin-ups (biceps focus)"};

    exercises["Triceps"] = {"Tricep Pushdown", "Overhead Tricep Extension", "Skullcrusher", "Close-Grip Bench Press", "Bench Dips",
                            "Cable Overhead Extension", "Rope Pushdown", "Kickbacks", "Machine Tricep Extension", "Diamond Push-ups",
                            "Single-arm Pushdown", "Bar Pushdown", "EZ Bar Extension", "Resistance Band Extension", "Floor Press (close grip)"};

    exercises["Core / Abs"] = {"Crunch", "Sit-ups", "Leg Raises", "Hanging Leg Raises", "Plank",
                               "Side Plank", "Russian Twists", "Bicycle Crunch", "Mountain Climbers", "Flutter Kicks",
                               "Toe Touches", "V-ups", "Reverse Crunch", "Ab Rollout", "Dead Bug"};

    exercises["Full Body"] = {"Deadlift", "Clean and Press", "Burpees", "Kettlebell Swing", "Thrusters",
                              "Squat to Press", "Farmer's Walk", "Battle Ropes", "Jump Squats", "Push Press",
                              "Snatch (light)", "Sled Push", "Row + Squat combo", "Lunge + Curl combo", "Jump Rope"};

    loadExercisesFromFile("exercises.txt");
}

void MainWindow::loadExercisesFromFile(const std::string &fileName)
{
    std::ifstream inputFile(fileName.c_str());

    // If the file does not exist yet, write the default exercise data first.
    if (!inputFile.is_open())
    {
        saveExercisesToFile(fileName);
        return;
    }

    std::map<std::string, std::vector<std::string>> loadedExercises;
    std::string line;
    std::string currentGroup;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (line.front() == '[' && line.back() == ']')
        {
            currentGroup = line.substr(1, line.size() - 2);
            loadedExercises[currentGroup] = std::vector<std::string>();
        }
        else if (!currentGroup.empty())
        {
            loadedExercises[currentGroup].push_back(line);
        }
    }

    if (!loadedExercises.empty())
    {
        exercises = loadedExercises;
    }
}

void MainWindow::saveExercisesToFile(const std::string &fileName) const
{
    std::ofstream outputFile(fileName.c_str());

    for (std::map<std::string, std::vector<std::string>>::const_iterator it = exercises.begin();
         it != exercises.end();
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
