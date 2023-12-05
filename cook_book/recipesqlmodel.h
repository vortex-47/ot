#ifndef RECIPESQLMODEL_H
#define RECIPESQLMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class RecipeSqlModel : public QSqlQueryModel {
  Q_OBJECT
  Q_PROPERTY(
      QString query READ queryStr /*WRITE setQueryStr*/ NOTIFY queryStrChanged)
public:
  enum Roles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    PersonsRole,
    IngredientsRole,
    DescriptionRole,
    CategoryRole
  };
  explicit RecipeSqlModel(QObject *parent = 0);
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  QString queryStr() const;
  void setQueryStr(const QString &query, const QString &nameCategory);

  Q_INVOKABLE void refreshQuery(const QString &nameCategory);
  Q_INVOKABLE void insertQuery(const QString &nameRecipe,
                               const QString &numberPersons,
                               const QString &ingredients,
                               const QString &cookProcess,
                               const QString &nameCategory);
  Q_INVOKABLE void deleteQuery(int idRec, const QString &nameCategory);
  Q_INVOKABLE void recipeQuery(int idRec, const QString &nameCategory);

protected:
  QHash<int, QByteArray> roleNames() const;
signals:
  void queryStrChanged();
};

#endif // RECIPESQLMODEL_H
