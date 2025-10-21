/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *chapter_1;
    QAction *chapter_2;
    QAction *song;
    QAction *weiruan;
    QAction *size_9;
    QAction *size_12;
    QAction *size_15;
    QAction *chapter_3;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QPushButton *nextButton;
    QPushButton *lastButton;
    QPushButton *backButton;
    QPushButton *changeDNButton;
    QMenuBar *menubar;
    QMenu *menu1;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 636);
        chapter_1 = new QAction(MainWindow);
        chapter_1->setObjectName("chapter_1");
        chapter_2 = new QAction(MainWindow);
        chapter_2->setObjectName("chapter_2");
        song = new QAction(MainWindow);
        song->setObjectName("song");
        weiruan = new QAction(MainWindow);
        weiruan->setObjectName("weiruan");
        size_9 = new QAction(MainWindow);
        size_9->setObjectName("size_9");
        size_12 = new QAction(MainWindow);
        size_12->setObjectName("size_12");
        size_15 = new QAction(MainWindow);
        size_15->setObjectName("size_15");
        chapter_3 = new QAction(MainWindow);
        chapter_3->setObjectName("chapter_3");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(textEdit, 1, 0, 1, 3);

        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName("nextButton");

        gridLayout->addWidget(nextButton, 5, 2, 1, 1);

        lastButton = new QPushButton(centralwidget);
        lastButton->setObjectName("lastButton");

        gridLayout->addWidget(lastButton, 5, 0, 1, 1);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");

        gridLayout->addWidget(backButton, 5, 1, 1, 1);

        changeDNButton = new QPushButton(centralwidget);
        changeDNButton->setObjectName("changeDNButton");

        gridLayout->addWidget(changeDNButton, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menu1 = new QMenu(menubar);
        menu1->setObjectName("menu1");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu1->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu1->addAction(chapter_1);
        menu1->addAction(chapter_2);
        menu1->addAction(chapter_3);
        menu_2->addAction(song);
        menu_2->addAction(weiruan);
        menu_3->addAction(size_9);
        menu_3->addAction(size_12);
        menu_3->addAction(size_15);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        chapter_1->setText(QCoreApplication::translate("MainWindow", "\347\254\254\344\270\200\347\253\240", nullptr));
        chapter_2->setText(QCoreApplication::translate("MainWindow", "\347\254\254\344\272\214\347\253\240", nullptr));
        song->setText(QCoreApplication::translate("MainWindow", "\345\256\213\344\275\223", nullptr));
        weiruan->setText(QCoreApplication::translate("MainWindow", "\345\276\256\350\275\257\351\233\205\351\273\221", nullptr));
        size_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        size_12->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        size_15->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        chapter_3->setText(QCoreApplication::translate("MainWindow", "\347\254\254\344\270\211\347\253\240", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        nextButton->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\347\253\240", nullptr));
        lastButton->setText(QCoreApplication::translate("MainWindow", "\345\211\215\344\270\200\347\253\240", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        changeDNButton->setText(QCoreApplication::translate("MainWindow", "\345\244\234\351\227\264\346\250\241\345\274\217", nullptr));
        menu1->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\253\240\350\212\202", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
