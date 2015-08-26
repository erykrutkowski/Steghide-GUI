#include "extractdialog.h"
#include "ui_extractdialog.h"

ExtractDialog::ExtractDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtractDialog)
{
    ui->setupUi(this);
}

ExtractDialog::~ExtractDialog()
{
    delete ui;
}

void ExtractDialog::setlabeltext(QString new_text){
    ui->label->setText(new_text);
}

void ExtractDialog::setprogressbarvalue(int k){
    ui->progressBar->setValue(k);
}

void ExtractDialog::on_pushButton_clicked()
{
    delete this;
}
