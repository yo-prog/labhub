#ifndef TASK_H
#define TASK_H
#include <QString>
#include<QtSql/QSqlQuery>
#include"QtSql/QSqlDatabase"
#include<QtSql/QSqlQueryModel>
#include <QDebug>
#include "connection.h"
#include <QDate>
#include <QStandardItemModel>


class Task
{
public:
    Task();
    Task(QDate start,QDate end,QString state, int id_projet, QString nom, int estimate, QString confidence, int budget, int progres);
    bool ajouter();
    bool modifier(QDate debut, QDate fin, QString etat, int idd, QString nom, QString cellname, int estimate, QString confidence, int budget, int progres);
    QSqlQueryModel* afficher(int idd);
    int totalbudget(int id);
    QString n;
private:
    int id;
    int id_projet;
    QDate start;
    QDate end;
    QString state;
    QString nom;
    int estimate;
    QString confidence;
    int budget;
    int progres;
};
#endif // TASK_H
