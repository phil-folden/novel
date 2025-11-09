#ifndef INITIAL_H
#define INITIAL_H

#include <QNetworkReply>
#include <QWidget>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>

#include "novelbase.h"
#include "select_text.h"

namespace Ui {
class initial;
}

class initial : public QWidget
{
    Q_OBJECT

private:
    void show_novel();

public:
    explicit initial(QWidget *parent = nullptr);
    ~initial();

private:
    QNetworkAccessManager *netmanager;
    Ui::initial *ui;
    int novelid;
};

#endif // INITIAL_H
