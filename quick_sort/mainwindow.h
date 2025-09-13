#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int total;

private slots:
    void on_pushButton_clicked();
    void quick_sort(string arr[], int left, int right, QString& sortedStr);
    void quick_sort2(string arr[], int left, int right, QString& sortedStr);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
