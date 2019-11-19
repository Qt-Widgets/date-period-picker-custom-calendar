#ifndef DATEPICKERABSTRACTFORMATER_H
#define DATEPICKERABSTRACTFORMATER_H

#include <QDate>
#include "datepicker_common.h"

class DATEPICKER_EXPORT DatePickerAbstractFormater {
protected:
    DatePickerAbstractFormater();
public:
    virtual ~DatePickerAbstractFormater();

    virtual QString format(const QDate &date) const = 0;
    virtual QString format(const QDate &begin, const QDate &end) const = 0;
    virtual QString format(const QDateTime &begin, const QDateTime &end) const = 0;
};

#endif // DATEPICKERABSTRACTFORMATER_H
