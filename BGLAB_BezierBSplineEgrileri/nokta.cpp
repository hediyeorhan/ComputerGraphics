#include "nokta.h"
#include "resim.h"

nokta::nokta(QWidget *parent) : QLabel (parent)
{
    setScaledContents(true);
    QImage nok(":/res/images/nokta.png");
    setPixmap(QPixmap::fromImage(nok));
}

