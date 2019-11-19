#include "include/datepickerpopup.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include "include/datepickercalendar.h"
#include "include/datepickertimeedit.h"
#include "include/datepickerpopupfooter.h"


class DatePickerPopupPrivate {
    Q_DECLARE_PUBLIC(DatePickerPopup)

    DatePickerPopup *q_ptr;
    bool is_time_editable;
    DatePickerCalendar *calendar_widget_1;
    DatePickerCalendar *calendar_widget_2;
    DatePickerTimeEdit *time_edit_1;
    DatePickerTimeEdit *time_edit_2;
    DatePickerPopupFooter *footer;

    DatePickerPopupPrivate(DatePickerPopup *q) : q_ptr(q), is_time_editable(false) {}
    ~DatePickerPopupPrivate() {}

    void initUi()
    {
        Q_Q(DatePickerPopup);

        calendar_widget_1 = new DatePickerCalendar(q);
        calendar_widget_2 = new DatePickerCalendar(q);

        time_edit_1 = new DatePickerTimeEdit(q);
        time_edit_2 = new DatePickerTimeEdit(q);

        footer = new DatePickerPopupFooter(q);

        QGridLayout *inputs_layout = new QGridLayout();
        inputs_layout->setContentsMargins(QMargins(0, 0, 0, 5));
        inputs_layout->setHorizontalSpacing(20);
        inputs_layout->setVerticalSpacing(5);
        inputs_layout->setSizeConstraint(QLayout::SetFixedSize);

        inputs_layout->addWidget(calendar_widget_1, 0, 0);
        inputs_layout->addWidget(calendar_widget_2, 0, 1);

        inputs_layout->addWidget(time_edit_1, 1, 0);
        inputs_layout->addWidget(time_edit_2, 1, 1);

        QVBoxLayout *main_layout = new QVBoxLayout(q);
        main_layout->setContentsMargins(QMargins(15, 10, 15, 10));
        main_layout->setSizeConstraint(QLayout::SetFixedSize);
        main_layout->setSpacing(0);
        main_layout->addLayout(inputs_layout, 1);
        main_layout->addWidget(footer);

        q->setLayout(main_layout);

        q->setDatePickerType(footer->pickerType());

        q->setAttribute(Qt::WA_TranslucentBackground);

        QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(q);
        shadow_effect->setBlurRadius(10.0);
        shadow_effect->setOffset(2.0);
        q->setGraphicsEffect(shadow_effect);

        QFont font = q->font();
        font.setPointSize(9);

        q->setFont(font);

        q->setWindowTitle(QObject::tr("Date Picker"));

        q->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);
    }
};


DatePickerPopup::DatePickerPopup(QWidget *parent) :
    QWidget(parent),
    d_ptr(new DatePickerPopupPrivate(this))
{
    setObjectName("datepicker_popup");

    Q_D(DatePickerPopup);
    d->initUi();

    connect(d->calendar_widget_1, SIGNAL(dateSelected(QDate)), SLOT(onCalendar1DateSelected(QDate)));
    connect(d->calendar_widget_2, SIGNAL(dateSelected(QDate)), SLOT(onCalendar2DateSelected(QDate)));

    connect(d->calendar_widget_1, SIGNAL(scrolledTo(QDate)), SLOT(onCalendar1Scrolled(QDate)));
    connect(d->calendar_widget_2, SIGNAL(scrolledTo(QDate)), SLOT(onCalendar2Scrolled(QDate)));

    connect(d->time_edit_1, SIGNAL(timeChanged(QTime)), SLOT(onTimeEdit1TimeChanged(QTime)));
    connect(d->time_edit_2, SIGNAL(timeChanged(QTime)), SLOT(onTimeEdit2TimeChanged(QTime)));

    connect(d->footer, SIGNAL(datePickerTypeChanged(DatePickerType)),
            SLOT(setDatePickerType(DatePickerType)));

    setDate(QDate::currentDate());
    d->time_edit_1->setTime(QTime(0, 0, 0));
    d->time_edit_2->setTime(QTime(23, 59, 59));
}

DatePickerPopup::~DatePickerPopup()
{
    delete d_ptr;
}

bool DatePickerPopup::isTimeEditable() const
{
    Q_D(const DatePickerPopup);
    return d->is_time_editable;
}

QString DatePickerPopup::timeInputFormat() const
{
    Q_D(const DatePickerPopup);
    return d->time_edit_1->displayFormat();
}

void DatePickerPopup::setMinimumDate(const QDate &date)
{
    Q_D(DatePickerPopup);
    d->calendar_widget_1->setMinimumDate(date);
    d->calendar_widget_2->setMinimumDate(date);
}

void DatePickerPopup::setMaximumDate(const QDate &date)
{
    Q_D(DatePickerPopup);
    d->calendar_widget_1->setMaximumDate(date);
    d->calendar_widget_2->setMaximumDate(date);
}

void DatePickerPopup::setDatePickerType(DatePickerType picker_type)
{
    Q_D(DatePickerPopup);

    bool is_period_type = (picker_type == PeriodType);
    bool show_time_input = (is_period_type && isTimeEditable());

    d->calendar_widget_2->setVisible(is_period_type);

    d->calendar_widget_1->setFrameVisible(show_time_input);
    d->calendar_widget_2->setFrameVisible(show_time_input);

    d->time_edit_1->setVisible(show_time_input);
    d->time_edit_2->setVisible(show_time_input);

    if (is_period_type && isTimeEditable()) {
        setDatePeriod(d->calendar_widget_1->selectedDate(), d->calendar_widget_2->selectedDate());
        setTimePeriod(d->time_edit_1->time(), d->time_edit_2->time());
    }
    else if (is_period_type) {
        setDatePeriod(d->calendar_widget_1->selectedDate(), d->calendar_widget_2->selectedDate());
    }
    else {
        setDate(d->calendar_widget_1->selectedDate());
    }
}

void DatePickerPopup::setAllowedPickerTypes(DatePickerTypes picker_types)
{
    Q_D(DatePickerPopup);
    d->footer->setAllowedPickerTypes(picker_types);
}

void DatePickerPopup::setTimeEditable(bool on)
{
    Q_D(DatePickerPopup);

    d->is_time_editable = on;

    bool show_time_input = (d->is_time_editable && (d->footer->pickerType() == PeriodType));

    d->time_edit_1->setVisible(show_time_input);
    d->time_edit_2->setVisible(show_time_input);
    d->calendar_widget_1->setFrameVisible(show_time_input);
    d->calendar_widget_2->setFrameVisible(show_time_input);
}

void DatePickerPopup::setTimeInputFormat(const QString &format)
{
    Q_D(DatePickerPopup);
    d->time_edit_1->setDisplayFormat(format);
    d->time_edit_2->setDisplayFormat(format);
}

void DatePickerPopup::reset()
{
    Q_D(DatePickerPopup);
    d->calendar_widget_1->reset();
    d->calendar_widget_2->reset();
}

void DatePickerPopup::onCalendar1DateSelected(const QDate &date)
{
    Q_D(DatePickerPopup);

    if (d->footer->pickerType() == DayType)
        emit dateSelected(date);
    if (d->footer->pickerType() == PeriodType)
        emit datePeriodSelected(date, d->calendar_widget_2->selectedDate());
}

void DatePickerPopup::onCalendar2DateSelected(const QDate &date)
{
    Q_D(DatePickerPopup);

    if (d->footer->pickerType() == PeriodType)
        emit datePeriodSelected(d->calendar_widget_1->selectedDate(), date);
    if (isTimeEditable())
        emit timePeriodSelected(d->time_edit_1->time(), d->time_edit_2->time());
}

void DatePickerPopup::onCalendar1Scrolled(const QDate &date)
{
    Q_D(DatePickerPopup);

    if (d->footer->pickerType() == PeriodType)
        setDatePeriod(date, d->calendar_widget_2->selectedDate());
}

void DatePickerPopup::onCalendar2Scrolled(const QDate &date)
{
    Q_D(DatePickerPopup);

    if (d->footer->pickerType() == PeriodType)
        setDatePeriod(d->calendar_widget_1->selectedDate(), date);
}

void DatePickerPopup::onTimeEdit1TimeChanged(const QTime &time)
{
    Q_D(DatePickerPopup);

    if (isTimeEditable())
        emit timePeriodSelected(time, d->time_edit_2->time());
}

void DatePickerPopup::onTimeEdit2TimeChanged(const QTime &time)
{
    Q_D(DatePickerPopup);

    if (isTimeEditable())
        emit timePeriodSelected(d->time_edit_1->time(), time);
}

void DatePickerPopup::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect bakcground_rect = rect().adjusted(10, 10, -10, -10);;

    QPainterPath background_path(QPoint(30, 10));
    //    background_path.lineTo(50, 10);  // TODO: draw pick according to popup position
    //    background_path.lineTo(40, 0);
    background_path.addRoundedRect(bakcground_rect, 10, 10);

    painter.fillPath(background_path, Qt::white);

    event->accept();
}

void DatePickerPopup::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    QRect popup_geometry = geometry();
    popup_geometry.moveTo(parentWidget()->mapToGlobal(parentWidget()->rect().bottomLeft()));
    QRect screen_geometry = QApplication::desktop()->screenGeometry();

    if (popup_geometry.right() > screen_geometry.right())
        popup_geometry.moveRight(screen_geometry.right());
    if (popup_geometry.bottom() > screen_geometry.bottom())
        popup_geometry.moveBottom(parentWidget()->mapToGlobal(parentWidget()->rect().topLeft()).y());

    move(popup_geometry.topLeft());
}

void DatePickerPopup::setDate(const QDate &date)
{
    Q_D(DatePickerPopup);
    d->footer->setPickerType(DayType);
    d->calendar_widget_1->setDate(date);
    d->calendar_widget_2->setDate(date);
}

void DatePickerPopup::setDatePeriod(const QDate &begin, const QDate &end)
{
    Q_D(DatePickerPopup);
    d->footer->setPickerType(PeriodType);
    d->calendar_widget_1->setPeriod(begin, end, true);
    d->calendar_widget_2->setPeriod(begin, end, false);
}

void DatePickerPopup::setTimePeriod(const QTime &begin, const QTime &end)
{
    Q_D(DatePickerPopup);

    d->footer->setPickerType(PeriodType);

    d->time_edit_1->setTime(begin);
    d->time_edit_2->setTime(end);
}
