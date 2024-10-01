QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS +=  ../circuitfinder.h \
            ../directedgraph.h \
            ../functions.h \
            ../structs.h

SOURCES +=  tst_tests.cpp \
            ../circuitfinder.cpp \
            ../directedgraph.cpp \
            ../functions.cpp
