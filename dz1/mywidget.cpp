#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget) {
    ui->setupUi(this);

    connect(ui->pb_reset, &QPushButton::clicked, this, &MyWidget::resetAll);

    connect(ui->pb_add, &QPushButton::clicked, this, &MyWidget::add);
    connect(ui->pb_sub, &QPushButton::clicked, this, &MyWidget::sub);
    connect(ui->pb_mul, &QPushButton::clicked, this, &MyWidget::mul);
    connect(ui->pb_div, &QPushButton::clicked, this, &MyWidget::div);
    connect(ui->pb_dot, &QPushButton::clicked, this, &MyWidget::dot);
    connect(ui->pb_result, &QPushButton::clicked, this, &MyWidget::result);

    connect(ui->pb_1, &QPushButton::clicked, this, [=]() { addSym("1"); });
    connect(ui->pb_2, &QPushButton::clicked, this, [=]() { addSym("2"); });
    connect(ui->pb_3, &QPushButton::clicked, this, [=]() { addSym("3"); });
    connect(ui->pb_4, &QPushButton::clicked, this, [=]() { addSym("4"); });
    connect(ui->pb_5, &QPushButton::clicked, this, [=]() { addSym("5"); });
    connect(ui->pb_6, &QPushButton::clicked, this, [=]() { addSym("6"); });
    connect(ui->pb_7, &QPushButton::clicked, this, [=]() { addSym("7"); });
    connect(ui->pb_8, &QPushButton::clicked, this, [=]() { addSym("8"); });
    connect(ui->pb_9, &QPushButton::clicked, this, [=]() { addSym("9"); });
    connect(ui->pb_0, &QPushButton::clicked, this, [=]() { addSym("0"); });
}

MyWidget::~MyWidget() { delete ui; }

void MyWidget::add() {
    res();
    addSym("+");
    act = 1;
    isFinish = true;
}

void MyWidget::sub() {
    res();
    addSym("-");
    act = 2;
    isFinish = true;
}

void MyWidget::mul() {
    res();
    addSym("X");
    act = 3;
    isFinish = true;
}

void MyWidget::div() {
    res();
    addSym("/");
    act = 4;
    isFinish = true;
}

void MyWidget::dot() {
    QString temp = ui->indicator->text();
    QString st = "X+-/";
    if (st.contains(temp) || temp.isEmpty()) {
        temp = "0";
    }
    temp.append(".");
    ui->indicator->setText(temp);
    ui->pb_dot->blockSignals(true);
    isFinish = false;
}

void MyWidget::result() {
    res();
    act = 0;
    isFinish = true;
    resetBlockDot();
}

void MyWidget::addSym(const char *sym) {
    if (isFinish) {
        ui->indicator->setText("");
        isFinish = false;
    }
    QString temp = ui->indicator->text();
    temp.append(sym);
    ui->indicator->setText(temp);
}

void MyWidget::resetBlockDot() { ui->pb_dot->blockSignals(false); }

void MyWidget::resetAll() {
    ui->indicator->setText("");
    op1 = 0.0f;
    op2 = 0.0f;
    act = 0;
    isSetOp1 = false;
    isSetOp2 = false;
    resetBlockDot();
}

void MyWidget::res() {
    if (!isSetOp1) {
        op1 = ui->indicator->text().toDouble();
        ui->indicator->setText("");
        isSetOp1 = true;
        resetBlockDot();
    }
    if (!isSetOp2) {
        op2 = ui->indicator->text().toDouble();
        ui->indicator->setText("");
        isSetOp2 = true;
        resetBlockDot();
    }
    if (op2 == 0.0f && act == 4) {
        resetAll();
        ui->indicator->setText("Division by zero");
        return;
    }
    double temp;
    switch (act) {
    case 1:
        temp = op1 + op2;
        break;
    case 2:
        temp = op1 - op2;
        break;
    case 3:
        temp = op1 * op2;
        break;
    case 4:
        temp = op1 / op2;
        break;
    default:
        temp = op1;
        break;
    }
    op1 = temp;
    op2 = 0.0f;
    isSetOp2 = false;
    ui->indicator->setText(QString::number(temp));
    resetBlockDot();
}
