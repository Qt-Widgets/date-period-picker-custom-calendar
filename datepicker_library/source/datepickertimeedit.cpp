#include "include/datepickertimeedit.h"
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>


DatePickerTimeEdit::DatePickerTimeEdit(QWidget *parent) :
    QTimeEdit(parent)
{
    setButtonSymbols(QAbstractSpinBox::NoButtons);

    setFrame(false);

    setWrapping(true);

    setDisplayFormat("hh:mm:ss");

    QPalette p = palette();
    p.setBrush(QPalette::Base, QBrush(Qt::white));
    lineEdit()->setPalette(p);
    setPalette(p);

    lineEdit()->setContentsMargins(QMargins(7, 2, 7, 2));

    lineEdit()->setAlignment(Qt::AlignCenter);

    QFont f = font();
    f.setPointSize(14);
    setFont(f);

    setFixedWidth(QFontMetrics(font()).boundingRect(displayFormat()).width() + 14);
}

DatePickerTimeEdit::~DatePickerTimeEdit()
{
}

void DatePickerTimeEdit::paintEvent(QPaintEvent *event)
{
    QTimeEdit::paintEvent(event);

    QRect item_rect = rect().adjusted(0, 0, -1, -1);

    QPainter painter(this);
    painter.setPen(palette().color(QPalette::Window));
    painter.drawRect(item_rect);
}
