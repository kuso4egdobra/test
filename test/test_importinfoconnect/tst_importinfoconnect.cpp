#include <QtTest>
#include <iostream>
#include <fstream>
#include <QDebug>

#include "AccessData/AccessDataConfiguration/importinfoconnection.h"

class importinfoconnect : public QObject
{
    Q_OBJECT

private:
    QString typeDatabase = "QPSQL";
    QString hostName = "127.0.0.1";
    QString userName = "postgres";
    QString databaseName = "postgres";
    QString password = "123456";
    QString port = "5433";

public:
    importinfoconnect();
    ~importinfoconnect();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_no_existant_file();
    void test_read_file_data();
    void test_read_file();
    void test_empty_file_data();
    void test_empty_file();

};

importinfoconnect::importinfoconnect()
{

}

importinfoconnect::~importinfoconnect()
{

}

void importinfoconnect::initTestCase()
{

}

void importinfoconnect::cleanupTestCase()
{

}

void importinfoconnect::test_no_existant_file()
{
   delete(new ImportInfoConnection(""));
}

void importinfoconnect::test_read_file_data()
{
    std::ofstream out;
    out.open("./file.txt");
    if (out.is_open())
    {
        out << typeDatabase.toStdString() << std::endl;
        out << hostName.toStdString() << std::endl;
        out << userName.toStdString() << std::endl;
        out << databaseName.toStdString() << std::endl;
        out << password.toStdString() << std::endl;
        out << port.toStdString() << std::endl;
    }
    else
    {
        assert(false);
    }
}

void importinfoconnect::test_read_file()
{
    ImportInfoConnection *info = new ImportInfoConnection("./file.txt");

    QCOMPARE(info->getTypeDatabase(), typeDatabase);
    QCOMPARE(info->getHostName(), hostName);
    QCOMPARE(info->getUserName(), userName);
    QCOMPARE(info->getDatabaseName(), databaseName);
    QCOMPARE(info->getPassword(), password);
    QCOMPARE(info->getPort(), port);

    delete info;
}

void importinfoconnect::test_empty_file_data()
{
    std::ofstream out;
    out.open("./file1.txt");
}

void importinfoconnect::test_empty_file()
{
    ImportInfoConnection *info = new ImportInfoConnection("./file1.txt");
    delete info;
}

QTEST_APPLESS_MAIN(importinfoconnect)

#include "tst_importinfoconnect.moc"
