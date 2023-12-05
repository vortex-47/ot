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
  Q_INVOKABLE QString getName(int id);

private:
  QSqlDatabase m_dbConnect;
};

#endif // DATABASE_H
