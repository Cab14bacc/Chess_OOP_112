#ifndef PROMOMENU_H
#define PROMOMENU_H

#include "ui_promomenu.h"
#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>

namespace Ui {
class PromoMenu;
}

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    ClickableLabel(const QPixmap& pixmap, int label_number, QWidget* parent = nullptr) :
        QLabel(parent), label_number_(label_number) {
        setPixmap(pixmap);
    }

signals:
    void clicked(int label_number);

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked(label_number_);
    }

private:
    int label_number_;
};

class PromoMenu : public QDialog
{
    Q_OBJECT
private:
    Ui::PromoMenu *ui;
    void label_clicked(int label_number) {
        // Return the label number that was clicked
        result = label_number;
        accept();
    }
public:
    int result = 0;
    ~PromoMenu()
    {
        delete ui;
    }
    PromoMenu(QWidget *parent = nullptr,QString player = ""):QDialog(parent){
        // Create 4 ClickableLabels with QPixmaps
        setWindowFlags(Qt::FramelessWindowHint);
        ClickableLabel* label1 = new ClickableLabel(QPixmap("./images/"+player+"Queen.png"), 1, this);
        ClickableLabel* label2 = new ClickableLabel(QPixmap("./images/"+player+"Knight.png"), 2, this);
        ClickableLabel* label3 = new ClickableLabel(QPixmap("./images/"+player+"Bishop.png"), 3, this);
        ClickableLabel* label4 = new ClickableLabel(QPixmap("./images/"+player+"Rook.png"), 4, this);

        // Create a QVBoxLayout and add the labels to it
        QVBoxLayout* vbox = new QVBoxLayout(this);
        vbox->addWidget(label1);
        vbox->addWidget(label2);
        vbox->addWidget(label3);
        vbox->addWidget(label4);

        // Connect the clicked signal of each label to a slot
        connect(label1, &ClickableLabel::clicked, this, &PromoMenu::label_clicked);
        connect(label2, &ClickableLabel::clicked, this, &PromoMenu::label_clicked);
        connect(label3, &ClickableLabel::clicked, this, &PromoMenu::label_clicked);
        connect(label4, &ClickableLabel::clicked, this, &PromoMenu::label_clicked);
    }


};

#endif // PROMOMENU_H





