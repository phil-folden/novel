/********************************************************************************
** Form generated from reading UI file 'initial.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIAL_H
#define UI_INITIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_initial
{
public:
    QGridLayout *gridLayout_2;
    QListWidget *novelList;

    void setupUi(QWidget *initial)
    {
        if (initial->objectName().isEmpty())
            initial->setObjectName("initial");
        initial->resize(644, 486);
        gridLayout_2 = new QGridLayout(initial);
        gridLayout_2->setObjectName("gridLayout_2");
        novelList = new QListWidget(initial);
        novelList->setObjectName("novelList");

        gridLayout_2->addWidget(novelList, 0, 0, 1, 1);


        retranslateUi(initial);

        QMetaObject::connectSlotsByName(initial);
    } // setupUi

    void retranslateUi(QWidget *initial)
    {
        initial->setWindowTitle(QCoreApplication::translate("initial", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class initial: public Ui_initial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIAL_H
