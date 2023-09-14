#include "parsejson.h"

ParseJson::ParseJson(QObject *parent, GoodsModel *model) : m_model(model) {
  Q_UNUSED(parent);
  // model.addGood(Good("111", 2, true, 33, 2, "aaa"));
  networkManager = new QNetworkAccessManager();
  connect(networkManager, &QNetworkAccessManager::finished, this,
          &ParseJson::onResult);
  networkManager->get(
      QNetworkRequest(QUrl("https://otestserver_1-1-o9142362.deta.app/goods")));
}

void ParseJson::onResult(QNetworkReply *reply) {
  if (!reply->error()) {
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    QJsonArray ja = (root.value("goods")).toArray();
    for (int i = 0; i < ja.count(); i++) {
      QJsonObject jo = ja[i].toObject();
      // QJsonValue jv = jo.value("name");
      QString tName = (jo.value("name")).toString();
      int tPrice = (jo.value("price")).toInt();
      bool tFavorite = (jo.value("in_favorite")).toBool();
      int tDPrice = (jo.value("discont_price")).toInt();
      if (tDPrice == 0)
        tDPrice = (jo.value("discount_price")).toInt();
      int tQuantity = (jo.value("quantity")).toInt();
      QString tImage = "https://otestserver_1-1-o9142362.deta.app" +
                       (jo.value("image")).toString();
      m_model->addGood(
          Good(tName, tPrice, tFavorite, tDPrice, tQuantity, tImage));
    }
  }
  reply->deleteLater();
}
