#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include <QSlider>
#include <QVBoxLayout>

#include "myprogressbar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QVBoxLayout *vb = new QVBoxLayout();
    QProgressBar *pb = new QProgressBar(this);

    MyProgressBar *myPb = new MyProgressBar(this);
    myPb->setMinimumSize(20);
    myPb->setMaximumSize(200);

    QSlider *gs = new QSlider(Qt::Horizontal, this);
    gs->setMinimum(0);
    gs->setMaximum(100);
    vb->addWidget(pb);
    vb->addWidget(myPb);
    vb->addWidget(gs);
    ui->centralwidget->setLayout(vb);

    connect(gs, &QSlider::valueChanged, pb, &QProgressBar::setValue);
    connect(gs, &QSlider::valueChanged, myPb, &MyProgressBar::setValue);
    gs->setValue(10);
}

MainWindow::~MainWindow() { delete ui; }
