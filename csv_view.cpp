#include "csv_view.h"
#include "ui_csv_view.h"

CSV_View::CSV_View(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSV_View)
{
    ui->setupUi(this);
}

CSV_View::~CSV_View()
{
    delete ui;
}

void CSV_View::set_text(QString row){
    ui->textEdit->setText(row);
}
void CSV_View::on_closeButton_clicked()
{
    close();
}

