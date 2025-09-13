#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void BTree_draw(QPainter &painter, Node *root, int layer, int x, int y);
    bool flag;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
