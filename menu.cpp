#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_b_2_clicked()
{
   MainWindow *w =new MainWindow ;
   w->show();
   this->hide();
}
