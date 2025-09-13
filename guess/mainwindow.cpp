#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
using namespace std;
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
    string input = str.toStdString();
    size_t pos;

    int n;
    float k;
    string sub;
    sub = input.substr(0,input.find(" "));
    n = stoi(input.substr(0,input.find(" ")));
    input = input.erase(0, input.find(" ") + 1);
    k = stoi(input.substr(0,input.find(" ")));
    input = input.erase(0, input.find(" ") + 1);
    cout << n << " " << k << " " << input << '\n';
    int count[n];
    float player[n];
    for(int i = 1; i <= n; i++){
        player[i] = 0;
    }
    input + ' ';
        while ((pos = input.find(" ")) != std::string::npos) {
           sub =  input.substr(0,input.find(" "));
           int player1 = stoi(sub);
           input = input.erase(0, input.find(" ") + 1);
           sub =  input.substr(0,input.find(" "));
           string pattern1  = sub;
           input = input.erase(0, input.find(" ") + 1);
           sub =  input.substr(0,input.find(" "));
           int player2 = stoi(sub);
           input = input.erase(0, input.find(" ") + 1);
           sub =  input.substr(0,input.find(" "));
           string pattern2  = sub;
           input = input.erase(0, input.find(" ") + 1);
           if(pattern1 == "scissors" && pattern2 == "paper"){
               count[player1] ++;
           } else if(pattern1 == "rock" && pattern2 == "scissors"){
               count[player1] ++;
           } else if(pattern1 == "paper" && pattern2 == "rock"){
               count[player1] ++;
           } else if(pattern2 == "scissors" && pattern1 == "paper"){
               count[player2] ++;
           } else if(pattern2 == "rock" && pattern1 == "scissors"){
               count[player2] ++;
           } else if(pattern2 == "paper" && pattern1 == "rock"){
               count[player2] ++;
           } else if(pattern2 == "scissors" && pattern1 == "scissors"){
               k--;
           } else if(pattern2 == "rock" && pattern1 == "rock"){
                k--;
           } else if(pattern2 == "paper" && pattern1 == "paper"){
                k--;
           }
        }
        for(int i = 1; i <= n; i++){
           player[i] = count[i] / k;
           //cout << player[i] << ' ';
           printf("%3f\n", player[i]);
        }

        string output;
        for(int i = 1; i <= n; i++){
//           output = output + player[i] + '\n';
        }


        ui->lineEdit_2->setText(QString::fromStdString(output));

}

