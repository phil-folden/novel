/********************************************************************************
** Form generated from reading UI file 'select_text.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_TEXT_H
#define UI_SELECT_TEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_layout
{
public:
    QGridLayout *gridLayout;
    QPushButton *selectButton;
    QTextEdit *textEdit;
    QPushButton *fontButton;
    QPushButton *lastButton;
    QPushButton *nightButton;
    QPushButton *sizeButton;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi(QWidget *select_layout)
    {
        if (select_layout->objectName().isEmpty())
            select_layout->setObjectName("select_layout");
        select_layout->resize(640, 535);
        gridLayout = new QGridLayout(select_layout);
        gridLayout->setObjectName("gridLayout");
        selectButton = new QPushButton(select_layout);
        selectButton->setObjectName("selectButton");

        gridLayout->addWidget(selectButton, 0, 4, 1, 1);

        textEdit = new QTextEdit(select_layout);
        textEdit->setObjectName("textEdit");

        gridLayout->addWidget(textEdit, 1, 0, 1, 5);

        fontButton = new QPushButton(select_layout);
        fontButton->setObjectName("fontButton");

        gridLayout->addWidget(fontButton, 0, 2, 1, 1);

        lastButton = new QPushButton(select_layout);
        lastButton->setObjectName("lastButton");

        gridLayout->addWidget(lastButton, 4, 0, 1, 1);

        nightButton = new QPushButton(select_layout);
        nightButton->setObjectName("nightButton");

        gridLayout->addWidget(nightButton, 0, 3, 1, 1);

        sizeButton = new QPushButton(select_layout);
        sizeButton->setObjectName("sizeButton");

        gridLayout->addWidget(sizeButton, 0, 1, 1, 1);

        backButton = new QPushButton(select_layout);
        backButton->setObjectName("backButton");

        gridLayout->addWidget(backButton, 2, 0, 1, 1);

        nextButton = new QPushButton(select_layout);
        nextButton->setObjectName("nextButton");

        gridLayout->addWidget(nextButton, 5, 0, 1, 1);

        selectButton->raise();
        textEdit->raise();
        lastButton->raise();
        backButton->raise();
        sizeButton->raise();
        nightButton->raise();
        fontButton->raise();
        nextButton->raise();

        retranslateUi(select_layout);

        QMetaObject::connectSlotsByName(select_layout);
    } // setupUi

    void retranslateUi(QWidget *select_layout)
    {
        select_layout->setWindowTitle(QCoreApplication::translate("select_layout", "Form", nullptr));
        selectButton->setText(QCoreApplication::translate("select_layout", "\351\200\211\346\213\251\347\253\240\350\212\202", nullptr));
        fontButton->setText(QCoreApplication::translate("select_layout", "\345\255\227\344\275\223", nullptr));
        lastButton->setText(QCoreApplication::translate("select_layout", "\344\270\212\344\270\200\347\253\240", nullptr));
        nightButton->setText(QCoreApplication::translate("select_layout", "\345\244\234\351\227\264\346\250\241\345\274\217", nullptr));
        sizeButton->setText(QCoreApplication::translate("select_layout", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        backButton->setText(QCoreApplication::translate("select_layout", "\350\277\224\345\233\236", nullptr));
        nextButton->setText(QCoreApplication::translate("select_layout", "\344\270\213\344\270\200\347\253\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class select_layout: public Ui_select_layout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_TEXT_H
