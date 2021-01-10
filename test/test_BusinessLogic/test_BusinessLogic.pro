include(gtest_dependency.pri)

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

INCLUDEPATH += ../../course_project_BD

HEADERS += \
        tst_businesslogic.h \
    ../../course_project_BD/AccessData/AccessDataConfiguration/accessdataconfiguration.h \
    ../../course_project_BD/AccessData/AccessDataConfiguration/importinfoconnection.h \
    ../../course_project_BD/AccessData/AccessDataUtil/iaccessdatautil.h \
    ../../course_project_BD/AccessData/AccessDataUtil/sqlaccessdatautil.h \
    ../../course_project_BD/AccessData/QueryGenerator/iquerygenerator.h \
    ../../course_project_BD/AccessData/QueryGenerator/psgrequerygenerator.h \
    ../../course_project_BD/AccessData/accesstodb.h \
    ../../course_project_BD/AccessData/connection.h \
    ../../course_project_BD/BusinessLogic/DataToBusiness/datafromguitobusiness.h \
    ../../course_project_BD/BusinessLogic/ImportSqlQueries/importsqlqueries.h \
    ../../course_project_BD/BusinessLogic/businesslogic.h \
    ../../course_project_BD/Docs/basedoc.h \
    ../../course_project_BD/Docs/birthdoc.h \
    ../../course_project_BD/Docs/deathdoc.h \
    ../../course_project_BD/Docs/marriagedoc.h \
    ../../course_project_BD/Docs/residencedoc.h \
    ../../course_project_BD/Docs/studydoc.h \
    ../../course_project_BD/Docs/workdoc.h \
    ../../course_project_BD/MyClasses/myqsqldatabase.h \
    ../../course_project_BD/MyClasses/myqsqlquery.h \
    ../../course_project_BD/MyClasses/myqsqlquerymodel.h \
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
    ../../course_project_BD/BusinessLogic/DataToBusiness/datafromguitobusiness.cpp \
    ../../course_project_BD/BusinessLogic/ImportSqlQueries/importsqlqueries.cpp \
    ../../course_project_BD/BusinessLogic/businesslogic.cpp \
    ../../course_project_BD/Docs/basedoc.cpp \
    ../../course_project_BD/Docs/birthdoc.cpp \
    ../../course_project_BD/Docs/deathdoc.cpp \
    ../../course_project_BD/Docs/marriagedoc.cpp \
    ../../course_project_BD/Docs/residencedoc.cpp \
    ../../course_project_BD/Docs/studydoc.cpp \
    ../../course_project_BD/Docs/workdoc.cpp \
    ../../course_project_BD/MyClasses/myqsqldatabase.cpp \
    ../../course_project_BD/MyClasses/myqsqlquery.cpp \
    ../../course_project_BD/MyClasses/myqsqlquerymodel.cpp \
    ../../course_project_BD/loggingcategories.cpp \
    ../../course_project_BD/terminal.cpp
