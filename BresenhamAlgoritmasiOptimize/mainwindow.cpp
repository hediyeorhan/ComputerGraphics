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
    if(kontrol==0)
    {
        ilkNokta=event->pos();
        kontrol++;
    }
    else
    {
        sonNokta=event->pos();
        kontrol=0;
        BresenhamAlgoritmasi();
    }
}

void MainWindow::BresenhamAlgoritmasi()
{
    int hata = ilkNokta.x() - sonNokta.x();
    int dx2 = (sonNokta.x() - ilkNokta.x()) * 2;
    int dy2 = (sonNokta.y() - ilkNokta.y()) * 2;

    int x;
    int y = ilkNokta.y();

    for(x=ilkNokta.x(); x<sonNokta.x(); x++)
    {
        resim.setPixel(x,y,renk);
        ui->label->setPixmap(QPixmap::fromImage(resim));
        hata += dy2;
        if(hata > 0)
        {
            y++;
            hata -= dx2;
        }
    }


}

