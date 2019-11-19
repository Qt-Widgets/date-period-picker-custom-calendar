#ifndef DATEPICKERCALENDAR_H
#define DATEPICKERCALENDAR_H

#include <QDate>
#include <QWidget>
#include "datepicker_common.h"

class DatePickerCalendarPrivate;

class DatePickerCalendar : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerCalendar)

    DatePickerCalendarPrivate * const d_ptr;
public:
    explicit DatePickerCalendar(QWidget *parent = 0);
    ~DatePickerCalendar();

    QDate selectedDate() const;
signals:
    void dateSelected(const QDate &date);
    void scrolledTo(const QDate &date);
public slots:
    void setFrameVisible(bool on);

    void setView(DatePickerView picker_view);

    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);

    void setDate(const QDate &date);
    void setPeriod(const QDate &begin, const QDate &end, bool shows_begin = true);

    void previous();
    void next();

    void reset();
private slots:
    void onYearViewMonthClicked(int month);
    void onDecadeViewYearClicked(int year);
    void onCurrentMonthChanged(int year, int month);
};

#endif // DATEPICKERCALENDAR_H
