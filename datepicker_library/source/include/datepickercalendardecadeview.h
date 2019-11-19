#ifndef DATEPICKERCALENDARDECADEVIEW_H
#define DATEPICKERCALENDARDECADEVIEW_H

#include <QDate>
#include <QTableWidget>

class DatePickerCalendarDecadeViewPrivate;

class DatePickerCalendarDecadeView : public QTableWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePickerCalendarDecadeView)

    DatePickerCalendarDecadeViewPrivate * const d_ptr;
public:
    explicit DatePickerCalendarDecadeView(QWidget *parent = 0);
    ~DatePickerCalendarDecadeView();
signals:
    void yearClicked(int year);
public slots:
    void setDate(const QDate &date);

    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);
private slots:
    void onCellClicked(int row, int column);
};

#endif // DATEPICKERCALENDARDECADEVIEW_H
