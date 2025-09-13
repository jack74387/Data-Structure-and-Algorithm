#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include "TreeNode.h"
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
    ui->lineEdit->insert("CPKiauh");
    ui->lineEdit_2->insert("PiKaChu");
    ui->lineEdit_3->insert("P");
//    ui->label_2->setFont(QFont("Timers" , 16 ,  QFont::Bold));
//    ui->label_4->setFont(QFont("Timers" , 16 ,  QFont::Bold));
//    ui->label->setFont(QFont("Timers" , 16 ,  QFont::Bold));
//    ui->label_3->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    root = NULL;
    flag = false;
    clear = false;
    x=350;
    y=300;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FindAForder(char* inorder, char* preorder, int length, char* aforder, int &dis, string &print)
{
    if (length == 0)
        return;
    TreeNode* node = new TreeNode;
    node->key = *preorder;
    int root;
    for (root = 0; root < length; root++)
    {
        /*每次都是找出根結點*/
        if (inorder[root] == *preorder)
            break;

    }
    //Left
    FindAForder(inorder, preorder + 1, root, aforder, dis, print);
    //Right
    FindAForder(inorder + root + 1, preorder + root + 1, length - (root + 1), aforder, dis, print);
    print.push_back(node->key);
//    aforder[dis++] = (char)node->key;  //postorder stored in aforder[]
    //cout << node->num << ' ';
}
void search_parent(TreeNode* root, char node, string &parent, bool &flag)
{
    if (root == NULL)
        return;
    if (root->key != node)
    {

        if(!flag){
            parent = root->key;
            search_parent(root->left, node, parent, flag);
        }
        if (!flag){
            parent = root->key;
            search_parent(root->right, node, parent, flag);
        }
    }
    else
    {
        flag = 1;
        return;
    }

}
void search_child(TreeNode* root, char node, bool &flag, string &a)
{
    if (root == NULL)
        return;
    //find node
    if (root->key == node)
    {
        a="";
        if (root->left != NULL)
            a += root->left->key;
        if (root->right != NULL)
            a += root->right->key;
        flag = 1;
    }
    else
    {
        if (!flag)
            search_child(root->left, node, flag, a);
        if (!flag)
            search_child(root->right, node, flag, a);
    }


}
TreeNode* insert_pr(TreeNode* root,int limit, char *pr, char *in)
{
    int x, j;
    int center = 0;
    for (x = 0; x < limit; x++)
    {
        if (pr[0] == in[x])
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
            if (pr[j] == in[x])
                break;
        }
        root = root->insert(root, pr[j], x);
    }

    return root;
}

void MainWindow::on_pushButton_clicked()
{
    //clear
    string print="";
    for(int j=0;j<pr_s.size();j++)
        root=root->deleteNode(root,pr[j]);
    this->update();
    //字串處理
    pr_s=ui->lineEdit->text();
    in_s=ui->lineEdit_2->text();
    QString node_s=ui->lineEdit_3->text();
    node = node_s.toStdString();
    pr=strdup(pr_s.toStdString().c_str());
    in=strdup(in_s.toStdString().c_str());
    char *af=new char(pr_s.size());

    print += "Preorder: " + pr_s.toStdString()+'\n';
    print += "Inorder: " + in_s.toStdString()+'\n';
    print += "Postorder: ";
    //找出postorder
    int i=0;
    FindAForder(in, pr, pr_s.size(), af, i, print);
    print+='\n';

    root = insert_pr(root, pr_s.size(), pr, in);

    //找出parent child
    bool bools = 0, bools2 = 0;
    string ans;
    search_parent(root, node[0], ans, bools);
    string ans2;
    search_child(root, node[0], bools2, ans2);
//    string ans_s;
//    ans_s.push_back(ans);
    print += "parent: " + ans + '\n';
    print += "child: " + ans2 + '\n';

    QString str=QString::fromStdString(print);
    ui->textBrowser->setText(str);
//    ui->textBrowser->setFont(QFont("Timers" , 16 ,  QFont::Bold));

    this->update();
}


