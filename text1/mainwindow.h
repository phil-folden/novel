#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void loadNightModeState();

    void loadChapterCount();

    void loadSize();

    void loadFont();

private slots:

    void Chapter_1Slot();

    void Chapter_2Slot();

    void Chapter_3Slot();

    void Font_song();

    void Font_weiruan();

    void Size_9();

    void Size_12();

    void Size_15();

    void on_changeDNButton_clicked();

    void apply_day();

    void apply_night();

private:
    Ui::MainWindow *ui;
    QSettings m_settings, ch_settings, font_settings, size_settings;
    int ch_count, size, _font;
    bool isNightMode;
};
#endif // MAINWINDOW_H
