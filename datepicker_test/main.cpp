#include <QApplication>

#include <datepicker.h>
#include <datepickerhumanreadableformater.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // initilize library resources (needed for translations)
    init_datepicker(&app/*, QLocale::system()*/);

    // create date picker widget
    DatePicker picker;

    DatePickerHumanReadableFormater *formater = new DatePickerHumanReadableFormater();
    // setup period delimeters in date string representation
//    formater->setDateFromWord(QString::null);
//    formater->setDateToWord("-");

    // disable showing words "today"/"yesterday"/"tomorrow" instead of date
//    formater->setSpecialDayWordShown(false);

    // formater is used for date string representation in date picker label
    picker.setFormater(formater);

    // default combination on DatePickerTypes
    picker.setAllowedPickerTypes(PeriodType | DayType);

    // editable datepicker shows calendar popup on mouse click
    picker.setEditable(true);

    // enabling time inputs (enabled by default)
    picker.setTimeEditable(true);

    // set time input format (default is hh:mm:ss)
    picker.setTimeInputFormat("hh:mm:ss");

    // date picker label can be customized in usual way
    Q_UNUSED(picker.label());

    // set initial date or period
    picker.setDate(QDate::currentDate());
//    picker.setDatePeriod(QDate::currentDate(), QDate::currentDate().addDays(1));

    // set initial time
//    picker.setTimePeriod(QTime(0, 0, 0), QTime(23, 59, 59));

//    picker.setMinimumDate(QDate(2013, 4, 23));
//    picker.setMaximumDate(QDate(2015, 9, 13));
    picker.setRange(QDate(2013, 4, 23), QDate(2015, 9, 13));

    picker.show();

    // wait for signal DatePicker::editingFinished()
    // use picker.pickerType() to obtain input format (day or period)
    // based on obtained input format extract selected date or period by
    // picker.date() or
    // picker.datePeriodBegin() and picker.datePeriodEnd()

    // if picker.isTimeEditEnabled() and picker.pickerType() is PeriodType
    // selected time range can be obtained with methods
    // picker.timePeriodBegin() and picker.timPeriodEnd()
    // or more convenient
    // picker.dateTimePeriodBegin() and picker.dateTimePeriodEnd()

    return app.exec();
}
