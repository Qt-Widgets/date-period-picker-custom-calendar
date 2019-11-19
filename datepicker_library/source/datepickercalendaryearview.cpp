#include "include/datepickercalendaryearview.h"
#include <QHeaderView>


class DatePickerCalendarYearViewPrivate {
    Q_DECLARE_PUBLIC(DatePickerCalendarYearView)

    DatePickerCalendarYearView *q_ptr;

    QDate current_date;
    QDate minimum_date;
    QDate maximum_date;

    DatePickerCalendarYearViewPrivate(DatePickerCalendarYearView *q) : q_ptr(q) {}
    ~DatePickerCalendarYearViewPrivate() {}

    void updateItemFlags()
    {
        Q_Q(DatePickerCalendarYearView);

        int disable_minimum_cell_from = 0;
        int disable_minimum_cell_to = 0;

        if (minimum_date.isValid()) {
            if (minimum_date.year() == current_date.year())
                disable_minimum_cell_to = minimum_date.month() - 1;
            else if (minimum_date.year() > current_date.year())
                disable_minimum_cell_to = 12;
        }

        int disable_maximum_cell_from = 12;

        if (maximum_date.isValid()) {
            if (maximum_date.year() == current_date.year())
                disable_maximum_cell_from = maximum_date.month();
            else if (maximum_date.year() < current_date.year())
                disable_maximum_cell_from = 0;
        }

        int disable_maximum_cell_to = 12;

        QTableWidgetItem *month_item = 0;

        for (int i = disable_minimum_cell_from; i < disable_minimum_cell_to; ++ i) {
            month_item = q->item(i / 4, i % 4);
            month_item->setFlags(Qt::NoItemFlags);
        }
        for (int i = disable_minimum_cell_to; i < disable_maximum_cell_from; ++ i) {
            month_item = q->item(i / 4, i % 4);
            month_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
        for (int i =  disable_maximum_cell_from; i < disable_maximum_cell_to; ++ i) {
            month_item = q->item(i / 4, i % 4);
            month_item->setFlags(Qt::NoItemFlags);
        }
    }
};


DatePickerCalendarYearView::DatePickerCalendarYearView(QWidget *parent) :
    QTableWidget(parent),
    d_ptr(new DatePickerCalendarYearViewPrivate(this))
{
    setRowCount(3);
    setColumnCount(4);

    QTableWidgetItem *item = 0;
    for (int i = 0; i < 12; ++ i) {
        item = new QTableWidgetItem(QDate::shortMonthName(i + 1, QDate::StandaloneFormat));
        item->setTextAlignment(Qt::AlignCenter);
        item->setBackgroundColor(Qt::white);
        setItem(i / 4, i % 4, item);
    }

    verticalHeader()->hide();
    horizontalHeader()->hide();

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    verticalHeader()->setResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameStyle(QFrame::NoFrame);

    setShowGrid(false);

    connect(this, SIGNAL(cellClicked(int,int)), SLOT(onCellClicked(int,int)));
}

DatePickerCalendarYearView::~DatePickerCalendarYearView()
{
    delete d_ptr;
}

void DatePickerCalendarYearView::setDate(const QDate &date)
{
    Q_D(DatePickerCalendarYearView);
    d->current_date = date;
    d->updateItemFlags();
    setCurrentCell((date.month() - 1) / 4, (date.month() - 1) % 4, QItemSelectionModel::SelectCurrent);
}

void DatePickerCalendarYearView::setMinimumDate(const QDate &date)
{
    Q_D(DatePickerCalendarYearView);
    d->minimum_date = date;
    d->updateItemFlags();
}

void DatePickerCalendarYearView::setMaximumDate(const QDate &date)
{
    Q_D(DatePickerCalendarYearView);
    d->maximum_date = date;
    d->updateItemFlags();
}

void DatePickerCalendarYearView::onCellClicked(int row, int column)
{
    if (item(row, column)->flags() & Qt::ItemIsEnabled)
        emit monthClicked(row * 4 + column + 1);
}
