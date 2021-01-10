#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include <QDebug>

#include "BusinessLogic/businesslogic.h"

using namespace testing;

class MockAccess : public AccessToDB
{
public:
    virtual ~MockAccess() {}

    MOCK_METHOD(
            int,
            insert,
            (MyQSqlQuery &query),
            (override)
    );

    MOCK_METHOD(
            void,
            run,
            (MyQSqlQuery &query),
            (override)
    );
};

class MockSqlAccessDataUtil : public SqlAccessDataUtil
{
public:
    virtual ~MockSqlAccessDataUtil() {}
    MockSqlAccessDataUtil(AccessToDB* access) : SqlAccessDataUtil(access) { }

    MOCK_METHOD(
            bool,
            commit,
            (),
            (override)
    );
};

class IntegrationBusinessToDB : public Test
{
public:
    MockAccess *mockAccess;
    MockSqlAccessDataUtil *mockSqlAccessDataUtil;
    BusinessLogic *business;

private:
    void SetUp() override
    {
        mockAccess = new MockAccess;
        mockSqlAccessDataUtil = new MockSqlAccessDataUtil(mockAccess);
        business = new BusinessLogic(mockSqlAccessDataUtil);
    }

    void TearDown() override
    {
        delete business;
        delete mockAccess;
    }
};

TEST_F(IntegrationBusinessToDB, insertBaseDoc)
{
    BaseDoc doc;

    EXPECT_CALL(*mockAccess, insert(_))
            .Times(AtLeast(1))
            .WillRepeatedly(Return(0));

    EXPECT_CALL(*mockSqlAccessDataUtil, commit())
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));

    bool res = business->addNewDoc(doc);

    ASSERT_EQ(res, true);
}

TEST_F(IntegrationBusinessToDB, runQuery)
{
    EXPECT_CALL(*mockAccess, run(_))
            .Times(AtLeast(1));

    EXPECT_CALL(*mockSqlAccessDataUtil, commit())
            .Times(AtLeast(1))
            .WillRepeatedly(Return(true));

    QSqlQueryModel *res = business->run("query", false);

    ASSERT_TRUE(res);
}
