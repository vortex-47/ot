#include "cppstandartdelegate.h"
#include <QPainter>

CppStandartDelegate::CppStandartDelegate(QObject *parent)
    : QSqlRelationalDelegate(parent) {}

CppStandartDelegate::~CppStandartDelegate() {}

void CppStandartDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
    QImage img = QImage(QString("%1%2%3")
                            .arg(":/img/")
                            .arg(index.data().toString())
                            .arg(".png"));
    if (!img.isNull()) {
        painter->save();
        img = img.scaledToHeight(option.rect.height() - 4);
        painter->drawImage(
            QRect(option.rect.x() + option.rect.width() / 2 - img.width() / 2,
                  option.rect.y() + 2, img.width(), img.height()),
            img);
        painter->restore();
    }
    //   QSqlRelationalDelegate::paint(painter, option, index);
}
