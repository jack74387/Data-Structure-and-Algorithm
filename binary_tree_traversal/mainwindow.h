#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeNode.h"
#include <QList>
#include <QLabel>
#include <string>
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
    void FindAForder(char* inorder, char* preorder, int length, char* aforder, int &dis, std::string &print);
    TreeNode *root;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString pr_s;
    QString in_s;
    char *pr;
    char *in;
    string node;
    bool flag;
    bool clear;
    int x;
    int y;

};

#endif // MAINWINDOW_H
