#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>   // 用于文件操作
#include <QTextStream>  // 用于文本流读取
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_settings("Mycompany", "Txtreader"),
    ch_settings("Mycompany", "chapter_count"),
    size_settings("Mycompany", "size"),
    font_settings("Mycompany", "_font")
{
    ui->setupUi(this);
    connect(ui->chapter_1, &QAction::triggered, this, &MainWindow::Chapter_1Slot);
    connect(ui->chapter_2, &QAction::triggered, this, &MainWindow::Chapter_2Slot);
    connect(ui->chapter_3, &QAction::triggered, this, &MainWindow::Chapter_3Slot);
    connect(ui->song, &QAction::triggered, this, &MainWindow::Font_song);
    connect(ui->weiruan, &QAction::triggered, this, &MainWindow::Font_weiruan);
    connect(ui->size_9, &QAction::triggered, this, &MainWindow::Size_9);
    connect(ui->size_12, &QAction::triggered, this, &MainWindow::Size_12);
    connect(ui->size_15, &QAction::triggered, this, &MainWindow::Size_15);
    loadNightModeState();
    loadChapterCount();
    loadSize();
    loadFont();
}

void MainWindow::Chapter_1Slot(){
    ui->textEdit->clear();
    this->setWindowTitle("第一章");
    QString filepath = "chapter_1.txt";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "错误", "无法打开文件：" + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    ui->textEdit->setText(content);
    file.close();
    ch_count = 1;
    ch_settings.setValue("ch_count", ch_count);
}

void MainWindow::Chapter_2Slot(){
    ui->textEdit->clear();
    this->setWindowTitle("第二章");
    QString filepath("Chapter_2.txt");
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "错误", "无法打开文件：" + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    ui->textEdit->setText(content);
    file.close();
    ch_count = 2;
    ch_settings.setValue("ch_count", ch_count);
}

void MainWindow::Chapter_3Slot(){
    ui->textEdit->clear();
    this->setWindowTitle("第三章");
    QString filepath("Chapter_3.txt");
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "错误", "无法打开文件：" + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    ui->textEdit->setText(content);
    file.close();
    ch_count = 3;
    ch_settings.setValue("ch_count", ch_count);
}

void MainWindow::Font_song(){
    QFont font = ui->textEdit->font();
    font.setFamily("宋体");
    ui->textEdit->setFont(font);
    _font = 1;
    font_settings.setValue("_font", _font);
}

void MainWindow::Font_weiruan(){
    QFont font = ui->textEdit->font();
    font.setFamily("微软雅黑");
    ui->textEdit->setFont(font);
    _font = 2;
    font_settings.setValue("_font", _font);
}

void MainWindow::Size_9(){
    QFont font = ui->textEdit->font();
    font.setPointSize(9);
    ui->textEdit->setFont(font);
    size = 9;
    size_settings.setValue("size", size);
}

void MainWindow::Size_12(){
    QFont font = ui->textEdit->font();
    font.setPointSize(12);
    ui->textEdit->setFont(font);
    size = 12;
    size_settings.setValue("size", size);
}

void MainWindow::Size_15(){
    QFont font = ui->textEdit->font();
    font.setPointSize(15);
    ui->textEdit->setFont(font);
    size = 15;
    size_settings.setValue("size", size);
}

void MainWindow::loadChapterCount(){
    ch_count = ch_settings.value("ch_count", 0).toInt();

    switch(ch_count){
    case 0:
        break;

    case 1:
        Chapter_1Slot();
        break;

    case 2:
        Chapter_2Slot();
        break;

    case 3:
        Chapter_3Slot();
        break;
    }

}

void MainWindow::loadNightModeState(){
    isNightMode = m_settings.value("isNightMode" ,false).toBool();

    if(isNightMode){
        apply_day();
    }
    else{
        apply_night();
    }
}

void MainWindow::loadSize(){
    size = size_settings.value("size", 12).toInt();

    switch(size){
    case 9:
        Size_9();
        break;

    case 12:
        Size_12();
        break;

    case 15:
        Size_15();
        break;
    }
}

void MainWindow::loadFont(){
    _font = font_settings.value("_font", 1).toInt();
    switch (_font) {
    case 1:
        Font_song();
        break;
    case 2:
        Font_weiruan();
        break;
    }
}

void MainWindow::on_changeDNButton_clicked()
{
    isNightMode = !isNightMode;
    if(isNightMode){
        apply_day();
    }
    else{
        apply_night();
    }
    m_settings.setValue("isNightMode", isNightMode);
}

void MainWindow::apply_day(){
    ui->textEdit->setStyleSheet(
        "background-color: #FFFFFF;" // 背景色（白色）
        "color: #000000;"            // 文字色（黑色）
        );
}

void MainWindow::apply_night(){
    ui->textEdit->setStyleSheet(
        "background-color: #2D2D2D;" // 背景色（深灰，不刺眼）
        "color: #E0E0E0;"           // 文字色（浅灰）
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

