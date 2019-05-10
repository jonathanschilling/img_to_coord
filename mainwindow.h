#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QGridLayout>
#include <QString>
#include <QList>
#include <QPainter>

#include "mouselabel.h"

#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_arguments(int _argc, char** _argv);

public slots:
    void slot_mouse_pressed(QMouseEvent *event);


private:
    Ui::MainWindow *ui;

    mouseLabel *label;

    int argc;
    char** argv;

    size_t x_start;
    size_t x_end;

    size_t y_start;
    size_t y_end;

    double x_dim;
    double y_dim;

    QList<QString> files;
    int current_file;

    QPainter *ptr_tmp;
    QPixmap pm_temp;

    std::ofstream outfile;
};

#endif // MAINWINDOW_H
