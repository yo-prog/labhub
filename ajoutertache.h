#ifndef AJOUTERTACHE_H
#define AJOUTERTACHE_H

#include <QDialog>
#include <QMessageBox>
#include "task.h"

namespace Ui {
class ajouterTache;
}

class ajouterTache : public QDialog
{
    Q_OBJECT
    Task t;

public:
    int idd;
    QString val;
    QString cellname;
    explicit ajouterTache(QWidget *parent = nullptr);
    ~ajouterTache();

private slots:
    void on_validerajout_clicked();

    void on_validermodif_clicked();

    void on_validermodif_2_clicked();

private:
    Ui::ajouterTache *ui;
};

#endif // AJOUTERTACHE_H
