#include "include/datepickerpopupfooter.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QRadioButton>
#include <QButtonGroup>


class DatePickerPopupFooterPrivate {
    Q_DECLARE_PUBLIC(DatePickerPopupFooter)

    DatePickerPopupFooter *q_ptr;
    DatePickerTypes allowed_picker_types;
    QButtonGroup *picker_type_button_group;
    QRadioButton *day_picker_type_radio_button;
    QRadioButton *period_picker_type_radio_button;

    DatePickerPopupFooterPrivate(DatePickerPopupFooter *q) :
        q_ptr(q), allowed_picker_types(DayType | PeriodType) {}
    ~DatePickerPopupFooterPrivate() {}

    void initUi()
    {
        Q_Q(DatePickerPopupFooter);

        day_picker_type_radio_button = new QRadioButton(QObject::tr("day"), q);
        period_picker_type_radio_button = new QRadioButton(QObject::tr("range"), q);

        picker_type_button_group = new QButtonGroup(q);
        picker_type_button_group->setExclusive(true);
        picker_type_button_group->addButton(day_picker_type_radio_button);
        picker_type_button_group->addButton(period_picker_type_radio_button);

        QHBoxLayout *buttons_layout = new QHBoxLayout();
        buttons_layout->addWidget(day_picker_type_radio_button);
        buttons_layout->addWidget(period_picker_type_radio_button);
        buttons_layout->addStretch();

        QVBoxLayout *main_layout = new QVBoxLayout();
        main_layout->setContentsMargins(QMargins(3, 6, 3, 6));
        main_layout->setSpacing(6);

        QFrame *top_line = new QFrame(q);
        top_line->setFrameStyle(QFrame::HLine | QFrame::Plain);

        main_layout->addWidget(top_line);
        main_layout->addLayout(buttons_layout);

        q->setLayout(main_layout);

        q->setAllowedPickerTypes(allowed_picker_types);
    }
};


DatePickerPopupFooter::DatePickerPopupFooter(QWidget *parent) :
    QWidget(parent),
    d_ptr(new DatePickerPopupFooterPrivate(this))
{
    setObjectName("datepicker_popup_footer");
    Q_D(DatePickerPopupFooter);
    d->initUi();
    connect(d->picker_type_button_group, SIGNAL(buttonClicked(int)),
            SLOT(onDatePickerTypeButtonClicked()));
}

DatePickerPopupFooter::~DatePickerPopupFooter()
{
    delete d_ptr;
}

DatePickerType DatePickerPopupFooter::pickerType() const
{
    Q_D(const DatePickerPopupFooter);
    if (d->day_picker_type_radio_button->isChecked())
        return DayType;
    return PeriodType;
}

void DatePickerPopupFooter::setPickerType(DatePickerType picker_type)
{
    Q_D(DatePickerPopupFooter);
    if (pickerType() != picker_type) {
        d->day_picker_type_radio_button->setChecked(picker_type == DayType);
        d->period_picker_type_radio_button->setChecked(picker_type == PeriodType);
        onDatePickerTypeButtonClicked();
    }
}

void DatePickerPopupFooter::setAllowedPickerTypes(DatePickerTypes picker_types)
{
    Q_D(DatePickerPopupFooter);

    d->allowed_picker_types = picker_types;

    d->day_picker_type_radio_button->setVisible(picker_types & DayType);
    d->period_picker_type_radio_button->setVisible(picker_types & PeriodType);

    if (d->day_picker_type_radio_button->isVisible())
        d->day_picker_type_radio_button->setChecked(true);
    else
        d->period_picker_type_radio_button->setChecked(true);

    onDatePickerTypeButtonClicked();
}

void DatePickerPopupFooter::reset()
{
    Q_D(DatePickerPopupFooter);
    setAllowedPickerTypes(d->allowed_picker_types);
}

void DatePickerPopupFooter::onDatePickerTypeButtonClicked()
{
    DatePickerType picker_type = DayType;

    Q_D(DatePickerPopupFooter);
    if (d->day_picker_type_radio_button->isChecked())
        picker_type = DayType;
    else if (d->period_picker_type_radio_button->isChecked())
        picker_type = PeriodType;

    emit datePickerTypeChanged(picker_type);
}
