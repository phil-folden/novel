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

void Tcp_Server::socket_info(QTcpSocket* clientSocket){
    QByteArray responseData;


    QByteArray info1 = clientSocket->readAll();
    QString info2 = QString::fromUtf8(info1);

    QStringList list1 = info2.split("\r\n");
    QStringList list2 = list1[0].split(" ");
    QStringList list3 = list2[1].split("/");
    if(list2.isEmpty()) return;

    if(list2[1] == "/api/home"){
        //传递给前端小说名字
        responseData = Tcp_Server::transform_name();
    }

    else if(list3.size() == 3){
        responseData = Tcp_Server::transform_title(list3[2].toInt());
    }

    else if(list3.size() == 4){
        //传递给前端小说章节和小说内容
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
