Виджет выбора даты/периода
==========================

Подробный пример использования можно найти [здесь](/source/unit-test/main.cpp)

Основный классы
---------------

*	[DatePicker](/source/library/source/datepicker/datepicker.h)

	Виджет выбора даты/периода при помощи выпадающего календаря

*	[DatePickerStandardFormater](/source/library/source/datepicker/datepickerstandardformater.h)

	Класс для вывода дат на экран на основе метода `QDate::toString(const QString &format)`.

*	[DatePickerHumanReadableFormater](/source/library/source/datepicker/datepickerhumanreadableformater.h)

	Класс вывода дат в удобном для чтения формате.

*	[DatePickerAbstractFormater](/source/library/source/datepicker/datepickerabstractformater.h)

	Базовый класс для написания собственных преобразователей дат в строку.
