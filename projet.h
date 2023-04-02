#ifndef PROJET_H
#define PROJET_H
#include <QString>
#include<QtSql/QSqlQuery>
#include"QtSql/QSqlDatabase"
#include<QtSql/QSqlQueryModel>
#include <QDebug>
#include "connection.h"

class projet
{

public:
    //entete
    projet();
    projet(QString,QString, int);
    int get_id();
    void Set_nom(QString val);
    QString get_nom();
    void Set_theme(QString val) ;
    QString get_theme();
    void Set_periode(int val) ;
    int get_periode();
    bool ajouter();
    bool  modifier_projet(int,QString,QString,int);
    bool supprimer(int idd);
    QSqlQueryModel * afficher();
    Connection c;
private:
    int id;
    QString nom;
    QString theme;
    int periode;
};

#endif // PROJET_H
