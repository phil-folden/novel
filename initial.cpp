#include "initial.h"
#include "ui_initial.h"

initial::initial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::initial)
{
    ui->setupUi(this);
    show_novel();
    connect(ui->novelList, &QListWidget::itemClicked, this, [=](QListWidgetItem *item){
        novelid = item->data(Qt::UserRole).toInt();
        this->hide();
        select_text* b = new select_text(novelid);
        b->show();
    });
}

void initial::show_novel() {
    QSqlDatabase db;
    db = NovelBase::getDatabase();
    QSqlQuery query(db);
    query.prepare(
        R"(
            SELECT title, novel_id
            FROM novel
            )"
        );
    query.exec();
    while(query.next()){
        QString title = query.value(0).toString();
        QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(title));
        item->setData(Qt::UserRole, query.value(1).toInt());
        ui->novelList->addItem(item);
    }
}



initial::~initial()
{
    delete ui;
}
