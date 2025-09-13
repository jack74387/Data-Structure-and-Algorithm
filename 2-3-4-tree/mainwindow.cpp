#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <iostream>
#include <QPainter>
#include <QLabel>
#include <QRect>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
#define BTree_D 2
#define ORDER 4

BTNode *sorttree = NULL;
void BTree_print(BTNode *node, int layer)
{
    if (node != NULL)
    {
        printf("%d, %d node", layer, node->keynum);

        for (int i = 0; i < node->keynum; ++i)
            printf(" %c", node->key[i]);

        ++layer;

        int count = 0;
        for (int i = 0; i <= node->keynum; i++)
            if (node->child[i] != NULL)
                ++count;
        printf(" %d", count);
        printf("\n");
        for (int i = 0; i < count; i++)
        {
            BTree_print(node->child[i], layer);
        }

    }
    else
        printf("\n");
}




void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
    int i;

    BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
    if (!newNode)
    {
        printf("Error! out of memory!\n");
        return;
    }

    //initilization
    newNode->isLeaf = node->isLeaf;
    newNode->keynum = BTree_D - 1;  //分裂後為1
    for (int i = 0; i < ORDER; i++)
        newNode->child[i] = NULL;

    //給new node key
    for (i = 0; i < newNode->keynum; ++i)
    {
        newNode->key[i] = node->key[BTree_D - i];//給分裂後node value
        node->key[BTree_D - i] = 0;
    }


    if (!node->isLeaf)
    {
        for (i = 0; i < BTree_D; i++)
        {
            newNode->child[i] = node->child[BTree_D + i];
            node->child[BTree_D + i] = NULL;
        }
    }

    node->keynum = BTree_D - 1;

    //update parent
    for (i = parent->keynum; i > index; --i)
    {
        parent->child[i + 1] = parent->child[i];
    }

    parent->child[index + 1] = newNode;

    for (i = parent->keynum - 1; i >= index; --i)
    {
        parent->key[i + 1] = parent->key[i];
    }

    parent->key[index] = node->key[BTree_D - 1];
    ++parent->keynum;

    node->key[BTree_D - 1] = 0;
    parent->key[parent->keynum] = 0;
}

void BTree_insert_nonfull(BTNode* node, int key)
{
    int i;

    if (node->isLeaf)
    {
        //向右移動
        i = node->keynum - 1;
        while (i >= 0 && key <= node->key[i])
        {
            node->key[i + 1] = node->key[i];
            --i;
        }
        //插入-1+1
        node->key[i + 1] = key;
        ++node->keynum;
    }
    else
    {
        //找出適當的位置
        i = node->keynum - 1;
        while (i >= 0 && key <= node->key[i])
        {
            --i;
        }

        ++i;


        if (node->child[i] == NULL || node->child[i]->keynum == (ORDER - 1))
        {
            BTree_split_child(node, i, node->child[i]);
            if (key > node->key[i])
                ++i;
        }
        BTree_insert_nonfull(node->child[i], key);
    }
}

BTNode* BTree_insert(BTNode* tree, int key)
{
    //null tree
    if (tree == NULL)
    {
        tree = (BTNode *)malloc(sizeof(BTNode));
        if (!tree)
        {
            printf("Error! out of memory!\n");
            return NULL;
        }
        tree->isLeaf = true;
        tree->keynum = 1;
        tree->key[0] = key;
        for (int i = 1; i < ORDER - 1; i++)
            tree->key[i] = 0;
        for (int i = 0; i < ORDER; i++)
            tree->child[i] = NULL;
        return tree;
    }
    //3 node
    if (tree->keynum == (ORDER - 1))
    {
        BTNode *node = (BTNode *)malloc(sizeof(BTNode));
        if (!node)
        {
            printf("Error! out of memory!\n");
            return NULL;
        }
        node->isLeaf = false;
        node->keynum = 0;
        node->child[0] = tree;
        for (int i = 1; i < ORDER; i++)
            node->child[i] = 0;
        BTree_split_child(node, 0, tree);

        BTree_insert_nonfull(node, key);
        return node;
    }
    else
    {
        BTree_insert_nonfull(tree, key);
        return tree;
    }

}

void erase(QPainter &painter)
{
    painter.eraseRect(0, 0, 800, 600);
}
void MainWindow::BTree_draw(QPainter &painter, BTNode *root, int layer, int x, int y)
{
    if(root==nullptr)
        return;
    else
    {
        QLabel *label;
        label = new QLabel(this);
        char temp[100]={};
        if(root->keynum >= 3){
            sprintf(temp,"%c %c %c",root->key[0], root->key[1], root->key[2]);
        } else if(root->keynum == 2){
            sprintf(temp,"%c %c",root->key[0], root->key[1]);
        }
        else if(root->keynum == 1)
            sprintf(temp,"%c",root->key[0]);
//        cout << root->keynum;
        string print = temp;
        QString str = QString::fromStdString(print);
        label->setText(str);

        label->setGeometry(QRect(QPoint(x, y),QSize(300, 50)));
        label->show();
        painter.drawRect(x-3, y+17, 33, 20);


        int count = 0;
        for (int i = 0; i <= root->keynum; i++)
            if (root->child[i] != NULL)
                ++count;


        for (int i = 0; i < count; i++)
        {
            int childX, childY;
            if(count == 1){
                childX = x;
                childY = y + 80;
            }
            else if(count == 2){
                if(i==0){
                    childX = x - 80;
                    childY = y + 80;
                }
                if(i==1){
                    childX = x + 80;
                    childY = y + 80;
                }
            }
            else if(count == 3){
                if(i==0){
                    childX = x - 50;
                    childY = y + 80;
                }
                if(i==1){
                    childX = x;
                    childY = y + 80;
                }
                if(i==2){
                    childX = x + 50;
                    childY = y + 80;
                }
            }
            else if(count == 4){
                if(i==0){
                    childX = x - 80;
                    childY = y + 80;
                }
                if(i==1){
                    childX = x - 40;
                    childY = y + 80;
                }
                if(i==2){
                    childX = x + 40;
                    childY = y + 80;
                }
                if(i==3){
                    childX = x + 80;
                    childY = y + 80;
                }
            }

            painter.drawLine(x, y+35, childX, childY+15);
            BTree_draw(painter, root->child[i], layer + 1, childX, childY);

        }

    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(flag){
        erase(painter);
//        BTree_print(painter, node, layer);
         BTree_draw(painter, sorttree, 0, 350, 150);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();
    QString sortedStr = str + '\n';
    string input = str.toStdString() + ',';
    size_t pos;
    string sortStr;
    //字串處理
    while ((pos = input.find(",")) != std::string::npos) {
        string data = input.substr(0, pos);
        sortStr += data;
        input.erase(0, pos + 1);
    }
    cout<< sortStr <<'\n';
    //insert
    char *data = _strdup(sortStr.c_str());
    for (size_t i = 0; i < sortStr.size(); i++)
    {
        sorttree = BTree_insert(sorttree, data[i]);
    }
    flag = true;
    this->update();
//    BTree_print(sorttree, 0);
}

