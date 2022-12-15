#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setGeometry(0,0,600,600);
    ui->label->setFrameShape(QFrame::Box);
    ui->label->show();
    renk=qRgb(255,255,255);
    QImage ortam(600,600,QImage::Format_RGB32);
    ui->label->setPixmap(QPixmap::fromImage(ortam));
    resim=ortam;
    kontrol=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    ilkNokta = event->pos();
    DaireAlgoritmasi();
}

void MainWindow::DaireAlgoritmasi()
{
    int yaricap = ui->lineEdit->text().toInt();
    double x, y;
    double aci=0.0;
    while(aci <= 360)
    {
        QApplication::processEvents();
        x = cos(qDegreesToRadians(aci)) * yaricap;
        y = sin(qDegreesToRadians(aci)) * yaricap;
        SimetriBul(x, y);
        aci += 0.01;
        ui->label->setPixmap(QPixmap::fromImage(resim));
    }
}

void MainWindow::SimetriBul(int x, int y)
{
    resim.setPixel(ilkNokta.x() + x, ilkNokta.y() + y, renk);
    resim.setPixel(ilkNokta.x() + x, ilkNokta.y() - y, renk);
    resim.setPixel(ilkNokta.x() + y, ilkNokta.y() + x, renk);
    resim.setPixel(ilkNokta.x() - y, ilkNokta.y() + x, renk);
    resim.setPixel(ilkNokta.x() - x, ilkNokta.y() + y, renk);
    resim.setPixel(ilkNokta.x() + y, ilkNokta.y() - x, renk);
    resim.setPixel(ilkNokta.x() - y, ilkNokta.y() - x, renk);
    resim.setPixel(ilkNokta.x() - x, ilkNokta.y() - y, renk);
}

