#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loggingcategories.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new DataFromGuiToBusiness(&business);
    docWindow = new NewDocumentWindow(sender);
    adminWindow = new AdminWindow(sender);
    statWindow = new StatisticsWindow(sender);
    connect(docWindow, &NewDocumentWindow::openWindow, this, &MainWindow::show);
    connect(adminWindow, &AdminWindow::openWindow, this, &MainWindow::show);
    connect(statWindow, &StatisticsWindow::openWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sender;

    delete adminWindow;
    delete docWindow;
    delete statWindow;
}

NewDocumentWindow *MainWindow::getNewDocumentWindow()
{
    return docWindow;
}

AdminWindow *MainWindow::getAdminWindow()
{
    return adminWindow;
}

StatisticsWindow *MainWindow::getStatisticsWindow()
{
    return statWindow;
}

void MainWindow::on_BtnNewDoc_clicked()
{
    qDebug(logInfo()) << "Переход в окно добавления документа";
    this->close();
    docWindow->show();
}

void MainWindow::on_Btn_admin_clicked()
{
    qDebug(logInfo()) << "Переход в окно администрирования";
    this->close();
    adminWindow->show();
}

void MainWindow::on_Btn_stat_clicked()
{
    qDebug(logInfo()) << "Переход в окно получения статистики";
    this->close();
    statWindow->show();
}


//    time_t seconds = time(NULL);
//    tm* timeinfo = localtime(&seconds);
//    qDebug() <<"Current Datetime:"<<asctime(timeinfo)<<endl;

//    db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("127.0.0.1");
//    db.setDatabaseName("postgres");
//    db.setUserName("postgres");
//    db.setPassword("19021999");
//    db.setPort(5433);

//    if (!db.open())
//    {
//        qDebug() << db.lastError() << endl;
//        return;
//    }
//    else
//        qDebug() << "Success" << endl;

//    db.transaction();
//    QSqlQuery query = QSqlQuery(db);
//    query.exec("insert into doc_type (name) values ('Base doc1') returning id;");
//    query.exec("select * from doc_type");
//    while (query.next())
//    {
//        qDebug() << query.record();
//    }

//    QSqlQuery query1 = QSqlQuery(db);
//    query1.exec("insert into doc_type (id, name) values (5, 'Base doc2');");
//    db.commit();
//    db.rollback();



//    datetime_t time;
//    time.date = 10;
//    time.hour = 10;
//    time.secs = 10;
//    time.year = 1999;
//    time.month = 10;
//    time.minute = 10;
//    time.time_need = true;

//    fio_t fio;
//    fio.sex = 'M';
//    fio.name = "Andrey";
//    fio.surname = "Korotkov";
//    fio.patronymic = "Qwerty";

//    QVector<otherAtribute_t> list;

//    BaseDoc doc(-1, time, 1, 1, 1, "athority", time, time, time, fio, list);
//    Business_NewDoc business;
//    business.addNewDoc(doc);

//    if (!db.open())
//    {
//        qDebug() << db.lastError() << endl;
//        return;
//    }
//    else
//        qDebug() << "Success" << endl;

//    qDebug() << db.tables();

//    QSqlQuery query = QSqlQuery(db);
//    query.exec("select * from clients");
//    model = new QSqlQueryModel();
//    model->setQuery(query);
//    model = new QSqlRelationalTableModel(this, db);

//    model->setTable("filial");
//    if (!model->select())
//        qDebug() << model->lastError();

//    qDebug() << model->record();
//    qDebug() << model->query().record();
//    QSqlQuery query = model->query();
//    while (query.next())
//    {
//         qDebug() << query.record();
//        qDebug() << query.record().value(1);
//    }


//    ui->tableView->setModel(model);
//    ui->comboBox->setModel(model);

//    Training *temp = new Training();
//    qDebug() << temp->i; // 1
//    temp->~Training();
//    delete temp;
//    qDebug() << temp->i; // 1
//    temp = new Training();
//    qDebug() << temp->i; // 2
//    ui->comboBox->setModelColumn(2);



//void MainWindow::on_pushButton_clicked()
//{
//    QSqlQuery query = QSqlQuery(db);
//    if (!query.exec("INSERT INTO filial (name, adress, telephone) VALUES ('1', '1', '1') RETURNING id"))
//    {
//        qDebug() << query.lastError().databaseText();
//        qDebug() << query.lastError().driverText();
//        return;
//    }

//    qDebug() << query.result();

//    while (query.next())
//    {
//        qDebug() << query.record();
//    }
//}

//void MainWindow::on_pushButton_2_clicked()
//{

//}
