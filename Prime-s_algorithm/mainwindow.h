#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
using std::string;
using std::vector;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void print_graph(QPainter &painter);
    void print_mst(QPainter &painter);
    void prime_mst(string start);
    int minKey(int key[], bool mstSet[]);
    bool flag;
    bool flag_2;
    bool flag_3;
    string vertex;
    int** edge;
    int x1, y1, x2, y2;
    QPoint all_e[100];

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
