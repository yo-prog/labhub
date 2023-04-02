#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projet.h"
#include "connection.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Connection c;

private slots:

    void on_validerajout_clicked();

    void on_afficher_projet_activated(const QModelIndex &index);

    void on_validermodif_clicked();

    void on_validersuppression_clicked();

private:
    Ui::MainWindow *ui;
    projet p;
};
#endif // MAINWINDOW_H
