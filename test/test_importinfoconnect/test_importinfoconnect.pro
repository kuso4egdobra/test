QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../course_project_BD/

HEADERS += ../../course_project_BD/AccessData/AccessDataConfiguration/importinfoconnection.h

SOURCES +=  tst_importinfoconnect.cpp \
            ../../course_project_BD/AccessData/AccessDataConfiguration/importinfoconnection.cpp
