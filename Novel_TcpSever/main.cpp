#include "widget.h"
#include "novelbase.h"
#include "tcp_server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    NovelBase::importNovel("蛊真人_蛊真人");
    NovelBase::importNovel("义妹生活");
    NovelBase::importNovel("诡秘之主");

    Tcp_Server b;
    b.show();

    return a.exec();
}
