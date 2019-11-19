#ifndef DATEPICKERHUMANREADABLEFORMATER_H
#define DATEPICKERHUMANREADABLEFORMATER_H

#include "datepicker_common.h"
#include "datepickerabstractformater.h"

class DatePickerHumanReadableFormaterPrivate;

class DATEPICKER_EXPORT DatePickerHumanReadableFormater : public DatePickerAbstractFormater {
    Q_DECLARE_PRIVATE(DatePickerHumanReadableFormater)

    DatePickerHumanReadableFormaterPrivate * const d_ptr;
public:
    DatePickerHumanReadableFormater();
    ~DatePickerHumanReadableFormater();

    QString format(const QDate &date) const;
    QString format(const QDate &begin, const QDate &end) const;
    QString format(const QDateTime &begin, const QDateTime &end) const;

    QString dateFromWord() const;
    void setDateFromWord(const QString &word);

    QString dateToWord() const;
    void setDateToWord(const QString &word);

    QString invalidDateWord() const;
    void setInvalidDateWord(const QString &word);

    QString invalidPeriodWord() const;
    void setInvalidPeriodWord(const QString &word);

    bool isSpecialDayWordShown() const;
    void setSpecialDayWordShown(bool on);
};

#endif // DATEPICKERHUMANREADABLEFORMATER_H
