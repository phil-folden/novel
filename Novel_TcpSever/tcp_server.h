#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>


namespace Ui {
class Tcp_Server;
}

class Tcp_Server : public QWidget
{
    Q_OBJECT

private:
    void socket_info(QTcpSocket *clientSocket);
    static QByteArray transform_name();
    static QByteArray transform_title(int novel_id);
    static QByteArray transform_content(int novel_id, int chapter_id);

public:
    explicit Tcp_Server(QWidget *parent = nullptr);
    ~Tcp_Server();

private:
    Ui::Tcp_Server *ui;
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;
    static QMap<QString,QVariant> nameMap;
};

#endif // TCP_SERVER_H
