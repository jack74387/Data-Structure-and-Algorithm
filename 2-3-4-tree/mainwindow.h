#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define BTree_D 2
#define ORDER 4

struct tree234
{
    int keynum;           //這一層的節點數量
    char key[ORDER - 1];
    tree234* child[ORDER];
    bool isLeaf;
};
typedef tree234 BTNode;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void BTree_draw(QPainter &painter, BTNode *root, int layer, int x, int y);
    bool flag;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent *);

};
#endif // MAINWINDOW_H
