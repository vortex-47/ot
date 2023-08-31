#ifndef MYSQLMODEL_H
#define MYSQLMODEL_H

#include <QObject>
#include <QSqlTableModel>

class MySqlModel : public QSqlTableModel {
    Q_OBJECT
  public:
    explicit MySqlModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE bool updateDescription(int row, const QVariant &value);
  public slots:
    void updateModel();

  protected:
    QHash<int, QByteArray> roleNames() const;
};

#endif // MYSQLMODEL_H
