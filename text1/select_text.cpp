#include "select_text.h"
#include "ui_select_text.h"
#include "initial.h"

select_text::select_text(int novelid, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::select_layout)
    ,night_settings("Mycompany", "night")
    ,select_settings("Mycompany", "is_select")
    ,size_settings("Mycompany", "size")
    ,font_settings("Mycompany", "font")
    ,reading_settings("Mycompany", "readingProcess")
    ,chapterlist(nullptr)
    ,id(novelid)
    ,chapterid(1)
{

    netmanager = new QNetworkAccessManager(this);

    ui->setupUi(this);
    setWindowTitle("倪鑫牌小说阅读器");
    chapterlist = new QListWidget(this);
    sizelist = new QListWidget(this);
    fontlist = new QListWidget(this);
    dornlist = new QListWidget(this);
    sizelist->setVisible(false);
    chapterlist->setVisible(false);
    fontlist->setVisible(false);
    dornlist->setVisible(false);
    loadchapter(novelid);
    connect(chapterlist, &QListWidget::itemClicked, this, [=](QListWidgetItem *item){
        chapterid = item->data(Qt::UserRole).toInt();
        showContent();
        saveProcess(id, chapterid);
    });

    connect(sizelist, &QListWidget::itemClicked, this, [=](QListWidgetItem *item){
        ch_size = item->data(Qt::UserRole + 1).toInt();
        QFont font = ui->textEdit->font();
        font.setPointSize(ch_size);
        ui->textEdit->setFont(font);
        size_settings.setValue("size", ch_size);
    });

    connect(fontlist, &QListWidget::itemClicked, this, [=](QListWidgetItem *item){
        font_size = item->data(Qt::UserRole + 2).toString();
        QFont font = ui->textEdit->font();
        font.setFamily(font_size);
        ui->textEdit->setFont(font);
        font_settings.setValue("font", font_size);
    });

    loadProcess(id);

    loadSize();
    loadFont();
    loadDay();
}


void select_text::showContent(){
    // QSqlDatabase db;
    // db = NovelBase::getDatabase();
    // QSqlQuery query(db);
    // query.prepare(R"(
    //             SELECT content
    //             FROM chapter
    //             WHERE chapter_id = :chapterid
    //         )");
    // query.bindValue(":chapterid", chapterid);

    // if(!query.exec()){
    //     qDebug() <<"select_text查询章节内容失败";
    //     return;
    // }

    // QString content;

    // if (query.next()) {
    //     content = query.value("content").toString();
    // } else {
    //     content = "未找到章节内容"; // 或空字符串
    //     qDebug() << "未找到ID为" << chapterid << "的章节";
    // }

    QUrl url("http://127.0.0.1:8000/api/" + QString::number(id) + "/" + QString::number(chapterid));
    QNetworkRequest request(url);
    QNetworkReply *reply = netmanager->get(request);


    connect(reply, &QNetworkReply::finished, this, [reply, this]{
        QByteArray wdf = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(wdf);
        QJsonObject root = doc.object();

        QJsonObject data = root["content"].toObject();
        QString content = data["txtcontent"].toString();

        saveProcess(id, chapterid);

        ui->textEdit->setText(content);

        reply->deleteLater();
    });


}

void select_text::saveProcess(int novel_id, int reading_process){
    //结构为process_1 12   process_2 20
    reading_settings.setValue(QString("process_%1").arg(novel_id), reading_process);
}

void select_text::loadProcess(int novel_id){
    chapterid = reading_settings.value(QString("process_%1").arg(novel_id), 1).toInt();
    showContent();
    return;
}

void select_text::loadSize(){
    ch_size = size_settings.value("size", 9).toInt();
    QFont font = ui->textEdit->font();
    font.setPointSize(ch_size);
    ui->textEdit->setFont(font);
}

void select_text::loadFont(){
    font_size = font_settings.value("font", "宋体").toString();
    QFont font = ui->textEdit->font();
    font.setFamily(font_size);
    ui->textEdit->setFont(font);
}

void select_text::loadDay(){
    night_settings.value("is_night", false);
    if(!is_night){
        ui->textEdit->setStyleSheet(
            "background-color: #FFFFFF;" // 背景色（白色）
            "color: #000000;"            // 文字色（黑色）
            );
    }
    else{
        ui->textEdit->setStyleSheet(
            "background-color: #2D2D2D;" // 背景色（深灰，不刺眼）
            "color: #E0E0E0;"           // 文字色（浅灰）
            );
    }
}

void select_text::loadchapter(int novel_id){
    chapterlist->clear();

    QUrl listurl("http://127.0.0.1:8000/api/" + QString::number(novel_id));
    QNetworkRequest request(listurl);
    QNetworkReply *reply = netmanager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]{
        qDebug() << "章节目录显示传送到了";
        QByteArray info = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(info);
        QJsonObject rootobj = doc.object();

        int code = rootobj["code"].toInt();
        qDebug() << "章节目录的code" <<code;

        // QJsonObject data = rootobj["content"].toObject();
        QJsonArray data = rootobj["content"].toArray();


        for(const QJsonValue& value : data){
            int chapter_id = value["chapter_id"].toInt();
            QString title = value["title"].toString();
            QListWidgetItem *item = new QListWidgetItem(
                QString("%1").arg(title)
                );
            item->setData(Qt::UserRole, chapter_id);
            chapterlist->addItem(item);

        }
        // for(auto i = data.begin(); i != data.end(); ++i){
        //     int chapter_id = i.key().toInt();
        //     QString title = i.value().toString();

        // QListWidgetItem *item = new QListWidgetItem(
        //     QString("%1").arg(title)
        //     );
        // item->setData(Qt::UserRole, chapter_id);
        // chapterlist->addItem(item);
        // }

    });


    // QList<QMap<QString,QVariant>> chapters;
    // chapters = NovelBase::getChapter(novel_id);

    //foreach:chapters是个QList的列表，每次会给t一个QMap，比如一开始给的是QList[0]的，第二次QList[1]
    // foreach(const auto &t, chapters){
    //     QString title2 = t["title"].toString();
    //     int chapterid = t["chapter_id"].toInt();
    //     QListWidgetItem *item = new QListWidgetItem(
    //         QString("%1").arg(title2)
    //         );
    //      item->setData(Qt::UserRole, chapterid);
    //      chapterlist->addItem(item);

    // }
}

void select_text::on_selectButton_clicked()
{
    // is_select = select_settings.value("is_select", false).toBool();
    is_select = !is_select;
    if(is_select){
        ui->gridLayout->addWidget(chapterlist);
        //设置属性
        chapterlist->setStyleSheet(
            "QListWidget {"
            "    background-color: #000000;"
            "    border: 2px solid #cccccc;"
            "    border-radius: 5px;"
            "    font-size: 14px;"
            "}"
            "QListWidget::item {"
            "    padding: 8px;"
            "    border-bottom: 1px solid #eeeeee;"
            "}"
            "QListWidget::item:hover {"
            "    background-color: #e6f3ff;"
            "}"
            "QListWidget::item:selected {"
            "    background-color: #0078d4;"
            "    color: white;"
            "}"
            );
        showChapterlist();
    }

    else{
        hideChapterlist();
    }
}

void select_text::showChapterlist(){

    chapterlist->setVisible(true);
    ui->gridLayout->removeWidget(ui->textEdit);
    ui->gridLayout->addWidget(ui->textEdit, 1, 0);

    if(is_size && is_font){
        ui->gridLayout->removeWidget(sizelist);
        ui->gridLayout->removeWidget(fontlist);
        ui->gridLayout->addWidget(chapterlist, 1, 3, 5, 2);
        ui->gridLayout->addWidget(sizelist, 1, 1, 5, 1);
        ui->gridLayout->addWidget(fontlist, 1, 2, 5, 1);
    }

    else if(!is_size && is_font){
        ui->gridLayout->removeWidget(fontlist);
        ui->gridLayout->addWidget(fontlist, 1, 1, 5, 1);
        ui->gridLayout->addWidget(chapterlist, 1, 2, 5, 3);
    }

    else if(is_size && !is_font){
        ui->gridLayout->removeWidget(sizelist);
        ui->gridLayout->addWidget(sizelist, 1, 1, 5 ,1);
        ui->gridLayout->addWidget(chapterlist, 1, 1, 5, 3);
    }

    else{
        ui->gridLayout->addWidget(chapterlist, 1, 1, 5, 4);
    }
    chapterlist->setVisible(true);
    ui->selectButton->setText("隐藏章节");

    ui->gridLayout->setColumnStretch(0, 100);  // textEdit占6份
    ui->gridLayout->setRowStretch(1, 1);  // 第1行
    ui->gridLayout->setRowStretch(2, 1);  // 第2行

}

void select_text::hideChapterlist(){
    ui->gridLayout->removeWidget(chapterlist);
    chapterlist->setVisible(false);
    ui->selectButton->setText("选择章节");

    ui->gridLayout->removeWidget(ui->textEdit);
    ui->gridLayout->addWidget(ui->textEdit, 1, 0);

    if(is_size && is_font){
        ui->gridLayout->removeWidget(sizelist);
        ui->gridLayout->removeWidget(fontlist);
        ui->gridLayout->addWidget(sizelist, 1, 1, 5, 2);
        ui->gridLayout->addWidget(fontlist, 1, 3, 5, 2);
    }

    else if(!is_size && is_font){
        ui->gridLayout->removeWidget(fontlist);
        ui->gridLayout->addWidget(fontlist, 1, 1, 5, 4);
    }

    else if(is_size && !is_font){
        ui->gridLayout->removeWidget(sizelist);
        ui->gridLayout->addWidget(sizelist, 1 ,1, 5, 4);
    }

    else{
        ui->gridLayout->addWidget(ui->textEdit, 1, 0, 1, 5);
    }

}

void select_text::on_sizeButton_clicked()
{
    //第一步：把要记录的东西记入到item并显示，同时在connect的时候能够点击并且有相应的变化
    //第二步：修改显示在item上面的字体，背景的颜色
    //第三步：把展开的列表加入到栅格布局中（gridlayout)，并且调整布局
    is_size = !is_size;
    if (is_size) {
        sizelist->clear();

        for(int i = 8; i <= 30; i++){
            QListWidgetItem *item = new QListWidgetItem(
                QString("%1").arg(i)
                );
            item->setData(Qt::UserRole+1, i);
            sizelist->addItem(item);
        }

        sizelist->setStyleSheet(
            "QListWidget {"
            "    background-color: #000000;"
            "    border: 2px solid #cccccc;"
            "    border-radius: 5px;"
            "    font-size: 14px;"
            "}"
            "QListWidget::item {"
            "    padding: 8px;"
            "    border-bottom: 1px solid #eeeeee;"
            "}"
            "QListWidget::item:hover {"
            "    background-color: #e6f3ff;"
            "}"
            "QListWidget::item:selected {"
            "    background-color: #0078d4;"
            "    color: white;"
            "}"
            );


        ui->gridLayout->removeWidget(ui->textEdit);
        ui->gridLayout->addWidget(ui->textEdit, 1, 0);
        if(is_select && is_font){
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 1);
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->removeWidget(fontlist);
            ui->gridLayout->addWidget(chapterlist, 1, 3, 5, 2);
            ui->gridLayout->addWidget(fontlist, 1, 2, 5 ,1);
        }

        else if(!is_select && is_font){
            ui->gridLayout->removeWidget(fontlist);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 2);
            ui->gridLayout->addWidget(fontlist, 1, 3, 5, 2);
        }

        else if(is_select && !is_font){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 1);
            ui->gridLayout->addWidget(chapterlist, 1, 2, 5, 3);
        }

        else{
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 4);
        }

        ui->gridLayout->setColumnStretch(0, 100);
        sizelist->setVisible(true);
    }

    else{
        ui->gridLayout->removeWidget(sizelist);
        sizelist->setVisible(false);

        if(is_select && is_font){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->removeWidget(fontlist);
            ui->gridLayout->addWidget(fontlist, 1, 1, 5, 1);
            ui->gridLayout->addWidget(chapterlist, 1, 2, 5, 3);
        }

        else if(!is_select && is_font){
            ui->gridLayout->removeWidget(fontlist);
            ui->gridLayout->addWidget(fontlist, 1, 1, 5, 4);
        }

        else if(is_select && !is_font){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->addWidget(chapterlist, 1, 1, 5, 4);
        }

        else{
            ui->gridLayout->addWidget(ui->textEdit, 1, 0, 1, 5);
        }

    }
}

void select_text::on_fontButton_clicked()
{
    is_font = !is_font;
    if(is_font){
        fontlist->clear();

        QListWidgetItem *item= new QListWidgetItem(
            QString("宋体")
            );
        item->setData(Qt::UserRole + 2, "宋体");
        fontlist->addItem(item);

        QListWidgetItem *item1= new QListWidgetItem(
            QString("微软雅黑")
            );
        item1->setData(Qt::UserRole + 2, "微软雅黑");
        fontlist->addItem(item1);

        fontlist->setStyleSheet(
            "QListWidget {"
            "    background-color: #000000;"
            "    border: 2px solid #cccccc;"
            "    border-radius: 5px;"
            "    font-size: 14px;"
            "}"
            "QListWidget::item {"
            "    padding: 8px;"
            "    border-bottom: 1px solid #eeeeee;"
            "}"
            "QListWidget::item:hover {"
            "    background-color: #e6f3ff;"
            "}"
            "QListWidget::item:selected {"
            "    background-color: #0078d4;"
            "    color: white;"
            "}"
            );

        ui->gridLayout->removeWidget(ui->textEdit);
        ui->gridLayout->addWidget(ui->textEdit, 1, 0);
        if(!is_select && !is_size){
            ui->gridLayout->addWidget(fontlist, 1, 1, 5, 4);
        }
        else if(is_select && !is_size){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->addWidget(fontlist, 1, 1, 5, 1);
            ui->gridLayout->addWidget(chapterlist, 1, 2, 5, 3);
        }
        else if(!is_select && is_size){
            ui->gridLayout->removeWidget(sizelist);
            ui->gridLayout->addWidget(fontlist, 1, 3, 5, 2);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 2);
        }
        else{
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->removeWidget(sizelist);
            ui->gridLayout->addWidget(fontlist, 1, 2, 5, 1);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 1);
            ui->gridLayout->addWidget(chapterlist, 1, 3, 5, 2);
        }
        fontlist->setVisible(true);
    }
    else{
        ui->gridLayout->removeWidget(fontlist);
        fontlist->setVisible(false);
        ui->gridLayout->removeWidget(ui->textEdit);
        ui->gridLayout->addWidget(ui->textEdit, 1, 0);
        if(is_select && !is_size){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->addWidget(chapterlist, 1, 1, 5, 4);
        }
        else if(!is_select && is_size){
            ui->gridLayout->removeWidget(sizelist);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 4);
        }
        else if(is_select && is_size){
            ui->gridLayout->removeWidget(chapterlist);
            ui->gridLayout->addWidget(chapterlist, 1, 2, 5, 3);
            ui->gridLayout->removeWidget(sizelist);
            ui->gridLayout->addWidget(sizelist, 1, 1, 5, 1);
        }
        else{
            ui->gridLayout->removeWidget(ui->textEdit);
            ui->gridLayout->addWidget(ui->textEdit, 1, 0, 1, 5);
        }
    }
}

select_text::~select_text()
{
    delete ui;
}

void select_text::on_lastButton_clicked()
{
    chapterid--;
    showContent();
    saveProcess(id, chapterid);
}

void select_text::on_nextButton_clicked()
{
    chapterid++;
    showContent();
    saveProcess(id, chapterid);
}

void select_text::on_nightButton_clicked()
{
    is_night = !is_night;
    night_settings.setValue("is_night", is_night);
    loadDay();
}

void select_text::on_backButton_clicked()
{
    this->hide();
    initial* d = new initial();
    d->show();
}

