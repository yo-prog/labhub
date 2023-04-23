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
   bool test=c.createconnect();

   if(test){
       QMessageBox::information(nullptr, QObject::tr("database is open"),
                   QObject::tr("connection successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
   else{
       QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                   QObject::tr("connection failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
        }
}
projet::projet(QString nom,QString theme,int periode)
{

   this->nom=nom.toUpper();
   this->theme=theme.toUpper();
   this->periode=periode;
}

void projet::Set_id(int idd) { this->id= idd; }
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
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
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
QSqlQueryModel *projet::trie_id()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet order BY ID");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
 return model;
}

QSqlQueryModel *projet::trie_nom()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet order BY NOM");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
 return model;
}

QSqlQueryModel *projet::trie_theme()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet order BY THEME");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
 return model;
}
QSqlQueryModel *projet::trie_periode()
{
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet order BY PERIODE");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
 return model;
}

QSqlQueryModel *projet::recherche(QString nom)
{
 QSqlQuery qry;
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery("SELECT * FROM projet where  NOM='"+nom+"' ");
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("THEME"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("PERIODE\n(en semaines)"));
 return model;
}








