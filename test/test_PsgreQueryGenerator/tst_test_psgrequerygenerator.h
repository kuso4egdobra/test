#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QStringList>
#include <QDebug>

#include "AccessData/QueryGenerator/psgrequerygenerator.h"

using namespace testing;

class PsgreQueryGeneratorFixture : public Test
{
public:
    PsgreQueryGenerator *gen;

private:
    void SetUp() override
    {
        gen = new PsgreQueryGenerator();
    }

    void TearDown() override
    {
        delete gen;
    }
};

TEST_F(PsgreQueryGeneratorFixture, insert)
{
    QString tableName = "table";
    QStringList atributesName({"Name1", "Name2"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "INSERT INTO table (Name1, Name2) VALUES (Value1, Value2) RETURNING id;";

    QString res_str = gen->insert(tableName, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, insertEmptyTableName)
{
    QString tableName = "";
    QStringList atributesName({"Name1", "Name2"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "";

    QString res_str = gen->insert(tableName, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, insertEmptyAtributes)
{
    QString tableName = "table";
    QStringList atributesName({});
    QStringList atributesValue({});
    QString waiting_res = "";

    QString res_str = gen->insert(tableName, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, insertNESizeAtributes)
{
    QString tableName = "table";
    QStringList atributesName({"Name1"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "";

    QString res_str = gen->insert(tableName, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, update)
{
    QString tableName = "table";
    int id = 0;
    QStringList atributesName({"Name1", "Name2"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "UPDATE table SET (Name1, Name2) = (Value1, Value2) WHERE id = 0;";

    QString res_str = gen->update(tableName, id, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, updateEmptyTableName)
{
    QString tableName = "";
    int id = 0;
    QStringList atributesName({"Name1", "Name2"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "";

    QString res_str = gen->update(tableName, id, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, updateEmptyAtributes)
{
    QString tableName = "table";
    int id = 0;
    QStringList atributesName({});
    QStringList atributesValue({});
    QString waiting_res = "";

    QString res_str = gen->update(tableName, id, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}

TEST_F(PsgreQueryGeneratorFixture, updateNESizeAtributes)
{
    QString tableName = "table";
    int id = 0;
    QStringList atributesName({"Name1"});
    QStringList atributesValue({"Value1", "Value2"});
    QString waiting_res = "";

    QString res_str = gen->update(tableName, id, atributesName, atributesValue);

    EXPECT_STREQ(res_str.toStdString().c_str(), waiting_res.toStdString().c_str());
}
