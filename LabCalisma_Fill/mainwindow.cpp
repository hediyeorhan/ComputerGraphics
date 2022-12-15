#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renk = qRgb(255,255,255);
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->label->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    ui->label->setGeometry(0,0,1024,768);
    ui->label->setFrameShape(QFrame::Box);
    ui->label->show();
    kontrol = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //ilkNokta = event->pos();
    //cemberBres();

    if(kontrol == 0)
    {
        ilkNokta = event->pos();
        kontrol++;
    }
    else
    {
        sonNokta = event->pos();
        kontrol = 0;
    }
    Koseler.append(event->pos());
}

void MainWindow::cemberBres()
{
    int x = ui->lineEdit->text().toInt(), y = 0;
    int hata = 0;
    int hata1; // x, y+1
    int hata2; // x-1, y+1
    simetriBul(x, y);
    while(x >= y) {
        QApplication::processEvents();
        hata1 = hata + 2*y + 1;
        hata2 = hata + 2*y + 1 - 2*x + 1;
        if (abs(hata1) < abs(hata2)) {
            y++;
            hata = hata1;
        } else {
            x--;
            y++;
            hata = hata2;
        }
        simetriBul(x, y);
        ui->label->setPixmap(QPixmap::fromImage(res));
    }
    doldur(ilkNokta.x(),ilkNokta.y(),res.pixel(ilkNokta.x(),ilkNokta.y()),renk);
}

void MainWindow::simetriBul(int X, int Y)
{
    res.setPixel(ilkNokta.x() + X, ilkNokta.y() + Y, renk);
    res.setPixel(ilkNokta.x() + Y, ilkNokta.y() + X, renk);
    res.setPixel(ilkNokta.x() - Y, ilkNokta.y() + X, renk);
    res.setPixel(ilkNokta.x() - X, ilkNokta.y() + Y, renk);
    res.setPixel(ilkNokta.x() - X, ilkNokta.y() - Y, renk);
    res.setPixel(ilkNokta.x() - Y, ilkNokta.y() - X, renk);
    res.setPixel(ilkNokta.x() + Y, ilkNokta.y() - X, renk);
    res.setPixel(ilkNokta.x() + X, ilkNokta.y() - Y, renk);
}

void MainWindow::doldur(int x, int y, QRgb zemin, QRgb yeniRenk)
{
    QApplication::processEvents();
    if(res.pixel(x,y)==zemin)
    {
        res.setPixel(x,y,yeniRenk);
        ui->label->setPixmap(QPixmap::fromImage(res));
        doldur(x+1,y,zemin,yeniRenk);
        doldur(x-1,y,zemin,yeniRenk);
        doldur(x,y+1,zemin,yeniRenk);
        doldur(x,y-1,zemin,yeniRenk);
    }
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
    {
        adim=fabs(dy);
    }
    Xartim=dx/adim;
    Yartim=dy/adim;
    x=ilk.x();
    y=ilk.y();

    for(int i=0; i<adim; i++)
    {
        QApplication::processEvents();
        x+=Xartim;
        y+=Yartim;
        res.setPixel(round(x),round(y),renk);
        ui->label->setPixmap(QPixmap::fromImage(res));
    }

}

void MainWindow::DogruCizDDAKesikli()
{
    double dx=sonNokta.x()-ilkNokta.x();
    double dy=sonNokta.y()-ilkNokta.y();
    double Xartim, Yartim;
    double adim;
    double x,y;
    bool cizgimi = true;
    int uzunluk = 0;
    if(fabs(dx)>fabs(dy))
    {
        adim=fabs(dx);
    }
    else
    {
        adim=fabs(dy);
    }
    Xartim=dx/adim;
    Yartim=dy/adim;
    x=ilkNokta.x();
    y=ilkNokta.y();

    for(int i=0; i<adim; i++)
    {
        QApplication::processEvents();
        x+=Xartim;
        y+=Yartim;
        if(cizgimi)
        {
            res.setPixel(round(x),round(y),renk);
            ui->label->setPixmap(QPixmap::fromImage(res));
        }
        if(uzunluk == 40 && cizgimi == true) // cizgi cizdirme sarti
        {
            uzunluk = 0;
            cizgimi = false;
        }
        else if(uzunluk == 15 && cizgimi == false) // bosluk cizdirme sarti
        {
            uzunluk = 0;
            cizgimi = true;
        }
        uzunluk++;


    }
}

void MainWindow::on_pushButton_clicked()
{
    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    //Koseler.clear(); // herhangi bir noktadan doldurmasi ve asagidaki fonksyonun calismasi icin temizlemedik
}


void MainWindow::on_pushButton_2_clicked()
{
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1; // poligon cizerken en son ilk noktayı tekrar koselere ekledigimiz icin -1 yapiyoruz.
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renk);
    Koseler.clear();
    //doldur(ilkNokta.x(),ilkNokta.y(),res.pixel(ilkNokta.x(),ilkNokta.y()),renk);
}


void MainWindow::on_pushButton_3_clicked()
{
    DogruCizDDAKesikli();
}

