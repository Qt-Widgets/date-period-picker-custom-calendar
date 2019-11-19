#include "include/datepickerstandardformater.h"


class DatePickerStandardFormaterPrivate {
    Q_DECLARE_PUBLIC(DatePickerStandardFormater)

    DatePickerStandardFormater *q_ptr;
    QString date_format_template;
    QString date_time_format_template;

    DatePickerStandardFormaterPrivate(DatePickerStandardFormater *q) :
        q_ptr(q), date_format_template("d MMMM yyyy"), date_time_format_template("d MMMM yyyy hh:mm:ss") {}
    ~DatePickerStandardFormaterPrivate() {}
};

DatePickerStandardFormater::DatePickerStandardFormater() :
    DatePickerAbstractFormater(),
    d_ptr(new DatePickerStandardFormaterPrivate(this))
{
}

DatePickerStandardFormater::~DatePickerStandardFormater()
{
    delete d_ptr;
}

QString DatePickerStandardFormater::format(const QDate &date) const
{
    Q_D(const DatePickerStandardFormater);
    return date.toString(d->date_format_template);
}

QString DatePickerStandardFormater::format(const QDate &begin, const QDate &end) const
{
    Q_D(const DatePickerStandardFormater);
    return QString("%1 - %2")
            .arg(begin.toString(d->date_format_template))
            .arg(end.toString(d->date_format_template));
}

QString DatePickerStandardFormater::format(const QDateTime &begin, const QDateTime &end) const
{
    Q_D(const DatePickerStandardFormater);
    return QString("%1 - %2")
            .arg(begin.toString(d->date_time_format_template))
            .arg(end.toString(d->date_time_format_template));
}

QString DatePickerStandardFormater::dateFormatTemplate() const
{
    Q_D(const DatePickerStandardFormater);
    return d->date_format_template;
}

void DatePickerStandardFormater::setDateFormatTemplate(const QString &format_template)
{
    Q_D(DatePickerStandardFormater);
    d->date_format_template = format_template;
}

QString DatePickerStandardFormater::dateTimeFormatTemplate() const
{
    Q_D(const DatePickerStandardFormater);
    return d->date_time_format_template;
}

void DatePickerStandardFormater::setDateTimeFormatTemplate(const QString &format_template)
{
    Q_D(DatePickerStandardFormater);
    d->date_time_format_template = format_template;
}
