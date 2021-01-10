#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include <QString>
#include <QDebug>

#include "AccessData/AccessDataUtil/sqlaccessdatautil.h"

using namespace testing;

class MockConnection : public Connection
{
public:
    MOCK_METHOD(
            QSqlDatabase*,
            getConnection,
            (),
            (override)
    );
};

class SqlAccessDataUtilFixture : public Test
{
public:
    SqlAccessDataUtil *util;
    MockConnection *mockConnection;

private:
    void SetUp() override
    {
        util = new SqlAccessDataUtil();
        mockConnection = new MockConnection();

        util->setConnection(mockConnection);
        EXPECT_CALL(*mockConnection, getConnection())
                .Times(AtLeast(1))
                .WillOnce(Return(nullptr));
    }

    void TearDown() override
    {
        delete util;
    }
};

TEST_F(SqlAccessDataUtilFixture, InsertNoConnection)
{
    int res = util->insert("person", QStringList(), QStringList());

    ASSERT_EQ(res, -1);
}

TEST_F(SqlAccessDataUtilFixture, UpdateNoConnection)
{
    int res = util->update("person", 0, QStringList(), QStringList());

    ASSERT_EQ(res, -1);
}

TEST_F(SqlAccessDataUtilFixture, GetSamePeopleNoConnection)
{
    QStringList res = util->getSamePeople("", 0, "", "");

    ASSERT_EQ(res.size(), 0);
}

TEST(SqlAccessDataUtil, InsertInvalidTableName)
{
    SqlAccessDataUtil *util = new SqlAccessDataUtil();

    int res = util->insert("", QStringList(), QStringList());

    ASSERT_EQ(res, -1);
}
