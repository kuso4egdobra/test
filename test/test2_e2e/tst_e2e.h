#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <fstream>

#include "UI/mainwindow.h"
#include "UI/newdocumentwindow.h"

#define NAME_SQL "Кол-во людей в БД"
#define SQL_NUM_REC_PERSON "select count(*) from person;"
#define FILE_NAME "./file_e2e_test.txt"

using namespace testing;

class e2eFixture : public Test
{
public:
    MainWindow w;
    NewDocumentWindow *docWindow;
    AdminWindow *adminWindow;
    StatisticsWindow *statWindow;

private:
    void SetUpNewBaseDoc()
    {
        QCheckBox *checkBox_personInDB = docWindow->checkBox_personInDB;
        checkBox_personInDB->setCheckState(Qt::CheckState::Checked);

        QLineEdit *lineEdit_surname = docWindow->lineEdit_surname;
        lineEdit_surname->setText("Surname");

        QLineEdit *lineEdit_name = docWindow->lineEdit_name;
        lineEdit_name->setText("Name");

        QLineEdit *lineEdit_patronymic = docWindow->lineEdit_patronymic;
        lineEdit_patronymic->setText("Patronymic");

        QSpinBox *spinBox_numDoc = docWindow->spinBox_numDoc;
        spinBox_numDoc->setValue(1);

        QSpinBox *spinBox_version = docWindow->spinBox_version;
        spinBox_version->setValue(1);

        QLineEdit *lineEdit_authority = docWindow->lineEdit_authority;
        lineEdit_authority->setText("Moscow");
    }

    void SetUpAdminWindow()
    {
        QTextEdit *textEdit_sqlEntry = adminWindow->textEdit_sqlEntry;
        textEdit_sqlEntry->setText(SQL_NUM_REC_PERSON);
    }

    void SetUpStatWindow()
    {
        std::ofstream out;
        out.open(FILE_NAME);
        if (out.is_open())
        {
            out << NAME_SQL << "\n" << SQL_NUM_REC_PERSON << "\n";
            out.close();
        }
        else
        {
            assert(false);
        }
    }

    void SetUp() override
    {
        w.show();
        w.on_BtnNewDoc_clicked();
        docWindow = w.getNewDocumentWindow();
        adminWindow = w.getAdminWindow();
        statWindow = w.getStatisticsWindow();

        SetUpNewBaseDoc();
        SetUpAdminWindow();
        SetUpStatWindow();
    }

    void TearDown() override
    {

    }
};

TEST_F(e2eFixture, demoCourse)
{
    // AdminWidow
    docWindow->close();
    w.on_Btn_admin_clicked();

    int num_row_start = adminWindow->on_BtnOk_clicked();

    adminWindow->close();

    // Add new BaseDoc
    bool res = docWindow->on_BtnOk_clicked();

    ASSERT_EQ(res, true);

    // AdminWidow
    docWindow->close();
    w.on_Btn_admin_clicked();

    int num_row_end = adminWindow->on_BtnOk_clicked();

    ASSERT_EQ(num_row_start + 1, num_row_end);

    adminWindow->close();

    // StatWindow
    w.on_Btn_stat_clicked();
    statWindow->importFile(FILE_NAME);
    int statRes = statWindow->on_BtnOk_clicked();

    ASSERT_EQ(statRes, num_row_end);
}
