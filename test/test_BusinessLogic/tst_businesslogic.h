#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include "BusinessLogic/businesslogic.h"

using namespace testing;

class MockBusiness : public SqlAccessDataUtil
{
public:
    virtual ~MockBusiness() { }

    MOCK_METHOD(
            bool,
            transaction,
            (),
            (override)
    );

    MOCK_METHOD(
            bool,
            commit,
            (),
            (override)
    );

    MOCK_METHOD(
            bool,
            rollback,
            (),
            (override)
    );

    MOCK_METHOD(
            int,
            insert,
            (const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue),
            (override)
    );

    MOCK_METHOD(
            int,
            update,
            (const QString &tableName, int idUpdate, const QStringList &atributesName,
             const QStringList &atributesValue),
            (override)
    );
};

class BusinessLogicFixture : public Test
{
public:
    BusinessLogic *business;
    MockBusiness *mockBusiness;

private:
    void SetUp() override
    {
        mockBusiness = new MockBusiness;
        business = new BusinessLogic(mockBusiness);
    }

    void TearDown() override
    {
        delete business;
    }
};

TEST_F(BusinessLogicFixture, ErrorCommit)
{
    EXPECT_CALL(*mockBusiness, transaction())
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    EXPECT_CALL(*mockBusiness, insert(_, _, _))
            .Times(AtLeast(1))
            .WillOnce(Return(1));

    EXPECT_CALL(*mockBusiness, commit())
            .Times(AtLeast(1))
            .WillOnce(Return(false));

    EXPECT_CALL(*mockBusiness, rollback())
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    BaseDoc doc;
    bool res = business->addNewDoc(doc);

    ASSERT_EQ(res, false);
}

TEST_F(BusinessLogicFixture, ErrorTransaction)
{
    EXPECT_CALL(*mockBusiness, transaction())
            .Times(AtLeast(1))
            .WillOnce(Return(false));

    EXPECT_CALL(*mockBusiness, rollback())
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    BaseDoc doc;
    bool res = business->addNewDoc(doc);

    ASSERT_EQ(res, false);
}

TEST_F(BusinessLogicFixture, SuccessfulTransact)
{
    EXPECT_CALL(*mockBusiness, transaction())
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    EXPECT_CALL(*mockBusiness, insert(_, _, _))
            .Times(AtLeast(1))
            .WillOnce(Return(1));

    EXPECT_CALL(*mockBusiness, commit())
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    BaseDoc doc;
    bool res = business->addNewDoc(doc);

    ASSERT_EQ(res, true);
}
