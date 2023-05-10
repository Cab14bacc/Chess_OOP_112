
#ifndef MYLABEL_H
#define MYLABEL_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
    using QLabel::QLabel;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event)
    {
        if(event->button() == Qt::LeftButton)
        {
            emit clicked();
        }
    }
};

#endif // MYLABEL_H
