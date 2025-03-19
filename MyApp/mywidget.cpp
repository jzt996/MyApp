#include "mywidget.h"
#include <QPainter>
#include <QPixmap>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 200);
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap(":/images/logo.png"); // 确保图片已添加到资源文件
    painter.drawPixmap(rect(), pixmap);
}
