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
    QString str=ui->lineEdit->text();
    QString sortedStr = str + '\n';
    string input = str.toStdString() + ',';
    size_t pos;

    struct element{
        int color_int;
        int num;
    };
    //std::vector<element> elements;
    element newElm[256];
    int elmSize = 0;

    while ((pos = input.find(",")) != string::npos) {
        string data = input.substr(0, pos);
        int color_int;
        if(data[0]=='R')color_int = 5;
        else if(data[0]=='B')color_int = 4;
        else if(data[0]=='G')color_int = 3;
        else if(data[0]=='Y')color_int = 2;
        else if(data[0]=='P')color_int = 1;
        else color_int = 0;
        int num = std::stoi(data.substr(1));

        //elements.push_back({color_int, num});
        newElm[elmSize].color_int = color_int;
        newElm[elmSize].num = num;
        elmSize++;

        input.erase(0, pos + 1);
    }

    element tmp;
    int type = 0;

    for(int i = 1; i < elmSize; i++){
        tmp = newElm[i];
        int j = i;
        type = 0;
        while((newElm[j - 1].color_int < tmp.color_int)
            ||((newElm[j - 1].color_int == tmp.color_int)&&(newElm[j - 1].num < tmp.num))){

            newElm[j] = newElm[j -1];
            j--;
            type = 1;           //如果大於，小於他的數字往後移一位
        }
        newElm[j] = tmp;        //最大的數字插到最前面
        if(type == 1){
            for(int m = 0; m < elmSize; m++){
                QString colorStr;
                switch (newElm[m].color_int) {
                    case 5: colorStr = "R"; break;
                    case 4: colorStr = "B"; break;
                    case 3: colorStr = "G"; break;
                    case 2: colorStr = "Y"; break;
                    case 1: colorStr = "P"; break;
                    default: colorStr = "Unknown"; break;
                }
                sortedStr += colorStr + QString::number(newElm[m].num) + ",";
            }
            sortedStr = sortedStr.left(sortedStr.length() - 1);
            sortedStr +='\n';
        }

    }

    ui->label_2->setText(sortedStr);
}

