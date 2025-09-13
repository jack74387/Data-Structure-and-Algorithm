#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
using  std::cout;
using std::string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
string result = "";
void MainWindow::printProduct(int best[][100], int i, int j, string name) {

    if (i == j) {
        result = result + name[i - 1];
    }
    else {
        result = result + "(";
        printProduct(best, i, best[i][j] - 1, name);
        printProduct(best, best[i][j], j, name);
        result = result + ")";
    }
    ui->label_4->setText(QString::fromStdString(result));
}

int MainWindow::chainProduction(int row[], int n, string name){
    int cost[n+1][n+1], best[100][100], tmp = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j<= n; j++){
            cost[i][j] = INT_MAX;
        }
    }
    for(int i = 1; i <= n; i++)
        cost[i][i] = 0;
    for(int j = 1; j < n; j++){             //一次考慮多少個矩陣
        for(int i = 1; i <= n - j; i++){
            for(int k = i + 1; k <= i + j; k++){           //切在第k個前
                tmp = cost[i][k - 1] + cost[k][i + j] + row[i - 1] * row[i + j] * row[k - 1];
                if(cost[i][i + j] > tmp ){
                    cost[i][i + j] = tmp;
                    best[i][i + j] = k;
                }
                //cout << i <<' '<< k << ' ' << cost[i][k] << '\n';
            }
        }
    }
    printProduct(best, 1, n, name);
    return cost[1][n];

}

void MainWindow::on_pushButton_clicked()
{
    result = "";
    QString q_name=ui->lineEdit->text();
    QString q_size=ui->lineEdit_2->text();

    string name = q_name.toStdString();
    string size = q_size.toStdString() + ',';
    int row[name.size() + 1], i = 0;
    size_t pos;
    int fin_col = 0;
    while ((pos = size.find(",")) != string::npos) {
        string data = size.substr(0, pos);
        size_t star_pos = data.find("*");
        row[i] = std::stoi(data.substr(0, star_pos));
        fin_col = std::stoi(data.substr(star_pos + 1));
        size.erase(0, pos + 1);
        i++;
    }
    row[i] = fin_col;
    //for(size_t i = 0; i < name.size() + 1; i++){
    //    cout << row[i] << ' ' << '\n';
    //}

    int total = chainProduction(row, name.size(), name);
    //cout << "total:" << total << '\n';
    ui->label_6->setText( QString::number(total));
}

