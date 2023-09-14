#include "goodsmodel.h"
#include "parsejson.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  GoodsModel model;
  ParseJson pj(&app, &model);

  //  QQmlApplicationEngine engine;
  //  const QUrl url(QStringLiteral("qrc:/main.qml"));
  //  QObject::connect(
  //      &engine, &QQmlApplicationEngine::objectCreated, &app,
  //      [url](QObject *obj, const QUrl &objUrl) {
  //        if (!obj && url == objUrl)
  //          QCoreApplication::exit(-1);
  //      },
  //      Qt::QueuedConnection);

  //  QQmlContext *context = engine.rootContext();
  //  context->setContextProperty("initGoods", ParseJson::instance());

  //  engine.load(url);
  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setInitialProperties({{"model", QVariant::fromValue(&model)}});
  view.setSource(QUrl("qrc:main.qml"));
  view.setTitle("Домашнее задание №5");
  view.show();

  return app.exec();
}
