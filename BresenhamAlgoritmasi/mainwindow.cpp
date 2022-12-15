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
    float egim = (sonNokta.y() - ilkNokta.y()) / (sonNokta.x() - ilkNokta.x());
    float hata = 0.0;
    int x;
    int y = ilkNokta.y();

    for(x=ilkNokta.x(); x<sonNokta.x(); x++)
    {
        resim.setPixel(x,y,renk);
        ui->label->setPixmap(QPixmap::fromImage(resim));
        hata += egim;
        if(hata > 0.5)
        {
            y += 1;
            hata--;
        }

    }
}

