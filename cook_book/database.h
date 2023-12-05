#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QObject>
#include <QQmlEngine>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DataBase : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(DataBase)
public:
  DataBase();
  ~DataBase();

  static QObject *dbInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return new DataBase;
  }
  Q_INVOKABLE void init() const;
  Q_INVOKABLE bool isEmpty(QString table);
  Q_INVOKABLE bool isEmptyCategory(QString categoryName);
  Q_INVOKABLE QString recipeName(int idRec);
  Q_INVOKABLE int persons(int idRec);
  Q_INVOKABLE QString ingredients(int idRec);
  Q_INVOKABLE QString description(int idRec);

  // signals:
  //   void changeCount(const QString& request, const QVariant& parameters);

private:
  QSqlDatabase m_dbConnect;
  QString m_DBPath;
};

#endif // DATABASE_H
