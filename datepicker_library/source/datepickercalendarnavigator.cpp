#include "include/datepickercalendarnavigator.h"
#include <QHBoxLayout>
#include <QPushButton>


class DatePickerCalendarNavigatorPrivate {
    Q_DECLARE_PUBLIC(DatePickerCalendarNavigator)

    DatePickerCalendarNavigator *q_ptr;
    DatePickerView picker_view;
    QDate date;
    QPushButton *previous_button;
    QPushButton *next_button;
    QPushButton *current_button;

    DatePickerCalendarNavigatorPrivate(DatePickerCalendarNavigator *q) : q_ptr(q) {}
    ~DatePickerCalendarNavigatorPrivate() {}

    void initUi()
    {
        Q_Q(DatePickerCalendarNavigator);

        picker_view = MonthView;

        previous_button = new QPushButton("<", q);
        previous_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        previous_button->setFixedSize(20, 20);
        previous_button->setFlat(true);
        previous_button->setCursor(Qt::PointingHandCursor);
        previous_button->setFocusPolicy(Qt::NoFocus);

        next_button = new QPushButton(">", q);
        next_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        next_button->setFixedSize(20, 20);
        next_button->setFlat(true);
        next_button->setCursor(Qt::PointingHandCursor);
        next_button->setFocusPolicy(Qt::NoFocus);

        current_button = new QPushButton(q);
        current_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        current_button->setFixedHeight(20);
        current_button->setFlat(true);
        current_button->setCursor(Qt::PointingHandCursor);
        current_button->setFocusPolicy(Qt::NoFocus);

        QHBoxLayout *main_layout = new QHBoxLayout(q);
        main_layout->setContentsMargins(QMargins(0, 9, 0, 0));
        main_layout->addWidget(previous_button);
        main_layout->addWidget(current_button);
        main_layout->addWidget(next_button);

        q->setLayout(main_layout);

        QFont font = q->font();
        font.setBold(true);
        q->setFont(font);
    }
};


DatePickerCalendarNavigator::DatePickerCalendarNavigator(QWidget *parent) :
    QWidget(parent),
    d_ptr(new DatePickerCalendarNavigatorPrivate(this))
{
    Q_D(DatePickerCalendarNavigator);

    d->initUi();

    connect(d->previous_button, SIGNAL(clicked()), SLOT(onPreviousButtonClicked()));
    connect(d->next_button, SIGNAL(clicked()), SLOT(onNextButtonClicked()));
    connect(d->current_button, SIGNAL(clicked()), SLOT(onCurrentButtonClicked()));

}

DatePickerCalendarNavigator::~DatePickerCalendarNavigator()
{
    delete d_ptr;
}

QDate DatePickerCalendarNavigator::date() const
{
    Q_D(const DatePickerCalendarNavigator);
    return d->date;
}

DatePickerView DatePickerCalendarNavigator::view() const
{
    Q_D(const DatePickerCalendarNavigator);
    return d->picker_view;
}

void DatePickerCalendarNavigator::setView(DatePickerView view)
{
    Q_D(DatePickerCalendarNavigator);
    if (d->picker_view != view) {
        d->picker_view = view;
        setDate(d->date);
        emit viewChanged(view);
    }
}

void DatePickerCalendarNavigator::setDate(const QDate &date)
{
    Q_D(DatePickerCalendarNavigator);

    d->date = date;

    QString current_button_text = QString::null;

    switch (d->picker_view) {
        case MonthView:
            current_button_text = date.toString("MMMM yyyy");
            break;
        case YearView:
            current_button_text = date.toString("yyyy");
            break;
        case DecadeView:
            current_button_text = QString("%1 - %2")
                                  .arg(date.addYears(-4).toString("yyyy"))
                                  .arg(date.addYears(5).toString("yyyy"));
            break;
        default:
            break;
    }

    d->current_button->setText(current_button_text);
}

void DatePickerCalendarNavigator::reset()
{
    setView(MonthView);
}

void DatePickerCalendarNavigator::onPreviousButtonClicked()
{
    emit toPrevious();
}

void DatePickerCalendarNavigator::onNextButtonClicked()
{
    emit toNext();
}

void DatePickerCalendarNavigator::onCurrentButtonClicked()
{
    Q_D(DatePickerCalendarNavigator);
    switch (d->picker_view) {
        case MonthView:
            setView(YearView);
            break;
        case YearView:
            setView(DecadeView);
            break;
        case DecadeView:
            break;
        default:
            break;
    }
}
