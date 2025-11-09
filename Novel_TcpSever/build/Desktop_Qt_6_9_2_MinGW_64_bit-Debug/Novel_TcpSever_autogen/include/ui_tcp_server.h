/********************************************************************************
** Form generated from reading UI file 'tcp_server.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_SERVER_H
#define UI_TCP_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tcp_Server
{
public:

    void setupUi(QWidget *Tcp_Server)
    {
        if (Tcp_Server->objectName().isEmpty())
            Tcp_Server->setObjectName("Tcp_Server");
        Tcp_Server->resize(400, 300);

        retranslateUi(Tcp_Server);

        QMetaObject::connectSlotsByName(Tcp_Server);
    } // setupUi

    void retranslateUi(QWidget *Tcp_Server)
    {
        Tcp_Server->setWindowTitle(QCoreApplication::translate("Tcp_Server", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tcp_Server: public Ui_Tcp_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_SERVER_H
