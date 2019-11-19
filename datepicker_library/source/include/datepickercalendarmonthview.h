#ifndef DATEPICKERCALENDARMONTHVIEW_H
#define DATEPICKERCALENDARMONTHVIEW_H

#include <QCalendarWidget>

class DatePickerCalendarMonthViewPrivate;

class DatePickerCalendarMonthView : public QCalendarWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerCalendarMonthView)

    class DatePickerCalendarMonthViewPrivate * const d_ptr;
public:
    explicit DatePickerCalendarMonthView(QWidget *parent = 0);
    ~DatePickerCalendarMonthView();

    QSize minimumSizeHint() const;
signals:
    void dateClicked(const QDate &date);
public slots:
    void setDate(const QDate &date);
    void setPeriod(const QDate &begin, const QDate &end, bool shows_begin = true);
private:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;
};

#endif // DATEPICKERCALENDARMONTHVIEW_H
