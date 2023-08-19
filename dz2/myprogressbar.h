#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QObject>
#include <QProgressBar>

class MyProgressBar : public QProgressBar {
    Q_OBJECT
  public:
    MyProgressBar(QWidget *parent = nullptr);
    void setMaximumSize(int);
    void setMinimumSize(int);

  protected:
    void paintEvent(QPaintEvent *) override;

  private:
    using QProgressBar::setMaximumHeight;
    using QProgressBar::setMinimumHeight;

    using QProgressBar::setMaximumWidth;
    using QProgressBar::setMinimumWidth;

    using QProgressBar::setMinimumSize;

    using QProgressBar::setMaximumSize;
};

#endif // MYPROGRESSBAR_H
