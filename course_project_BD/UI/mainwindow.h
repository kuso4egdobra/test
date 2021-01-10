#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newdocumentwindow.h"
#include "adminwindow.h"
#include "statisticswindow.h"

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    NewDocumentWindow* getNewDocumentWindow();
    AdminWindow* getAdminWindow();
    StatisticsWindow* getStatisticsWindow();

public slots:
    void on_BtnNewDoc_clicked();
    void on_Btn_admin_clicked();

    void on_Btn_stat_clicked();

private:
    BusinessLogic business;
    DataFromGuiToBusiness *sender;

    Ui::MainWindow *ui;
    NewDocumentWindow *docWindow;
    AdminWindow *adminWindow;
    StatisticsWindow *statWindow;

//    QSqlDatabase db;
//    QSqlRelationalTableModel *model;
};

#endif // MAINWINDOW_H
