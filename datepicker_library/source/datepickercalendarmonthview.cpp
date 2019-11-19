#include "include/datepickercalendarmonthview.h"
#include <QTextCharFormat>
#include <QTableView>
#include <QHeaderView>
#include <QPainter>


class DatePickerCalendarMonthViewPrivate {
    Q_DECLARE_PUBLIC(DatePickerCalendarMonthView)

    DatePickerCalendarMonthView *q_ptr;

    QDate period_begin;
    QDate period_end;

    QColor normal_background;
    QColor normal_foreground;

    QColor invalid_background;
    QColor invalid_foreground;

    QColor highlighted_background;
    QColor highlighted_foreground;

    DatePickerCalendarMonthViewPrivate(DatePickerCalendarMonthView *q) :
        q_ptr(q)
    {
        normal_background = QColor(Qt::white);
        normal_foreground = QColor(Qt::black);

        invalid_background = QColor(Qt::white);
        invalid_foreground = QColor(Qt::lightGray);

        highlighted_background = QColor("#d3dde5");
        highlighted_foreground = QColor(Qt::black);
    }

    ~DatePickerCalendarMonthViewPrivate() {}
};


DatePickerCalendarMonthView::DatePickerCalendarMonthView(QWidget *parent) :
    QCalendarWidget(parent),
    d_ptr(new DatePickerCalendarMonthViewPrivate(this))
{
    setDateEditEnabled(false);
    setNavigationBarVisible(false);
    setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setFirstDayOfWeek(Qt::Monday);

    QTableView *calendar_view = findChild<QTableView *>("qt_calendar_calendarview");
    if (calendar_view) {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
        calendar_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        calendar_view->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
        calendar_view->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
        calendar_view->verticalHeader()->setResizeMode(QHeaderView::Fixed);
#endif
        calendar_view->horizontalHeader()->setDefaultSectionSize(32);
        calendar_view->verticalHeader()->setDefaultSectionSize(32);

        calendar_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        calendar_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    QTextCharFormat cell_text_format = headerTextFormat();
    cell_text_format.setFontPointSize(9);
    cell_text_format.setBackground(QBrush(Qt::white));
    cell_text_format.setForeground(palette().windowText());

    QTextCharFormat header_text_format = cell_text_format;
    header_text_format.setFontWeight(QFont::Bold);

    setHeaderTextFormat(header_text_format);
    setWeekdayTextFormat(Qt::Monday, cell_text_format);
    setWeekdayTextFormat(Qt::Tuesday, cell_text_format);
    setWeekdayTextFormat(Qt::Wednesday, cell_text_format);
    setWeekdayTextFormat(Qt::Thursday, cell_text_format);
    setWeekdayTextFormat(Qt::Friday, cell_text_format);
    setWeekdayTextFormat(Qt::Saturday, cell_text_format);
    setWeekdayTextFormat(Qt::Sunday, cell_text_format);

    connect(this, SIGNAL(clicked(QDate)), SIGNAL(dateClicked(QDate)));
}

DatePickerCalendarMonthView::~DatePickerCalendarMonthView()
{
    delete d_ptr;
}

QSize DatePickerCalendarMonthView::minimumSizeHint() const
{
    /* correct-size-of-a-qtablewidget:
     * https://stackoverflow.com/a/19094947/4435650
     */

    QTableView *calendar_view = findChild<QTableView *>("qt_calendar_calendarview");

    if (calendar_view) {
        int w = 0, h = 0;
        calendar_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        calendar_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        w += calendar_view->contentsMargins().left()
                + calendar_view->contentsMargins().right();
        h += calendar_view->contentsMargins().top()
                + calendar_view->contentsMargins().bottom();

        w += calendar_view->verticalHeader()->width();
        h += calendar_view->horizontalHeader()->height();

        for (int i=0; i<7; ++i)
            w += calendar_view->columnWidth(i);
        for (int i=0; i<7; ++i)
            h += calendar_view->rowHeight(i);

        return QSize(w, h);
    }

    return QSize(0, 0);
}

void DatePickerCalendarMonthView::setDate(const QDate &date)
{
    Q_D(DatePickerCalendarMonthView);

    d->period_begin = QDate();
    d->period_end = QDate();

    setCurrentPage(date.year(), date.month());
    setSelectedDate(date);

    updateCells();
}

void DatePickerCalendarMonthView::setPeriod(const QDate &begin, const QDate &end, bool shows_begin)
{
    Q_D(DatePickerCalendarMonthView);

    d->period_begin = begin;
    d->period_end = end;

    QDate shown_date = shows_begin ? begin : end;

    setCurrentPage(shown_date.year(), shown_date.month());
    setSelectedDate(shown_date);

    updateCells();
}

void DatePickerCalendarMonthView::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    Q_D(const DatePickerCalendarMonthView);

    painter->save();

    bool is_invalid_date = ((date < minimumDate()) ||
                            (date > maximumDate()) ||
                            (date.month() != monthShown()) ||
                            (date.year() != yearShown()));

    bool is_highlighted_date = (date == selectedDate());
    if (d->period_begin.isValid() && d->period_end.isValid())
        is_highlighted_date = ((date >= d->period_begin) && (date <= d->period_end));

    QColor background_color = is_invalid_date ? d->invalid_background
                                              : is_highlighted_date ? d->highlighted_background
                                                                    : d->normal_background;

    QColor foreground_color = is_invalid_date ? d->invalid_foreground
                                              : is_highlighted_date ? d->highlighted_foreground
                                                                    : d->normal_foreground;

    painter->fillRect(rect, background_color);

    painter->setPen(foreground_color);
    painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));

    painter->restore();
}
