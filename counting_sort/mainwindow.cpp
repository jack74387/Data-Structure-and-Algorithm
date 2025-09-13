#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <vector>
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


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    QString sortedStr;
    string input = str.toStdString() + ',';
    size_t pos;

    std::vector<int> a;
    while ((pos = input.find(",")) != std::string::npos) {
        string data = input.substr(0, pos);
        int sortNum = stoi(data);
        a.push_back(sortNum);
        input.erase(0, pos + 1);
    }
    for (size_t i = 0; i < a.size(); i++)
        sortedStr += "-1 ";
    sortedStr += '\n';

    int maxVal = *std::max_element(a.begin(), a.end());

    //initialization
    std::vector<int> count(maxVal + 1, 0);
    std::vector<int> tmp(a.size(), -1);
    //appearing times
    for (size_t i = 0; i < a.size(); i++)
        count[a[i]]++;
    //the index of a[]
    for (int i = 1; i <= maxVal; i++)
        count[i] = count[i] + count[i-1];

    for(int i = (a.size() - 1); i >=0; i--){
        tmp[count[a[i]] - 1] = a[i];         //把最後一個值排到正確的位置上(-1是因為陣列從0開始)
        count[a[i]]--;                       //該最末位置-1
        for(const int& value : tmp){
            sortedStr += QString::number(value) + " ";
        }
        sortedStr += '\n';
    }

    QStringList lines = sortedStr.split('\n', Qt::SkipEmptyParts);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(lines.size()); // Number of rows
    ui->tableWidget->setColumnCount(a.size()); // Number of columns

    for (int i = 0; i < lines.size(); i++) {
        QStringList numbers = lines[i].split(' ', Qt::SkipEmptyParts);
        for (int j = 0; j < numbers.size(); j++) {
            QString value = (numbers[j] == "-1") ? "?" : numbers[j];
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setColumnWidth(j, 35);
            ui->tableWidget->setItem(i, j, item);
        }
    }

   // ui->label_2->setText(sortedStr);
}

