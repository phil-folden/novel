#include "mainwindow.h"
#include "select_text.h"
#include "initial.h"
#include "novelbase.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NovelBase::importNovel("蛊真人_蛊真人");
    NovelBase::importNovel("义妹生活");
    NovelBase::importNovel("诡秘之主");

    initial c;
    c.show();
    return a.exec();
}
