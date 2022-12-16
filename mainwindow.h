#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <adding.h>
#include <csv_view.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    void addding(QString creator, QString name, QString color, QString delivery_time, int count, int row = -1);
private slots:

    void on_CreateButton_clicked();

    void on_AddButton_clicked();
    void on_AboutButton_clicked();

    void on_EditButton_clicked();

    void on_DeleteButton_clicked();

    void on_ClearButton_clicked();

    void on_InputButton_clicked();

    void on_Merge_clicked();

    void on_SaveButton_clicked();

    void on_SaveAsButton_clicked();

    void on_ExitButton_clicked();

    void on_SearchBar_textChanged(const QString &arg1);

    void on_CSVButton_clicked();

    void on_ExitButtonMenu_triggered();

    void on_AboutButtonMenu_triggered();

    void on_AddButtonMenu_triggered();

    void on_DeleteButtonMenu_triggered();

    void on_EditButtonMenu_triggered();

    void on_ClearButtonMenu_triggered();

    void on_CreateButtonMenu_triggered();

    void on_OpenButtonMenu_triggered();

    void on_SaveButtonMenu_triggered();

    void on_SaveAsButtonMenu_triggered();

    void on_MergeButtonMenu_triggered();

private:
    Ui::MainWindow *ui;
    adding *add;;
    CSV_View *csv;
    QString file_ = "";

};
#endif // MAINWINDOW_H
