#ifndef DATEPICKERCALENDARYEARVIEW_H
#define DATEPICKERCALENDARYEARVIEW_H

#include <QDate>
#include <QTableWidget>

class DatePickerCalendarYearViewPrivate;

class DatePickerCalendarYearView : public QTableWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerCalendarYearView)

    DatePickerCalendarYearViewPrivate * const d_ptr;
public:
    explicit DatePickerCalendarYearView(QWidget *parent = 0);
    ~DatePickerCalendarYearView();
signals:
    void monthClicked(int month);
public slots:
    void setDate(const QDate &date);

    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);
private slots:
    void onCellClicked(int row, int column);
};

#endif // DATEPICKERCALENDARYEARVIEW_H
