/********************************************************************************
** Form generated from reading UI file 'select_text1.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_TEXT1_H
#define UI_SELECT_TEXT1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_text1
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *select_text1)
    {
        if (select_text1->objectName().isEmpty())
            select_text1->setObjectName("select_text1");
        select_text1->resize(800, 600);
        centralwidget = new QWidget(select_text1);
        centralwidget->setObjectName("centralwidget");
        select_text1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(select_text1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        select_text1->setMenuBar(menubar);
        statusbar = new QStatusBar(select_text1);
        statusbar->setObjectName("statusbar");
        select_text1->setStatusBar(statusbar);

        retranslateUi(select_text1);

        QMetaObject::connectSlotsByName(select_text1);
    } // setupUi

    void retranslateUi(QMainWindow *select_text1)
    {
        select_text1->setWindowTitle(QCoreApplication::translate("select_text1", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class select_text1: public Ui_select_text1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_TEXT1_H
