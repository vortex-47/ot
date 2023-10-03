#ifndef GOODSMODEL_H
#define GOODSMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Good {
public:
  Good(const QString &name, const int price, const bool inFavorite,
       const int discontPrice, const int quantity, const QString &image);

  QString name() const;
  int price() const;
  bool inFavorite() const;
  int discontPrice() const;
  int quantity() const;
  QString image() const;

private:
  QString m_name;
  int m_price;
  bool m_inFavorite;
  int m_discontPrice;
  int m_quantity;
  QString m_image;
};

class GoodsModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum GoodRoles {
    NameRole = Qt::UserRole + 1,
    PriceRole,
    FavoriteRole,
    DiscontPriceRole,
    QuantityRole,
    ImageRole
  };
  GoodsModel(QObject *parent = 0);

  void addGood(const Good &good);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<Good> m_goods;
};

#endif // GOODSMODEL_H
