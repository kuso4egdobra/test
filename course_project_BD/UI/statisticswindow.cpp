#include "statisticswindow.h"
#include "ui_statisticswindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "loggingcategories.h"

StatisticsWindow::StatisticsWindow(DataFromGuiToBusiness *sender, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
    this->sender = sender;
    configFilePath = "";
    model = nullptr;
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;

    if (model)
        delete model;
}

void StatisticsWindow::importFile(QString fileName)
{
    configFilePath = fileName;
    sender->setImport(fileName);
    ui->comboBox->addItems(sender->getListNameImport());
//    QMessageBox::information(this, "", "Файл успешно импортирован");
}

void StatisticsWindow::on_BtnReset_clicked()
{
    qDebug(logInfo()) << "Выход из окна получения статистики";
    this->close();
    emit openWindow();
}

void StatisticsWindow::on_Btn_importConfig_clicked()
{
    configFilePath = QFileDialog::getOpenFileName(this, "", "", "Text Files (*.txt)").toUtf8().constData();
    if (configFilePath.size() > 0)
    {
        importFile(configFilePath);
    }
}

int StatisticsWindow::on_BtnOk_clicked()
{
    int res = -1;
    qDebug(logInfo()) << "Получение статистики...";
    if (model)
    {
        delete model;
        model = nullptr;
    }

    if (configFilePath.size() > 0)
    {
        auto str = sender->getListSqlQueryImport()[ui->comboBox->currentIndex()];
        model = sender->sendSqlQuery(str);
        res = model->record(0).value(0).toInt();

        if (model)
            ui->tableView->setModel(model);
        else
        {
            QMessageBox::critical(this, "", "Ошибка выполнения запроса!");
            qDebug(logCritical()) << "Ошибка выполнения запроса";
        }
    }
    else
    {
        QMessageBox::critical(this, "", "Ошибка! Выберите конфигурационный файл.");
        qDebug(logCritical()) << "Не выбран конфигурационный файл";
    }

    return res;
}
