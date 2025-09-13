#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
using std::string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    total = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::quick_sort2(string arr[], int left, int right, QString& sortedStr){

    //i,j from left to right
    string tmp;
    if(right >= left){
        string pivot = arr[right];
        for(int m = 0; m < right; m++){
            sortedStr += QString::fromStdString(arr[m]) + ',';
        }
        sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[right]) + "</span>,";
        for(int m = right + 1; m <= total; m++){
            sortedStr += QString::fromStdString(arr[m]) + ',';
        }
        sortedStr = sortedStr.left(sortedStr.length() - 1);
        sortedStr +="<br>";
        int x = left -1;
        for (int y = left; y < right; y++) {
            if (arr[y] < pivot) {  //如果找到較小值便交換到前面
                x++;
                tmp = arr[x];
                arr[x] = arr[y];
                arr[y] = tmp;
                if(x != y){
                    for(int m = 0; m < right; m++){
                        sortedStr += QString::fromStdString(arr[m]) + ',';
                    }
                    sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[right]) + "</span>,";
                    for(int m = right + 1; m <= total; m++){
                        sortedStr += QString::fromStdString(arr[m]) + ',';
                    }
                    sortedStr = sortedStr.left(sortedStr.length() - 1);
                    sortedStr +="<br>";
                }
            }
        }
        x++;
        tmp = arr[x];
        arr[x] = arr[right];
        arr[right] = tmp;  //使pivot到達正確位置
        if(x != right){
            for(int m = 0; m < x; m++){
                sortedStr += QString::fromStdString(arr[m]) + ',';
            }
            sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[x]) + "</span>,";
            for(int m = x + 1; m <= total; m++){
                sortedStr += QString::fromStdString(arr[m]) + ',';
            }
            sortedStr = sortedStr.left(sortedStr.length() - 1);
            sortedStr +="<br>";
        }
        quick_sort2(arr,left, x - 1, sortedStr);
        quick_sort2(arr, x + 1, right, sortedStr);
    }

}
//      i from left to right
//      j from right to left
void MainWindow::quick_sort(string arr[], int left, int right, QString& sortedStr){
    string v,tmp;
    if(right >= left){
        v = arr[right];
        int i = left - 1;
        int j = right;

        for(int m = 0; m < right; m++){
            sortedStr += QString::fromStdString(arr[m]) + ',';
        }
        sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[right]) + "</span>,";
        for(int m = right + 1; m <= total; m++){
            sortedStr += QString::fromStdString(arr[m]) + ',';
        }
        sortedStr = sortedStr.left(sortedStr.length() - 1);
        sortedStr +="<br>";

        do{
            do i++; while(arr[i] < v);     //由左向右找比v大或=v
            do j--; while(arr[j] >= v);    //由右向左找比v小
            if(i < j){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                for(int m = 0; m < right; m++){
                    sortedStr += QString::fromStdString(arr[m]) + ',';
                }
                sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[right]) + "</span>,";
                for(int m = right + 1; m <= total; m++){
                    sortedStr += QString::fromStdString(arr[m]) + ',';
                }
                sortedStr = sortedStr.left(sortedStr.length() - 1);
                sortedStr +="<br>";
            }
        }while(i < j);

        tmp = arr[i];
        arr[i] = arr[right];
        arr[right] = tmp;

        if(i != right){//使pivot到達正確位置
            for(int m = 0; m < i; m++){
                sortedStr += QString::fromStdString(arr[m]) + ',';
            }
            sortedStr += "<span style='color:red;'>" + QString::fromStdString(arr[i]) + "</span>,";
            for(int m = i + 1; m <= total; m++){
                sortedStr += QString::fromStdString(arr[m]) + ',';
            }
            sortedStr = sortedStr.left(sortedStr.length() - 1);
            sortedStr +="<br>";
        }
        quick_sort(arr,left, i - 1, sortedStr);
        quick_sort(arr, i + 1, right, sortedStr);

    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    QString sortedStr = str + "<br>";
    string data[256], input = str.toStdString() + ',';
    size_t pos;
    int count = 0;

    while((pos = input.find(',')) != std::string::npos){
        data[count] = input.substr(0, pos);
        count++;
        input.erase(0, pos + 1);
    }
    total = count - 1;
    quick_sort2(data, 0, count-1, sortedStr);


   // ui->label->setTextFormat(Qt::RichText);   //HTML style
    ui->label->setText(sortedStr);

}

