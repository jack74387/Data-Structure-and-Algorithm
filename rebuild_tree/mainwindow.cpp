#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include "TreeNode.h"
#include <iostream>
#include <QPainter>
#include <QLabel>
#include <string>
#include <QRect>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->label->setFont(QFont("Timers" , 16 ,  QFont::Bold));
//    ui->label_2->setFont(QFont("Timers" , 16 ,  QFont::Bold));
//    ui->label_3->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    root = NULL;
    flag = false;
    clear = false;
    x=400;
    y=185;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::print_Tree(QPainter &painter, TreeNode* root, int type, int x, int y)
{
    if(root==nullptr)
        return;
    else
    {
        print_Tree(painter, root->left, 1, x-80, y+80);
        QLabel *label;
        label = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%c",root->key);
        string print = temp;
        QString str = QString::fromStdString(print);
        label->setText(str);
        switch(type)
        {
        case 0:
            painter.drawEllipse(x-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-10,y+50,x-40,y+80);
            if(root->right!=NULL)
                painter.drawLine(x+20,y+50,x+40,y+80);
            label->setGeometry(QRect(QPoint(x, y),QSize(300, 50)));
            break;
        case 1:
            painter.drawEllipse(x+40-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-10+25,y+42,x-10-20,y+80);
            if(root->right!=NULL)
                painter.drawLine(x+10+40,y+50,x+10+40,y+80);
            label->setGeometry(QRect(QPoint(x+40, y),QSize(300, 50)));
            break;
        case 2:
            painter.drawEllipse(x-40-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-40+5,y+50,x-40+5,y+80);
            if(root->right!=NULL)
                painter.drawLine(x-40+25,y+44,x-40+70,y+80);
            label->setGeometry(QRect(QPoint(x-40, y),QSize(300, 50)));
            break;
        }
//        label->setFont(QFont("Timers" , 12 ,  QFont::Bold));
        label->show();
        label_array.push_back(label);
        print_Tree(painter, root->right, 2, x+80, y+80);
    }

}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(flag)
        print_Tree(painter, root, 0, x, y);
}
void MainWindow::erase(QPainter &painter)
{
    painter.eraseRect(0, 0, 800, 600);
}
//TreeNode* inss(TreeNode *root, int num)
//{
//    TreeNode *a = new TreeNode;
//    a->left =root;
//    a->right =NULL;
//    a->key = num;
//    return a;
//}
TreeNode* insert_pr(TreeNode* root,int limit, char *pr, char *in)
{
    //找出根，並插入相對應的位置(<left, >right)
    int x, j;
    int center = 0;
    for (x = 0; x < limit; x++)
    {
        if (pr[0] == in[x])    //找出跟節點
        {
            center = x;
            break;
        }

    }
    root = root->insert(root, pr[0], center);
    for (j = 1; j < limit; j++)
    {
        for (x = 0; x < limit; x++)
        {
            if (pr[j] == in[x])   //找出跟節點
                break;
        }
        root = root->insert(root, pr[j], x);
    }

    return root;
}
TreeNode* insert_af(TreeNode* root, int limit, char *af, char *in)
{
    int x, j;
    int center = 0;
    for (x = 0; x < limit; x++)
    {
        if (af[limit-1] == in[x])
        {
            center = x;
            break;
        }

    }
    root = root->insert(root, af[limit - 1], center);
    for (j = limit-2; j >= 0; j--)
    {
        for (x = 0; x < limit; x++)
        {
            if (af[j] == in[x])
                break;
        }
        root = root->insert(root, af[j], x);
    }
    return root;
}
void MainWindow::on_pushButton_clicked()
{
    //clear
    QPainter painter(this);
    erase(painter);
    for(int j=0;j<pr_s.size();j++)
        root=root->deleteNode(root,pr[j]);
    this->update();
    for(int i=0;i<label_array.size();i++)
    {
        label_array[i]->clear();
        label_array[i]->show();
        label_array[i]->deleteLater();
    }
    label_array.clear();
    //字串處理
    pr_s=ui->lineEdit->text();
    in_s=ui->lineEdit_2->text();
    af_s=ui->lineEdit_3->text();

    pr=strdup(pr_s.toStdString().c_str());
    in=strdup(in_s.toStdString().c_str());
    af=strdup(af_s.toStdString().c_str());

    if(pr_s!="")
        root = insert_pr(root, pr_s.size(), pr, in);

    else
        root = insert_af(root, af_s.size(), af, in);
    flag= true;
    this->update();

}


