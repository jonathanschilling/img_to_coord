#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    x_start = 324;
//    x_end = 905;

//    y_start = 571;
//    y_end = 198;

//    x_dim = 60;
//    y_dim = 36;

    // dimensions of green rectangle => dimensions of electrode interspace
    x_start = 300; // px
    x_end = 905; // px

    y_start = 436; // px
    y_end = 118; // px

    x_dim = 60; // mm
    y_dim = 30; // mm

    //QPixmap empty(1600, 896);
    QPixmap empty(1280, 720); // image size

    label = new mouseLabel(this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->centralWidget->layout()->addWidget(label);

    label->setPixmap(empty);

    connect(label, SIGNAL(mousePressed(QMouseEvent*)), this, SLOT(slot_mouse_pressed(QMouseEvent*)));

    current_file=0;

    label->setCursor(QCursor(Qt::CrossCursor));

    outfile.open("positions.dat", std::ios::out | std::ios::ate);
    if (!outfile.is_open()) {
        qDebug() << "error opening positions.dat!";
        qApp->quit();
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    outfile.close();
}

void MainWindow::set_arguments(int _argc, char **_argv)
{
    this->argc = _argc;
    this->argv = _argv;

    for (int i=1; i<argc; ++i) {
        files.append(QString(argv[i]));
    }

    if (files.size() > 0) {
        pm_temp = QPixmap(files.at(0));
        ptr_tmp = new QPainter(&pm_temp);
        ptr_tmp->setPen(Qt::green);
        ptr_tmp->drawRect(x_start, y_start, (x_end-x_start), (y_end-y_start));
        label->setPixmap(pm_temp);
        ptr_tmp->end();
        this->setWindowTitle(files.at(0));
    }
}

void MainWindow::slot_mouse_pressed(QMouseEvent *event)
{
    double x_factor = x_dim/((double)x_start-(double)x_end);
    double y_factor = y_dim/((double)y_start-(double)y_end);


    //qDebug() << "mouse press position: " << event->pos();

    //qDebug() << "current file: " << files.at(current_file);

    // calc next index
    if (event->button() == Qt::LeftButton) {
        // right mouse click appends clicked position and loads next image

        double realSpaceX = ((double)x_start - (double)event->pos().x())*x_factor;
        double realSpaceY = ((double)y_start - (double)event->pos().y())*y_factor;

        qDebug() << files.at(current_file) << " " << realSpaceX << " " << realSpaceY;

        outfile << files.at(current_file).toLatin1().data() << " " << realSpaceX << " " << realSpaceY << std::endl;
        outfile.flush();

        if (current_file == files.size()-1) {
            current_file = 0;
        }
        else {
            ++current_file;
        }
    }
    else if (event->button() == Qt::RightButton) {
        // right mouse button brings you back one image
        if (current_file == 0) {
            current_file = files.size()-1;
        }
        else {
            --current_file;
        }
    }

    // show next pic
    pm_temp = QPixmap(files.at(current_file));
    ptr_tmp = new QPainter(&pm_temp);
    ptr_tmp->setPen(Qt::green);
    ptr_tmp->drawRect(x_start, y_start, (x_end-x_start), (y_end-y_start));
    label->setPixmap(pm_temp);
    ptr_tmp->end();
    this->setWindowTitle(files.at(current_file));
}
