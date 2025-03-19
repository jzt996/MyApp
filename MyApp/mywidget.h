#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MYWIDGET_H
