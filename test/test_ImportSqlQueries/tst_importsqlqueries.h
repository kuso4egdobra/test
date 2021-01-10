#pragma once

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QDebug>

#include "BusinessLogic/ImportSqlQueries/importsqlqueries.h"

#define FILE_NAME "./fileTemp.txt"

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
                out << "Что запрос делает\nSQL-запрос;\n";

            out.close();
        }
        else
        {
            assert(false);
        }
    }
};

class ImportSqlQueriesFixture : public Test
{
public:
    ImportSqlQueries *importer;
    FileBuilder builder;

private:
    void SetUp() override
    {
        importer = new ImportSqlQueries();
    }

    void TearDown() override
    {
        delete importer;
    }
};

TEST_F(ImportSqlQueriesFixture, EmptyFile)
{
    builder.genEmptyFile(FILE_NAME);

    importer->setConfigFile(FILE_NAME);
    auto res = importer->getList();

    ASSERT_EQ(res.size(), 0);
}

TEST_F(ImportSqlQueriesFixture, InvalidFile)
{
    importer->setConfigFile("someFile");
    auto res = importer->getList();

    ASSERT_EQ(res.size(), 0);
}

TEST_F(ImportSqlQueriesFixture, CorrectFile)
{
    int num_recods = 10;
    builder.genCorrectFile(FILE_NAME, num_recods);

    importer->setConfigFile(FILE_NAME);
    auto res = importer->getList();

    ASSERT_EQ(res.size(), num_recods);
}
