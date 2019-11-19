#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <QDate>
#include <QWidget>
#include "datepicker_common.h"

class QLabel;

class DatePickerAbstractFormater;

class DatePickerPrivate;

class DATEPICKER_EXPORT DatePicker : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(DatePicker)
private:
    DatePickerPrivate * const d_ptr;
public:
    explicit DatePicker(QWidget *parent = 0);
    ~DatePicker();

    QLabel *label() const;
    QWidget *popup() const;

    bool isEditable() const;

    bool isTimeEditable() const;

    QString timeInputFormat() const;

    DatePickerAbstractFormater *formater() const;
    void setFormater(DatePickerAbstractFormater *formater);

    DatePickerType pickerType() const;

    QDate date() const;
    QDate datePeriodBegin() const;
    QDate datePeriodEnd() const;

    QTime timePeriodBegin() const;
    QTime timePeriodEnd() const;

    QDateTime dateTimePeriodBegin() const;
    QDateTime dateTimePeriodEnd() const;
signals:
    void editingFinished();
public slots:
    void setEditable(bool on);

    void setAllowedPickerTypes(DatePickerTypes picker_types);

    void setTimeEditable(bool on);

    void setTimeInputFormat(const QString &format);

    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);
    void setRange(const QDate &minimum, const QDate &maximum);

    void setDate(const QDate &date);
    void setDatePeriod(const QDate &begin, const QDate &end);

    void setTimePeriod(const QTime &begin, const QTime &end);

    void setDateTimePeriod(const QDateTime &begin, const QDateTime &end);
private slots:
    void onShowPopupButtonClicked();
private:
    bool eventFilter(QObject *object, QEvent *event);

    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // DATEPICKER_H
