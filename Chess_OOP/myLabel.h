
#ifndef MYLABEL_H
#define MYLABEL_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

//declear a class MyLabel can accept click signal
class MyLabel : public QLabel
{
    Q_OBJECT
    using QLabel::QLabel;

signals:
    void signalclicked();

protected:
    void mousePressEvent(QMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton)
        {
            emit signalclicked();
        }
    }
};

#endif // MYLABEL_H
