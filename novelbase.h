#ifndef NOVELBASE_H
#define NOVELBASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QDebug>
// #include <QTextCodec>
#include <QDebug>
#include <QRegularExpression>
#include <algorithm>

class NovelBase
{

public:

    static QSqlDatabase getDatabase();

    static bool initDatabase();

    static int insertNovel(const QString &title);

    static bool insertChapter(int novelID, const QString &chaptersDir);

    static void importNovel(const QString &novelDir);

    static QList<QMap<QString, QVariant>> getChapter(int novelId);

    static QList<QMap<QString, QVariant>> getNovel();

private:


public:

    static QString dbConnectionName;

    NovelBase();
};

#endif // NOVELBASE_H
