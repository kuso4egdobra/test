#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <fstream>
#include <QDebug>

#include "BusinessLogic/businesslogic.h"
#include "AccessData/connection.h"

#define FILE_NAME "./fileBusiness.txt"
#define NAME_SQL "Что запрос делает\n"
#define SQL_RECORD "SQL-запрос;"

using namespace testing;

class FileBuilder
{
public:
    FileBuilder() { }

    void genEmptyFile(QString fileName)
    {
        std::ofstream out;
        out.open(fileName.toStdString());
        if (out.is_open())
        {
            out.close();
        }
        else
        {
            assert(false);
        }
    }

    void genCorrectFile(QString fileName, int num_records)
    {
        std::ofstream out;
        out.open(fileName.toStdString());
        if (out.is_open())
        {
            for (int i = 0; i < num_records; i++)
                out << NAME_SQL << SQL_RECORD << "\n";

            out.close();
        }
        else
        {
            assert(false);
        }
    }
};

TEST(IntegrationBusiness, ImportSQlQuery)
{
    BusinessLogic business;
    FileBuilder builder;
    int num_records = 10;
    builder.genCorrectFile(FILE_NAME, num_records);
    business.setImport(FILE_NAME);

    QList<QString> res = business.getListSqlQueryImport();

    ASSERT_EQ(res.size(), num_records);
    for (int i = 0; i < res.size(); i++)
    {
        ASSERT_STREQ(res[i].toStdString().c_str(), SQL_RECORD);
    }
}

TEST(IntegrationConnection, ImportDB)
{
    QString typeDB = "QPSQL";
    QString nameDB = "postgres";
    QString hostName = "127.0.0.1";
    QString userName = "postgres";
    QString password = "123456";
    int portDB = 5433;

    Connection connection(typeDB, nameDB, userName, hostName, password, portDB);

    ASSERT_STREQ(connection.getTypeDB().toStdString().c_str(), typeDB.toStdString().c_str());
    ASSERT_STREQ(connection.getNameDB().toStdString().c_str(), nameDB.toStdString().c_str());
    ASSERT_EQ(connection.getPortDB(), portDB);
}
