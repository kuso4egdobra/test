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
        tst_test_connection.h \
        ../../course_project_BD/AccessData/AccessDataConfiguration/accessdataconfiguration.h \
        ../../course_project_BD/AccessData/AccessDataConfiguration/importinfoconnection.h \
        ../../course_project_BD/AccessData/AccessDataUtil/iaccessdatautil.h \
        ../../course_project_BD/AccessData/AccessDataUtil/sqlaccessdatautil.h \
        ../../course_project_BD/AccessData/QueryGenerator/iquerygenerator.h \
        ../../course_project_BD/AccessData/QueryGenerator/psgrequerygenerator.h \
        ../../course_project_BD/AccessData/accesstodb.h \
        ../../course_project_BD/AccessData/connection.h \
        ../../course_project_BD/MyClasses/myqsqlquerymodel.h \
        ../../course_project_BD/MyClasses/myqsqlquery.h \
        ../../course_project_BD/MyClasses/myqsqldatabase.h \
        ../../course_project_BD/doc_t.h \
        ../../course_project_BD/loggingcategories.h \
        ../../course_project_BD/terminal.h

SOURCES += \
        main.cpp \
        ../../course_project_BD/AccessData/AccessDataConfiguration/accessdataconfiguration.cpp \
        ../../course_project_BD/AccessData/AccessDataConfiguration/importinfoconnection.cpp \
        ../../course_project_BD/AccessData/AccessDataUtil/iaccessdatautil.cpp \
        ../../course_project_BD/AccessData/AccessDataUtil/sqlaccessdatautil.cpp \
        ../../course_project_BD/AccessData/QueryGenerator/iquerygenerator.cpp \
        ../../course_project_BD/AccessData/QueryGenerator/psgrequerygenerator.cpp \
        ../../course_project_BD/AccessData/accesstodb.cpp \
        ../../course_project_BD/AccessData/connection.cpp \
        ../../course_project_BD/MyClasses/myqsqlquerymodel.cpp \
        ../../course_project_BD/MyClasses/myqsqlquery.cpp \
        ../../course_project_BD/MyClasses/myqsqldatabase.cpp \
        ../../course_project_BD/loggingcategories.cpp
