#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treenode.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    root = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}
string findPath(TreeNode* root, int searchValue) {

    if (root == nullptr)
        return "";

    string str = to_string(root->key);
    // If the search value is smaller than the current node's value, go left
    if (searchValue < root->key){
        string leftPath = findPath(root->left, searchValue);
        if (!leftPath.empty()) // If a path is found on the left, append it to str
            str += ", " + leftPath;
    }
    // If the search value is larger than the current node's value, go right
    else if (searchValue > root->key){
        string rightPath = findPath(root->right, searchValue);
        if (!rightPath.empty()) // If a path is found on the right, append it to str
            str += ", " + rightPath;
    }
    // If the search value matches the current node's value, we've found the node
    else
        return str;

    return str;
}


void MainWindow::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();
    string input = str.toStdString() + ',';
    size_t pos;
    string sortStr;
    vector<int> lst;
    while ((pos = input.find(",")) != std::string::npos) {
        string data = input.substr(0, pos);
//        sortStr += data;
        lst.push_back(stoi(data));
        input.erase(0, pos + 1);
    }
    cout<< sortStr <<'\n';

    for(size_t j=0;j<lst.size();j++)
    {
        root=root->insert(root,lst[j]);
    }
    QString node=ui->lineEdit_2->text();
    int search = node.toInt() ;
    input = "";
    input = findPath(root, search);

    ui->textEdit->setText(QString::fromStdString(input));

}

