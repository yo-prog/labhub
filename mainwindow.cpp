#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projet.h"
#include <QMessageBox>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //input__control
        ui->lineEdit_periode->setValidator(new QIntValidator(0,99,this));
        ui->lineEdit_id->setValidator(new QIntValidator(0,999999,this));
        ui->lineEdit_periode_2->setValidator(new QIntValidator(0,99,this));
        ui->lineEdit_id2->setValidator(new QIntValidator(0,999999,this));
        QRegExp rx("[a-zA-Z]+");
        QValidator *validator = new
                QRegExpValidator (rx,this); //valider
        ui->lineEdit_nom->setValidator(validator);
        ui->lineEdit_theme->setValidator(validator);
        ui->lineEdit_nom_2->setValidator(validator);
        ui->lineEdit_theme_2->setValidator(validator);
        ui->afficher_projet->setModel(p.afficher());
        //c.createconnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_validerajout_clicked()
{
    QString nom =ui->lineEdit_nom->text();
    QString theme =ui->lineEdit_theme->text();
    int periode=ui->lineEdit_periode->text().toInt();
    projet p(nom,theme,periode);
    bool test=p.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajoute \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->lineEdit_nom->clear();
        ui->lineEdit_theme->clear();
        ui->lineEdit_periode->clear();
        ui->afficher_projet->setModel(p.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);

}

void MainWindow::on_afficher_projet_activated(const QModelIndex &index)
{

    QString val=ui->afficher_projet->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from projet  where ID='"+val+"' or NOM='"+val+"' or THEME='"+val+"' or PERIODE='"+val+"'");

    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->lineEdit_id->setText(qry.value(0).toString()); //pour modifier
            ui->lineEdit_nom_2->setText(qry.value(1).toString());
            ui->lineEdit_theme_2->setText(qry.value(2).toString());
            ui->lineEdit_periode_2->setText(qry.value(3).toString());
            //
            //delete
            //id
            ui->lineEdit_id2->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}
void MainWindow::on_validermodif_clicked()
{
    int id =ui->lineEdit_id->text().toUInt();
        QString nom =ui->lineEdit_nom_2->text();
        QString theme =ui->lineEdit_theme_2->text();
        int periode =ui->lineEdit_periode_2->text().toInt();
        bool test=p.modifier_projet(id ,nom,theme,periode);
        if(test){

            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("modifié \n"
                                                 "click to cancel"), QMessageBox::Cancel);
            ui->lineEdit_nom_2->clear();
            ui->lineEdit_theme_2->clear();
            ui->lineEdit_periode_2->clear();
            ui->lineEdit_id->clear();
            ui->afficher_projet->setModel(p.afficher());
        }

    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("modification non effectué"),QMessageBox::Cancel);
}

void MainWindow::on_validersuppression_clicked()
{
    int id =ui->lineEdit_id2->text().toUInt();
    bool test=p.supprimer(id);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Supprimé \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->lineEdit_id2->clear();
        ui->afficher_projet->setModel(p.afficher());
    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("suppression non effectué"),QMessageBox::Cancel);
}
