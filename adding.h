#ifndef ADDING_H
#define ADDING_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class adding;
}

class adding : public QDialog
{
    Q_OBJECT

public:
    explicit adding(QWidget *parent = nullptr);

    ~adding();
    void setData(QList<QTableWidgetItem *> list/*QString creator, QString name, QString color, QString delivery_time, QString count*/);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::adding *ui;
};

#endif // ADDING_H
