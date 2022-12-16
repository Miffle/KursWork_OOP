#ifndef CSV_VIEW_H
#define CSV_VIEW_H

#include <QDialog>

namespace Ui {
class CSV_View;
}

class CSV_View : public QDialog
{
    Q_OBJECT

public:
    explicit CSV_View(QWidget *parent = nullptr);
    ~CSV_View();
    void set_text(QString row);

private slots:
    void on_closeButton_clicked();

private:
    Ui::CSV_View *ui;
};

#endif // CSV_VIEW_H
