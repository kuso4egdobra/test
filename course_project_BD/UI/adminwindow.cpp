#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

#include "loggingcategories.h"

AdminWindow::AdminWindow(DataFromGuiToBusiness *sender, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->sender = sender;
    model = nullptr;

    textEdit_sqlEntry = ui->textEdit_sqlEntry;
}

AdminWindow::~AdminWindow()
{
    delete ui;

    if (model)
        delete model;
}

void AdminWindow::on_BtnReset_clicked()
{
    qDebug(logInfo()) << "Выход из окна администрирования";
    this->close();
    emit openWindow();
}

int AdminWindow::on_BtnOk_clicked()
{
    if (model)
    {
        delete model;
        model = nullptr;
    }

    auto str = ui->textEdit_sqlEntry->toPlainText();
    qDebug(logInfo()) << "Отправка SQL запроса";
    model = sender->sendSqlQuery(str, true);
    int res = model->record(0).value(0).toInt();

    if (model)
    {
        ui->tableView->setModel(model);
//        QMessageBox::information(this, "", "Запрос успешно выполнен");
        qDebug(logInfo()) << "Запрос успешно выполнен";
    }
    else
    {
        QMessageBox::critical(this, "", "Ошибка выполнения запроса!");
        qDebug(logCritical()) << "Ошибка выполнения запроса!";
    }

    return res;
}

void AdminWindow::on_checkBox_stateChanged(int checked)
{
    sender->setFlagNeedToColorOldDocs(checked);
}
