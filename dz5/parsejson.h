#ifndef PARSEJSON_H
#define PARSEJSON_H

#include "goodsmodel.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ParseJson : public QObject {
  Q_OBJECT

public:
  ParseJson(QObject *parent = nullptr, GoodsModel *model = nullptr);

private slots:
  void onResult(QNetworkReply *reply);

private:
  QNetworkAccessManager *networkManager;
  GoodsModel *m_model = nullptr;
};

#endif // PARSEJSON_H
