#include "tcp_server.h"
#include "ui_tcp_server.h"
#include "novelbase.h"

QMap<QString, QVariant> Tcp_Server::nameMap;

Tcp_Server::Tcp_Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tcp_Server)
{
    ui->setupUi(this);

    qDebug() << "服务器已打开";

    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection, this, [this](){
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
        if(clientSocket){
            //这个readyread的意思就是服务端已经准备好接受信号
            //换句话说，感知到了客户端发送的请求数据
            connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket](){
                this->socket_info(clientSocket);
            });

            qDebug() << "新客户端连接：" << clientSocket->peerAddress().toString();
        }
        else{
            qDebug() << "客户端连接失败 ";
        }
    });

    if(tcpServer->listen(QHostAddress::Any, 8000)){
        qDebug() << "服务器启动成功";
    }
    else{
        qDebug() << "服务器启动失败";
    }
}

//传递小说名
QByteArray Tcp_Server::transform_name(){
    QSqlDatabase db = NovelBase::getDatabase();
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT novel_id, title
        FROM novel
        )");
    query.exec();
    int i = 1;
    while(query.next()){
        QString novel_id = query.value(0).toString();
        QString title = query.value(1).toString();
        nameMap[novel_id] = title;
        i++;
    }

    QJsonObject data;
    data["code"] = 200;
    data["msg"] = "success";
    QJsonObject content;
    for(int j = 1; j <= i; j++){
        QString k = QString::number(j);
        content[k] = nameMap[k].toString();
    }
    data["content"] = content;
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}

//传递目录
QByteArray Tcp_Server::transform_title(int novel_id){

    QList<QMap<QString,QVariant>> chapters;
    chapters = NovelBase::getChapter(novel_id);

    QJsonObject data;
    data["code"] = 200;
    data["msg"] = "success";
    QJsonArray contentArray;
    foreach(auto& t, chapters){
        QJsonObject contentobj;
        contentobj["chapter_id"] = t["chapter_id"].toInt();
        contentobj["title"] = t["title"].toString();
        contentArray.append(contentobj);
    }
    data["content"] = contentArray;
    return QJsonDocument(data).toJson(QJsonDocument::Compact);

}

//传递章节
QByteArray Tcp_Server::transform_content(int novel_id, int chapter_id){
    qDebug() <<"后端传递的chapterid" << chapter_id;
    QSqlDatabase db = NovelBase::getDatabase();
    QSqlQuery query(db);

    query.prepare(R"(
        SELECT title, content
        FROM chapter
        WHERE chapter_id = :chapter_id
)");
    query.bindValue(":chapter_id", chapter_id);

    query.exec();
    QJsonObject data;
    data["code"] = 200;
    data["msg"] = "success";
    QJsonObject content;
    query.next();
    content["title"] = query.value(0).toString();
    content["txtcontent"] = query.value(1).toString();

    data["content"] = content;

    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}

//传递查找的内容
QByteArray Tcp_Server::transform_search(int novel_id, QString search_content){
    QSqlDatabase db = NovelBase::getDatabase();
    QSqlQuery query(db);

    query.prepare(R"(
        SELECT chapter_id, title
        FROM chapter
        WHERE title LIKE '%' || :search_content || '%'
        AND novel_id = :novel_id;
        )");

    QString decodedSearch = QUrl::fromPercentEncoding(search_content.toUtf8());
    query.bindValue(":novel_id", novel_id);
    query.bindValue(":search_content", decodedSearch);
    query.exec();

    QJsonObject data;

    // if(!query.exec()){
    //     data["code"] = 400;
    //     data["msg"] = "没有相关的内容";
    // }
    // else{
        data["code"] = 200;
        data["msg"] = "success";
    // }
    QJsonArray contentArray;

    while(query.next()){
        QJsonObject contentobj;
        contentobj["chapter_id"] = query.value(0).toInt();
        contentobj["title"] = query.value(1).toString();
        contentArray.append(contentobj);
    }

    data["content"] = contentArray;
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}

//传递reader_id
QByteArray Tcp_Server::transform_reader(QString account, QString password){
    int reader_id = NovelBase::checkAccount(account, password);

    QJsonObject data;
    if(reader_id != -1){
        data["code"] = 200;
        data["msg"] = "success";
        data["reader_id"] = reader_id;
    }
    else{
        data["code"] = 400;
        data["msg"] = "fail";
        data["reader_id"] = -1;
    }
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}


QByteArray Tcp_Server::loadnewReader(const QString& account, const QString& password){
    int i = NovelBase::addReader(account, password);

    QJsonObject data;

    if(i == -2){
        data["code"] = 400;
        data["msg"] = "fail";
        qDebug() << "loadnewReader失败";
    }

    else if(i == -1){
        data["code"] = 401;
        data["msg"] = "fail";
        qDebug() << "有相同的账号";
    }
    else{
        data["code"] = 200;
        data["msg"] = "success";
        qDebug() << "注册账号成功";
    }
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}


void Tcp_Server::change_collect(int reader_id, int novel_id, QString tof){
    qDebug() << "change_collect进行了";
    if(tof == "true"){
        NovelBase::addCollect(reader_id, novel_id);
    }
    else{
        NovelBase::deleteCollect(reader_id, novel_id);
    }

//     QSqlDatabase db = NovelBase::getDatabase();
//     QSqlQuery query(db);
//     query.prepare(R"(
//         SELECT reader_id, novel_id
//         FROM collect
// )");
//     query.exec();

}


QByteArray Tcp_Server::transform_collect(int reader_id){
    QSqlDatabase db = NovelBase::getDatabase();
    QSqlQuery query(db);

    query.prepare(R"(
        SELECT c.novel_id, n.title
        FROM collect c
        JOIN novel n ON c.novel_id = n.novel_id
        WHERE reader_id = :reader_id
)");
    query.bindValue(":reader_id", reader_id);

    QJsonObject data;

    if(!query.exec()){
        qDebug() << "transform_collect失败";
        data["code"] = "400";
        data["msg"] = "false";
    }
    else{
        data["code"] = 200;
        data["msg"] = "success";
    }
    \
    QJsonArray content;

    qDebug() << "query.size = " << query.size();
    while(query.next()){
        qDebug() << "transform_collect" << query.value(0).toInt() << query.value(1).toString();
        QJsonObject content1;
        content1["novel_id"] = query.value(0).toInt();
        content1["title"] = query.value(1).toString();

        content.append(content1);
    }
    data["content"] = content;
    return QJsonDocument(data).toJson(QJsonDocument::Compact);
}


void Tcp_Server::socket_info(QTcpSocket* clientSocket){
    QByteArray responseData;

    QByteArray info1 = clientSocket->readAll();
    QString info2 = QString::fromUtf8(info1);

    QStringList list1 = info2.split("\r\n");
    QStringList list4 = info2.split("\r\n\r\n");
    QStringList list2 = list1[0].split(" ");
    QStringList list3 = list2[1].split("/");
    if(list2.isEmpty()) return;

    //传递给前端小说名字
    if(list2[1] == "/api/home"){
        qDebug() << "服务器传输了小说名";
        responseData = Tcp_Server::transform_name();
    }

    //查询登录是否正确
    else if(list2[1] == "/api/login"){
        QString acc;
        QString psd;
        int i = 0;
        //传递reader_id
        QString body = list4[1];
        QMap<QString, QVariant> data;
        for(QString pair : body.split("&")){
            QStringList a = pair.split("=");

            if (a.size() != 2) {
                qDebug() << "参数格式错误：" << pair; // 打印错误参数，方便排查
                continue; // 跳过格式错误的参数，不影响其他参数解析
            }

            if(i == 0){
                acc = QUrl::fromPercentEncoding(a[1].toUtf8());
                i++;
            }

            else if (i == 1){
                psd = QUrl::fromPercentEncoding(a[1].toUtf8());
            }
        }
        responseData = Tcp_Server::transform_reader(acc, psd);
    }

    //向novelbase里加入新的账号密码
    else if(list2[1] == "/api/register"){
        QString acc;
        QString psd;
        int i = 0;
        //传递reader_id
        QString body = list4[1];
        for(QString pair : body.split("&")){
            QStringList a = pair.split("=");
            if(i == 0){
                acc = QUrl::fromPercentEncoding(a[1].toUtf8());
                i++;
            }

            else if (i == 1){
                psd = QUrl::fromPercentEncoding(a[1].toUtf8());
            }
        }
        responseData = Tcp_Server::loadnewReader(acc, psd);
    }   


    //在select_text中的查询功能
    else if(list3[2] == "search"){
        qDebug() << "服务端传输了search";
        responseData = Tcp_Server::transform_search(list3[3].toInt(), list3[4]);
    }


    //当点击收藏或取消收藏进行的操作
    else if(list3[2] == "collect" && list3.size() == 6){
        Tcp_Server::change_collect(list3[3].toInt(), list3[4].toInt(), list3[5]);
    }


    //当点击我的收藏时传递收藏的作品
    else if(list3[2] == "mycollect"){
        qDebug() << "mycollect中reader_id=" << list3[3].toInt();
        responseData = Tcp_Server::transform_collect(list3[3].toInt());
    }

    //传输目录
    else if(list3.size() == 3){
        qDebug() << "服务器传输了目录";
        responseData = Tcp_Server::transform_title(list3[2].toInt());
    }

    //传递给前端小说章节和小说内容
    else if(list3.size() == 4){
        responseData = Tcp_Server::transform_content(list3[2].toInt(),list3[3].toInt());
    }


    QByteArray httpResponse = QString(
                                  "HTTP/1.1 200 OK\r\n"
                                  "Content-Type: application/json; charset=utf-8\r\n"
                                  "Content-Length: %1\r\n"
                                  "Connection: Close\r\n" // 短连接，处理完就断开
                                  "\r\n" // 空行分隔头和体
                                  ).arg(responseData.size()).toUtf8() + responseData;

    clientSocket->write(httpResponse);
    clientSocket->flush();
}


Tcp_Server::~Tcp_Server()
{
    delete ui;
}


//我们来简单回顾一下:
//首先服务器创建用TcpServer, 还需要创建一个TcpSocket作为客户端。
//创建完TcpServer,我们需要手动定义一个端口，然后持续监听这个端口
//当客户端第一次请求连接的时候，TcpServer会受到newConnect的信号，收到信号之后，我们可以让服务器与客户端建立长久的联系
//当客户端给服务端发信号的时候，TcpSocket会发出ReadyRead的信号，信息是二进制的，在TcpSocket里，可以创建一个二进制变量存储信息，readall
//客户端传来的是二进制形式的信息，把二进制形式的转化为QString字符串形式的
//传来的url信息的差别在于第一行，我们把第一行信息分开处理
//比如是home传来的信息，那我们需要用数据库把所有的小说名和id给前端
//服务端信息的传递我用的是JSON形式，JSON也是键值对存储的
//最后只需要把我们的信息包装成http协议的包给客户端就可以了
