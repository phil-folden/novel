#include "initial.h"
#include "ui_initial.h"

initial::initial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::initial)
{
    ui->setupUi(this);
    netmanager = new QNetworkAccessManager(this);
    show_novel();
    connect(ui->novelList, &QListWidget::itemClicked, this, [=](QListWidgetItem *item){
        novelid = item->data(Qt::UserRole).toInt();
        this->hide();
        select_text* b = new select_text(novelid);
        b->show();
    });
}

void initial::show_novel() {
    QTcpSocket testSocket;
    testSocket.connectToHost("127.0.0.1", 8000);

    if (testSocket.waitForConnected(3000)) {
        qDebug() << "服务器连接成功";
        testSocket.close();
    } else {
        qDebug() << "服务器连接失败:" << testSocket.errorString();
        qDebug() << "请确保后端服务器正在运行并监听端口 8000";
        return;
    }
    //连接服务端
    QUrl url("http://127.0.0.1:8000/api/home");
    QNetworkRequest request(url);

    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    QNetworkReply *reply = netmanager->get(request);

    connect(reply, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError error){
        qDebug() << "网络请求错误:" << error << reply->errorString();
    });

    connect(reply, &QNetworkReply::finished, this, [=](){
        qDebug() << "收到数据";
        QByteArray info = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(info);
        QJsonObject rootobj = doc.object();

        int code = rootobj["code"].toInt();
        QString msg = rootobj["msg"].toString();
        QJsonObject content = rootobj["content"].toObject();
        qDebug() << code;

        // for(auto it = rootobj.begin(); it != rootobj.end(); ++it) {
        //     qDebug() << "字段:" << it.key() << "类型:" << it.value().type();
        //     if (it.value().isObject()) {
        //         qDebug() << "  -> 是对象，包含" << it.value().toObject().size() << "个元素";
        //     } else if (it.value().isArray()) {
        //         qDebug() << "  -> 是数组，包含" << it.value().toArray().size() << "个元素";
        //     } else {
        //         qDebug() << "  -> 值:" << it.value();
        //     }
        // }

        // qDebug() << data.begin.value().toString();

        for(auto i = content.begin(); i != content.end(); ++i){
            qDebug() << "2";
            int novel_id = i.key().toInt();
            QString title = i.value().toString();
            qDebug() << novel_id;
            qDebug() << title;
            QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(title));
            item->setData(Qt::UserRole, novel_id);
            ui->novelList->addItem(item);
        };
});




    // QSqlDatabase db;
    // db = NovelBase::getDatabase();
    // QSqlQuery query(db);
    // query.prepare(
    //     R"(
    //         SELECT title, novel_id
    //         FROM novel
    //         )"
    //     );
    // query.exec();
    // while(query.next()){
    //     QString title = query.value(0).toString();
    //     QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(title));
    //     item->setData(Qt::UserRole, query.value(1).toInt());
    //     ui->novelList->addItem(item);
    // }
}



initial::~initial()
{
    delete ui;
}
