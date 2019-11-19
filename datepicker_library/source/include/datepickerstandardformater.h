#ifndef DATEPICKERSTANDARDFORMATER_H
#define DATEPICKERSTANDARDFORMATER_H

#include "datepicker_common.h"
#include "datepickerabstractformater.h"

class DatePickerStandardFormaterPrivate;

class DATEPICKER_EXPORT DatePickerStandardFormater : public DatePickerAbstractFormater {
    Q_DECLARE_PRIVATE(DatePickerStandardFormater)

    DatePickerStandardFormaterPrivate * const d_ptr;
public:
    DatePickerStandardFormater();
    ~DatePickerStandardFormater();

    QString format(const QDate &date) const;
    QString format(const QDate &begin, const QDate &end) const;
    QString format(const QDateTime &begin, const QDateTime &end) const;

    QString dateFormatTemplate() const;
    void setDateFormatTemplate(const QString &format_template);

    QString dateTimeFormatTemplate() const;
    void setDateTimeFormatTemplate(const QString &format_template);
};

#endif // DATEPICKERSTANDARDFORMATER_H
