#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projet.h"
#include <QMessageBox>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
#include "ajoutertache.h"
#include <QColor>
#include "dialogstats.h"
#include <qpdfwriter.h>
#include <QPainter>
#include <QTextDocument>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
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
        //ui->afficher_budget->setModel(t.afficher(p.get_id()));
        //c.createconnect();
        jourSelectionne = QDate::currentDate();

        // Style calendar
        ui->calendrier->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        QTextCharFormat weekendFormat;
        weekendFormat.setForeground(QBrush(QColor(236,64,122,250), Qt::SolidPattern));
        ui->calendrier->setWeekdayTextFormat(Qt::Saturday, weekendFormat);
        ui->calendrier->setWeekdayTextFormat(Qt::Sunday, weekendFormat);
        ui->calendrier->setFirstDayOfWeek(Qt::Monday);
        QTableView *view = ui->calendrier->findChild<QTableView*>("qt_calendar_calendarview");
        if (view)
        {
            QPalette pal = view->palette();
            pal.setColor(QPalette::Highlight, QColor(26,128,182,250));
            view->setPalette(pal);
        }
        // Style week view
        QHeaderView* header = ui->vueHebdomadaire->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
        this->updateVueHebdomadaire();
        connect(ui->calendrier, SIGNAL (clicked(QDate)), this, SLOT (updateJourSelectionne(QDate)));
        connect(ui->calendrier, SIGNAL (clicked(QDate)), this, SLOT (updateVueHebdomadaire()));
        connect(ui->vueHebdomadaire, SIGNAL (cellclicked(int, int)) , this, SLOT(on_vueHebdomadaire_cellDoubleClicked));
        connect(ui->afficher_projet->horizontalHeader(), &QHeaderView::sectionClicked, [=](int index) {
            qDebug() << "Clicked column header:" << index;
            qDebug()<< "shiiiiiiit";
            if(index==0)ui->afficher_projet->setModel(p.trie_id());
            else if(index==1)ui->afficher_projet->setModel(p.trie_nom());
            else if (index==2)ui->afficher_projet->setModel(p.trie_theme());
            else if (index==3)ui->afficher_projet->setModel(p.trie_periode());
        });

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
            int id = qry.value(0).toInt();
            QString nom= qry.value(1).toString();
            p.Set_id(id);
            p.Set_nom(nom);
            ui->afficher_budget->setModel(t.afficher(p.get_id()));
            ui->afficher_budget->resizeColumnsToContents();
            int total=t.totalbudget(p.get_id());
            ui->label_10->setText("Total budget: "+QString::number(total));
            data.append(p.get_nom().toUtf8());
            data.append(',');
            data.append(QString::number(total));
            A.write_to_arduino(data);
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
    {QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("suppression non effectué"),QMessageBox::Cancel);}
    ui->afficher_budget->setModel(t.afficher(p.get_id()));
    ui->afficher_budget->resizeColumnsToContents();
}

const QDate MainWindow::getSelectedMonday()
{
    return jourSelectionne.addDays(- jourSelectionne.dayOfWeek() + 1);
}

void MainWindow::updateJourSelectionne(const QDate & date)
{
    Q_UNUSED(date);
    jourSelectionne = ui->calendrier->selectedDate();
}

void MainWindow::updateVueHebdomadaire() {

    //Nettoyage de l'affichage précédent
    ui->vueHebdomadaire->clearContents();
    ui->vueHebdomadaire->clearSpans();

    //Mise à jour des labels horizontaux
    QStringList listeJours(getSelectedMonday().toString("dddd d"));
    int i;
    for(i=1;i<7;i++){
        listeJours << getSelectedMonday().addDays(i).toString("dddd d");
    }
    ui->vueHebdomadaire->setHorizontalHeaderLabels(listeJours);

    //Mise à jour des labels Verticaux et style du tableau

    QStringList listeHeures;
    QTime h(8,0) ;
    ui->vueHebdomadaire->setStyleSheet("gridline-color: white;");
    int j;
    for(i=0; i<=72; i++){
        if(i%6 == 0){
            for(j=0;j<7;j++){
                QTableWidgetItem * case_heure = new QTableWidgetItem();
                case_heure->setBackgroundColor(QColor("#E8E8E8"));
                ui->vueHebdomadaire->setItem(i,j,case_heure);
            }
            listeHeures << h.toString("H:mm");
            h = h.addSecs(3600);
        }
        else
            listeHeures << QString("");
    }
    ui->vueHebdomadaire->verticalHeader()->setStyleSheet("QHeaderView::section {border : none;}");
    ui->vueHebdomadaire->setVerticalHeaderLabels(listeHeures);

    //Mise à jour des evenements de la semaine

    QFont policeTitre;
    policeTitre.setPointSize(12);
    QDate monday =getSelectedMonday();
    const QDate sunday = monday.addDays(6);
    QSqlQuery qry;
    qry.prepare("SELECT * FROM task WHERE ID_PROJET= :id AND START_DATE>= :monday AND END_DATE<= :sunday");
    qDebug() << p.get_id();
    qry.bindValue(":id",p.get_id());
    qry.bindValue(":monday", monday);
    qry.bindValue(":sunday", sunday);
    qry.exec();
    while (qry.next()) {
        QTableWidgetItem * case_event = new QTableWidgetItem(qry.value(5).toString());
        case_event->setFont(policeTitre);
        case_event->setTextAlignment(Qt::AlignCenter);
        QColor bc;
        if(qry.value(3).toString()=="To-do")bc="#ADD8E6";
        else if (qry.value(3).toString()=="Doing") bc="#f4fc53";
        else bc="#6afc53";
        case_event->setBackgroundColor(bc);
        //case_event->setToolTip(evenement->getDesc());

        int colonne = qry.value(1).toDate().daysTo(getSelectedMonday()) + 1;
        int days= qry.value(1).toDate().daysTo(qry.value(2).toDate());

        //int ligne = (evenement->getDebut()->time().hour() - 8) * 6; //Heures
        //ligne = ligne + evenement->getFin()->time().minute() / 10; //Minutes

        ui->vueHebdomadaire->removeCellWidget(2,-colonne + 1);
        ui->vueHebdomadaire->setItem(2,-colonne + 1,case_event);
        ui->vueHebdomadaire->setSpan(2,-colonne + 1,2,days);


        }
}
void MainWindow::on_pushButton_clicked()
{
    ajouterTache d;
    d.idd=p.get_id();
    d.exec();
    ui->afficher_budget->setModel(t.afficher(p.get_id()));
    ui->afficher_budget->resizeColumnsToContents();
    ui->label_10->setText("Total budget: "+QString::number(t.totalbudget(p.get_id())));
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    updateVueHebdomadaire();
}



void MainWindow::on_vueHebdomadaire_cellDoubleClicked(int row, int column)
{
    QTableWidgetItem *item = ui->vueHebdomadaire->item(row, column);
    QString cellText = item->text();
        ajouterTache d;
        d.idd=p.get_id();
        d.cellname=cellText;
        d.exec();
}

void MainWindow::on_afficher_budget_activated(const QModelIndex &index)
{
    qDebug()<<"testing";
    int row = index.row();
    QModelIndex otherIndex = ui->afficher_budget->model()->index(row, 0);
    QVariant value = ui->afficher_budget->model()->data(otherIndex);
    qDebug()<< value.toString();
    qDebug()<<"hahahahahahahaha";
    ajouterTache d;
    d.val=value.toString();
    d.exec();
    ui->afficher_budget->setModel(t.afficher(p.get_id()));
    ui->afficher_budget->resizeColumnsToContents();
    int total= t.totalbudget(p.get_id());
    ui->label_10->setText("Total budget: "+QString::number(total));
    data.append(p.get_nom().toUtf8());
    data.append(',');
    data.append(QString::number(total));
    A.write_to_arduino(data);
}


void MainWindow::on_afficher_budget_clicked(const QModelIndex &index)
{
    int row = index.row();
    QModelIndex otherIndex = ui->afficher_budget->model()->index(row, 2);
    QVariant value = ui->afficher_budget->model()->data(otherIndex);
    ui->calendrier->setSelectedDate(value.toDate());
    updateJourSelectionne(value.toDate());

}


void MainWindow::on_pushButton_4_clicked()
{
    QString val=ui->recherche->text();
    ui->afficher_projet->setModel(p.recherche(val));
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->afficher_projet->setModel(p.afficher());
}

void MainWindow::on_pushButton_6_clicked()
{
    dialogstats stats;
    stats.setModal(true);
    stats.exec();
}



void MainWindow::on_pushButton_7_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/listeprojets.pdf");
                           QPainter painter(&pdf);
                          int i = 4000;

                                painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C://"));
                                painter.drawText(900,650,"smart RDI center");
                               painter.setPen(Qt::red);
                               painter.setFont(QFont("Time New Roman", 25));
                               painter.drawText(3000,1400,"Liste projets");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500);
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"Nom");
                               painter.drawText(4000,3300,"Theme");
                               painter.drawText(5600,3300,"Periode");
                               //painter.drawText(8000,3300,"Date ajout");
                               painter.drawRect(100,3000,9400,10700);
                               QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from projet");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                  i = i +500;
                               }
                               int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                   QMessageBox::Yes|QMessageBox::No);
                                   if (reponse == QMessageBox::Yes)
                                   {
                                       QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/listeprojets.pdf"));

                                   }
                                   painter.end();
}
