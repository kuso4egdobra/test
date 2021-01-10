#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include <QSqlQuery>
#include <QSqlField>
#include <QDebug>

#include <AccessData/accesstodb.h>
#include "MyClasses/myqsqlquery.h"

using namespace testing;

class MockQuery : public MyQSqlQuery
{
public:
    virtual ~MockQuery() {}

    MOCK_METHOD(
            bool,
            my_exec,
            (),
            (override)
    );

    MOCK_METHOD(
            bool,
            my_next,
            (),
            (override)
    );

    MOCK_METHOD(
            QSqlRecord,
            my_record,
            (),
            (const, override)
    );
};

class AccessToDBFixture : public Test
{
public:
    AccessToDB *access;
    MockQuery *mockQuery;
    QSqlRecord record;
    int waiting_val = 12345;

    AccessToDBFixture()
    {
        QSqlField field("tableName", QVariant::Int, "fieldName");
        field.setValue(waiting_val);
        record.append(field);
    }

private:
    void SetUp() override
    {
        access = new AccessToDB();
        mockQuery = new MockQuery();
    }

    void TearDown() override
    {
        delete access;
        delete mockQuery;
    }
};

TEST_F(AccessToDBFixture, run)
{
    EXPECT_CALL(*mockQuery, my_exec())
            .Times(AtLeast(1))
            .WillOnce(Return(1));

    access->run(*mockQuery);
}

TEST_F(AccessToDBFixture, insert)
{
    EXPECT_CALL(*mockQuery, my_exec())
            .Times(AtLeast(1))
            .WillOnce(Return(1));

    EXPECT_CALL(*mockQuery, my_next())
            .Times(AtLeast(1))
            .WillOnce(Return(1));

    EXPECT_CALL(*mockQuery, my_record())
            .Times(AtLeast(1))
            .WillOnce(Return(record));

    int res = access->insert(*mockQuery);

    ASSERT_EQ(res, waiting_val);
}

TEST_F(AccessToDBFixture, update)
{
    EXPECT_CALL(*mockQuery, my_exec())
            .Times(AtLeast(1))
            .WillOnce(Return(0));

    access->update(*mockQuery);
}
