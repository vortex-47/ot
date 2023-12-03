#include "recipesqlmodel.h"
#include <QDebug>

RecipeSqlModel::RecipeSqlModel(QObject *parent) : QSqlQueryModel(parent) {}

QVariant RecipeSqlModel::data(const QModelIndex &index, int role) const {
  int columnId = role - Qt::UserRole - 1;
  QModelIndex modelIndex = this->index(index.row(), columnId);
  return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QString RecipeSqlModel::queryStr() const { return query().lastQuery(); }

void RecipeSqlModel::setQueryStr(const QString &queryType,
                                 const QString &nameCategory) {
  QString query = queryType;
  if (queryStr() == query)
    return;
  setQuery(query);
  setQuery("SELECT * FROM recipes WHERE category = '" + nameCategory + "'");
  emit queryStrChanged();
}

void RecipeSqlModel::refreshQuery(const QString &nameCategory) {
  setQueryStr("SELECT * FROM recipes WHERE category = '" + nameCategory + "'",
              nameCategory);
}

void RecipeSqlModel::insertQuery(const QString &nameRecipe,
                                 const QString &numberPersons,
                                 const QString &ingredients,
                                 const QString &cookProcess,
                                 const QString &nameCategory) {
  setQueryStr("INSERT INTO recipes (name_recipe, persons, ingredients, "
              "description, category) VALUES ('" +
                  nameRecipe + "', '" + numberPersons + "', '" + ingredients +
                  "', '" + cookProcess + "', '" + nameCategory + "')",
              nameCategory);
}

void RecipeSqlModel::deleteQuery(int idRec, const QString &nameCategory) {
  setQueryStr("DELETE FROM recipes WHERE id = " + QString::number(idRec),
              nameCategory);
}

void RecipeSqlModel::recipeQuery(int idRec, const QString &nameCategory) {

  setQueryStr("SELECT * FROM recipes WHERE id = '" + QString::number(idRec) +
                  "'",
              nameCategory);
}

QHash<int, QByteArray> RecipeSqlModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IdRole] = "idRec";
  roles[NameRole] = "nameRec";
  roles[PersonsRole] = "personsRec";
  roles[IngredientsRole] = "ingredientsRec";
  roles[DescriptionRole] = "descriptionRec";
  roles[CategoryRole] = "categoryRec";
  return roles;
}
