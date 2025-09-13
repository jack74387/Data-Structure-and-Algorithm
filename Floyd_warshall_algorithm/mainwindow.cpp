#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString q_path = ui->lineEdit_2->text();
    string result = "";
    string path = q_path.toStdString();
    int edge[100][100];


    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (i == j) edge[i][j] = 0;
            else edge[i][j] = 1000;
        }
    }

    size_t pos;
    int N = 0;
    while((pos=path.find(')'))!=string::npos){
        string tmp = path.substr(path.find('(') + 1,pos - 1);

        char e1 = tmp.substr(0,tmp.find(','))[0];
        tmp.erase(0, tmp.find(',') + 1);
        char e2 = tmp.substr(0,tmp.find(','))[0];

        int weight = stoi(tmp.substr(tmp.find(',') + 1));
        int i = e1 - 'A';
        int j = e2 - 'A';
        if (i>N)N = i;
        if (j>N)N = j;
        edge[i][j] = weight;
        edge[j][i] = weight;
        //std::cout << i << ' ' << j << ' ' << weight<<'\n';
        path.erase(0, pos+1);
    }

    result += "initial";
    result = result + "<table border width=400><tr height='400'><td></td>";
    char a = 'A';
    for(int i = 0; i <= N; i++)
        result = result + "<td>" + char(a+i) + "</td>";
    for(int i = 0; i <= N; i++){
        result = result + "</tr><tr><td>" + char(a+i) + "</td>";
        for(int j = 0; j <= N; j++){
            result += "<td>" + std::to_string(edge[i][j]) +"</td>";
        }
    }

    int tmp;
    for(int j = 0; j <= N; j++){
        for(int i = 0; i <= N; i++){
            for(int k = 0; k <= N; k++){
                if((i != j) && (j != k) && (edge[i][j] != 1000) && (edge[j][k] != 1000)){
                    tmp = edge[i][j] + edge[j][k];
                    if(tmp < edge[i][k]){
                        edge[i][k] = tmp;
                    }
                }
            }
        }
        result = result + "</tr></table><br><br>include "+ char(a+j) +"<table border width=400><tr height='400'><td></td>";
        for(int i = 0; i <= N; i++)
            result = result + "<td>" + char(a+i) + "</td>";
        for(int i = 0; i <= N; i++){
            result = result + "</tr><tr><td>" + char(a+i) + "</td>";
            for(int j = 0; j <= N; j++){
                result += "<td>" + std::to_string(edge[i][j]) +"</td>";
            }
        }
    }


//    for(int i = 0; i <= N; i++){             //+
//        result = result + "</tr><tr><td>" + char(a+i) + "</td>";
//        for(int j = 0; j <= N; j++){
//            result += "<td>" + std::to_string(edge[i][j]) +"</td>";
//        }
//    }

//    result += "</table>";           //+
//(A,B,1) (A,C,1) (A,D,2) (B,D,3) (C,D,2) (C,E,3) (D,E,1)
//    (A,B,2) (A,C,6) (A,D,8) (B,C,-2) (B,D,3) (C,A,4) (C,D,1)
//    (A,B,15) (A,C,31) (B,C,10)
    result += "</tr></table>";
    ui->label_3->setText(QString::fromStdString(result));
}

