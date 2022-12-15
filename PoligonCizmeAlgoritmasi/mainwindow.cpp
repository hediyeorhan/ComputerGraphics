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
    //ilkNokta = event->pos();
    koseler.append(event->pos());
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

void MainWindow::DogruCizDDA2(QPoint ilk, QPoint son)
{
    double dx=son.x()-ilk.x();
    double dy=son.y()-ilk.y();
    double Xartim, Yartim;
    double adim;
    double x,y;

    if(fabs(dx)>fabs(dy))
    {
        adim=fabs(dx);
    }
    else
        adim=fabs(dy);

    Xartim=dx/adim;
    Yartim=dy/adim;

    x=ilk.x();
    y=ilk.y();

    for(int i=0; i<adim; i++)
    {
        QApplication::processEvents();
        x+=Xartim;
        y+=Yartim;
        resim.setPixel(round(x),round(y),renk);
        ui->label->setPixmap(QPixmap::fromImage(resim));

    }
}

void MainWindow::on_pushButton_clicked()
{
    koseler.append(koseler[0]);
    for(int i=0; i<koseler.length()-1; i++)
    {
        DogruCizDDA2(koseler[i], koseler[i+1]);
    }
    koseler.clear();
}

