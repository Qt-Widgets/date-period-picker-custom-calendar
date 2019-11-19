QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = datepicker

CODECFORSRC = UTF-8

DEFINES += DATEPICKER_LIBRARY

DESTDIR = $$PWD/source/lib
DLLDESTDIR = $DESTDIR

INCLUDEPATH += \
    source

HEADERS += \
    source/include/datepicker_common.h \
    source/include/datepicker.h \
    source/include/datepickerpopupfooter.h \
    source/include/datepickerpopup.h \
    source/include/datepickercalendar.h \
    source/include/datepickercalendarnavigator.h \
    source/include/datepickercalendarmonthview.h \
    source/include/datepickercalendaryearview.h \
    source/include/datepickercalendardecadeview.h \
    source/include/datepickerabstractformater.h \
    source/include/datepickerstandardformater.h \
    source/include/datepickerhumanreadableformater.h \
    source/include/datepickertimeedit.h

SOURCES += \
    source/datepicker_common.cpp \
    source/datepicker.cpp \
    source/datepickerpopupfooter.cpp \
    source/datepickerpopup.cpp \
    source/datepickercalendar.cpp \
    source/datepickercalendarnavigator.cpp \
    source/datepickercalendarmonthview.cpp \
    source/datepickercalendaryearview.cpp \
    source/datepickercalendardecadeview.cpp \
    source/datepickerabstractformater.cpp \
    source/datepickerstandardformater.cpp \
    source/datepickerhumanreadableformater.cpp \
    source/datepickertimeedit.cpp

RESOURCES = \
    resource/datepicker_resources.qrc

TRANSLATIONS = \
    resource/locale/datepicker_en.ts \
    resource/locale/datepicker_ru.ts


#headers.files = \
#    source/include/datepicker_common.h \
#    source/include/datepicker.h \
#    source/include/datepickerabstractformater.h \
#    source/include/datepickerstandardformater.h \
#    source/include/datepickerhumanreadableformater.h
