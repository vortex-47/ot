#ifndef CPPSTANDARTDELEGATE_H
#define CPPSTANDARTDELEGATE_H

#include <QObject>
#include <QSqlRelationalDelegate>

class CppStandartDelegate : public QSqlRelationalDelegate {
    Q_OBJECT
  public:
    CppStandartDelegate(QObject *parent = nullptr);
    ~CppStandartDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // CPPSTANDARTDELEGATE_H
