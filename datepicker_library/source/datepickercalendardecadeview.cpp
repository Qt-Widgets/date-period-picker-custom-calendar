#include "include/datepickercalendardecadeview.h"
#include <QHeaderView>


class DatePickerCalendarDecadeViewPrivate {
    Q_DECLARE_PUBLIC(DatePickerCalendarDecadeView)

    DatePickerCalendarDecadeView *q_ptr;

    QDate current_date;
    QDate minimum_date;
    QDate maximum_date;

    DatePickerCalendarDecadeViewPrivate(DatePickerCalendarDecadeView *q) : q_ptr(q) {}
    ~DatePickerCalendarDecadeViewPrivate() {}

    void updateItemFlags()
    {
        Q_Q(DatePickerCalendarDecadeView);

        int disable_minimum_cell_from = 0;
        int disable_minimum_cell_to = 0;
        if (minimum_date.isValid()) {
            disable_minimum_cell_to = qMax(0,
                                           qMin(minimum_date.year() - current_date.year() + 5, 12));
        }

        int disable_maximum_cell_from = 12;
        if (maximum_date.isValid()) {
            disable_maximum_cell_from = qMax(0,
                                             qMin(maximum_date.year() - current_date.year() + 6, 12));
        }
        int disable_maximum_cell_to = 12;

        QTableWidgetItem *year_item = 0;

        for (int i = disable_minimum_cell_from; i < disable_minimum_cell_to; ++ i) {
            year_item = q->item(i / 4, i % 4);
            year_item->setFlags(Qt::NoItemFlags);
        }
        for (int i = disable_minimum_cell_to; i < disable_maximum_cell_from; ++ i) {
            year_item = q->item(i / 4, i % 4);
            year_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
        for (int i =  disable_maximum_cell_from; i < disable_maximum_cell_to; ++ i) {
            year_item = q->item(i / 4, i % 4);
            year_item->setFlags(Qt::NoItemFlags);
        }
    }
};


DatePickerCalendarDecadeView::DatePickerCalendarDecadeView(QWidget *parent) :
    QTableWidget(parent),
    d_ptr(new DatePickerCalendarDecadeViewPrivate(this))
{
    setRowCount(3);
    setColumnCount(4);

    QTableWidgetItem *item = 0;
    for (int i = 0; i < 12; ++ i) {
        item = new QTableWidgetItem();
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

DatePickerCalendarDecadeView::~DatePickerCalendarDecadeView()
{
    delete d_ptr;
}

void DatePickerCalendarDecadeView::setDate(const QDate &date)
{
    Q_D(DatePickerCalendarDecadeView);
    d->current_date = date;

    for (int i = 0; i < 12; ++ i)
        item(i / 4, i % 4)->setText(date.addYears(i - 5).toString("yyyy"));

    d->updateItemFlags();

    setCurrentCell(1, 1, QItemSelectionModel::SelectCurrent);
}

void DatePickerCalendarDecadeView::setMinimumDate(const QDate &date)
{
    Q_D(DatePickerCalendarDecadeView);
    d->minimum_date = date;
    d->updateItemFlags();
}

void DatePickerCalendarDecadeView::setMaximumDate(const QDate &date)
{
    Q_D(DatePickerCalendarDecadeView);
    d->maximum_date = date;
    d->updateItemFlags();
}

void DatePickerCalendarDecadeView::onCellClicked(int row, int column)
{
    if (item(row, column)->flags() & Qt::ItemIsEnabled)
        emit yearClicked(QDate::fromString(item(row, column)->text(), "yyyy").year());
}
