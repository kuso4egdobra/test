include(gtest_dependency.pri)

QT       += core gui \
            sql

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

INCLUDEPATH += ../../course_project_BD

HEADERS += \
        tst_importsqlqueries.h \
        ../../course_project_BD/BusinessLogic/ImportSqlQueries/importsqlqueries.h \
        ../../course_project_BD/loggingcategories.h

SOURCES += \
        main.cpp \
        ../../course_project_BD/BusinessLogic/ImportSqlQueries/importsqlqueries.cpp \
        ../../course_project_BD/loggingcategories.cpp
