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
    std::vector<element> elements;

    while ((pos = input.find(",")) != std::string::npos) {
        string data = input.substr(0, pos);
        int color;
        if     (data[0]=='R')color = 5;
        else if(data[0]=='B')color = 4;
        else if(data[0]=='G')color = 3;
        else if(data[0]=='Y')color = 2;
        else if(data[0]=='P')color = 1;
        else color = 0;
        int num = std::stoi(data.substr(1));

        elements.push_back({color, num});
        input.erase(0, pos + 1);
    }
    int flag,type=0;
    element tmp;
    do{
        tmp = elements[0];
        flag = 0;
        for(size_t i = 1; i < elements.size();i++){
            if((elements[i-1].color_int == elements[i].color_int)
                &&(elements[i-1].num < elements[i].num)){
                tmp = elements[i-1];
                elements[i-1] = elements[i];
                elements[i] = tmp;
                flag = 1;
                type = 1;
            } else if(elements[i-1].color_int < elements[i].color_int){
                tmp = elements[i-1];
                elements[i-1] = elements[i];
                elements[i] = tmp;
                flag = 1;
                type = 1;             //如果小於便交換
            }
            if(type == 1){
                for (const element& e : elements) {
                    QString colorStr;
                    switch (e.color_int) {
                        case 5: colorStr = "R"; break;
                        case 4: colorStr = "B"; break;
                        case 3: colorStr = "G"; break;
                        case 2: colorStr = "Y"; break;
                        case 1: colorStr = "P"; break;
                        default: colorStr = "Unknown"; break;
                    }

                    sortedStr += colorStr + QString::number(e.num) + ",";

                }
                sortedStr = sortedStr.left(sortedStr.length() - 1);
                sortedStr +='\n';
            }
            type = 0;
        }

    }while(flag == 1);      //只要前一個小於後一個(順序錯誤)就繼續再做一次

    ui->label->setText(sortedStr);


}



