#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include "treenode.h"
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
    //    ui->lineEdit->insert("7,4,1,5,13,8,11,12,15,9,2");
    //    ui->label->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    root = NULL;
    flag = false;
    clear = false;
    x=350;
    y=150;
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
        sprintf(temp,"%d",root->key);
        string print = temp;
        QString str = QString::fromStdString(print);
        label->setText(str);
        switch(type)
        {
        //root
        case 0:
            painter.drawEllipse(x-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-10,y+50,x-40,y+80);
            if(root->right!=NULL)
                painter.drawLine(x+20,y+50,x+40,y+80);
            label->setGeometry(QRect(QPoint(x, y),QSize(300, 50)));
            break;
        //left
        case 1:
            painter.drawEllipse(x+40-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-10+25,y+42,x-10-20,y+80);
            if(root->right!=NULL)
                painter.drawLine(x+10+40,y+50,x+10+40,y+80);
            label->setGeometry(QRect(QPoint(x+40, y),QSize(300, 50)));
            break;
            //right
        case 2:
            painter.drawEllipse(x-40-30, y, 70, 50);
            if(root->left!=NULL)
                painter.drawLine(x-40+5,y+50,x-40+5,y+80);
            if(root->right!=NULL)
                painter.drawLine(x-40+25,y+44,x-40+70,y+80);
            label->setGeometry(QRect(QPoint(x-40, y),QSize(300, 50)));
            break;
        }
        label->setFont(QFont("Timers" , 12 ,  QFont::Bold));
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

void MainWindow::on_pushButton_clicked()
{
    QPainter painter(this);
    erase(painter);
    for(int j=0;j<pr_s.size();j++)
        root=root->deleteNode(root,pr[j]);
    //    deleteTree(root);
    //    root = nullptr;

    //ui->label_3->clear();
    //ui->label_3->show();

    for(int i=0;i<label_array.size();i++)
    {
        label_array[i]->clear();
        label_array[i]->show();
        label_array[i]->deleteLater();
    }
    label_array.clear();
    this->update();
    pr_s=ui->lineEdit->text();
    cout << pr_s.toStdString()<<" \n";


    string tmp;
    QString in_s=ui->lineEdit->text();
    QString delete_node=ui->lineEdit_2->text();
    string a=in_s.toStdString();
    for (int i = 0; i < (int)a.length(); i++)
    {
        if (a[i] == ',')
        {
            lst.push_back(atoi(tmp.c_str()));
            tmp = "";
        }
        else
        {
            tmp += a[i];
        }
    }
    lst.push_back(atoi(tmp.c_str()));
    tmp = "";

//    string print="";
    for(size_t j=0;j<lst.size();j++)
    {
        root=root->insert(root,lst[j]);
    }

    root=root->deleteNode(root,delete_node.toInt());
    lst.clear();
    flag= true;
    this->update();

}


