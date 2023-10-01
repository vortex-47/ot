#include "mainwindow.h"
#include "cppstandartdelegate.h"
#include "mydelegate.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

void connectDB() {
    auto dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName("cppref_db.sqlite");
    if (!dbConnect.open())
        qDebug() << dbConnect.lastError().text();
    else
        qDebug() << "DB connected!";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connectDB();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("algorithms");
    // model->setRelation(2, QSqlRelation("standart", "id", "name"));
    //  Здесь когда ставим связь, то не отрисовываются изображения, и
    //  соответственно когда убираем, то работает немного не так как задумано.
    // Хотел попробовать реализовать свою QSqlRelationalTableModel, но что-то
    // совсем запутался. Как можно реализовать это? Чтобы и картинка были и
    // связи с др. таблицей работали?
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(4, new MyDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(
        2, new CppStandartDelegate(ui->tableView));
}

MainWindow::~MainWindow() { delete ui; }
