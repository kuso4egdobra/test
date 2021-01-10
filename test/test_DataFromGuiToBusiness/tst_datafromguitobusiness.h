#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include <QDebug>
#include <QApplication>

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"

using namespace testing;

class UiDataBuilder
{
    QString lineData;
    QString comboData;
    QTime timeData;
    enum Qt::CheckState stateCheckBox;
    int spinBoxData;
    int curIndexCombo;
    int numDocs = 8;

public:
    UiDataBuilder()
    {
        lineData = "";
        comboData = "";
        timeData = QTime(0, 0, 0);
        stateCheckBox = Qt::CheckState::Checked;
        spinBoxData = 1;
        curIndexCombo = 0;
    }

    void setCurIndex(int index)
    {
        if (index >=0 && index < numDocs)
            curIndexCombo = index;
    }

    void Build(QLineEdit** line, QDateTimeEdit** time, QComboBox** combo,
               QSpinBox** spin, QTableWidget** table, QCheckBox** checkBox)
    {
        int argc = 0;
        QApplication a(argc, nullptr);

        *line = new QLineEdit;
        (*line)->insert(lineData);

        *combo = new QComboBox;
        for (int i = 0; i < numDocs; i++)
            (*combo)->insertItem(i, comboData);
        (*combo)->setCurrentIndex(curIndexCombo);

        *table = new QTableWidget;

        *time = new QDateTimeEdit;
        (*time)->setTime(timeData);

        *checkBox = new QCheckBox;
        (*checkBox)->setCheckState(stateCheckBox);

        *spin = new QSpinBox;
        (*spin)->setValue(spinBoxData);
    }
};

class MockBusiness : public BusinessLogic
{
public:
    virtual ~MockBusiness() { }

    MOCK_METHOD(
            bool,
            addNewDoc,
            (BaseDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (BirthDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (DeathDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (MarriageDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (WorkDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (StudyDoc&),
            (override)
    );

    MOCK_METHOD(
            bool,
            addNewDoc,
            (ResidenceDoc&),
            (override)
    );
};

class DataFromGuiToBusinessFixture : public Test
{
public:
    DataFromGuiToBusiness *sender;
    MockBusiness *mockBusiness;
    UiDataBuilder uiDataBuilder;

    QLineEdit* line;
    QDateTimeEdit* time;
    QComboBox* combo;
    QSpinBox* spin;
    QTableWidget* table;
    QCheckBox* checkBox;

private:
    void SetUp() override
    {
        mockBusiness = new MockBusiness;
        sender = new DataFromGuiToBusiness(mockBusiness);
    }

    void TearDown() override
    {
        delete sender;
        delete mockBusiness;

        delete line;
        delete time;
        delete combo;
        delete spin;
        delete table;
        delete checkBox;

//        line = nullptr;
//        time = nullptr;
//        combo = nullptr;
//        spin = nullptr;
//        table = nullptr;
//        checkBox = nullptr;
    }
};

TEST_F(DataFromGuiToBusinessFixture, AddBaseDoc)
{
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<BaseDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddBirthDoc)
{
    uiDataBuilder.setCurIndex(1);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<BirthDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddDeathDoc)
{
    uiDataBuilder.setCurIndex(2);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<DeathDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddMarriageDocStart)
{
    uiDataBuilder.setCurIndex(3);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<MarriageDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddMarriageDocEnd)
{
    uiDataBuilder.setCurIndex(4);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<MarriageDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddWorkDoc)
{
    uiDataBuilder.setCurIndex(5);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<WorkDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddStudyDoc)
{
    uiDataBuilder.setCurIndex(6);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<StudyDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}

TEST_F(DataFromGuiToBusinessFixture, AddResidenceDoc)
{
    uiDataBuilder.setCurIndex(7);
    uiDataBuilder.Build(&line, &time, &combo, &spin, &table, &checkBox);

    EXPECT_CALL(*mockBusiness, addNewDoc(Matcher<ResidenceDoc&>(_)))
            .Times(AtLeast(1))
            .WillOnce(Return(true));

    bool res = sender->sendDataNewDoc(table, line, time, line, checkBox, time, time, combo, time, spin,
                           line, combo, line, spin, spin, line, line, line, combo, line, line,
                           time, spin, time, line, line, time, time, line, line, spin, line, line,
                           time, line, time, line, time, line, time, combo, line, line, line, spin,
                           spin, spin, spin, combo, combo);

    ASSERT_THAT(res, true);
}
