/********************************************************************************
** Form generated from reading UI file 'promomenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMOMENU_H
#define UI_PROMOMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_PromoMenu
{
public:

    void setupUi(QDialog *PromoMenu)
    {
        if (PromoMenu->objectName().isEmpty())
            PromoMenu->setObjectName(QString::fromUtf8("PromoMenu"));
        PromoMenu->setWindowModality(Qt::ApplicationModal);
        PromoMenu->resize(114, 223);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(16);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PromoMenu->sizePolicy().hasHeightForWidth());
        PromoMenu->setSizePolicy(sizePolicy);

        retranslateUi(PromoMenu);

        QMetaObject::connectSlotsByName(PromoMenu);
    } // setupUi

    void retranslateUi(QDialog *PromoMenu)
    {
        PromoMenu->setWindowTitle(QCoreApplication::translate("PromoMenu", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PromoMenu: public Ui_PromoMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMOMENU_H
