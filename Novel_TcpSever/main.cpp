#include "widget.h"
#include "novelbase.h"
#include "tcp_server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NovelBase::importNovel("justbecause");
    NovelBase::importNovel("义妹生活");
    NovelBase::importNovel("我当备胎女友也没关系");
    NovelBase::importNovel("蛊真人");
    NovelBase::importNovel("诡秘之主");
    NovelBase::importNovel("果然我的青春恋爱喜剧搞错了");
    NovelBase::importNovel("我的妹妹哪有这么可爱");
    Tcp_Server b;
    b.show();

    return a.exec();
}
