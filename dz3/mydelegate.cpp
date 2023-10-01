#include "mydelegate.h"
#include "qobjectdefs.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

MyDelegate::~MyDelegate() {}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const {
    Q_UNUSED(index)

    painter->save();
    QTextOption toptions(Qt::AlignCenter);
    painter->setBrush(QBrush(QColor(255, 255, 0, 255), Qt::SolidPattern));
    painter->setPen(QPen(Qt::NoPen));
    painter->drawRect(option.rect.x(), option.rect.y(), option.rect.width(),
                      option.rect.height());
    painter->setPen(QPen(Qt::SolidLine));
    painter->drawText(option.rect, QString("Посмотреть"), toptions);
    painter->restore();
}

bool MyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) {
    Q_UNUSED(option);

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        Q_UNUSED(mouseEvent);

        QWidget *qw = new QWidget();
        qw->setWindowModality(Qt::ApplicationModal);
        qw->setWindowFlag(Qt::FramelessWindowHint);
        QVBoxLayout *vbl = new QVBoxLayout(qw);
        QTextEdit *te = new QTextEdit(qw);
        QPushButton *pb = new QPushButton("Закрыть", qw);
        vbl->addWidget(te);
        vbl->addWidget(pb);
        qw->setLayout(vbl);

        QObject::connect(pb, &QPushButton::clicked, qw, &QWidget::deleteLater);
        QObject::connect(pb, &QPushButton::clicked, this, [model, index, te]() {
            model->setData(index, QVariant(te->toPlainText()));
        }); // Сделал здесь через лямбду, но хотелось бы увидеть ваше видение
            // решения.

        qw->setWindowTitle((model->headerData(4, Qt::Horizontal).toString()));
        te->clear();
        te->setText((model->data(index).toString()));
        qw->show();

        return false;
    }

    return true;
}
