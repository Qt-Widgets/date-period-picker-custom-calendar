#include "include/datepicker.h"
#include <QDate>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>
#include "include/datepickerpopup.h"
#include "include/datepickerabstractformater.h"
#include "include/datepickerhumanreadableformater.h"


class DatePickerPrivate {
    Q_DECLARE_PUBLIC(DatePicker)

    DatePicker *q_ptr;
    bool is_editable;
    DatePickerType picker_type;
    QDate date_begin;
    QDate date_end;
    QTime time_begin;
    QTime time_end;
    QLabel *date_label;
    QPushButton *show_popup_button;
    DatePickerPopup *popup;
    DatePickerAbstractFormater *formater;
private:
    DatePickerPrivate(DatePicker *q) :
        q_ptr(q), is_editable(true), picker_type(DayType), date_label(0), popup(0), formater(0) {}

    ~DatePickerPrivate()
    {
        delete popup;

        if (formater != 0)
            delete formater;
    }

    void initUi()
    {
        Q_Q(DatePicker);

        formater = new DatePickerHumanReadableFormater();

        date_label = new QLabel(q);
        date_label->setObjectName("datepicker_label");
        date_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        date_label->installEventFilter(q);

        show_popup_button = new QPushButton(QIcon(":/datepicker_icons/calendar-button-icon"), QString::null, q);
        show_popup_button->setToolTip(QObject::tr("Edit"));
        show_popup_button->setFlat(true);
        show_popup_button->setFixedSize(20, 20);
        show_popup_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        show_popup_button->setCursor(Qt::PointingHandCursor);
        show_popup_button->setFocusPolicy(Qt::NoFocus);

        popup = new DatePickerPopup(q);
        popup->installEventFilter(q);
        popup->adjustSize();

        q->setLayout(new QHBoxLayout(q));
        q->layout()->setContentsMargins(QMargins());
        q->layout()->addWidget(date_label);
        q->layout()->addWidget(show_popup_button);

        q->setWindowTitle(QObject::tr("Date Picker"));
    }

    void adjustPopupPosition()
    {
        Q_Q(DatePicker);

        QRect popup_geometry = popup->geometry();
        popup_geometry.moveTo(q->mapToGlobal(q->rect().bottomLeft()));
        QRect screen_geometry = QApplication::desktop()->screenGeometry(q);

        if (popup_geometry.right() > screen_geometry.right())
            popup_geometry.moveRight(screen_geometry.right());
        if (popup_geometry.bottom() > screen_geometry.bottom())
            popup_geometry.moveBottom(q->mapToGlobal(q->rect().topLeft()).y());

        popup->move(popup_geometry.topLeft());
    }
};

DatePicker::DatePicker(QWidget *parent) :
    QWidget(parent),
    d_ptr(new DatePickerPrivate(this))
{
    Q_D(DatePicker);
    d->initUi();

    connect(d->show_popup_button, SIGNAL(clicked()), SLOT(onShowPopupButtonClicked()));

    connect(d->popup, SIGNAL(dateSelected(QDate)), SLOT(setDate(QDate)));
    connect(d->popup, SIGNAL(datePeriodSelected(QDate,QDate)), SLOT(setDatePeriod(QDate,QDate)));
    connect(d->popup, SIGNAL(timePeriodSelected(QTime,QTime)), SLOT(setTimePeriod(QTime,QTime)));

    d->date_begin = QDate::currentDate();
    d->date_end = QDate::currentDate();

    d->time_begin = QTime(0, 0, 0);
    d->time_end = QTime(23, 59, 59);
}

DatePicker::~DatePicker()
{
    delete d_ptr;
}

QLabel *DatePicker::label() const
{
    Q_D(const DatePicker);
    return d->date_label;
}

QWidget *DatePicker::popup() const
{
    Q_D(const DatePicker);
    return d->popup;
}

bool DatePicker::isEditable() const
{
    Q_D(const DatePicker);
    return d->is_editable;
}

bool DatePicker::isTimeEditable() const
{
    Q_D(const DatePicker);
    return d->popup->isTimeEditable();
}

QString DatePicker::timeInputFormat() const
{
    Q_D(const DatePicker);
    return d->popup->timeInputFormat();
}

DatePickerAbstractFormater *DatePicker::formater() const
{
    Q_D(const DatePicker);
    return d->formater;
}

void DatePicker::setFormater(DatePickerAbstractFormater *formater)
{
    Q_D(DatePicker);

    if (d->formater != 0) {
        delete d->formater;
        d->formater = 0;
    }

    d->formater = formater;

    if (d->formater != 0) {
        if (d->picker_type == DayType) {
            setDate(d->date_begin);
        }
        if (d->picker_type == PeriodType) {
            setDatePeriod(d->date_begin, d->date_end);
            if (isTimeEditable())
                setTimePeriod(d->time_begin, d->time_end);
        }
    }
}

DatePickerType DatePicker::pickerType() const
{
    Q_D(const DatePicker);
    return d->picker_type;
}

QDate DatePicker::date() const
{
    Q_D(const DatePicker);
    return d->date_begin;
}

QDate DatePicker::datePeriodBegin() const
{
    Q_D(const DatePicker);
    return d->date_begin;
}

QDate DatePicker::datePeriodEnd() const
{
    Q_D(const DatePicker);
    return d->date_end;
}

QTime DatePicker::timePeriodBegin() const
{
    Q_D(const DatePicker);
    return d->time_begin;
}

QTime DatePicker::timePeriodEnd() const
{
    Q_D(const DatePicker);
    return d->time_end;
}

QDateTime DatePicker::dateTimePeriodBegin() const
{
    Q_D(const DatePicker);
    return QDateTime(d->date_begin, d->time_begin);
}

QDateTime DatePicker::dateTimePeriodEnd() const
{
    Q_D(const DatePicker);
    return QDateTime(d->date_end, d->time_end);
}

void DatePicker::setEditable(bool on)
{
    Q_D(DatePicker);
    d->is_editable = on;
    d->show_popup_button->setVisible(on);
}

void DatePicker::setAllowedPickerTypes(DatePickerTypes picker_types)
{
    Q_D(DatePicker);
    d->popup->setAllowedPickerTypes(picker_types);
}

void DatePicker::setTimeEditable(bool on)
{
    Q_D(DatePicker);
    d->popup->setTimeEditable(on);
}

void DatePicker::setTimeInputFormat(const QString &format)
{
    Q_D(DatePicker);
    d->popup->setTimeInputFormat(format);
}

void DatePicker::setMinimumDate(const QDate &date)
{
    Q_D(DatePicker);
    d->popup->setMinimumDate(date);
}

void DatePicker::setMaximumDate(const QDate &date)
{
    Q_D(DatePicker);
    d->popup->setMaximumDate(date);
}

void DatePicker::setRange(const QDate &minimum, const QDate &maximum)
{
    Q_D(DatePicker);
    d->popup->setMinimumDate(minimum);
    d->popup->setMaximumDate(maximum);
}

void DatePicker::setDate(const QDate &date)
{
    Q_D(DatePicker);

    d->picker_type = DayType;

    d->date_begin = date;
    d->date_end = date;

    d->popup->setDate(date);

    if (d->formater != 0)
        d->date_label->setText(d->formater->format(date));
    else
        d->date_label->clear();
}

void DatePicker::setDatePeriod(const QDate &begin, const QDate &end)
{
    Q_D(DatePicker);

    d->picker_type = PeriodType;

    d->date_begin = begin;
    d->date_end = end;

    d->popup->setDatePeriod(begin, end);

    if (d->formater != 0) {
        d->date_label->setText(
                    isTimeEditable()
                    ? d->formater->format(dateTimePeriodBegin(), dateTimePeriodEnd())
                    : d->formater->format(begin, end));
    }
    else {
        d->date_label->clear();
    }
}

void DatePicker::setTimePeriod(const QTime &begin, const QTime &end)
{
    Q_D(DatePicker);

    d->picker_type = PeriodType;

    d->time_begin = begin;
    d->time_end = end;

    d->popup->setTimePeriod(begin, end);

    if (d->formater != 0)
        d->date_label->setText(d->formater->format(dateTimePeriodBegin(), dateTimePeriodEnd()));
    else
        d->date_label->clear();
}

void DatePicker::setDateTimePeriod(const QDateTime &begin, const QDateTime &end)
{
    Q_D(DatePicker);

    d->date_begin = begin.date();
    d->date_end = end.date();

    d->time_begin = begin.time();
    d->time_end = end.time();

    d->popup->setDatePeriod(begin.date(), end.date());
    d->popup->setTimePeriod(begin.time(), end.time());

    if (d->formater != 0)
        d->date_label->setText(d->formater->format(dateTimePeriodBegin(), dateTimePeriodEnd()));
    else
        d->date_label->clear();
}

void DatePicker::onShowPopupButtonClicked()
{
    Q_D(DatePicker);

    if (!d->popup->isVisible()) {
        d->popup->reset();

        if (d->picker_type == DayType) {
            d->popup->setDate(d->date_begin);
        }
        if (d->picker_type == PeriodType) {
            d->popup->setDatePeriod(d->date_begin, d->date_end);
            if (d->popup->isTimeEditable())
                d->popup->setTimePeriod(d->time_begin, d->time_end);
        }

        d->adjustPopupPosition();
        d->popup->show();
        d->popup->raise();
        d->popup->activateWindow();
    }
}

bool DatePicker::eventFilter(QObject *object, QEvent *event)
{
    Q_D(DatePicker);

    if (!d->is_editable)
        return QWidget::eventFilter(object, event);

    if ((object == d->popup) && (event->type() == QEvent::WindowDeactivate)) {
        d->popup->close();
        emit editingFinished();
    }

    return QWidget::eventFilter(object, event);
}

void DatePicker::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    Q_D(DatePicker);
    d->adjustPopupPosition();
}

void DatePicker::hideEvent(QHideEvent *event)
{
    Q_D(DatePicker);
    d->popup->hide();
    QWidget::hideEvent(event);
}

void DatePicker::closeEvent(QCloseEvent *event)
{
    Q_D(DatePicker);
    d->popup->close();
    QWidget::closeEvent(event);
}

void DatePicker::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);

    Q_D(DatePicker);
    d->adjustPopupPosition();
}

void DatePicker::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    Q_D(DatePicker);
    d->adjustPopupPosition();
}
