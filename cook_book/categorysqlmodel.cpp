#include "categorysqlmodel.h"

CategorySqlModel::CategorySqlModel(QObject *parent) : QSqlQueryModel(parent) {}

QVariant CategorySqlModel::data(const QModelIndex &index, int role) const {
  int columnId = role - Qt::UserRole - 1;
  QModelIndex modelIndex = this->index(index.row(), columnId);
  return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QString CategorySqlModel::queryStr() const { return query().lastQuery(); }

void CategorySqlModel::setQueryStr(const QString &queryType) {
  QString query = queryType;
  if (queryStr() == query)
    return;
  setQuery(query);
  setQuery("SELECT * FROM category");
  emit queryStrChanged();
}

void CategorySqlModel::insertQuery(const QString &nameCategory) {
  setQueryStr("INSERT INTO category (name_category) VALUES ('" + nameCategory +
              "')");
}

void CategorySqlModel::updateQuery(const QString &nameCategory, int idCat) {
  setQueryStr("UPDATE category SET name_category = '" + nameCategory +
              "' WHERE id = " + QString::number(idCat));
}

void CategorySqlModel::deleteQuery(int idCat) {
  setQueryStr("DELETE FROM category WHERE id = " + QString::number(idCat));
}

void CategorySqlModel::refreshQuery() { setQueryStr("SELECT * FROM category"); }

QHash<int, QByteArray> CategorySqlModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "idCat";
  roles[NameRole] = "nameCat";
  return roles;
}
