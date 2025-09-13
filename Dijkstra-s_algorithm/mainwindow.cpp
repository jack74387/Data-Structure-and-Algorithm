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
int minDistance(int dist[], int sptSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V+1; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void MainWindow::on_pushButton_clicked()
{
    QString q_start = ui->lineEdit->text();
    QString q_path = ui->lineEdit_2->text();
    string result = "Initial <br>";
    string start = q_start.toStdString();
    string path = q_path.toStdString() + ",";
    int length[100];
    int edge[100][100];
    int visited[100] = {0};

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (i == j) edge[i][j] = 0;
            else edge[i][j] = 9999;
        }
    }

    size_t pos;
    int num = 0;
    while((pos=path.find(','))!=string::npos){
        string tmp = path.substr(0,pos);
        std::cout << tmp << '\n';
        char e1 = tmp.substr(0,tmp.find(' '))[0];
        tmp.erase(0, tmp.find(' ') + 1);
        char e2 = tmp.substr(0,tmp.find(' '))[0];

        int weight = stoi(tmp.substr(tmp.find(' ') + 1));
        int i = e1 - 'A';
        int j = e2 - 'A';
        if (i>num)num = i;
        if (j>num)num = j;
        edge[i][j] = weight;
        edge[j][i] = weight;
        //std::cout << i << ' ' << j << ' ' << weight;
        path.erase(0, pos+1);
    }
    std::copy(std::begin(edge[start[0] - 'A']), std::end(edge[start[0] - 'A']), length);

    result = result + "<table border width=400><tr><td></td>";
    char a = 'A';
    for(int i =0; i <= num; i++)
        result = result + "<td>" + char(a+i) + "</td>";
    result += "</tr><tr><td>" + start + "</td>";
    for(int i =0; i <= num; i++)
        result += "<td>" + std::to_string(length[i]) + "</td>";

    visited[start[0] - 'A'] = 1;        //開始的點
    for(int k = 0; k < num; k++){

        int u = minDistance(length, visited, num);  //造訪過的點，連出去之後的最小值

        for(int j = 0; j <= num; j++){       //一次次把加進來的點連出去之後更新成最短路徑
            if((visited[j] == 0) && (length[j] > length[u] + edge[u][j])){
                length[j] = length[u] + edge[u][j];
            }
        }
        visited[u] = 1;
        // output
        result = result + "</tr></table><br><br>Including " + char(a+u) + "<table border width=400><tr><td></td>";
        for(int i =0; i <= num; i++)
            result = result + "<td>" + char(a+i) + "</td>";
        result += "</tr><tr><td>" + start + "</td>";
        for(int i =0; i <= num; i++)
            result += "<td>" + std::to_string(length[i]) + "</td>";
    }

    result += "</tr></table>";
    ui->label_3->setText(QString::fromStdString(result));
}

