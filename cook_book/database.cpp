#include "database.h"
#include <QDir>
#include <auroraapp.h>

DataBase::DataBase() {
  qDebug() << "DataBase is created";

  static const QDir dataDir(
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

  if (!dataDir.exists())
    dataDir.mkpath(dataDir.absolutePath());

  m_DBPath = dataDir.absolutePath() + "/cook_book_db.sqlite";
  m_dbConnect = QSqlDatabase::addDatabase("QSQLITE");
  m_dbConnect.setDatabaseName(m_DBPath);
  if (!m_dbConnect.open()) {
    qDebug() << m_dbConnect.lastError().text();
  }

  QSqlQuery query;
  query.prepare("CREATE TABLE IF NOT EXISTS category(id INTEGER PRIMARY KEY "
                "AUTOINCREMENT, name_category VARCHAR(30) NOT NULL DEFAULT "
                "'empty', position INTEGER DEFAULT 0)");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }

  query.prepare("CREATE TABLE IF NOT EXISTS recipes(id INTEGER PRIMARY KEY "
                "AUTOINCREMENT, name_recipe VARCHAR(50) NOT NULL DEFAULT "
                "'empty', persons INTEGER, ingredients TEXT, "
                "description TEXT, category VARCHAR(30))");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
}

DataBase::~DataBase() { m_dbConnect.close(); }

void DataBase::init() const { return; }

bool DataBase::isEmpty(QString table) {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM " + table);
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return !query.value(0).toBool();
}

bool DataBase::isEmptyCategory(QString categoryName) {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM recipes WHERE category = '" +
                categoryName + "'");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return !query.value(0).toBool();
}

QString DataBase::recipeName(int idRec) {
  QSqlQuery query;
  query.prepare("SELECT name_recipe FROM recipes WHERE id = '" +
                QString::number(idRec) + "'");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return query.value(0).toString();
}

int DataBase::persons(int idRec) {
  QSqlQuery query;
  query.prepare("SELECT persons FROM recipes WHERE id = '" +
                QString::number(idRec) + "'");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return query.value(0).toInt();
}

QString DataBase::ingredients(int idRec) {
  QSqlQuery query;
  query.prepare("SELECT ingredients FROM recipes WHERE id = '" +
                QString::number(idRec) + "'");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return query.value(0).toString();
}

QString DataBase::description(int idRec) {
  QSqlQuery query;
  query.prepare("SELECT description FROM recipes WHERE id = '" +
                QString::number(idRec) + "'");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  return query.value(0).toString();
}
