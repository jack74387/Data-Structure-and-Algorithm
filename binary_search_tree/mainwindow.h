#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "treenode.h"
#include <QList>
#include <QLabel>
#include <vector>
using namespace std;
namespace Ui {
class MainWindow;
}
struct point
{
    int x;
    int y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void print_Tree(QPainter &painter, TreeNode* root, int type, int x, int y);
    void erase(QPainter &painter);
    QString  pr_s;
    char* pr;
    QList<QLabel*> label_array;
    TreeNode *root;
    vector<int> lst;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool flag;
    bool clear;
    int x;
    int y;


protected:
    void paintEvent(QPaintEvent *);


};

#endif // MAINWINDOW_H
