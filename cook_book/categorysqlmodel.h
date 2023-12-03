#ifndef CATEGORYSQLMODEL_H
#define CATEGORYSQLMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class CategorySqlModel : public QSqlQueryModel {
  Q_OBJECT
  Q_PROPERTY(
      QString query READ queryStr /*WRITE setQueryStr*/ NOTIFY queryStrChanged)
public:
  enum Roles { IdRole = Qt::UserRole + 1, NameRole };
  explicit CategorySqlModel(QObject *parent = 0);
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  QString queryStr() const;
  void setQueryStr(const QString &query);
  Q_INVOKABLE void refreshQuery();
  Q_INVOKABLE void updateQuery(const QString &nameCategory, int idCat);
  Q_INVOKABLE void insertQuery(const QString &nameCategory);
  Q_INVOKABLE void deleteQuery(int idCat);

protected:
  QHash<int, QByteArray> roleNames() const;
signals:
  void queryStrChanged();
};

#endif // CATEGORYSQLMODEL_H
