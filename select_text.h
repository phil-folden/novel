#ifndef SELECT_TEXT_H
#define SELECT_TEXT_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>

#include "novelbase.h"
#include "QSqlQuery"


namespace Ui {
class select_layout;
}

class select_text : public QWidget
{
    Q_OBJECT

private:
    void showContent();

    void saveProcess(int novel_id, int reading_process);

    void loadProcess(int novel_id);

    void loadchapter(int novel_id);

    void hideChapterlist();

    void showChapterlist();

    void loadSize();

    void loadFont();

    void loadDay();

public:
    explicit select_text(int novelid, QWidget *parent = nullptr);
    ~select_text();

private slots:
    void on_selectButton_clicked();

    void on_sizeButton_clicked();

    void on_fontButton_clicked();

    void on_lastButton_clicked();

    void on_nextButton_clicked();

    void on_nightButton_clicked();

    void on_backButton_clicked();

private:
    QSettings font_settings, size_settings, night_settings, select_settings, reading_settings;
    bool is_select = false, is_night = false, is_size = false, is_font = false;
    int ch_size;
    QString font_size;
    int id, chapterid;
    Ui::select_layout *ui;
    QListWidget *fontlist = nullptr;
    QListWidget *sizelist = nullptr;
    QListWidget *dornlist = nullptr;
    QListWidget *chapterlist = nullptr;
};

#endif // SELECT_TEXT_H

