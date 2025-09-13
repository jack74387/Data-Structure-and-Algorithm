#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.1415926
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = false;
    x1 = 0; y1 = 0; x2 = 0; y2 = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void DrawLineWithArrow(QPainter& painter, QPoint start, QPoint end, bool bidirectional) {

    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal arrowSize = 15;
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    end = QPoint(end.rx(), end.ry()+20);
    start = QPoint(start.rx(), start.ry()+20);
    if (bidirectional) {
        end += QPoint(0, -12);
        start += QPoint(0, -12);
    }
    QLineF line(end, start);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF newEndPoint = line.p2() - QPointF(line.dx()*0.92, line.dy()*0.92);
    line.setP1(newEndPoint);

    angle = std::atan2(-line.dy(), line.dx());

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);

}
void MainWindow::print_graph(QPainter &painter)
{
    painter.eraseRect(0, 0, width(), height());

    int length = vertex.length();
    int radius = 200;
    int center_x = 650, center_y = 310;
    //painter.drawEllipse(650, 310, 30, 30);


    for(int i = 0; i < length; i++){
        int x, y;
        x = center_x + radius * cos(2 * PI / length * i);
        y = center_y + radius * sin(2 * PI / length * i);
        all_e[i] = QPoint(x, y);
    }
// (B,A,1) (B,C,2) (B,D,4) (C,D,3) (D,B,5) (D,E,6)
    std::vector<QLabel*> labels;
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            if(edge[i][j] != 0){
                QLabel *label;
                label = new QLabel(this);
                char temp[100]={};
                sprintf(temp,"%d", edge[i][j]);
                string print = temp;
                label->setText(QString::fromStdString(print));

                QPoint position = (all_e[i] + all_e[j]) / 2;
                if (i<j&&edge[j][i] != 0) {
                    position += QPoint(0, -20);
                }
                label->setGeometry(QRect(position,QSize(80, 80)));
                label->show();
                labels.push_back(label);
                //painter.drawLine(all_e[i].x(), all_e[i].y()+20, all_e[j].x(), all_e[j].y()+20);
                DrawLineWithArrow(painter, all_e[i], all_e[j], i<j&&edge[j][i] != 0);
            }
        }
    }

    for(int i = 0; i < length; i++){
        int x = all_e[i].x();
        int y = all_e[i].y();

        QLabel *label1;
        label1 = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%c", vertex[i]);
        string print = temp;
        QString str = QString::fromStdString(print);
        painter.setBrush(Qt::white);
        painter.drawEllipse(x-11, y+5, 30, 30);
        label1->setText(str);
        label1->setGeometry(QRect(all_e[i],QSize(40, 40)));
        label1->show();

        labels.push_back(label1);
    }

    for(auto label : labels) {
        label->deleteLater();
    }

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen;

    if(flag){
        print_graph(painter);
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString q_vertex=ui->lineEdit->text();
    QString q_edge=ui->lineEdit_2->text();

    vertex = q_vertex.toStdString();
    string edgeStr = q_edge.toStdString();

    int length = vertex.length();
    edge = new int*[length];
    for (int i = 0; i < length; ++i) {
        edge[i] = new int[length];
        for (int j = 0; j < length; ++j) {
            edge[i][j] = 0;
        }
    }
    size_t pos;

    while((pos=edgeStr.find(')'))!=string::npos){
        string tmp, e1, e2;
        int weight, i, j;
        tmp = edgeStr.substr(edgeStr.find('(') + 1,pos - 1);
        e1 = tmp.substr(0,tmp.find(','));
        tmp.erase(0, tmp.find(',') + 1);
        e2 = tmp.substr(0,tmp.find(','));
        weight = stoi(tmp.substr(tmp.find(',') + 1));
        i = vertex.find(e1);
        j = vertex.find(e2);
        edge[i][j] = weight;
        //std::cout << e1 << ' ' << e2 << ' ' << weight;
        edgeStr.erase(0, pos+2);
    }



    ui->tableWidget->setRowCount(length);
    ui->tableWidget->setColumnCount(length);

    QStringList headers;
    for (int i = 0; i < length; i++) {
        headers.append(QString(QChar(vertex[i])));
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setVerticalHeaderLabels(headers);

    for (int i = 0; i < length; i++) {
        ui->tableWidget->setColumnWidth(i, 35);
        for (int j = 0; j < length; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(edge[i][j]));
            ui->tableWidget->setItem(i, j, item);
        }
    }
//(B,A,1) (B,C,2) (B,D,4) (C,D,3) (D,B,5) (D,E,6)





    flag= true;
    this->update();
}



