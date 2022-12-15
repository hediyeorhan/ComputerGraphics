#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

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

private:
    Ui::MainWindow *ui;
    QRgb renk;
    QImage resim;
    QPoint ilkNokta, sonNokta;
    int kontrol;
    void mousePressEvent(QMouseEvent *);
    void SimetriBul(int, int);
    QList<QPoint> koseler;
    void DogruCizDDA2(QPoint ilk, QPoint son);
};
#endif // MAINWINDOW_H
