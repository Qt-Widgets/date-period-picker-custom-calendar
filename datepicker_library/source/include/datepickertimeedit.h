#ifndef DATEPICKERTIMEEDIT_H
#define DATEPICKERTIMEEDIT_H

#include <QTimeEdit>
#include "datepicker_common.h"

class DatePickerTimeEdit : public QTimeEdit {
    Q_OBJECT
public:
    explicit DatePickerTimeEdit(QWidget *parent = 0);
    ~DatePickerTimeEdit();
private:
    void paintEvent(QPaintEvent *event);
};

#endif // DATEPICKERTIMEEDIT_H
