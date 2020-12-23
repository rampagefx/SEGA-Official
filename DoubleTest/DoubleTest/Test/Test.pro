include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_tst.h \
        ../DoublePlayer/doubleplayer.h

SOURCES += \
        double_unit_test.cpp \
        main.cpp \
        ../DoublePlayer/doubleplayer.cpp
