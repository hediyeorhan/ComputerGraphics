#include "resim.h"
#include <math.h>
#include <QApplication>
#include <qmath.h>
#include <math.h>

resim::resim(QWidget *parant) : QLabel(parant)
{
    renk = qRgb(255,255,255);
    QImage ortam(1024,768,QImage::Format_RGB32);
    setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    kontrol = 0;
}

void resim::mousePressEvent(QMouseEvent *event)
{
    nokta *n=new nokta(this);
    n->setGeometry(event->x(),event->y(),10,10);
    n->resimAdres=this;
    n->show();
    noktalarB.push_back(n);

}

int resim::faktoriyel(int n)
{
    if(n==0)
    {
        return 1;
    }
    else
    {
        return n*faktoriyel(n-1);
    }

}

double resim::Cfonksiyon(int n, int i)
{
    return faktoriyel(n)/(faktoriyel(i)*faktoriyel(n-i));

}

QPoint resim::Bfonksiyon(double u)
{
    QPoint yeniNokta;
    double X=0,Y=0;
    for(int i=0; i<noktalarB.size(); i++)
    {
        X+=noktalarB[i]->x()*Cfonksiyon(noktalarB.size()-1,i)*pow(u,i)*pow(1-u,(noktalarB.size()-1)-i);
        Y+=noktalarB[i]->y()*Cfonksiyon(noktalarB.size()-1,i)*pow(u,i)*pow(1-u,(noktalarB.size()-1)-i);
    }
    yeniNokta.setX(round(X));
    yeniNokta.setY(round(Y));
    return yeniNokta;

}

void resim::cizBezier()
{
    QPoint nokta;
    double u=0;
    while(u<=1)
    {
        QApplication::processEvents();
        nokta=Bfonksiyon(u);
        res.setPixel(nokta.x(),nokta.y(),renk);
        setPixmap(QPixmap::fromImage(res));
        u+=0.001;
    }
}

void resim::cizBSpline()
{
    dugumVektoru.clear();
    int i=1,k=0;
    int vektorboyu=derece+noktalarB.size();
    while(k<vektorboyu)
    {
        if(k<derece)
        {
            dugumVektoru.push_back(0);
        }
        else if(k>=noktalarB.size())
        {
            dugumVektoru.push_back(i);
        }
        else
        {
            dugumVektoru.push_back(i);
            i++;
        }
        k++;
    }
    QPoint nokta;
    double u=0;
    while(u<dugumVektoru[dugumVektoru.size()-1])
    {
        QApplication::processEvents();
        nokta=Spline(u,derece);
        res.setPixel(nokta.x(),nokta.y(),renk);
        setPixmap(QPixmap::fromImage(res));
        u+=0.001;
    }

}

QPoint resim::Spline(double u, int k)
{
    QPoint yeniNokta;
    double X,Y,carpan;
    for(int i=0; i<noktalarB.size();i++)
    {
        carpan=splineFonk(i,k,u);
        X+=noktalarB[i]->x()*carpan;
        Y+=noktalarB[i]->y()*carpan;
    }
    yeniNokta.setX(round(X));
    yeniNokta.setY(round(Y));
    return yeniNokta;

}

double resim::splineFonk(int i, int k, double u)
{
    double v;
    double payda;
    if(k==1)
    {
        if(dugumVektoru[i]<=u && u<=dugumVektoru[i+1])
        {
            v=1.0;
        }
        else
        {
            v=0.0;
        }
    }
    else
    {
        v=0.0;
        payda=dugumVektoru[i+k-1]-dugumVektoru[i];
        if(payda!=0)
        {
            v=((u-dugumVektoru[i])/payda)*splineFonk(i,k-1,u);
        }
        payda=dugumVektoru[i+k]-dugumVektoru[i+1];
        if(payda!=0)
        {
            v+=((dugumVektoru[i+k]-u)/payda)*splineFonk(i+1,k-1,u);
        }
    }
    return v;

}





