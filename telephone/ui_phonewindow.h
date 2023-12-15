/********************************************************************************
** Form generated from reading UI file 'phonewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHONEWINDOW_H
#define UI_PHONEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PhoneWindow
{
public:

    void setupUi(QWidget *PhoneWindow)
    {
        if (PhoneWindow->objectName().isEmpty())
            PhoneWindow->setObjectName("PhoneWindow");
        PhoneWindow->resize(400, 300);

        retranslateUi(PhoneWindow);

        QMetaObject::connectSlotsByName(PhoneWindow);
    } // setupUi

    void retranslateUi(QWidget *PhoneWindow)
    {
        PhoneWindow->setWindowTitle(QCoreApplication::translate("PhoneWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PhoneWindow: public Ui_PhoneWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHONEWINDOW_H
