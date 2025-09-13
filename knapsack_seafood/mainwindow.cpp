#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    string form = "食材名稱,Salmon,Tuna,Istiophoridate,Fenneropenaeus,食品重量,153,260,67,93,食品價錢,253,530,153,196,食材名稱,Borealis,Adductor,Haliotis,Gratilla,食品重量,152,50,58,13,食品價錢,250,87,191,33,食材名稱,Kuroge,Chionoecetes,Eriocheir,Palinuridae,食品重量,166,77,151,60,食品價錢,431,90,180,100";
    QString qstr = QString::fromStdString(form);
    QStringList lines = qstr.split(',', Qt::SkipEmptyParts);

    ui->tableWidget->setRowCount(lines.size() / 5);
    ui->tableWidget->setColumnCount(5);

    int row = 0;
    for (int i = 0; i < lines.size(); i += 5) {
        for (int j = 0; j < 5; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(lines[i + j]);
            ui->tableWidget->setItem(row, j, item);
            if((j == 0)||((i % 3) == 0))
                ui->tableWidget->item(i/5, j)->setBackground(QColor(220, 220, 220));
        }
        row++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString q_upper=ui->lineEdit->text();
    QString q_name=ui->lineEdit_2->text();
    int upper = q_upper.toInt();
    string input_name = q_name.toStdString() + ",";
    string result = "過程(物品以" + q_name.toStdString() +"命名)：<br><br>";
    string form = "Salmon,153,253,Tuna,260,530,Istiophoridae,67,153,Fenneropenaeus,93,196,Borealis,152,250,Adductor,50,87,Haliotis,58,191,Gratilla,13,33,Kuroge,166,431,Chionoecetes,77,90,Eriocheir,151,180,Palinuridae,60,100";
    string name[100];
    int size[100] = {}, value[100] = {}, cost[5000] = {}, best[5000] = {}, len = 1;
    size_t pos;

    while ((pos = form.find(",")) != string::npos) {
        name[len] = form.substr(0, pos);
        form.erase(0, pos + 1);

        pos = form.find(",");
        size[len] = std::stoi(form.substr(0, pos));
        form.erase(0, pos + 1);

        pos = form.find(",");
        value[len] = std::stoi(form.substr(0, pos));
        form.erase(0, pos + 1);
        len++;
    }

    QStringList inName = q_name.split(",");
    string fin_name[100], total;
    int index = inName.size();
    int new_size[100] = {}, new_value[100] = {};
    for(int i = 1; i <= index; i++ ){
        for(int j = 1; j < len; j++){
            if(inName[i - 1].toStdString() == name[j]){
                new_size[i] = size[j];
                new_value[i] = value[j];
                break;
            }
        }
        fin_name[i] = inName[i - 1].toStdString();
    }
    //    cout << index<<'\n';
    //    for(int i = 1; i<= index; i++){
    //        cout << new_size[i] << ' ' << new_value[i] << '\n';
    //    }
    for(int j = 1; j <= index; j++){                //考慮幾個
        for(int i = 1; i <= upper; i++){            //考慮有限的上限中的最佳解
            if((i - new_size[j]) >= 0){
                if(cost[i] < (cost[i - new_size[j]] + new_value[j])){
                    cost[i] = cost[i - new_size[j]] + new_value[j];
                    best[i] = j;
                }
            }
        }
        result = result + "僅考慮 ";

        for(int k = 1; k <= j; k++)
            result = result + inName[k - 1].toStdString() + ' ';
        result = result + "<br><table border width=400><tr>";
        int row = 0;
        int minimal = INT_MAX;
        for(int i = 1; i <= j; i++){
            if (minimal > new_size[i]) minimal = new_size[i];
        }
        for(int i = upper; i >= minimal; i = i - new_size[best[i]]){

            result = result + "<td>" + fin_name[best[i]] + "</td>";
            if(row%5 == 4)
                result += "</tr><tr>";
            row++;
        }
        result += "</tr></table><br><br>";
    }
    int count[100] = {};
    int min = INT_MAX;
    for(int i = 1; i <= index; i++){
        if (min > new_size[i]) min = new_size[i];
    }

    for(int j = upper; j >= min; j = j - new_size[best[j]]){
        count[best[j]]++;
    }
    result += "<hr><br>當胃容量大小為 " + q_upper.toStdString() + "，拿 ";
    for(int i = 1; i <= index; i++){
        if(count[i] != 0)
            result += fin_name[i] + " " + std::to_string(count[i]) + " 個，";
    }
     result += "得總價值 " + std::to_string(cost[upper]) + "<br><hr>";
//    result = result + std::to_string(upper) + ' ' + std::to_string(cost[upper]);
    ui->label_4->setTextFormat(Qt::RichText);
    ui->label_4->setText( QString::fromStdString(result));


}

