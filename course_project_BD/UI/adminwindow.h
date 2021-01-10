#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <QTextEdit>

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(DataFromGuiToBusiness *sender, QWidget *parent = nullptr);
    ~AdminWindow();
    QTextEdit *textEdit_sqlEntry;

signals:
    void openWindow();

public slots:
    void on_BtnReset_clicked();
    int on_BtnOk_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::AdminWindow *ui;
    DataFromGuiToBusiness *sender;
    QSqlQueryModel *model;
};

#endif // ADMINWINDOW_H
