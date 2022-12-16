#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include <QMessageBox>
#include <QTableWidget>
#include <adding.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CreateButton_clicked()
{
    QMessageBox question;
    question.setWindowTitle("Внимание");
    question.setText("Вы уверены, что хотите создать новый файл?\nВсе изменения не сохранятся");
    question.addButton(QMessageBox::Yes);
    question.addButton(QMessageBox::No);
    if(question.exec() == QMessageBox::Yes){
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Производитель"<<"Название"<<"Цвет"<<"Время доставки"<<"Количество");
        file_ = "";
        ui->statusbar->showMessage("Файл создан");
    }
}


void MainWindow::on_AddButton_clicked()
{
    add = new adding(this);
    if(add->exec() == QDialog::Accepted){
        setWindowTitle("*" + file_);

    }

}

void MainWindow::addding(QString creator, QString name, QString color, QString delivery_time, int count, int row){
        int Count = count;
        auto list = ui->tableWidget->selectedItems();
        if (list.size() > 0){row = list.at(0)->row();}
        QTableWidgetItem *itm = new QTableWidgetItem(creator);
        QTableWidgetItem *itm1 = new QTableWidgetItem(name);
        QTableWidgetItem *itm2 = new QTableWidgetItem(color);
        QTableWidgetItem *itm3 = new QTableWidgetItem(delivery_time);
        QTableWidgetItem *itm4 = new QTableWidgetItem(QString::number(Count));
        if(row == -1){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, itm);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, itm1);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, itm2);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, itm3);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, itm4);
            ui->statusbar->showMessage("Запись добавлена");
        } else{
            ui->tableWidget->setItem(row, 0, itm);
            ui->tableWidget->setItem(row, 1, itm1);
            ui->tableWidget->setItem(row, 2, itm2);
            ui->tableWidget->setItem(row, 3, itm3);
            ui->tableWidget->setItem(row, 4, itm4);}

}

void MainWindow::on_AboutButton_clicked()
{
    QMessageBox::about(this,
                           "О программе",
                           "Курсовая работа по дисциплине ООП\n"
                           "Вариант 12\n"
                           "Выполнил студент группы ИКПИ-12\n"
                           "Межуев Роман\n"
                           "Санкт-Петербург\n"
                           "2022 год");
}


void MainWindow::on_EditButton_clicked()
{
    auto list = ui->tableWidget->selectedItems();
    if (list.size() > 0) {
        add = new adding(this);
        ui->tableWidget->selectRow(list.at(0)->row());
        auto list = ui->tableWidget->selectedItems();
        add->setData(list);
        add->exec();
        ui->tableWidget->clearSelection();
        ui->statusbar->showMessage("Запись отредактирована");
        setWindowTitle("*" + file_);
    }
}


void MainWindow::on_DeleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Внимание");
    msgBox.setText("Вы уверены, что хотите удалить строку с выбранным элементом?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if (msgBox.exec() == QMessageBox::Yes) {
        auto list = ui->tableWidget->selectedItems();
        if (list.size() > 0){
            for(int i = 0; i<list.length(); i++){
            ui->tableWidget->removeRow(list.at(i)->row());}
         }
        ui->statusbar->showMessage("Запись удалена");
     }
}


void MainWindow::on_ClearButton_clicked()
{
    if(ui->tableWidget->rowCount()>0){
        QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Вы уверены, что хотите очистить таблицу?");
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                if (msgBox.exec() == QMessageBox::Yes) {
                    ui->tableWidget->setRowCount(0);
                }
                ui->statusbar->showMessage("Таблица очищена");
                setWindowTitle("*" + file_);
    }
}


void MainWindow::on_InputButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFile file(file_name);
    file_ = file_name;
    if (file.open(QIODevice::ReadOnly)) {
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(5);
//        for(int i = 0; i<5; i++){
//        ui->tableWidget->setColumnWidth(i, 140);}
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Производитель"<<"Название"<<"Цвет"<<"Время доставки"<<"Количество");
               QTextStream in(&file);
               while (!in.atEnd()) {
                   QString line = in.readLine();
                   QStringList fields = line.split(";");
                   addding(fields.at(0).simplified(), fields.at(1).simplified(), fields.at(2).simplified(), fields.at(3).simplified(), fields.at(4).simplified().toInt());
               }
               file.close();
               setWindowTitle(file_name);
               ui->statusbar->showMessage("Файл '" + file_name + "' импортирован");
    }else ui->statusbar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");

}


void MainWindow::on_Merge_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
        if(ui->tableWidget->rowCount() == 0){
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Производитель"<<"Название"<<"Цвет"<<"Время доставки"<<"Количество");
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(";");
            addding(fields.at(0).simplified(), fields.at(1).simplified(), fields.at(2).simplified(), fields.at(3).simplified(), fields.at(4).simplified().toInt());

        }
        file.close();
        ui->statusbar->showMessage("Базы соединены");
        ui->progressBar->setValue(100);

    }
}


void MainWindow::on_SaveButton_clicked()
{
    if (file_ == "") {
            MainWindow::on_SaveAsButton_clicked();
            return;
        }
    QFile file(file_);
    if (file.open(QIODevice::WriteOnly)) {
           QTextStream out(&file);
           int len = ui->tableWidget->rowCount();
           for (int i = 0; i < len; ++i) {
               QString creator = ui->tableWidget->item(i, 0)->text();
               QString name = ui->tableWidget->item(i, 1)->text();
               QString color = ui->tableWidget->item(i, 2)->text();
               QString delivery_time = ui->tableWidget->item(i, 3)->text();
               QString count = ui->tableWidget->item(i, 4)->text();
               out << creator << ";" << name << ";" << color << ";" << delivery_time << ";" << count << ";" << "\n";
           }
           ui->statusbar->showMessage("Сохранено");
           file.close();
       }
    setWindowTitle(file_);
}


void MainWindow::on_SaveAsButton_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    if (file_name != "") {
        file_ = file_name;
        MainWindow::on_SaveButton_clicked();
        setWindowTitle(file_);
        ui->statusbar->showMessage("Сохранено");
    }
}


void MainWindow::on_ExitButton_clicked()
{
    if (ui->tableWidget->rowCount() > 0 || file_ != "") {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Вы уверены, что хотите выйти?\nВсе проделанные изменения не будут сохранены.");
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            if (msgBox.exec() == QMessageBox::No) {
                return;
            }
        }
        exit(0);
}


void MainWindow::on_SearchBar_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentCell(-1, -1);
       if (arg1 == "") {
           return;
       }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
        auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
        int len = find_items.size();
        for (int i = 0; i < len; ++i) {
            auto item = find_items.at(i);
            ui->tableWidget->setItemSelected(item, true);
        }
        ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        ui->statusbar->showMessage("Найдено " + QString::number(len) + " ячеек");
}


void MainWindow::on_CSVButton_clicked()
{
    int len = ui->tableWidget->rowCount();
    csv = new CSV_View();
    QString row = "";
    for (int i = 0; i < len; ++i) {
        QString creator = ui->tableWidget->item(i, 0)->text();
        QString name = ui->tableWidget->item(i, 1)->text();
        QString color = ui->tableWidget->item(i, 2)->text();
        QString delivery_time = ui->tableWidget->item(i, 3)->text();
        QString count = ui->tableWidget->item(i, 4)->text();
        row += creator + ";" + name + ";" + color + ";" + delivery_time + ";" + count + ";\n";}
    csv->set_text(row);
    csv->exec();
}


void MainWindow::on_ExitButtonMenu_triggered()
{
    on_ExitButton_clicked();
}


void MainWindow::on_AboutButtonMenu_triggered()
{
    on_AboutButton_clicked();
}


void MainWindow::on_AddButtonMenu_triggered()
{
    on_AddButton_clicked();
}


void MainWindow::on_DeleteButtonMenu_triggered()
{
    on_DeleteButton_clicked();
}


void MainWindow::on_EditButtonMenu_triggered()
{
    on_EditButton_clicked();
}


void MainWindow::on_ClearButtonMenu_triggered()
{
    on_ClearButton_clicked();
}


void MainWindow::on_CreateButtonMenu_triggered()
{
    on_CreateButton_clicked();
}


void MainWindow::on_OpenButtonMenu_triggered()
{
    on_InputButton_clicked();
}


void MainWindow::on_SaveButtonMenu_triggered()
{
    on_SaveButton_clicked();
}


void MainWindow::on_SaveAsButtonMenu_triggered()
{
    on_SaveAsButton_clicked();
}


void MainWindow::on_MergeButtonMenu_triggered()
{
    on_Merge_clicked();
}

