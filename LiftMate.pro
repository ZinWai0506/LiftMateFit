# LiftMate.pro
# This file lets the project open directly in Qt Creator.

QT += widgets

CONFIG += c++17
TEMPLATE = app
TARGET = LiftMate

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    User.cpp \
    Calculator.cpp \
    WorkoutPlan.cpp \
    MealPlan.cpp \
    ProgressTracker.cpp

HEADERS += \
    MainWindow.h \
    User.h \
    Calculator.h \
    WorkoutPlan.h \
    MealPlan.h \
    ProgressTracker.h
