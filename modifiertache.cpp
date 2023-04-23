#include "modifiertache.h"
#include "ui_modifiertache.h"

modifiertache::modifiertache(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifiertache)
{
    ui->setupUi(this);
}

modifiertache::~modifiertache()
{
    delete ui;
}
