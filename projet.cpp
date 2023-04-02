#include "projet.h"
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


using namespace std;


projet::projet()
{
   this->nom=" ";
   this->theme=" ";
   this->periode=0;
   c.createconnect();
}
projet::projet(QString nom,QString theme,int periode)
{

   this->nom=nom.toUpper();
   this->theme=theme.toUpper();
   this->periode=periode;
}


int projet::get_id(){return this->id;}
void projet::Set_nom(QString val) { this->nom = val; }
QString projet::get_nom(){return this->nom;}
void projet::Set_theme(QString val) { this->theme = val; }
QString projet:: get_theme(){return this->theme;}
void projet::Set_periode(int val) { this->periode = val; }
int projet::get_periode(){return this->periode;}


bool projet::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO projet (NOM,THEME,PERIODE)"
                          "VALUES (:nom, :theme, :periode)");
    query.bindValue(":nom",nom);
    query.bindValue(":theme",theme);
    query.bindValue(":periode",periode);
    return query.exec();
}

QSqlQueryModel *projet::afficher()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE"));
 return model;
}

bool projet :: modifier_projet(int id ,QString nom,QString theme,int periode)
{

        QSqlQuery qry;
        qry.prepare("UPDATE projet set NOM=(?),theme=(?),periode=(?) where ID=(?) ");
        qry.addBindValue(nom);
        qry.addBindValue(theme);
        qry.addBindValue(periode);
        qry.addBindValue(id);
        return  qry.exec();
}

bool projet::supprimer(int idd)
{
    QSqlQuery query;
    query.prepare("Delete from projet where ID = :id ");
    query.bindValue(":id",idd);
    return query.exec();

}






