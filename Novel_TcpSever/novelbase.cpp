#include "novelbase.h"

NovelBase::NovelBase() {
}

QString NovelBase::dbConnectionName = "qt_sql_default_connection";

QSqlDatabase NovelBase::getDatabase(){
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbConnectionName)) {
        db = QSqlDatabase::database(dbConnectionName);
    }

    else{
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./novel_db.sqlite");
    }
    return db;
}

bool NovelBase::initDatabase() {
    //连接数据库
    QSqlDatabase db = getDatabase();

    if(!db.open()){
        qDebug() << "数据库打开失败：" << db.lastError().text();
        return false;
    }

    //创建novel表
    QSqlQuery query;
    QString createNovel = R"(
    CREATE TABLE IF NOT EXISTS
    novel(
        novel_id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT DEFAULT '未知作者'
    )
)";

    if(!query.exec(createNovel)) {
        qDebug() << "创建novel表失败：" << query.lastError().text();
        return false;
    }

    QString createChapter = R"(
    CREATE TABLE IF NOT EXISTS
        chapter(
        chapter_id INTEGER PRIMARY KEY AUTOINCREMENT,
        novel_id INTEGER NOT NULL,
        title TEXT,
        content TEXT NOT NULL,
        FOREIGN KEY (novel_id) REFERENCES novel(novel_id) ON DELETE CASCADE
        )
)";
    if (!query.exec(createChapter)) {
        qDebug() << "创建chapter表失败：" << query.lastError().text();
        return false;
    }

    return true;
}

int NovelBase::insertNovel(const QString &title) {
    if(title.isEmpty()){
        qDebug() << "小说标题不能为空";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO novel (title)"
                  "VALUES(:title)");
    query.bindValue(":title", title);

    if (!query.exec()) {
        qDebug() << "插入小说信息失败：" << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool NovelBase::insertChapter(int novelID, const QString &chaptersDir) {
    QDir dir(chaptersDir);
    if(!dir.exists()){
        qDebug() << "章节文件夹不存在：" << chaptersDir;
        return false;
    }

    //寻找名字格式为数字.什么什么.txt的文件
    QStringList chapterFiles1 = dir.entryList(
        QStringList() <<"*.txt",
        QDir::Files,
        QDir::Name
        );

    // 添加自定义排序
    std::sort(chapterFiles1.begin(), chapterFiles1.end(), [](const QString &a, const QString &b) {
        QRegularExpression regex(R"(^(\d{1,4})\..*\.txt$)");
        QRegularExpressionMatch matchA = regex.match(a);
        QRegularExpressionMatch matchB = regex.match(b);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            int numA = matchA.captured(1).toInt();
            int numB = matchB.captured(1).toInt();
            return numA < numB;
        }
        qDebug() << "无法提取数字，按默认排序:" << a << "vs" << b;
        return a < b;
    });


    QSqlQuery query;
    //提高插入速度
    if (!query.exec("BEGIN TRANSACTION")) {
        qDebug() << "开启事务失败：" << query.lastError().text();
        return false;
    }

    // 遍历章节文件并插入数据库
    for(int i = 0; i < chapterFiles1.size(); i++){
        const QString fileName = chapterFiles1[i];
        const QString filePath = dir.filePath(fileName);
        const int chapterNum = i + 1;

        QString chapterTitle1 = fileName.left(fileName.length() - 4);
        QRegularExpression regex(R"(^\d{1,4}\.(.*)$)");
        QRegularExpressionMatch match = regex.match(chapterTitle1);

        if(match.hasMatch()){
            chapterTitle1 = match.captured(1);
        }
        const QString chapterTitle = chapterTitle1;

        QFile chapterFile(filePath);
        if(!chapterFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "警告：无法打开章节文件，已跳过 -" << filePath;
            continue;
        }
        const QString content = chapterFile.readAll();

        chapterFile.close();
        query.prepare(R"(
            INSERT INTO chapter (novel_id, title, content)
            VALUES(:novel_id, :title, :content)
        )");

        query.bindValue(":novel_id", novelID);
        query.bindValue(":title", chapterTitle);
        query.bindValue(":content", content);

        if (!query.exec()) {
            query.exec("ROLLBACK");  // 插入失败，回滚事务
            qDebug() << "插入第" << chapterNum << "章失败：" << query.lastError().text();
            return false;
        }

    }
    if (!query.exec("COMMIT")) {
        qDebug() << "提交事务失败：" << query.lastError().text();
        return false;
    }

    return true;
}

void NovelBase::importNovel(const QString &novelDir){
    bool is_exit;
    if(!initDatabase()){
        qDebug() << "导入终止：数据库初始化失败";
        return;
    }

    QDir novelDirObj(novelDir);
    const QString novelTitle = novelDirObj.dirName();
    if (novelTitle.isEmpty()) {
        qDebug() << "导入终止：无效的小说文件夹路径";
        return;
    }

    QSqlQuery query;
    //当名字相等时把novel_id从novel表中查询出来
    query.prepare("SELECT novel_id "
                  "FROM novel "
                  "WHERE title = :title");

    query.bindValue(":title", novelTitle);

    int novelID = -1;

    if (query.exec() && query.next()) {
        is_exit = true;
        novelID = query.value(0).toInt();
        qDebug() << "小说已存在";
        qDebug() << "提示：小说《" << novelTitle << "》已导入（ID：" << query.value(0).toInt() << "）";
    }
    else{
        novelID = insertNovel(novelTitle);
        is_exit = false;
        if (novelID == -1) {
            qDebug() << "创建小说失败";
            return;
        }
        qDebug() << "创建新小说，ID：" << novelID;

    }


    QSqlQuery query1;
    if(is_exit == false){
        if(!insertChapter(novelID, novelDir)){
            qDebug() <<"导入章节失败";
            if (novelID != -1) {
                query.prepare("DELETE FROM novel WHERE novel_id = :id");
                query.bindValue(":id", novelID);
                query.exec();
            }
        }
        else{
            qDebug() << "导入成功！小说ID：" << novelID << "，标题：" << novelTitle;
        }
    }
}

QList<QMap<QString, QVariant>> NovelBase::getChapter(int novel_id){
    QList<QMap<QString, QVariant>> chapters;

    QSqlDatabase db;
    db = getDatabase();
    if(!db.open()){
        qDebug() << "数据库打开失败：" << db.lastError().text();
        return chapters;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT chapter_id, title, content
        FROM chapter
        WHERE novel_id = :novel_id
        ORDER BY chapter_id
        )");

    query.bindValue(":novel_id", novel_id);
    if (!query.exec()) {
        qDebug() << "查询章节失败：" << query.lastError().text();
        return chapters;
    }
    while(query.next()){
        QMap<QString, QVariant> chapter;
        chapter["chapter_id"] = query.value("chapter_id").toInt();
        chapter["title"] = query.value("title").toString();
        chapter["content"] = query.value("content").toString();
        chapters.append(chapter);
    }
    return chapters;
}

QList<QMap<QString, QVariant>> NovelBase::getNovel(){
    QList<QMap<QString, QVariant>> Novels;

    QSqlDatabase db = getDatabase();
    if(!db.open()){
        qDebug() << "连接数据库失败";
        return Novels;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT novel_id, title
        FROM novel
        ORDER BY novel_id
)");

    while(query.next()){
        QMap<QString, QVariant> Novel;
        Novel["novel_id"] = query.value("novel_id").toInt();
        Novel["title"] = query.value("title").toString();
        Novels.append(Novel);
    }
    return Novels;
}



//我么现在如果用importNovel创建一个
//通过点击来获取它的novel_id
//然后用getChapter来获取他的内容
//最后把内容显示在ui上

//总体上来说我比如一次性创建三个，需要把他们三个的名称显示在ui上。
//所以我们需要遍历novel数据库，获取到他们的名称，把他们的名称变成按钮，以及每个按钮都有它的novel_id
