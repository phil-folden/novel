#ifndef INITIAL_H
#define INITIAL_H

#include <QWidget>
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
    Ui::initial *ui;
    int novelid;
};

#endif // INITIAL_H
