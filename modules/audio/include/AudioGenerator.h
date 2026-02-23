#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


    static const int count = 1024;

    double Y , X = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void Dots_array();
     double dots[count];

private slots:


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
