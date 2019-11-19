Date / Period Widget
==========================

Original Repository: https://github.com/dmitrytoropchin/datepicker

A detailed usage example can be found [here](/datepicker_test/main.cpp)

Core classes
---------------

*	[DatePicker](/datepicker_library/source/include/datepicker.h)

	Date / period widget using the drop-down calendar

*	[DatePickerStandardFormater](/datepicker_library/source/include/datepickerstandardformater.h)

	A class for displaying dates based on a method `QDate::toString(const QString &format)`.

*	[DatePickerHumanReadableFormater](/datepicker_library/source/include/datepickerhumanreadableformater.h)

	The date output class in a readable format.

*	[DatePickerAbstractFormater](/datepicker_library/source/include/datepickerabstractformater.h)

	The base class for writing custom date to string converters.

![screenshot](https://github.com/Qt-Widgets/date-period-picker-custom-calendar/blob/master/Screenshot1.PNG)

![screenshot](https://github.com/Qt-Widgets/date-period-picker-custom-calendar/blob/master/Screenshot2.PNG)
