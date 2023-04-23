#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>

#include <QMainWindow>
#include "projet.h"
#include "task.h"
#include "connection.h"
#include <QDate>
#include <QStandardItem>
#include <QListWidgetItem>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QDate jourSelectionne;
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Connection c;

private slots:

    void on_validerajout_clicked();

    void on_afficher_projet_activated(const QModelIndex &index);

    void on_validermodif_clicked();

    void on_validersuppression_clicked();

    const QDate getSelectedMonday();

    void updateJourSelectionne(const QDate & date);

    void updateVueHebdomadaire();

    void on_pushButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_vueHebdomadaire_cellDoubleClicked(int row, int column);

    void on_afficher_budget_activated(const QModelIndex &index);

    void on_afficher_budget_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    projet p;
    Task t;
    QByteArray data; // variable contenant les données reçues
    int ret;
    arduino A; // objet temporaire
    //QSerialPort *serial;

};
#endif // MAINWINDOW_H
