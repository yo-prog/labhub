#ifndef DIALOGSTATS_H
#define DIALOGSTATS_H

#include <QDialog>

namespace Ui {
class dialogstats;
}

class dialogstats : public QDialog
{
    Q_OBJECT

public:
    explicit dialogstats(QWidget *parent = nullptr);
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
    void MakeStat();
    ~dialogstats();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialogstats *ui;
};

#endif // DIALOGSTATS_H
