#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlError>

#include "mysqlmodel.h"

void connectDB() {
    auto dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName("cppref_db.sqlite");
    if (!dbConnect.open())
        qDebug() << dbConnect.lastError().text();
    else
        qDebug() << "DB connected!";
}

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    connectDB();

    MySqlModel *model = new MySqlModel();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    //      model->setTable("algorithms");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("mySqlModel", model);
    //  engine.rootContext()->setContextProperty("myM", model->v);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    // qmlRegisterType<MySqlModel>("ru.ot.MySqlModel", 1, 0, "MySqlModel");
    engine.load(url);

    return app.exec();
}
