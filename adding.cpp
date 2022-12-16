#include "adding.h"
#include "ui_adding.h"
#include "mainwindow.h"

#include <QTableWidgetItem>

adding::adding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adding)
{
    ui->setupUi(this);
}

adding::~adding()
{
    delete ui;
}

void adding::on_buttonBox_accepted()
{

    QString name = (ui->name->text());
    QString Creator(ui->creator->text());
    int Count(ui->count->text().toInt());
    QString DeliveryTime(ui->delivery_time->text());
    QString Color(ui->color->text());
    MainWindow *main_window = (MainWindow *) parentWidget();
    main_window->addding(Creator, name, Color, DeliveryTime, Count);

}

void adding::setData(QList<QTableWidgetItem *> list){
    ui->creator->setText(list.at(0)->text());
    ui->name->setText(list.at(1)->text());
    ui->color->setText(list.at(2)->text());
    ui->delivery_time->setText(list.at(3)->text());
    ui->count->setText(list.at(4)->text());
}

