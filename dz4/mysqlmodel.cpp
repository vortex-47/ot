#include "mysqlmodel.h"
#include <QDebug>
#include <QSqlQuery>

enum Roles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    StandartRole,
    HeaderRole,
    DescriptionRole
};

MySqlModel::MySqlModel(QObject *parent)
    : QSqlTableModel{parent} {}

QVariant MySqlModel::data(const QModelIndex &index, int role) const {
    QVariant value;

    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlTableModel::data(index, role);
        } else {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlTableModel::data(modelIndex, Qt::DisplayRole);
        }
    }

    return value;
}

bool MySqlModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
    qDebug() << "C++";
    int columnIdx = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnIdx);

    if (index.isValid()) {
        QString col;
        switch (role) {
        case NameRole:
            col = "name";
            break;
        case HeaderRole:
            col = "header";
            break;
        case DescriptionRole:
            col = "description";
            break;
        default:
            break;
        }

        QModelIndex idIndex = this->index(index.row(), 0);
        QVariant valueId = QSqlTableModel::data(idIndex, Qt::DisplayRole);

        QSqlQuery query;
        query.prepare("UPDATE algorithms SET " + col +
                      " = :val WHERE id = :id");
        query.bindValue(":val", value);
        query.bindValue(":id", valueId);
        query.exec();

        emit dataChanged(modelIndex, modelIndex,
                         {Qt::EditRole, Qt::DisplayRole});
        return true;
    }
    return false;
}

bool MySqlModel::updateDescription(int row, const QVariant &value) {
    QModelIndex modelIndex = this->index(row, 4);

    QModelIndex idIndex = this->index(row, 0);
    QVariant valueId = QSqlTableModel::data(idIndex, Qt::DisplayRole);

    QSqlQuery query;
    query.prepare("UPDATE algorithms SET description = :val WHERE id = :id");
    query.bindValue(":val", value);
    query.bindValue(":id", valueId);
    query.exec();

    emit dataChanged(modelIndex, modelIndex, {Qt::EditRole, Qt::DisplayRole});
    return true;
}

void MySqlModel::updateModel() {
    qDebug() << "Update Model";
    QSqlQuery query("SELECT * FROM algorithms");
    this->setQuery(query);
}

QHash<int, QByteArray> MySqlModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[StandartRole] = "standart";
    roles[HeaderRole] = "header";
    roles[DescriptionRole] = "description";
    return roles;
}
