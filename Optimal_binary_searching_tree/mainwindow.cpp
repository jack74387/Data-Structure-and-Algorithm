#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    root = NULL;
    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::print_tree(QPainter &painter, TreeNode* root, int type, int x, int y){
    if(root==nullptr)
        return;
    else
    {
        print_tree(painter, root->left, 1, x-80, y+80);
        QLabel *label;
        label = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%c",root->key);
        string print = temp;
        std::cout << print << '\n';
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
        //        label->setFont(QFont("Timers" , 12 ,  QFont::Bold));
        label->show();
        //label_array.push_back(label);

        print_tree(painter, root->right, 2, x+80, y+80);
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(flag){
        print_tree(painter, root, 0, 600, 150);
    }
}

void MainWindow::insert_tree(TreeNode*& root, vector<vector<int>> best, int i, int j, string vertex){

    if (i > j) {
        return;
    }

    int idx = best[i][j];
    if (idx == -1) {
        return;
    }

    root->insert(root, vertex[idx - 1]);
    insert_tree(root, best, i, idx - 1, vertex); // Left subtree
    insert_tree(root, best, idx + 1, j, vertex); // Right subtree
}
void MainWindow::optimal_searching(vector<int>& freq_array, string vertex){

    int N = vertex.length();
    vector<vector<int>> cost(N + 2, vector<int>(N + 2, INT_MAX));
    vector<vector<int>> best(N + 2, vector<int>(N + 2, -1));
    int tmp = 0;
////    for(int i = 1; i <= N; i++){
////        for(int j = 1; j <= N + 1; j++){
////            cost[i][j] = INT_MAX;
////        }
////    }
    for(int i = 1; i <= N; i++){
        cost[i][i] = freq_array[i - 1];
        best[i][i] = i;
    }
    for(int i = 1; i <= N + 1; i++)
        cost[i][i - 1] = 0;
    for(int j = 1; j <= N - 1; j++){
        for(int i = 1; i <= N - j; i++){
            for(int k = i; k <= i + j; k++){
                tmp = cost[i][k - 1] + cost[k + 1][i + j];
                if(tmp < cost[i][i + j]){
                    cost[i][i + j] = tmp;
                    best[i][i + j] = k;
                }
            }
            tmp = 0;
            for(int k = i; k <= i + j; k++){
                tmp = tmp + freq_array[k - 1];
            }
            cost[i][i + j] = cost[i][i + j] + tmp;
        }
    }
//    for (int i = 1; i <= N; i++) {
//        for (int j = 1; j <= N; j++) {
//            std::cout<< cost[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
    root = NULL;
    insert_tree(root, best, 1, N, vertex);
    print_table(cost, best, vertex);
    flag = true;
    repaint();
}

void MainWindow::print_table(vector<vector<int>> cost, vector<vector<int>> best, string vertex){

    int N = vertex.length();
    ui->tableWidget->setRowCount(N);
    ui->tableWidget->setColumnCount(N);

    QStringList headers;
    for (int i = 0; i < N; i++) {
        headers.append(QString(QChar(vertex[i])));
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setVerticalHeaderLabels(headers);

    for (int i = 1; i <= N; i++) {
        ui->tableWidget->setColumnWidth(i - 1, 50);
        for (int j = i; j <= N; j++) {
            string result = std::to_string(cost[i][j]) + vertex[best[i][j] - 1];
//            std::cout << cost[i][j] << ' ' << best[i][j] << '\n';
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(result));
            ui->tableWidget->setItem(i - 1, j - 1, item);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString q_vertex = ui->lineEdit->text();
    QString q_freq = ui->lineEdit_2->text();

    string vertex = q_vertex.toStdString();
    string freq = q_freq.toStdString() + ',';
    size_t pos;
    vector<int> freq_array;

    while((pos = freq.find(',')) != string::npos){
        string tmp;
        tmp = freq.substr(0, pos);
        freq_array.push_back(stoi(tmp));
        freq.erase(0, pos + 1);
    }
    optimal_searching(freq_array, vertex);
}

