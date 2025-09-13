#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.1415926
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = false;
    flag_2 = false;
    flag_3 = false;
    x1 = 0; y1 = 0; x2 = 0; y2 = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
vector<int> index;
vector<int> index2;
vector<int> index3;
static int total = 0;
void MainWindow::print_mst(QPainter &painter){
    QPen pen;
    pen.setBrush(Qt::black);
    painter.setPen(pen);
    int length = vertex.length();
    std::vector<QLabel*> labels;
    for (int k = 0; k < length; k++) {
        int i = index.at(k);
        int j = index2.at(k);
        QLabel *label;
        label = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%d", edge[i][j]);
        string print = temp;
        label->setText(QString::fromStdString(print));
        int x = all_e[i].x() - 430;
        int y = all_e[i].y();
        int xx = all_e[j].x() - 430;
        int yy = all_e[j].y();
        label->setGeometry((x + xx)/2, (y + yy)/2, 80, 80);
        label->show();
        labels.push_back(label);
    }

    for(int i = 0; i < length; i++){
        int x = all_e[i].x();
        int y = all_e[i].y();
        x1 = all_e[index2.at(i)].rx() - 430;
        y1 = all_e[index2.at(i)].ry() + 13;
        x2 = all_e[index.at(i)].rx() - 430;
        y2 = all_e[index.at(i)].ry() + 13;
        painter.drawLine(x1,y1,x2,y2);
        QLabel *label1;
        label1 = new QLabel(this);
        char temp[100]={};
        sprintf(temp,"%c", vertex[i]);
        string print = temp;
        QString str = QString::fromStdString(print);
        painter.setBrush(Qt::white);
        painter.drawEllipse(x-441, y+5, 30, 30);
        label1->setText(str);
        label1->setGeometry(all_e[i].x() - 430, all_e[i].y(), 40, 40);
        label1->show();

        labels.push_back(label1);
    }


    QLabel *label2;
    label2 = new QLabel(this);
    string temp;
    for(auto i : index3){
        if(i == index3[length - 1])
            temp = temp + vertex[i] + "      ";
        else
            temp = temp + vertex[i] + "->";
    }
    QString str = QString::fromStdString(temp);
    label2->setText(str);
    label2->setGeometry(100, 550, length*21, 40);
    label2->show();

    labels.push_back(label2);

    for(auto label : labels) {
        label->deleteLater();
    }

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
                label->setGeometry(QRect((all_e[i] + all_e[j])/2,QSize(80, 80)));
                label->show();
                labels.push_back(label);
                painter.drawLine(all_e[i].x(), all_e[i].y()+20, all_e[j].x(), all_e[j].y()+20);
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
int MainWindow::minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    int V = vertex.length();

    for (int v = 0; v < V; v++){
        if ((mstSet[v] == false) && (key[v] < min)){
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void MainWindow::prime_mst(string start){
    int V = vertex.length();
    // Array to store constructed MST
    int parent[V];
    // Key values used to pick minimum weight edge in cut
    int key[V];

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    //std::cout << vertex.find(start)<<'a';
    key[vertex.find(start)] = 0;             //起始點加進來

    // First node is always root of MST
    parent[vertex.find(start)] = -1;

    index3.push_back(vertex.find(start));
    // The MST will have V vertices
    for (int count = 0; count < V; count++) {

        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);          //找出加進來的點連出去最小的值

        // Add the picked vertex to the MST Set
        mstSet[u] = true;                     //加進集合
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++){       //更新連出去的值
            if ((edge[u][v]!=0) && (mstSet[v] == false) && (edge[u][v] < key[v])){
                parent[v] = u, key[v] = edge[u][v];
            }
        }
        if(u!=vertex.find(start)){
            std::cout << "\n i:" << u << " parent[i]:" << parent[u];
            index.push_back(u);
            index2.push_back(parent[u]);
            index3.push_back(u);
        }
    }
//    (B,A,1) (B,C,2) (C,D,3) (D,B,6) (D,E,6)

    flag_2 = true;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen;

    if(flag){
        print_graph(painter);
    }
    if(flag_2){
        for (int i = 0; i < total; i++) {
            x1 = all_e[index2.at(i)].rx();
            y1 = all_e[index2.at(i)].ry() + 13;
            x2 = all_e[index.at(i)].rx();
            y2 = all_e[index.at(i)].ry() + 13;
            pen.setWidth(3);
            pen.setBrush(Qt::red);
            painter.setPen(pen);
            painter.drawLine(x1,y1,x2,y2);
        }
        update();
    }
    if(flag_3){
        print_mst(painter);
        update();
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
        edge[j][i] = weight;
        //std::cout << e1 << ' ' << e2 << ' ' << weight;
        edgeStr.erase(0, pos+2);
    }
    flag= true;
    this->update();
    QString q_start_vertex=ui->lineEdit_3->text();
    string start_vertex = q_start_vertex.toStdString();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString q_start_vertex=ui->lineEdit_3->text();
    string start_vertex = q_start_vertex.toStdString();
   // std::cout << 'a';
    total += 1;
    prime_mst(start_vertex);
}



void MainWindow::on_pushButton_3_clicked()
{
    flag_3 = true;
}
// (A,B,4) (A,D,2)  (B,C,8) (B,D,12) (B,E,14) (C,E,12) (C,F,20) (D,G,14) (D,H,16) (E,H,18) (E,I,8) (F,I,10) (G,J,24) (G,H,10) (H,I,6) (I,J,22)
