#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T17:49:29
#
#-------------------------------------------------

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_project_BD
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    training.cpp \
    AccessData/connection.cpp \
    AccessData/accesstodb.cpp \
    AccessData/AccessDataUtil/sqlaccessdatautil.cpp \
    AccessData/AccessDataUtil/iaccessdatautil.cpp \
    AccessData/AccessDataConfiguration/accessdataconfiguration.cpp \
    AccessData/AccessDataConfiguration/importinfoconnection.cpp \
    AccessData/QueryGenerator/iquerygenerator.cpp \
    AccessData/QueryGenerator/psgrequerygenerator.cpp \
    Docs/basedoc.cpp \
    Docs/birthdoc.cpp \
    Docs/deathdoc.cpp \
    Docs/marriagedoc.cpp \
    Docs/residencedoc.cpp \
    Docs/studydoc.cpp \
    Docs/workdoc.cpp \
    UI/mainwindow.cpp \
    UI/adminwindow.cpp \
    UI/newdocumentwindow.cpp \
    UI/statisticswindow.cpp \
    BusinessLogic/ImportSqlQueries/importsqlqueries.cpp \
    BusinessLogic/DataToBusiness/datafromguitobusiness.cpp \
    terminal.cpp \
    BusinessLogic/businesslogic.cpp \
    MyClasses/myqsqlquerymodel.cpp \
    loggingcategories.cpp \
    MyClasses/myqsqlquery.cpp \
    MyClasses/myqsqldatabase.cpp

HEADERS += \
    training.h \
    AccessData/connection.h \
    AccessData/accesstodb.h \
    doc_t.h \
    AccessData/AccessDataUtil/sqlaccessdatautil.h \
    AccessData/AccessDataUtil/iaccessdatautil.h \
    AccessData/AccessDataConfiguration/accessdataconfiguration.h \
    AccessData/AccessDataConfiguration/importinfoconnection.h \
    AccessData/QueryGenerator/iquerygenerator.h \
    AccessData/QueryGenerator/psgrequerygenerator.h \
    Docs/basedoc.h \
    Docs/birthdoc.h \
    Docs/deathdoc.h \
    Docs/marriagedoc.h \
    Docs/residencedoc.h \
    Docs/studydoc.h \
    Docs/workdoc.h \
    UI/mainwindow.h \
    UI/adminwindow.h \
    UI/newdocumentwindow.h \
    UI/statisticswindow.h \
    BusinessLogic/ImportSqlQueries/importsqlqueries.h \
    BusinessLogic/DataToBusiness/datafromguitobusiness.h \
    terminal.h \
    BusinessLogic/businesslogic.h \
    MyClasses/myqsqlquerymodel.h \
    loggingcategories.h \
    MyClasses/myqsqlquery.h \
    MyClasses/myqsqldatabase.h

FORMS += \
        mainwindow.ui \
    newdocumentwindow.ui \
    UI/adminwindow.ui \
    UI/statisticswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.txt \
    sqlQueries.txt
