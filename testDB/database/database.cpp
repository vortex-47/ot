#include "database.h"

DataBase::DataBase() {
  m_dbConnect = QSqlDatabase::addDatabase("QSQLITE");
  m_dbConnect.setDatabaseName("testbase.sqlite");
  if (!m_dbConnect.open()) {
    qDebug() << m_dbConnect.lastError().text();
  }

  QSqlQuery query;

  query.prepare("DROP TABLE IF EXISTS person");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }

  query.prepare("CREATE TABLE IF NOT EXISTS person(id INTEGER PRIMARY KEY "
                "AUTOINCREMENT, name VARCHAR(30), age INT, weight REAL)");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }

  query.prepare(
      "INSERT INTO person (name, age, weight) VALUES ('Anna', 32, 47.6)");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.prepare(
      "INSERT INTO person (name, age, weight) VALUES ('Bob', 44, 83.1)");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.prepare(
      "INSERT INTO person (name, age, weight) VALUES ('Mike', 23, 67.8)");
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }

  qDebug() << "DataBase is created";
}

DataBase::~DataBase() { m_dbConnect.close(); }

void DataBase::init() const { return; }

QString DataBase::getName(int id) {
  QSqlQuery query;
  query.prepare("SELECT name FROM person WHERE id = " + QString::number(id));
  if (!query.exec()) {
    qDebug() << query.lastError().text();
  }
  query.first();
  qDebug() << query.value(0).toString();
  return query.value(0).toString();
}
