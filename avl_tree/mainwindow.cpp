#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
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
#include <vector>
#include <cstdlib>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stringstream;
using std::string;

Node *sorttree = NULL;

int max(int a, int b);

// Calculate height
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
    Node *x = y->left;     //左子樹
    Node *T2 = x->right;   //左子樹的右子樹
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    return x;
}

// Rotate left
Node *leftRotate(Node *x) {
    Node *y = x->right;    //右子樹
    Node *T2 = y->left;    //右子樹的左子樹
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key >= node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key >= node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key >= node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

//// Node with minimum value
//Node *nodeWithMimumValue(Node *node) {
//    Node *current = node;
//    while (current->left != NULL)
//        current = current->left;
//    return current;
//}

//// Delete a node
//Node *deleteNode(Node *root, int key) {
//    // Find the node and delete it
//    if (root == NULL)
//        return root;
//    if (key < root->key)
//        root->left = deleteNode(root->left, key);
//    else if (key > root->key)
//        root->right = deleteNode(root->right, key);
//    else {
//        if ((root->left == NULL) ||
//            (root->right == NULL)) {
//            Node *temp = root->left ? root->left : root->right;
//            if (temp == NULL) {
//                temp = root;
//                root = NULL;
//            } else
//                *root = *temp;
//            free(temp);
//        } else {
//            Node *temp = nodeWithMimumValue(root->right);
//            root->key = temp->key;
//            root->right = deleteNode(root->right,
//                                     temp->key);
//        }
//    }

//    if (root == NULL)
//        return root;

//    // Update the balance factor of each node and
//    // balance the tree
//    root->height = 1 + max(height(root->left),
//                           height(root->right));
//    int balanceFactor = getBalanceFactor(root);
//    if (balanceFactor > 1) {
//        if (getBalanceFactor(root->left) >= 0) {
//            return rightRotate(root);
//        } else {
//            root->left = leftRotate(root->left);
//            return rightRotate(root);
//        }
//    }
//    if (balanceFactor < -1) {
//        if (getBalanceFactor(root->right) <= 0) {
//            return leftRotate(root);
//        } else {
//            root->right = rightRotate(root->right);
//            return leftRotate(root);
//        }
//    }
//    return root;
//}

// Print the tree
void printTree(Node *root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}
void erase(QPainter &painter)
{
    painter.eraseRect(0, 0, 800, 600);
}
void MainWindow::BTree_draw(QPainter &painter, Node *root, int type, int x, int y)
{
    if(root==nullptr)
        return;
    else
    {
        BTree_draw(painter, root->left, 1, x-80, y+80);
        QLabel *label;
        label = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%d",root->key);
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
        label->setFont(QFont("Timers" , 12 ,  QFont::Bold));
        label->show();
        BTree_draw(painter, root->right, 2, x+80, y+80);


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
    Node *root = NULL;
    while ((pos = input.find(",")) != std::string::npos) {
        string data = input.substr(0, pos);
        int num = stoi(data);
        sorttree = insertNode(sorttree, num);
        sortStr += data;
        input.erase(0, pos + 1);
    }
    cout<< sortStr <<'\n';
    //char *data = _strdup(sortStr.c_str());
//    for (size_t i = 0; i < sortStr.size(); i++)
//    {
//        sorttree = insertNode(sorttree, data[i]-48);
//    }
    printTree(root, "", true);
    flag = true;
    this->update();
}

