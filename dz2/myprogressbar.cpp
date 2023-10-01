#include "myprogressbar.h"
#include <QPainter>
#include <QPainterPath>

MyProgressBar::MyProgressBar(QWidget *parent) {
    Q_UNUSED(parent);
    setMinimumSize(50);
    setValue(0);
}

void MyProgressBar::setMaximumSize(int x) {
    setMaximumHeight(x);
    setMaximumWidth(x);
    return;
}
void MyProgressBar::setMinimumSize(int x) {
    if (x < 50)
        x = 50;
    setMinimumHeight(x);
    setMinimumWidth(x);
    return;
}

void MyProgressBar::paintEvent(QPaintEvent *) {
    qreal h_5 = height() / 5;
    qreal h_2 = height() / 2;
    qreal h2_5 = height() * 2 / 5;
    qreal h = height();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    QBrush brush = QBrush(QColor(100, 209, 86, 200), Qt::SolidPattern);
    painter.setBrush(brush);
    QRectF rectangle2(0, 0, h, h);
    QRectF rectangle1(h_5, h_5, h - h2_5, h - h2_5);
    qreal cur = 360.0f / this->maximum();
    qreal startAngle = 90;
    qreal spanAngle = cur * this->value();

    QPainterPath piePath;
    piePath.moveTo(h_2, h_2);
    piePath.arcTo(rectangle2, -1 * startAngle, -1 * spanAngle);
    piePath.arcTo(rectangle1, -1 * (spanAngle + startAngle), spanAngle);
    piePath.closeSubpath();

    painter.drawPath(piePath);

    painter.setPen(Qt::SolidLine);
    QFont qf = QFont();
    qf.setPixelSize(height() / 6);
    qreal qfps = qf.pixelSize();
    painter.setFont(qf);
    painter.drawText(QRect(0, h_2 - qfps / 2, h, qfps), Qt::AlignCenter,
                     this->text());
}
