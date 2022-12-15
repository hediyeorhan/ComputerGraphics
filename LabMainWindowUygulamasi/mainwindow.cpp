#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    QImage res("C://Users//dilara//Desktop//mr.jpg");
    ui->label->setPixmap(QPixmap::fromImage(res));
    resim=res;
    QImage don(ui->label_2->width(),ui->label_2->height(),QImage::Format_RGB32);
    ui->label_2->setPixmap(QPixmap::fromImage(don));
    donusum=don;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOtele_triggered()
{

    for(int i=0;i<resim.width();i++)
    {
        for(int j=0;j<resim.height();j++)
        {
            donusum.setPixel(i+150,j+200,resim.pixel(i,j));
        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(donusum));
}


void MainWindow::on_actionRostasyon_triggered()
{
    double x,y;
    double aci=90;

    for(int i=0;i<resim.width();i++)
    {
        for(int j=0;j<resim.height();j++)
        {
            x=i*cos(qDegreesToRadians(aci)-j*sin(qDegreesToRadians(aci)));
            y=i*sin(qDegreesToRadians(aci)+j*cos(qDegreesToRadians(aci)));
            //donusum.setPixel(round(x)+350,round(y),resim.pixel(i,j));
            donusum.setPixel(abs(round(x))+350,abs(round(y)),resim.pixel(i,j));

        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(donusum));
}

void MainWindow::on_actionOlceklendir_triggered()
{
    double x,y;
    double sx,sy;
    sx=0.5;
    sy=0.5;
    for(int i=0;i<resim.width();i++)
    {
        for(int j=0;j<resim.height();j++)
        {
           x=i*sx;
           y=j*sy;
           donusum.setPixel(x,y,resim.pixel(i,j));

        }
    }
    ui->label_2->setPixmap(QPixmap::fromImage(donusum));



}









