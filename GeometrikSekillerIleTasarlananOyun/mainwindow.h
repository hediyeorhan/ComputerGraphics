#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include<sekiller.h>
#include <QPoint>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void Hareket();

    void Durdurma();

private:
    Ui::MainWindow *ui;
    QRgb renk =  qRgb(74, 128, 77);
    QRgb renkucgen  = qRgb(255, 48, 48);
    QRgb renkkare = qRgb(0, 0, 238);
    QRgb renkyamuk = qRgb(0, 238, 0);
    QRgb renkaltigen = qRgb(205, 38, 38);
    QRgb renkbesgen = qRgb(238, 118, 0);
    QRgb renkbaklava = qRgb(0, 255, 255);

    QImage res;
    QImage ortam = QImage(1024,768,QImage::Format_RGB32);
    QImage ortampoligon = QImage(90, 90,QImage::Format_RGB32);

    QPoint baslangicCember = QPoint(40, 40);

    QList<QPixmap> sekillerdizisi;
    QList<sekiller*> sekil;
    QList<QPoint> Koseler;

    int oyunskor = 0;
    int toplayici_x = 550;
    int ilknokta = 40, sonnokta = 40;

    int kare_y_koordinat = 15;
    int ucgen_y_koordinat = 20;
    int yamuk_y_koordinat = 25;
    int altigen_y_koordinat = 30;
    int besgen_y_koordinat = 35;
    int cember_y_koordinat = 0;

    void mousePressEvent(QMouseEvent *);
    void Ucgen();
    void Kare();
    void skorkontrol();
    void doldur(int,int,QRgb,QRgb);
    void DogruCizDDA2(QPoint ilk, QPoint son);
    void Yamuk();
    void Besgen();
    void Altigen();
    void BaklavaDilimi();
    void Cember(QPoint newPosition);
    void simetriBul(int,int);


};
#endif // MAINWINDOW_H
