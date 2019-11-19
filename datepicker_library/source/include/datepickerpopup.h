#ifndef DATEPICKERPOPUP_H
#define DATEPICKERPOPUP_H

#include <QDate>
#include <QWidget>
#include "datepicker_common.h"

class DatePickerPopupPrivate;

class DatePickerPopup : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerPopup)

    DatePickerPopupPrivate * const d_ptr;
public:
    explicit DatePickerPopup(QWidget *parent = 0);
    ~DatePickerPopup();

    bool isTimeEditable() const;

    QString timeInputFormat() const;
signals:
    void dateSelected(const QDate &date);
    void datePeriodSelected(const QDate &begin, const QDate &end);

    void timePeriodSelected(const QTime &begin, const QTime &end);
public slots:
    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);

    void setDate(const QDate &date);
    void setDatePeriod(const QDate &begin, const QDate &end);

    void setTimePeriod(const QTime &begin, const QTime &end);

    void setDatePickerType(DatePickerType picker_type);

    void setAllowedPickerTypes(DatePickerTypes picker_types);

    void setTimeEditable(bool on);

    void setTimeInputFormat(const QString &format);

    void reset();
private slots:
    void onCalendar1DateSelected(const QDate &date);
    void onCalendar2DateSelected(const QDate &date);

    void onCalendar1Scrolled(const QDate &date);
    void onCalendar2Scrolled(const QDate &date);

    void onTimeEdit1TimeChanged(const QTime &time);
    void onTimeEdit2TimeChanged(const QTime &time);
private:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // DATEPICKERPOPUP_H
