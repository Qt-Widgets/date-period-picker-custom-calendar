QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = datepicker-test

SOURCES = \
    main.cpp


unix|win32: LIBS += -L$$PWD/../datepicker_library/source/lib/ -ldatepicker

INCLUDEPATH += $$PWD/../datepicker_library/source/include
DEPENDPATH += $$PWD/../datepicker_library/source/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../datepicker_library/source/lib/datepicker.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../datepicker_library/source/lib/libdatepicker.a
