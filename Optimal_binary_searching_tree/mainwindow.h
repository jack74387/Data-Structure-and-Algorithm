#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "treenode.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
    void optimal_searching(vector<int>& freq_array, string vertex);
    void print_table(vector<vector<int>> cost, vector<vector<int>> best, string vertex);
    void insert_tree(TreeNode*& root, vector<vector<int>> best, int i, int j, string vertex);
    void print_tree(QPainter &painter, TreeNode* root, int type, int x, int y);
    void paintEvent(QPaintEvent *);
    TreeNode *root;
    bool flag;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
