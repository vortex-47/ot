#include "goodsmodel.h"

Good::Good(const QString &name, const int price, const bool inFavorite,
           const int discontPrice, const int quantity, const QString &image)
    : m_name(name), m_price(price), m_inFavorite(inFavorite),
      m_discontPrice(discontPrice), m_quantity(quantity), m_image(image) {}

QString Good::name() const { return m_name; }

int Good::price() const { return m_price; }

bool Good::inFavorite() const { return m_inFavorite; }

int Good::discontPrice() const { return m_discontPrice; }

int Good::quantity() const { return m_quantity; }

QString Good::image() const { return m_image; }

GoodsModel::GoodsModel(QObject *parent) : QAbstractListModel(parent) {}

void GoodsModel::addGood(const Good &good) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_goods << good;
  endInsertRows();
}

int GoodsModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_goods.count();
}

QVariant GoodsModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_goods.count())
    return QVariant();

  const Good &good = m_goods[index.row()];
  switch (role) {
  case NameRole:
    return good.name();
    break;
  case PriceRole:
    return good.price();
    break;
  case FavoriteRole:
    return good.inFavorite();
    break;
  case DiscontPriceRole:
    return good.discontPrice();
    break;
  case QuantityRole:
    return good.quantity();
    break;
  case ImageRole:
    return good.image();
    break;
  }

  return QVariant();
}

QHash<int, QByteArray> GoodsModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[PriceRole] = "price";
  roles[FavoriteRole] = "inFavorite";
  roles[DiscontPriceRole] = "discontPrice";
  roles[QuantityRole] = "quantity";
  roles[ImageRole] = "image";
  return roles;
}
