#ifndef DATEPICKERCALENDARNAVIGATOR_H
#define DATEPICKERCALENDARNAVIGATOR_H

#include <QDate>
#include <QWidget>
#include "datepicker_common.h"

class DatePickerCalendarNavigatorPrivate;

class DatePickerCalendarNavigator : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerCalendarNavigator)

    DatePickerCalendarNavigatorPrivate * const d_ptr;
public:
    explicit DatePickerCalendarNavigator(QWidget *parent = 0);
    ~DatePickerCalendarNavigator();

    QDate date() const;
    DatePickerView view() const;
signals:
    void viewChanged(DatePickerView view);
    void toPrevious();
    void toNext();
public slots:
    void setView(DatePickerView view);
    void setDate(const QDate &date);
    void reset();
private slots:
    void onPreviousButtonClicked();
    void onNextButtonClicked();
    void onCurrentButtonClicked();
};

#endif // DATEPICKERCALENDARNAVIGATOR_H
