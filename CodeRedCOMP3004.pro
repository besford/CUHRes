#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T12:20:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeRedCOMP3004
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    user.cpp \
    employee.cpp \
    employeeposition.cpp \
    payrollspecialist.cpp \
    paystub.cpp \
    workterm.cpp \
    username.cpp \
    netpay.cpp \
    cunicsdb.cpp \
    employeeorm.cpp \
    userorm.cpp \
    payrollspecialistorm.cpp \
    roleorm.cpp \
    role.cpp \
    employeecontrol.cpp \
    cuhresparser.cpp \
    applyraisescontrol.cpp \
    cuhresdataprocessor.cpp

HEADERS  += mainwindow.h \
    user.h \
    employee.h \
    employeeposition.h \
    payrollspecialist.h \
    paystub.h \
    workterm.h \
    username.h \
    netpay.h \
    cunicsdb.h \
    employeeorm.h \
    userorm.h \
    payrollspecialistorm.h \
    roleorm.h \
    role.h \
    employeecontrol.h \
    cuhresparser.h \
    applyraisescontrol.h \
    cuhresdataprocessor.h


FORMS    += mainwindow.ui

DISTFILES += \
    CodeRedCOMP3004.pro.user \
    README.md

RESOURCES += \
    coderedcomp3004res.qrc

