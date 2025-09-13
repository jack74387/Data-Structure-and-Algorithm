#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clicked = false;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (clicked) {
        QPainter painter(this);
        int num = ui -> lineEdit ->text() .toInt();
        koch(painter, num, 100, 200, 420, 200);
        koch(painter, num, 420, 200, 260, (int)(200 + 160 * sqrt(3)));
        koch(painter, num, 260, (int)(200 + 160 * sqrt(3)), 100, 200);   //三角形的三邊
    }
}

void MainWindow::koch(QPainter &painter,int num, int x1, int y1, int x5, int y5)
{
    int x2, y2, x3, y3, x4, y4;
    int dx, dy;

    if(num == 0){
        painter.drawLine(x1, y1, x5, y5);
    }
    else {
        dx = (x5 - x1) / 3;
        dy = (y5 - y1) / 3;

        x2 = x1 + dx;
        y2 = y1 + dy;

        x3 = (int)(0.5*(x1 + x5) + sqrt(3)*(y5 - y1) / 6);
        y3 = (int)(0.5*(y1 + y5) + sqrt(3)*(x1 - x5) / 6);

        x4 = 2 * dx + x1;
        y4 = 2 * dy + y1;             //計算每個點的位置
        koch(painter,num - 1, x1, y1, x2, y2);
        koch(painter,num - 1, x2, y2, x3, y3);
        koch(painter,num - 1, x3, y3, x4, y4);
        koch(painter,num - 1, x4, y4, x5, y5);  //當num不等於0時，重複呼叫
    }
}
void MainWindow::on_pushButton_clicked()
{
    clicked = true;
    update();
}

