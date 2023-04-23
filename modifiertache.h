#ifndef MODIFIERTACHE_H
#define MODIFIERTACHE_H

#include <QDialog>

namespace Ui {
class modifiertache;
}

class modifiertache : public QDialog
{
    Q_OBJECT

public:
    explicit modifiertache(QWidget *parent = nullptr);
    ~modifiertache();

private:
    Ui::modifiertache *ui;
};

#endif // MODIFIERTACHE_H
