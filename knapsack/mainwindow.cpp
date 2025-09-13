#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    string form = "品項,價格,熱量/卡,莓果戀人,33,343,法式奶霜紅,20,366,英式鮮奶茶,36,366,珍珠鮮奶茶,55,520,南非國寶鮮奶茶,63,534,牛奶三兄弟,32,302,冬瓜鮮奶茶,58,534,紅豆牛奶,55,268,紅豆鮮奶茶,60,560,紅豆珍珠鮮奶茶,63,600";
    QString qstr = QString::fromStdString(form);
    QStringList lines = qstr.split(',', Qt::SkipEmptyParts);

    ui->tableWidget->setRowCount(lines.size() / 3);
    ui->tableWidget->setColumnCount(3);

    int row = 0;
    for (int i = 0; i < lines.size(); i += 3) {
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(lines[i + j]);
            ui->tableWidget->setItem(row, j, item);
            ui->tableWidget->item(0, j)->setBackground(QColor(220, 220, 220));
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
    string result = "過程(物品以" + q_name.toStdString() +"命名)：\n\n";
    string form = "莓果戀人,33,343,法式奶霜紅,20,366,英式鮮奶茶,36,366,珍珠鮮奶茶,55,520,南非國寶鮮奶茶,63,534,牛奶三兄弟,32,302,冬瓜鮮奶茶,58,534,紅豆牛奶,55,268,紅豆鮮奶茶,60,560,紅豆珍珠鮮奶茶,63,600";
    string name[100];
    int size[100] = {}, value[100] = {}, cost[5000] = {}, best[5000] = {}, len = 1;
    size_t pos;
    int minimal = INT_MAX;
    while ((pos = form.find(",")) != string::npos) {
        name[len] = form.substr(0, pos);
        form.erase(0, pos + 1);

        pos = form.find(",");
        value[len] = std::stoi(form.substr(0, pos));
        form.erase(0, pos + 1);

        pos = form.find(",");
        size[len] = std::stoi(form.substr(0, pos));
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
    for(int j = 1; j <= index; j++){
        for(int i = 1; i <= upper; i++){
            if((i - new_size[j]) >= 0){
                if(cost[i] < (cost[i - new_size[j]] + new_value[j])){
                    cost[i] = cost[i - new_size[j]] + new_value[j];
                    best[i] = j;
                }
            }
        }
        result = result + "僅考慮 ";

        for(int i = 1; i <= j; i++){
            if (minimal > new_size[i]) minimal = new_size[i];
        }
        for(int k = 1; k <= j; k++)
            result = result + inName[k - 1].toStdString() + ' ';
        result += ":\n";
        for(int i = upper; i >= minimal; i = i - new_size[best[i]]){
            result = result + fin_name[best[i]] + ' ';
        }
        result += "\n\n";
    }
    int count[100] = {};
    for(int j = upper; j >= minimal; j = j - new_size[best[j]]){
        count[best[j]]++;
    }
    result += "當熱量攝取上限" + std::to_string(upper) + "，買";
    for(int i = 1; i <= index; i++){
        if(count[i] != 0)
            result += fin_name[i] + " " + std::to_string(count[i]) + " 杯，";
    }
    result = result + "花了" + std::to_string(cost[upper]) + "元";
    ui->label_4->setText( QString::fromStdString(result));


}

