#include "task.h"
#include <QString>
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QString>
#include <QFile>
#include <QTextDocument>
#include<QTextStream>
#include<QIODevice>
#include<QDate>
#include <QSystemTrayIcon>
#include <QDebug>

Task::Task()
{

}
Task::Task(QDate start,QDate end,QString state, int id_projet, QString nom, int estimate, QString confidence, int budget, int progres)
{

   this->start=start;
   this->end=end;
   this->state=state;
   this->id_projet=id_projet;
   this->nom=nom;
   this->estimate=estimate;
   this->confidence=confidence;
   this->budget=budget;
   this->progres=progres;

}
bool Task::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO task (START_DATE,END_DATE,STATE, ID_PROJET, NAME, ESTIMATE, CONFIDENCE, BUDGET)"
                          "VALUES (:start, :end, :state, :id_projet, :nom, :estimate, :confidence, :budget)");
    //query.bindValue(":id",2);
    query.bindValue(":start",start);
    query.bindValue(":end",end);
    query.bindValue(":state",state);
    query.bindValue(":id_projet",id_projet);
    query.bindValue(":nom",nom);
    query.bindValue(":estimate",estimate);
    query.bindValue(":confidence",confidence);
    query.bindValue(":budget",budget);
    return query.exec();

}
bool Task ::modifier(QDate debut, QDate fin, QString etat, int idd, QString nom, QString cellname, int estimate, QString confidence, int budget, int progres)
{

        QSqlQuery qry;
        qry.prepare("UPDATE task set START_DATE=(?),END_DATE=(?),STATE=(?), NAME=(?), ESTIMATE=(?), CONFIDENCE=(?), BUDGET=(?), PROGRES=(?) where ID_PROJET=(?) AND NAME=(?) ");
        qry.addBindValue(debut);
        qry.addBindValue(fin);
        qry.addBindValue(etat);
        qry.addBindValue(nom);
        qry.addBindValue(estimate);
        qry.addBindValue(confidence);
        qry.addBindValue(budget);
        qry.addBindValue(progres);
        qry.addBindValue(idd);
        qry.addBindValue(cellname);
        qDebug() << "hellooo";
        return qry.exec();
}
QSqlQueryModel *Task::afficher(int idd)
{
 QSqlQuery qry;
 qry.prepare("SELECT ID, NAME, START_DATE, END_DATE, STATE, ESTIMATE, CONFIDENCE, BUDGET, PROGRES FROM task where ID_PROJET=(?) ");
 qry.addBindValue(idd);
 qry.exec();
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery(qry);
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom tache"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("Date début"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date fin"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("Etat"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("Estimation (TND)"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("Confiance"));
 model->setHeaderData(7, Qt::Horizontal,QObject::tr("Budget (TND)"));
 model->setHeaderData(8, Qt::Horizontal,QObject::tr("Progrès (%)"));
 return model;
}

int Task::totalbudget(int id)
{
    QSqlQuery qry;
    qry.prepare("select BUDGET from task  where ID_PROJET=(?)");
    qry.addBindValue(id);
    int total=0;
    if (qry.exec())
    { while (qry.next())
       {

           total+=qry.value(0).toInt();

       }
    }
    qDebug()<<total, "this is the total";
    return total;
}
