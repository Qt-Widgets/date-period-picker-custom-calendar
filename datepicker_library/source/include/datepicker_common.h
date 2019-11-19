#ifndef DATEPICKER_COMMON_H
#define DATEPICKER_COMMON_H

#include <QtGlobal>
#include <QLocale>

class QApplication;

#if _WIN32
#	if defined( __MINGW32__ )
#		define DATEPICKER_EXPORT
#	else
#		if defined DATEPICKER_LIBRARY
#			define DATEPICKER_EXPORT __declspec (dllexport)
#		else
#			define DATEPICKER_EXPORT __declspec(dllimport)
#		endif
#	endif
#else
#	define DATEPICKER_EXPORT
#endif


void DATEPICKER_EXPORT init_datepicker(QApplication *app, const QLocale &locale = QLocale::system());


enum DatePickerView {
    MonthView,
    YearView,
    DecadeView
};

enum DatePickerType {
    DayType = 0x0001,
    PeriodType = 0x0002
};


Q_DECLARE_FLAGS(DatePickerTypes, DatePickerType)
Q_DECLARE_OPERATORS_FOR_FLAGS(DatePickerTypes)

#endif // DATEPICKER_COMMON_H
