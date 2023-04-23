#include "ajoutertache.h"
#include "ui_ajoutertache.h"
#include "mainwindow.h"

ajouterTache::ajouterTache(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterTache)
{
    ui->setupUi(this);
}

ajouterTache::~ajouterTache()
{
    delete ui;
}

void ajouterTache::on_validerajout_clicked()
{
    QString nom = ui->nomtache->text();
    QDate debut = ui->date_debut->date();
    QDate fin = ui->date_fin->date();
    QString etat =ui->etat->currentText();
    Task t(debut, fin, etat, idd, nom, 0, 0, 0, 0);
    qDebug()<< idd;
    qDebug()<< "lol";
    t.ajouter();

}

void ajouterTache::on_validermodif_clicked()
{
    QString nom = ui->nomtache_2->text();
    QDate debut = ui->date_debut_2->date();
    QDate fin = ui->date_fin_2->date();
    QString etat =ui->etat_2->currentText();
    qDebug() << etat;
    t.modifier(debut, fin, etat, idd, nom, cellname, 0, 0, 0, 0);

}

void ajouterTache::on_validermodif_2_clicked()
{
    QSqlQuery qry;
    qry.prepare("select * from task  where ID='"+val+"'");
    int estimate=ui->estimate->text().toInt();
    QString confidence=ui->confidence->currentText();
    int budget = ui->budget->text().toInt();
    int progres = ui->progres->text().toInt();
    qDebug() <<budget;
    qDebug()<< "klgjkqjgkjffffff";

    if (qry.exec())
    { while (qry.next())
       {
           int days= qry.value(1).toDate().daysTo(qry.value(2).toDate());
           int daysSinceStart = qry.value(1).toDate().daysTo(QDate::currentDate());
           double ratio =static_cast<double>(daysSinceStart)/days;
           if(progres/100<ratio){
              QMessageBox::information(nullptr, QObject::tr("Tip!"),
                           QObject::tr("La tache '%1' est en retard."
                                       "Vous pouvez vouloir allouer plus de ressources pour revenir sur la bonne voie").arg(qry.value(5).toString()), QMessageBox::Cancel);
           }
           else if(progres/100>3*ratio){
               QMessageBox::information(nullptr, QObject::tr("Tip!"),
                            QObject::tr("La tache %1 est bien à l'avance."
                                        "Vous pouvez vouloir allouer plus de ressources à d'autre taches").arg(qry.value(5).toString()), QMessageBox::Cancel);
            }
           t.modifier(qry.value(1).toDate(), qry.value(2).toDate(), qry.value(3).toString(), qry.value(4).toInt(), qry.value(5).toString(), qry.value(5).toString(), estimate, confidence, budget, progres);

       }
    }
}
