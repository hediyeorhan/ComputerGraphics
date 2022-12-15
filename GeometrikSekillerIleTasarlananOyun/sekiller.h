#ifndef SEKILLER_H
#define SEKILLER_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class sekiller: public QLabel
{
    Q_OBJECT
public:
    explicit sekiller(QWidget *parent = 0);
};

#endif // SEKILLER_H
