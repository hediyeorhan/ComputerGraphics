#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QTimer>
#include "sekiller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    ui->label->setGeometry(0,0,1024,768);
    ui->label->setFrameShape(QFrame::Box);
    ui->label->show();


    ui->label->setPixmap(QPixmap::fromImage(ortam));


    ui->labelucgen->setGeometry(50, ucgen_y_koordinat, 80, 80);
    ui->labelucgen->setFrameShape(QFrame::Box);
    ui->labelucgen->show();
    ui->labelucgen->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelkare->setGeometry(150, kare_y_koordinat, 80, 80);
    ui->labelkare->setFrameShape(QFrame::Box);
    ui->labelkare->show();
    ui->labelkare->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelyamuk->setGeometry(250, yamuk_y_koordinat, 80, 80);
    ui->labelyamuk->setFrameShape(QFrame::Box);
    ui->labelyamuk->show();
    ui->labelyamuk->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelbesgen->setGeometry(350, besgen_y_koordinat, 80, 80);
    ui->labelbesgen->setFrameShape(QFrame::Box);
    ui->labelbesgen->show();
    ui->labelbesgen->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelaltigen->setGeometry(450, altigen_y_koordinat, 80, 80);
    ui->labelaltigen->setFrameShape(QFrame::Box);
    ui->labelaltigen->show();
    ui->labelaltigen->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelcember->setGeometry(550, cember_y_koordinat, 80, 80);
    ui->labelcember->setFrameShape(QFrame::Box);
    ui->labelcember->show();
    ui->labelcember->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labelbaklava->setGeometry(550, 0, 80, 80);
    ui->labelbaklava->setFrameShape(QFrame::Box);
    ui->labelbaklava->show();
    ui->labelbaklava->setPixmap(QPixmap::fromImage(ortampoligon));

    ui->labeltoplayici->setGeometry(toplayici_x, 500, 100, 30);
    ui->labeltoplayici->setFrameShape(QFrame::Box);
    ui->labeltoplayici->show();
    ui->labeltoplayici->setPixmap(QPixmap::fromImage(ortampoligon));


    res = ortampoligon;

    Ucgen();
    res = ortampoligon;
    Kare();
    res = ortampoligon;
    Yamuk();
    res = ortampoligon;
    Besgen();
    res = ortampoligon;
    Altigen();
    res = ortampoligon;
    Cember(baslangicCember);
    ui->labelcember->setPixmap(QPixmap::fromImage(res));
    res = ortampoligon;
    BaklavaDilimi();
    res = ortampoligon;

    //rastgele sekiller olusturmak icin  bunu yapiyoruz.
    sekillerdizisi.push_back(ui->labelucgen->pixmap());
    sekillerdizisi.push_back(ui->labelcember->pixmap());
    sekillerdizisi.push_back(ui->labelkare->pixmap());
    sekillerdizisi.push_back(ui->labelyamuk->pixmap());
    sekillerdizisi.push_back(ui->labelbesgen->pixmap());
    sekillerdizisi.push_back(ui->labelbaklava->pixmap());

    ui->labelkare->setGeometry(ui->labelkare->x(),
                               ui->labelkare->y()+690,
                               ui->labelkare->width(),
                               ui->labelkare->height());
    ui->labelyamuk->setGeometry(ui->labelyamuk->x(),
                               ui->labelyamuk->y()+690,
                               ui->labelyamuk->width(),
                               ui->labelyamuk->height());
    ui->labelbesgen->setGeometry(ui->labelbesgen->x(),
                               ui->labelbesgen->y()+690,
                               ui->labelbesgen->width(),
                               ui->labelbesgen->height());
    ui->labelaltigen->setGeometry(ui->labelaltigen->x(),
                               ui->labelaltigen->y()+690,
                               ui->labelaltigen->width(),
                               ui->labelaltigen->height());
    ui->labelbaklava->setGeometry(ui->labelbaklava->x(),
                               ui->labelbaklava->y()+690,
                               ui->labelbaklava->width(),
                               ui->labelbaklava->height());
    ui->labelcember->setGeometry(ui->labelcember->x(),
                               ui->labelcember->y()+690,
                               ui->labelcember->width(),
                               ui->labelcember->height());
    ui->labelucgen->setGeometry( ui->labelucgen->x(),
                                ui->labelucgen->y()+690,
                                ui->labelucgen->width(),
                                ui->labelucgen->height());

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    //std::cout<<"x : "<<event->pos().x()<<" y : "<<event->pos().y()<<std::endl;

    if(event->pos().x() >toplayici_x)
    {

        toplayici_x =30+toplayici_x;
        ui->labeltoplayici->setGeometry(toplayici_x, 500, 100, 30);
    }
    else
    {
        toplayici_x = toplayici_x-30;
        ui->labeltoplayici->setGeometry(toplayici_x, 500, 100, 30);
    }

}


void MainWindow::doldur(int x, int y, QRgb zemin, QRgb yeniRenk)
{
    if(res.pixel(x,y)==zemin)
    {
        res.setPixel(x,y,yeniRenk);
        doldur(x+1,y,zemin,yeniRenk);
        doldur(x-1,y,zemin,yeniRenk);
        doldur(x,y+1,zemin,yeniRenk);
        doldur(x,y-1,zemin,yeniRenk);
    }
}

void MainWindow::Ucgen()
{
    QPoint koordinat1(11, 23);
    QPoint koordinat2(73, 19);
    QPoint koordinat3(47, 56);
    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1;
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkucgen);
    ui->labelucgen->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::Kare()
{
    QPoint koordinat1(20, 15);
    QPoint koordinat2(60, 15);
    QPoint koordinat3(60, 55);
    QPoint koordinat4(20, 55);
    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);
    Koseler.append(koordinat4);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1;
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkkare);
    ui->labelkare->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::skorkontrol()
{

    //std::cout<<"\nToplayici X: "<<toplayici_x;
    int sayisi = sekil.size();
    for (int i = 0; i < sayisi; ++i)
    {

        if((sekil[i]->x() < toplayici_x+100 && sekil[i]->x() > toplayici_x) && (sekil[i]->y() >= 500 && sekil[i]->y() <= 515))
        {
           oyunskor++;
        }

    }

    ui->labelskor->setText(QString::number(oyunskor));

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

        x+=Xartim;
        y+=Yartim;
        res.setPixel(round(x),round(y),renk);
    }
}

void MainWindow::Yamuk()
{
    QPoint koordinat1(20, 15);
    QPoint koordinat2(60, 15);
    QPoint koordinat3(75, 55);
    QPoint koordinat4(5, 55);
    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);
    Koseler.append(koordinat4);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1;
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkyamuk);
    ui->labelyamuk->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::Besgen()
{
    QPoint koordinat1(20, 15);
    QPoint koordinat2(60, 15);
    QPoint koordinat3(70, 51);
    QPoint koordinat4(40, 70);
    QPoint koordinat5(10, 51);

    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);
    Koseler.append(koordinat4);
    Koseler.append(koordinat5);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1;
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkbesgen);
    ui->labelbesgen->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::Altigen()
{
    QPoint koordinat1(20, 15);
    QPoint koordinat2(60, 15);
    QPoint koordinat3(70, 45);
    QPoint koordinat4(60, 75);
    QPoint koordinat5(20, 75);
    QPoint koordinat6(10, 45);
    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);
    Koseler.append(koordinat4);
    Koseler.append(koordinat5);
    Koseler.append(koordinat6);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1;
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkaltigen);
    ui->labelaltigen->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::BaklavaDilimi()
{
    QPoint koordinat1(50, 5);
    QPoint koordinat2(27, 40);
    QPoint koordinat3(49, 75);
    QPoint koordinat4(71, 41);
    Koseler.append(koordinat1);
    Koseler.append(koordinat2);
    Koseler.append(koordinat3);
    Koseler.append(koordinat4);

    Koseler.append(Koseler[0]);
    for(int i=0; i<Koseler.length()-1; i++)
    {
        DogruCizDDA2(Koseler[i],Koseler[i+1]);
    }
    int x = 0, y = 0;
    for(int i=0; i<Koseler.length()-1; i++)
    {
        x += Koseler[i].x();
        y += Koseler[i].y();
    }
    x /= Koseler.length()-1; // poligon cizerken en son ilk noktayı tekrar koselere ekledigimiz icin -1 yapiyoruz.
    y /= Koseler.length()-1;
    doldur(x, y, res.pixel(x, y), renkbaklava);
    ui->labelbaklava->setPixmap(QPixmap::fromImage(res));
    Koseler.clear();
}

void MainWindow::simetriBul(int X, int Y)
{
    res.setPixel(ilknokta + X, sonnokta + Y, renk);
    res.setPixel(ilknokta + Y, sonnokta + X, renk);
    res.setPixel(ilknokta - Y, sonnokta + X, renk);
    res.setPixel(ilknokta - X, sonnokta + Y, renk);
    res.setPixel(ilknokta - X, sonnokta - Y, renk);
    res.setPixel(ilknokta - Y, sonnokta - X, renk);
    res.setPixel(ilknokta + Y, sonnokta - X, renk);
    res.setPixel(ilknokta + X, sonnokta - Y, renk);
}

void MainWindow::Durdurma()
{
    int sekilsecme,x_ekseni;

    sekilsecme=rand()%(0-6);
    x_ekseni=rand()%(1-30);


    sekiller *sekil_pointer = new  sekiller(this);

    sekil_pointer->setGeometry(x_ekseni*20,82,80,80);
    sekil_pointer->show();
    sekil.push_back(sekil_pointer);
    sekil_pointer->setPixmap(sekillerdizisi[sekilsecme]);

}


void MainWindow::Cember(QPoint newPosition)
{
    int x = 25, y = 0;
    int hata = 0;
    int hata1;
    int hata2;
    simetriBul(x, y);
    while(x >= y) {
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


    }
    doldur(newPosition.x()+10,newPosition.y(),res.pixel(newPosition.x()+10,newPosition.y()),renk);
    ui->labelcember->setPixmap(QPixmap::fromImage(res));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QTimer *zamanlayici = new QTimer(this);
    connect(zamanlayici,SIGNAL(timeout()),this,SLOT(Hareket()));
    zamanlayici->start(1000);

    QTimer *zamanlayici2 = new QTimer(this);
    connect(zamanlayici2,SIGNAL(timeout()),this,SLOT(Durdurma()));
    zamanlayici2->start(5000);
}

void MainWindow::Hareket()
{

    for (int i = 0; i < sekil.size(); ++i)
    {
           sekil[i]->setGeometry(sekil[i]->x(),
                                 sekil[i]->y() +15,
                                 sekil[i]->width(),
                                 sekil[i]->height());

    }

    skorkontrol();

}

