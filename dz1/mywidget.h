#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget {
    Q_OBJECT

  public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

  private:
    void resetBlockDot();
    void resetAll();
    void res();

  public slots:
    void add();
    void sub();
    void mul();
    void div();
    void dot();
    void result();
    void addSym(const char *);

  private:
    Ui::MyWidget *ui;
    double op1 = 0.0f;
    double op2 = 0.0f;
    int act = 0;
    bool isFinish = false;
    bool isSetOp1 = false;
    bool isSetOp2 = false;
};

#endif // MYWIDGET_H
