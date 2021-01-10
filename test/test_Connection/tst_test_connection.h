#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include "AccessData/connection.h"
#include "MyClasses/myqsqldatabase.h"

using namespace testing;

class MockDataBase : public MyQSqlDatabase
{
public:
    virtual ~MockDataBase() { }

    MOCK_METHOD(
            bool,
            my_is_open,
            (),
            (override)
    );
};

class ConnectionFixture : public Test
{
public:
    Connection *connection;
    MockDataBase *mockDB;

private:
    void SetUp() override
    {
        connection = new Connection(false);
        mockDB = new MockDataBase;
        connection->setDB(mockDB);
    }

    void TearDown() override
    {
        delete connection;
        delete mockDB;
    }
};

TEST_F(ConnectionFixture, connectionFalse)
{
    EXPECT_CALL(*mockDB, my_is_open())
            .Times(AtLeast(1))
            .WillRepeatedly(Return(false));

    QSqlDatabase *db = connection->getConnection();

    ASSERT_EQ(db, nullptr);
}

TEST_F(ConnectionFixture, connectionInterrupted)
{
    EXPECT_CALL(*mockDB, my_is_open())
            .Times(AtLeast(1))
            .WillOnce(Return(true))
            .WillOnce(Return(false));

    QSqlDatabase *db = connection->getConnection();

    ASSERT_EQ(db, nullptr);
}

TEST_F(ConnectionFixture, connectionSuccess)
{
    EXPECT_CALL(*mockDB, my_is_open())
            .Times(AtLeast(1))
            .WillOnce(Return(true))
            .WillOnce(Return(true));

    QSqlDatabase *db = connection->getConnection();

    ASSERT_TRUE(db);
}
